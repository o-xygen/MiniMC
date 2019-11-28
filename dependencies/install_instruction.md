目前选用 glut + glad的形式（其实 glut 太老了，用 Freeglut 或者 glfw 更好）。当然 glad 也可以换成 glew 。

### installation instructions

1. 将 glad、glm、KHR文件夹 放到编译环境的include文件夹下。使用 Visual Studio 路径一般是：`C:\Program Files (x86)\Microsoft Visual Studio\{visual studio version}\Community\VC\Tools\MSVC\{patch version}\include`
2. glut环境就不赘述了。
3. 需要注意 glad 库是与 OpenGL的版本相关的，当前 glad 的库对应 OpenGL 4.5+。如果 OpenGL 版本低于4.5，则可以选择升级驱动，或者选择安装低版本 glad，这个可以在 glad 官方的 web service上选择下载。