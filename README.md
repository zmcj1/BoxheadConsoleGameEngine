# Console

[中文](https://github.com/OpenGreatDream/MinConsole/blob/main/docs/README.md)

free, portable and powerful Windows Console/Terminal low-level library.

## What is this?

This is a low-level Console Lib for Windows Console, you can use it to draw in the console, get user input etc.

The purpose is to develop upper-level softwares such as text editors, 3D renderer, music player, etc with this library :).

If you think this project has brought you help, please leave a star!🌟

If you want to contribute code, welcome submit a [pull request](https://github.com/OpenGreatDream/MinConsole/pulls)!👍

## Examples:

[MazeExample:](https://github.com/OpenGreatDream/MinConsole/blob/main/src/MinConsoleNativeExample/MazeExample.cpp)

<img src="https://github.com/OpenGreatDream/MinConsole/blob/main/docs/pics/MazeExample.gif" width = "375">

[ConFPSSample:](https://github.com/OpenGreatDream/MinConsole/blob/main/src/MinConsoleNativeExample/ConsoleFPSSample.cpp)

![ConFPSSample](https://github.com/OpenGreatDream/MinConsole/blob/main/docs/pics/ConFPSSample.gif)

## Architecture:

[MinConsole](https://github.com/OpenGreatDream/MinConsole/tree/main/src/MinConsole) is a C# wrapper, provide cross-platform interface.

[MinConsoleNative](https://github.com/OpenGreatDream/MinConsole/tree/main/src/MinConsoleNative) C++ interface of the Console APIs, the kernel of this project.

[MinConsoleNativeExample](https://github.com/OpenGreatDream/MinConsole/tree/main/src/MinConsoleNativeExample) is bunch of examples about how to use MinConsoleNative.

## Features:

1. CellRenderer/GridRenderer/NativeRenderer and GDIRenderer!

1. Navigation and Maze support!

1. Simple but powerful class Audio, and you can use AudioPool too!

1. Clipboard interface

1. powerful Console class (Package of Windows Console API)

1. Render RGB true color in the console(Break the limit of 16 colors!)

1. Database class for basic data reading and writing

1. EventSystem class! Support mouse wheel input, mouse coordinates(You can even use mouse in Windows Terminal!)

1. Nice Input class(Allows you to handle the mouse)

1. PaletteSystem!

1. High precision Timer class

1. VTConverter class helps you generate VT sequence without manual spelling

1. Window class encapsulates common window operations

## How can I use it?

The current reliable method is to use VS2019 to compile MinConsoleNative.

Pay attention to the trap: You can't just add headerfile's folder's path to C/C++ Additional Include Directories in Visual Studio project, because the names of some header files conflict with the names of some header files in Windows.

You can only include it like this:

``` cpp
#include "../MinConsoleNative/MinConsoleNative.h"
```

[MinConsoleNativeExample](https://github.com/OpenGreatDream/MinConsole/tree/main/src/MinConsoleNativeExample) provides a series of examples.

## History: Why I develop this repository?

By chance, I used Windows Console as my 2D renderer in a console game(text-based) gamejam in January 2018.

In These years I have studied Unity, UE4. I master C# and know well C/C++. I always come back to are C/C++, Windows Console.

I spent a lot of time researching Windows Console, Win32API, C/C++, C#, 3D Math. I have checked a lot of ConsoleGameEngine repos in github. I have also tried to write them myself, but after many times, I'm still not satisfied, I always want to do more!

During this research I find the Windows console has great potential beyond your imagination!

About 2 weeks ago, I wanted to restart and create a awesome Console library and share my skills with Windows Console.

Make some intresting stuffs.

No hate, only fast code and bugs.

## Third Party:

[WinReg](https://github.com/GiovanniDicanio/WinReg)(MIT License): High-level C++ Wrapper Around the Low-level Windows Registry C-interface API.

## Links:

[olcConsoleGameEngine](https://github.com/OneLoneCoder/videos/blob/master/olcConsoleGameEngine.h)

[gui.cs](https://github.com/migueldeicaza/gui.cs)

[Console Framework](https://github.com/elw00d/consoleframework)

[Pastel](https://github.com/silkfire/Pastel)

## Postscript:

On April 11, 2021, this project is officially open source!

Made in Minsk, Belarus.