# 最小控制台

免费，便携与强大的Windows控制台/终端底层库。

<p style="color:red">这个项目处于早期开发阶段，所有事情都在高速变化！</p>

## QQ群：1013032729

欢迎加入QQ群获取帮助！

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

注意陷阱：你不能简单地在VisualStudio项目中的C/C++附加包含目录中添加此项目头文件所处的文件夹的路径，因为某一些头文件与Windows系统的头文件存在命名冲突。

你只能这样引入项目的头文件：

``` cpp
#include "../MinConsoleNative/MinConsoleNative.h"
using namespace MinConsoleNative;
```

[MinConsoleNativeExample](https://github.com/OpenGreatDream/MinConsole/tree/main/src/MinConsoleNativeExample)提供一系列的示例。

## 历史：为什么我开发这个仓库？

偶然的机会，我在2018年1月的控制台游戏Gamejam上使用过Windows控制台作为我的2D渲染器。

这些年我学习过Unity，UE4。我熟练C#并且了解C/C++。令我总是回头的是C/C++，Windows控制台。

我花了不少时间研究Windows控制台，Win32 API，C/C++，C#，3D数学。我查看过许多Github上的控制台游戏引擎仓库。我也试过几次自己编写，但是几次过后我依然不满足，我总是想要更多！

在这次研究期间我发现Windows控制台有你想象不到的潜能！

大约2周前，我想开始创造一个超棒的Windows控制台库并且分享我的技能。

做一些有趣的事情。

没有仇恨，只有快速代码跟bug。

## 第三方库:

[WinReg](https://github.com/GiovanniDicanio/WinReg)(MIT License): High-level C++ Wrapper Around the Low-level Windows Registry C-interface API.

## 后记

在2021年四月11日，这个仓库正式开源！

Made in Minsk, Belarus.