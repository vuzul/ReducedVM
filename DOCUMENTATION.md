## Using system:
 - Write an "asm.rasm" file in local root
 - Configure CMake (only needs to be done once)
 - Run cmake --build build in local root (only need to be done once after each update)
 - Run ./build/RVM.exe (Windows) or ./build/RVM (Mac/Linux) in local root
## Simple syntax:
 - Comments start with slash
 - `(X) INST Y Z (J)`:
Calculates INST with Y anc Z as arguments, (optional) writes result to register defined in X, (optional) jumps if the result is not 0
 - `SJT X`:
Sets jump target (instruction to jump to with J) to value in register X
## Register outline:
### R/W registers:
 - General purpose registers are A, B and C
 - A is RAM address to read from / write to
 - R is value stored in RAM at address stored in A
 - S is the stack pointer, currently unused
 - M is currently unused, refrain from using it as a GP register as it will have a use in the future
### Read only registers:
 - 0 stores, well, 0
 - 1 stores 1
 - X stores -1 (important for bitmasks)
### I register
 - Stores number from next instruction 
 - EG. `A ADD I 0` in line 1 and `42` in line 2 sets A to 42
##Example
```
B ADD I 0
7
C ADD I 0
7
SJT C
D ADD 0 0
D ADD D B
B SUB B 1 J
END
```
 - `B ADD I 0` Adds number from next instruction to B
 - `7` Defines number contained in I from previous instruction as 7
 - `C ADD I 0`, `7` do the same thing to C
 - `SJT C` sets the target for jumps to value contained in C register (line 7)
 - `D ADD 0 0` sets D to the sum of 0 and 0
 - `D ADD D B` adds B to the value of D
 - `B SUB B 1 J` subtracts 1 from B, and jumps to target defined in SJT (7) if the result is not 0
 - `END` marks the end of the program
## Notes
NOTE: Every program MUST end with `END`