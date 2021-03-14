# TinyRenderer2D
一个小型的2D渲染器（600+行），基于OpenGL。可以嵌入任何支持OpenGL的库

这个渲染器是参考SDL2的渲染器做的，因为觉得SDL2渲染器的功比较少所以就自己做了一个，比SDL的稍微强一点点🤣。

这个渲染器需要`GLM`库去编译。

## 可以做什么

渲染器可以:

* 绘制一些基本图形（线，矩形，多边形，圆）
* 通过给基本图形每个顶点一个颜色，来创建有丰富颜色的基本图形
* 绘制图像并且旋转/缩放/翻转，或者绘制图像的一部分
* 给图像增加额外的颜色
* 图像可以被作为渲染器的目标来实现离屏渲染
* 透明色和混合

## 编译测试程序

需要：
* glm
* SDL2
* glew

在工程根目录（就这个文件所在的目录）下运行`make`即可。如果你的make没办法运行，请修改Makefile让他找到需要的第三方库。

测试程序是:
* `hello_world`: 一个创建了渲染器，并且使用指定颜色清屏的空白窗体，展示了渲染器创建和删除的时机
* `draw_shapes`: 展示了如何绘制几何图形
* `draw_images`: 展示了如何绘制图像
* `target_texture`: 展示了如何将`Texture`作为渲染器的目标，来实现离屏渲染

## 如何使用

最基本的使用方法如下（注意你必须将OpenGL初始化好后才能创建渲染器）：
```c++
// using namespace
using namespace tinyrenderer2d;

// create render
Renderer* render = CreateRenderer(800, 600);

// in game loop
render->SetClearColor(255, 255, 255, 255);
render->Clear();    // clear screen
// use render draw something
render->DrawLines();

// destroy render
DestroyRenderer(render);
```

其他的重要函数见[include/tinyrenderer2d/renderer.hpp](include/tinyrenderer2d/renderer.hp)和[include/tinyrenderer2d/texture.hpp](include/tinyrenderer2d/texture.hpp)，函数很少，这里就不介绍了😁。

# 一些屏幕截图

绘制基本图形

![snapshot1](https://i.loli.net/2021/03/14/7LA9aqNTPZGKc6Y.png)



绘制图像

![snapshot2](https://i.loli.net/2021/03/14/1OhZ6LPgcEGxyS4.png)
