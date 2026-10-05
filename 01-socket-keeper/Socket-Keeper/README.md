cat <<'EOF' > README.md
# 🛡️ Socket Keeper — Secure C++ POSIX Web Server

![C++17](https://img.shields.io/badge/C++-17-00599C?style=flat&logo=cplusplus)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-FCC624?style=flat&logo=linux)
![Security](https://img.shields.io/badge/Security-UFW%20%7C%20Fail2ban-red?style=flat)
![Build](https://img.shields.io/badge/Build-CMake-064F8C?style=flat&logo=cmake)

**Socket Keeper** is a lightweight, low-level HTTP web server written in C++17 using POSIX sockets. The project demonstrates core **DevSecOps principles** by pairing raw socket networking with automated host-based security hardening (UFW firewalling & Fail2ban rate-limiting).

---

## 🚀 Architectural Overview

* **Multithreaded Connection Handling:** Spawns decoupled threads (`std::thread`) per client request to ensure responsiveness under load.
* **POSIX Networking:** Built directly on system sockets (`sys/socket.h`, `arpa/inet.h`) without heavy third-party web frameworks.
* **Automated Security Hardening (`harden.sh`):**
  * **UFW Integration:** Sets a strict default-deny incoming policy, allowing only essential ports (`22/TCP` for SSH, `8080/TCP` for HTTP).
  * **Fail2ban Jail:** Parses server log streams (`socket_keeper.log`) using custom regex patterns to dynamically ban IP addresses exhibiting rapid-fire request behavior.
  * **Principle of Least Privilege:** Automates build and runtime execution so the binary runs strictly under non-root user privileges.

---

## 🛠️ Project Structure

```text
socket-keeper/
├── CMakeLists.txt        # Build system configuration
├── public/               # Static assets
│   └── index.html        # Served HTML page
├── scripts/
│   └── harden.sh         # Security hardening & build automation script
├── src/
│   └── main.cpp          # C++ HTTP server source code
└── README.md             # Project documentation