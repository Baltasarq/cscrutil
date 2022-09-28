# SCR Util c lib

Gestión de pantalla para la consola multiplataforma.
*Multiplatform screen console management*

Esta librería, programada en C, puede manejar las consolas tanto de Windows (utilizando las llamadas al sistema operativo), como de *nix (empleando las secuencias de control ANSI).
*This library, written in C, can manage both Windows and Linux consoles. It uses the system call for Windows, and the control escape sequences for Linux.

## Using this library
Just drop `scrutil.c` and `scrutil.h` it in the same directory of your program. Then you can add both files to the compile system of your IDE, or just modify the provided `Makefile` and type `make`.

## License
[MIT License](https://github.com/Baltasarq/cscrutil/blob/master/LICENSE "MIT License")
