# WebServer


A lightweight, modular web server built in **C++** for learning and experimentation. This project is designed to deepen understanding of networking, HTTP protocols, and server design, while allowing future extensions in **Python** or **Go**.

## 🚀 Features

- HTTP 1.1 compliant server
- Basic routing (GET, POST)
- Static file serving
- Minimal dependency usage
- Extensible architecture

## 📦 Tech Stack

- **Language:** C++
- **Libraries:** Asio / Boost.Beast / cpp-httplib / custom socket handling
- **Optional (Future):** Python (Flask), Go (Gin/Fiber)

## 📁 Project Structure

```
--buffer
--thread pool
--http
--webserver
```




This is an example project using CMake.

The requirements are:

* CMake 3.11 or better; 3.14+ highly recommended.
* A C++17 compatible compiler
* The Boost libararies (header only part is fine)
* Git
* Doxygen (optional)

To configure:

```bash
cmake -S . -B build
```

Add `-GNinja` if you have Ninja.

To build:

```bash
cmake --build build
```

To test (`--target` can be written as `-t` in CMake 3.15+):

```bash
cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

To use an IDE, such as Xcode:

```bash
cmake -S . -B xbuild -GXcode
cmake --open xbuild
```

The CMakeLists show off several useful design patters for CMake.
