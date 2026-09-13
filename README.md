# ReducedVM
A simple emulated CPU with custom RISC architecture and assembler parser in C.

This project was originally developed for the **Croatian national science competition in software development** (*Natjecanje iz informatike - Razvoj softvera*) and **INOVA Zagreb 2027**

## Features
 - A custom emulated CPU
 - Custom RISC architecture (RISC_RVM) with 17 unique instructions
 - Assembler parser (see **DOCUMENTATION.txt** for usage)

## Usage
See **DOCUMENTATION.txt**

## Running
### Prerequisites
 - C Compiler with CMake support (GCC, Clang, MSVC...)
 - CMake 3.15.0+

### Compiling and running
Follow these steps to build and run the project locally using CMake:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/vuzul/ReducedVm.git
   cd ReducedVM
   ```

2. **Generate the build system and compile:**
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

3. **Run the executable:**
   ```bash
   ./RVM.exe
   ```
   (Windows)
   or
   ```bash
   ./RVM
   ```
   (Mac/Linux)

## License
This project is licensed under the MIT license, meaning any usage, modification, and publication is permitted, as long as the original creator (*vuzul*) is credited.
