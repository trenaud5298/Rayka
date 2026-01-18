# Rayka

> A modular rendering library focused on path tracing.  
> High-level scene abstractions with interchangeable CPU and GPU backends.

[![build status](https://img.shields.io/badge/build-unknown-lightgrey)](#)
[![license](https://img.shields.io/badge/license-BSD--3--Clause-blue)](LICENSE)
[![docs](https://img.shields.io/badge/docs-coming--soon-lightgrey)](#)
![version](https://img.shields.io/github/v/release/trenaud5298/Rayka)
![platforms](https://img.shields.io/badge/platform-linux%20|%20windows%20|%20macos-blue)

---

## Overview

**Rayka** is a path traced rendering library focused on delivering a high level abstraction away from the actual rendering complexity instead focused on designing and constructing scenes and animations.

The core goal of Rayka is to allow users to render complex scenes without needing to directly manage low-level rendering or GPU APIs, while still providing extensibility and performance through modular backend implementations.

Rayka is structured as a set of independent libraries:

- A **core library** providing scene representation, materials, animations, and baseline CPU renderers.
- Optional **GPU backend libraries** that add hardware-accelerated renderers using CUDA, OpenGL, or Vulkan.

Each backend is enabled or disabled at build time and distributed as a CMake component for consumption after installation.

> **Current status:**  
> Rayka is in an early development stage. The project currently focuses on `Rayka::Core` and the `Rayka::CUDA` backend. OpenGL and Vulkan backends are planned but not yet implemented.  
> The CMake structure and component setup are in place, with minimal test code.

---

## Table of Contents

- [Architecture](#architecture)
- [Modules](#modules)
- [Features](#features)
- [Quick Start](#quick-start)
- [Build Configuration](#build-configuration)
- [Examples](#examples)
- [Documentation](#documentation)
- [Roadmap](#roadmap)
- [Platforms & Dependencies](#platforms--dependencies)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)
- [Contact](#contact)

---

## Architecture

Rayka follows a **modular, layered design**:

- `Rayka::Core` defines the public API for scenes, materials, animations, and renderers.
- Backend modules implement renderer variants that operate on the core abstractions.
- Backend libraries link against `Rayka::Core` and do not duplicate scene logic.
- Users select which backends are available at build time. (Runtime selection is planned as a potential feature)

This structure allows:
- CPU-only builds
- GPU-accelerated builds
- Future expansion to additional rendering backends

---

## Modules

### Core Library

**`Rayka::Core`**

Provides:
- Scene API
- Ability to generate meshes and primitive geometric shapes
- Material abstraction including smoothness, transparency, and color either primitively or through textures
- Animation API
- Renderer API
- Simple CPU-side renderer implementations

This module is always available and required by all backends.

---

### GPU Backends

Each backend adds new renderer implementations using a specific graphics or compute API.

- **`Rayka::CUDA`**  
  CUDA-based GPU path tracing backend (in active development)

- **`Rayka::OpenGL`**  
  OpenGL-based backend (planned)

- **`Rayka::Vulkan`**  
  Vulkan-based backend (planned)

Each backend:
- Is built as a separate library
- Can be enabled or disabled at build time
- Is exported as a CMake component target

---

## Features

### Present / Planned Features

- High-level scene abstraction
- Path tracing–focused renderer design
- Modular renderer class hierarchy
- CPU reference implementations
- GPU-accelerated renderers (backend-dependent)
- Animation systems
- CMake component-based installation
- Optional example executables per backend

> Feature list will be expanded with detailed features as development progresses.

---

## Quick Start

> The below outlines an example on how to quickly build and install Rayka with the CUDA backend module

```bash
git clone https://github.com/trenaud5298/Rayka.git Rayka
cd Rayka

cmake -S . -B ./build -DRAYKA_BACKEND_CUDA=ON

cmake --build ./build
cmake --install ./build
```

---


## Build Configuration

> Documentation for build instructions will be light during initial development stage as options are expected to change.
> 
Detailed build instructions, CMake options, and backend requirements are documented separately:

- `docs/build.md` — build options, dependencies, and configuration

Current configuration options include:
- Enabling/disabling shared and static library targets
- Enabling/disabling individual backends
- Enabling/disabling example executables
- Installation and CMake package export

---

## Examples

Rayka provides example executables demonstrating usage of each library target:

- Core-only example (`Rayka::Core`)
- CUDA backend example (`Rayka::CUDA`)
- OpenGL example (planned)
- Vulkan example (planned)

Examples can be enabled or disabled at build time.

---

## Documentation

Detailed documentation will live under the `docs/` directory:

- `docs/build.md` — build and configuration guide
- More planned

---

## Roadmap

High-level project goals:

- [x] CMake project and component structure
- [ ] Core library scaffolding
- [ ] CUDA backend scaffolding
- [ ] CPU path tracer implementation
- [ ] CUDA path tracer implementation
- [ ] OpenGL backend
- [ ] Vulkan backend
- [ ] Example scenes and render outputs
- [ ] CI and automated builds
- [ ] API documentation generation
- [ ] Performance benchmarks

---

## Platforms & Dependencies

> **TODO:**  
> This section will be expanded with exact versions and requirements.

Planned support:
- Linux, Windows, macOS
- Modern C++ (Planned for C++ 20)
- CUDA toolkit (for `Rayka::CUDA`)
- Vulkan SDK (for `Rayka::Vulkan`)
- OpenGL development headers (for `Rayka::OpenGL`)

---

## License

Rayka is licensed under the **BSD 3-Clause License**.  
See the `LICENSE` file for full details.

---

## Acknowledgements

Rayka may optionally interface with or depend on external technologies such as:
- CUDA
- OpenGL
- Vulkan

These technologies are used according to their respective licenses.  
Third-party code that is redistributed will be acknowledged as required.

---

## Contact

**Author:** Tyler Renaud  
**Email:** trenaud_5298@email.ric.edu  
**Project:** Rayka  
**Repository:** https://github.com/trenaud5298/Rayka
