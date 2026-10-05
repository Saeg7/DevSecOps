#!/usr/bin/env bash
set -euo pipefail

if [[ $EUID -ne 0 ]]; then
   echo "[ERROR] Этот скрипт должен исполняться с правами root (sudo)." >&2
   exit 1
fi

# Автоматическое определение путей проекта
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
LOG_FILE="$SCRIPT_DIR/socket_keeper.log"
REAL_USER="${SUDO_USER:-$USER}"

echo "=== [1/3] Настройка сетевого экрана UFW ==="
ufw --force reset
ufw default deny incoming
ufw default allow outgoing
ufw allow 22/tcp comment 'SSH Protocol'
ufw allow 8080/tcp comment 'Socket Keeper C++ HTTP Server'
ufw --force enable

echo "=== [2/3] Настройка службы Fail2Ban ==="
cat <<'INNER_EOF' > /etc/fail2ban/filter.d/socket-keeper.conf
[Definition]
failregex = ^\[REQUEST\] Incoming connection from: <HOST>$
ignoreregex =
INNER_EOF

# Подготовка лог-файла
touch "$LOG_FILE"
chmod 666 "$LOG_FILE"

cat <<INNER_EOF > /etc/fail2ban/jail.d/socket-keeper.conf
[sshd]
enabled = true

[socket-keeper-ratelimit]
enabled  = true
port     = 8080
filter   = socket-keeper
logpath  = ${LOG_FILE}
maxretry = 10
findtime = 10s
bantime  = 10m
INNER_EOF

systemctl restart fail2ban
systemctl enable fail2ban

echo "=== [3/3] Сборка CMake и безопасный запуск ==="
# Переходим в корень и собираем проект
cd "$PROJECT_ROOT"
mkdir -p build
cd build
cmake ..
make

# Возвращаем права на собранные файлы обычному пользователю
chown -R "$REAL_USER:$REAL_USER" "$PROJECT_ROOT/build"

echo "=== [SUCCESS] Запуск сервера от пользователя $REAL_USER ==="
# Запускаем из корня проекта от обычного пользователя (не root!), чтобы не было 404
cd "$PROJECT_ROOT"
exec su - "$REAL_USER" -c "cd '$PROJECT_ROOT' && ./build/socket_keeper | tee -a '$LOG_FILE'"