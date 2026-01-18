# Build Guide — Quick Reference

Rayka build guide. Features all available cmake options designed to allow customizability on how to build the Rayka library.

> Note: Build guide is a work in progress. Options are expected to change and evolve during projects initial development
> 
## Options (names, defaults, short meaning)

- `RAYKA_BUILD_SHARED` - default: `ON`  
  Build shared libraries for all components (runtime artifacts)

- `RAYKA_BUILD_STATIC` - default `OFF`  
  Build static libraries for all components (development artifcats)

- `RAYKA_BUILD_EXAMPLES` — default: `${RAYKA_STANDALONE}`  
  Build example programs (per-backend example executables).

- `RAYKA_BUILD_TESTS` — default: `${RAYKA_STANDALONE}`  
  Placeholder option to enable tests once implemented. 

- `RAYKA_BUILD_DOCS` — default: `ON`  
  Placeholder option to enable documentation generation once implemented.

- `RAYKA_INSTALL` — default: `ON`  
  Enable `install()` rules and CMake package export.

- `RAYKA_PACKAGING` — default: `OFF`  
  Enable CPack packaging generation (ZIP, NSIS, TGZ depending on platform).

- `RAYKA_BACKEND_CUDA` — default: `OFF`  
  Enable the CUDA backend library.

- `RAYKA_BACKEND_OPENGL` — default: `OFF`  
  Enable the OpenGL backend library.

- `RAYKA_BACKEND_VULKAN` — default: `OFF`  
  Enable the Vulkan backend library.



---

## Minimal build (core only)

```bash
cmake -S . -B build \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release
cmake --install build --prefix ./install
```

---

## Full example: build everything

This example enables examples, tests, docs, installation, packaging, and all backends,
and builds shared libraries explicitly.

```bash
cmake -S . -B build-full \
  -DRAYKA_BUILD_SHARED=ON \
  -DRAYKA_BUILD_STATIC=ON \
  -DCMAKE_BUILD_TYPE=Release \
  -DRAYKA_BUILD_EXAMPLES=ON \
  -DRAYKA_BUILD_TESTS=ON \
  -DRAYKA_BUILD_DOCS=ON \
  -DRAYKA_INSTALL=ON \
  -DRAYKA_PACKAGING=ON \
  -DRAYKA_BACKEND_CUDA=ON \
  -DRAYKA_BACKEND_OPENGL=ON \
  -DRAYKA_BACKEND_VULKAN=ON \

cmake --build build-full --config Release
cmake --install build-full --prefix ./install-full

# Generate packages (if RAYKA_PACKAGING=ON)
cpack --config build-full/CPackConfig.cmake
```

