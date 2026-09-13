## Using system:
 - Write an "asm.rasm" file in local root
 - Configure CMake (only needs to be done once)
 - Run cmake --build build in local root (only need to be done once after each update)
 - Run ./build/RVM.exe (Windows) or ./build/RVM (Mac/Linux) in local root
## Simple syntax:
 - Comments start with slash
`(X) INST Y Z (J)`:
 - Calculates INST with Y anc Z as arguments, (optional) writes result to register defined in X, (optional) jumps if the result is not 0
`SJT X`:
 - Sets jump target (instruction to jump to with J) to value in register X
`X INP N`:
 - Inputs N (decimal number) to register X
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
## Notes
NOTE: Every program MUST end with "END" (without quotes)
NOTE 2: Every INP instruction counts as 2 instructions when calculating jumps. It is a good idea to put an empty comment after each INP instruction. There are no plans to fix this.