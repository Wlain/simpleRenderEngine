# graphicRenderEngine
这是一个基于C++17标准的，使用OpenGL语言编写的的简单渲染引擎（主要用于学习）

渲染引擎：克瑞斯（ceres）

谷神星：位于主小行星带的矮行星和最大的小行星

代表：农业女神，代表生产力、农业、自然和四季

# dependencies
* glfw:一个用于 OpenGL、 OpenGL ES、 Vulkan、窗口和输入的多平台库
* glew:OpenGL 扩展管理器库
* glm:OpenGL数学库
* spdlog:一个高效的C++日志库
* imgui：一个无依赖的的C++图形用户界面库
* stb:一个用于C/C++的单文件加载库
* json11:一个基于C++11标准的的小型json库
* lua:Lua是一种强大、高效、轻量级、可嵌入的脚本语言。
* sol2:一个具有高级功能和高性能的C++ <-> Lua API的工具库
* box2d:一个人用于游戏的2D物理引擎
* bullet3:一个适用于 VR、游戏、视觉效果、机器人、机器学习等的实时碰撞检测和多物理场仿真的工具库

# test demo
* 基于lua脚本语言的函数可视化

![avatar](samples/luaForMathematicalFuncTest.png)

* 布料仿真

![avatar](samples/clothSimulationTest.png)

* 天空盒：cubeMap + AmbientMap(Reflection + Refraction)

![avatar](samples/skybox.png)

* 模型加载

![avatar](samples/objLoader.png)
![avatar](samples/objLoader1.png)


* 环境贴图

![avatar](samples/ambientMap1.png)
![avatar](samples/ambientMap2.png)
![avatar](samples/ambientMap3.png)

* pbr材质

![avatar](samples/pbr.png)

* 点精灵

![avatar](samples/pointSprites.png)

* 立方贴图

![avatar](samples/cubemap.png)

* 硬阴影贴图

![avatar](samples/shadowmap.png)

* 阴影域算法（使用模板测试）

![avatar](samples/shadowVolume.png)

* 凹凸贴图

![avatar](samples/bumpmap.png)

* 粒子系统：封装简单粒子发射器

![avatar](samples/particleEmitter.png)