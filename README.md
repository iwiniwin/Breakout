# Breakout
基于[LearnOpenGL教程](https://learnopengl-cn.github.io/06%20In%20Practice/2D-Game/01%20Breakout/)（[LearnOpenGL tutorial](https://learnopengl.com/In-Practice/2D-Game/Breakout)）的2D实战项目Breakout游戏

以下是部分游戏运行截图
![](https://learnopengl-cn.github.io/img/06/Breakout/01/cover.png)

## 新增 & 优化
在原教程项目代码的基础上做了以下新增与优化

* 添加了更多的代码注释
* 新增按`P`键，打开或关闭左下角游戏帧率（FPS）显示

![](docs/debug_fps.png)

## 编译
克隆项目代码，在项目根目录执行以下命令
* 克隆子模块，依赖于[glfw](https://github.com/glfw/glfw)和[glm](https://github.com/g-truc/glm)
```
$ git submodule update --init
```
* 执行cmake
```
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .
```
已在以下平台编译通过
| 系统 | 版本号 |
|---|:-:|
| Windows | 1607 |
| Linux | TODO |
| MacOS | TODO | 