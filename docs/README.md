# MinConsole

免费，便携与强大的Windows控制台/终端底层库。————由Min编写

<p style="color:red">这个项目处于早期开发阶段，所有事情都在高速变化！</p>

## 这是什么？

这是一个针对Windows 10的底层控制台库，你可以使用它在控制台中渲染，获取用户输入等。

主要目标是用这个库开发上层软件，例如：文本编辑器，3D渲染器，音乐播放器:)

如果你认为这个项目对你有任何帮助，请帮忙点一个Star！🌟

如果你想提交代码，欢迎提交[pull request](https://github.com/OpenGreatDream/MinConsole/pulls)!👍

## 特性:

1. 剪切板接口（读/写）

1. 强大的Console类（封装了Windows控制台API）

1. 渲染真彩色（RGB）到控制台（打破16种颜色的限制）

1. Database类提供数据的读写帮助

1. 支持鼠标滚轮，鼠标坐标（你甚至可以在Windows Terminal中使用！）

1. 好用的Input类(允许你处理鼠标)

1. 调色盘系统！

1. 高帧率计时器

1. VTConverter类帮助你生成VT序列

1. Window类封装了常用的窗体操作

## 我如何使用它？

当前可靠的办法是使用VS2019编译MinConsoleNative。

MinConsoleNativeExample提供一系列的示例。

## 历史：为什么我开发这个仓库？

By chance, I used Windows Console as my 2D renderer in a console game(text-based) gamejam in January 2018.

In These years I have studied Unity, UE4. I master C# and know well C/C++. I always come back to are C/C++, Windows Console.

I spent a lot of time researching Windows Console, Win32API, C/C++, C#, 3D Math. I have checked a lot of ConsoleGameEngine repos in github.com. I have also tried to write them myself, but after many times, I'm still not satisfied, I always want to do more!

During this research I find the Windows console has great potential beyond your imagination!

About 1 week ago, I wanted to restart and create a awesome Console library and share my skills with Windows Console.

Make some intresting stuffs.

No hate, only fast code and bugs.

## Third Party:

[WinReg](https://github.com/GiovanniDicanio/WinReg)(MIT License): High-level C++ Wrapper Around the Low-level Windows Registry C-interface API.

## Postscript

On April 11, 2021, this project is officially open source!

Made in Minsk, Belarus.