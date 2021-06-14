# 在.NET控制台应用程序中使用高达1600万种颜色

学习Linux之余，在Github上闲逛时碰巧点开了一个有趣的仓库[Pastel](https://github.com/silkfire/Pastel)惊喜地发现原来Windows10的Console也开始支持渲染24bit/16M真彩色。

- In 2016, Microsoft released the Windows 10 Version 1511 update which unexpectedly implemented support for ANSI escape sequences.

在闲暇之余查阅了一些资料后决定写下了这篇文章分享出来。

## 准备

第一步当然是用Visual Studio创建一个DotNet Framework的空项目，并添加System与System.Drawing引用。

打开Nuget包管理控制台，输入：Install-Package Pastel -Version 1.3.1

## 示例

``` cs
using Pastel;
using System;
using System.Drawing;

namespace PastelSample
{
    class Class1
    {
        public static void Main()
        {
            Console.Title = "PastelSample";

            int r = 255, g = 0, b = 128;

            for (int i = 0; i < 20; i++)
            {
                r -= 10;
                g += 12;
                b += 4;
                Color fcolor = Color.FromArgb(r, g, b);
                Color bcolor = Color.FromArgb(b, g, r);
                Console.WriteLine("Hello World".Pastel(fcolor).PastelBg(bcolor));
            }

            Console.ReadLine();
        }
    }
}

```

点击运行就可以看到效果了。