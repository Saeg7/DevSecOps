<div align="center">

# 🛡️ Socket Keeper

**Высокопроизводительное Go-приложение для управления сетевыми сокетами и DevSecOps-практиками.**

[![Go Version](https://img.shields.io/badge/Go-1.22%2B-00ADD8?style=flat-square&logo=go)](https://golang.org/)
[![License](https://img.shields.io/badge/license-MIT-blue.style=flat-square)](#license)
[![DevSecOps](https://img.shields.io/badge/Security-DevSecOps-brightgreen?style=flat-square)](https://github.com/Saeg7/DevSecOps)

[Описание](#-описание) • [Особенности](#-особенности) • [Стек технологий](#-стек-технологий) • [Быстрый старт](#-быстрый-старт) • [Структура](#-структура-проекта)

</div>

---

## 📝 Описание

**Socket Keeper** — это проект в рамках практики DevSecOps, предназначенный для надёжного мониторинга, управления и защиты сетевых подключений по протоколам WebSockets / TCP.

Проект разработан с акцентом на безопасную обработку соединений, минимальное потребление ресурсов и соблюдение лучших стандартов контейнеризации и CI/CD.

---

## ✨ Особенности

- ⚡ **Высокая производительность:** Написан на Go с использованием асинхронной обработки горутин.
- 🔒 **Безопасность (DevSecOps):** Встроенные проверки уязвимостей, безопасная работа с окружением и изолированные контейнеры.
- 🐳 **Docker-ready:** Полностью подготовлен к запуску в контейнерах.
- 📊 **Мониторинг:** Логирование и отслеживание статуса активных подключений.

---

## 🛠 Стек технологий

| Категория | Технологии |
| :--- | :--- |
| **Язык программирования** | Go (Golang) |
| **Контейнеризация** | Docker, Docker Compose |
| **Безопасность & CI/CD** | DevSecOps Pipelines, Static Analysis (SAST) |
| **ОС / Окружение** | Linux (Ubuntu), Bash |

---

## 🚀 Быстрый старт

### Требования

Убедитесь, что у вас установлены:
* [Go](https://golang.org/doc/install) (версия 1.20+)
* [Git](https://git-scm.com/)
* [Docker](https://docs.docker.com/get-docker/) *(опционально)*

### Локальный запуск

1. **Клонируйте репозиторий:**
   ```bash
   git clone [https://github.com/Saeg7/DevSecOps.git](https://github.com/Saeg7/DevSecOps.git)
   cd DevSecOps/01-socket-keeper/Socket-Keeper