# Poco + PostgreSQL Sample projects (for static mingw runtime error)

```bash
# 1.
mkdir build && cd build

# 2.
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=d:\projects\my\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-mingw-static -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# 3.
cmake --build . --config Debug

# 4. and run program
poco_postgres_example.exe
```

## result

![libpq.dll not found error window](https://github.com/SeanTolstoyevski/vcpkg-mingw-libpq-bug-reproducer/blob/main/resource/bug.png?raw=true)

## after patch

![success terminal screen](https://github.com/SeanTolstoyevski/vcpkg-mingw-libpq-bug-reproducer/blob/main/resource/after-patch.png?raw=true)