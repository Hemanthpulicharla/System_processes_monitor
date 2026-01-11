
# C++ System Monitor

<div align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/CMake-3.0%2B-green.svg" alt="CMake">
</div>

A sleek, terminal-based system monitor crafted in C++, providing a real-time glimpse into your Linux system's inner workings. Inspired by classic tools like `htop`, this project offers a lightweight and efficient way to track system resources.

![demo](https://i.imgur.com/YOUR_GIF_HERE.gif) 

---

## 🚀 About The Project

This system monitor is a C++ application that leverages the `ncurses` library to create a dynamic and responsive terminal interface. It reads directly from the `/proc` filesystem to gather and display live data about your system's performance.

It's a great example of C++ programming for system-level tasks, showcasing object-oriented design, file parsing, and terminal UI manipulation.

## Features

- **Live System Overview:**
  - **Operating System & Kernel:** Know your environment.
  - **CPU Utilization:** A dynamic progress bar shows real-time CPU load.
  - **Memory Usage:** Instantly see your memory consumption with a visual progress bar.
  - **System Uptime:** Track how long your system has been running.
- **Detailed Process Information:**
  - **Process Count:** View the total number of processes and how many are currently running.
  - **Process List:** A scrollable list of running processes, sorted by CPU usage.
  - **Per-Process Metrics:** For each process, view the PID, User, CPU%, RAM usage, and command.

## Built With

* **C++ (17):** For its performance and system-level capabilities.
* **CMake:** For cross-platform build management.
* **ncurses:** For creating the terminal-based user interface.

---

## Getting Started

Follow these steps to get a local copy up and running.

### Prerequisites

You'll need `g++`, `make`, `cmake`, and the `ncurses` development library installed.

- **On Debian/Ubuntu-based systems:**
  ```sh
  sudo apt-get update
  sudo apt-get install -y g++ make cmake libncurses5-dev libncursesw5-dev
  ```

### Build & Run

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/Hemanthpulicharla/System_processes_monitor.git
    cd System_process_monitor
    ```

2.  **Create a build directory:**
    ```sh
    mkdir build && cd build
    ```

3.  **Configure with CMake and build the project:**
    ```sh
    cmake ..
    make
    ```

4.  **Run the monitor:**
    The executable will be located in the `results` directory.
    ```sh
    ../results/monitor
    ```

## 📖 Usage

Simply run the compiled executable from your terminal. The display will refresh automatically every second.

- The top panel shows a summary of your system's status.
- The bottom panel lists the top processes consuming the most CPU.
- Press `Ctrl+C` to exit the application.

---

## 🙏 Acknowledgments

*   The developers of `htop` for the inspiration.
*   The `ncurses` library for enabling rich terminal interfaces.
*   Anyone whose code was used as a reference.

