# 解释下MVP变换矩阵?
![alt text](image.png)


# 解释下VAO/VBO/EBO?
VAO: 保存顶点属性配置(glVertexAttribPointer)和 VBO 绑定状态的对象
VBO(Vertex buffer Object)：在GPU内存（通常被称为显存）中储存大量顶点数据（坐标、颜色等）
EBO/IBO(Index buffer Object): 在GPU内存（通常被称为显存）中储存顶点的索引


# 解释下模板测试?
[LearnOpengl](https://learnopengl-cn.github.io/04%20Advanced%20OpenGL/02%20Stencil%20testing/)

OpenGL模板测试（Stencil Testing）是 OpenGL 渲染管线中的一个重要阶段，用于根据模板缓冲区（Stencil Buffer）中的值来决定是否绘制某个片段。下面从模板缓冲区、工作原理、用途、基本步骤等方面进行详细解释。

### 模板缓冲区
模板缓冲区是一个与颜色缓冲区和深度缓冲区类似的附加缓冲区，它为帧缓冲区中的每个像素存储一个整数值，通常是 8 位，所以模板值的范围是 0 到 255。模板缓冲区的作用是控制哪些像素可以被绘制，哪些像素需要被忽略。

### 工作原理
在 OpenGL 渲染过程中，当一个片段即将被绘制时，模板测试会根据当前片段的模板值和预先设置的参考值以及比较函数来决定是否丢弃该片段。具体步骤如下：
1. **设置参考值**：通过 `glStencilFunc` 函数设置一个参考值（reference value），用于与模板缓冲区中的值进行比较。
2. **设置比较函数**：同样使用 `glStencilFunc` 函数指定一个比较函数（comparison function），例如 `GL_ALWAYS`（总是通过测试）、`GL_EQUAL`（相等时通过测试）等。
3. **执行比较**：对于每个即将绘制的片段，OpenGL 会将参考值与该片段对应位置的模板缓冲区中的值进行比较，根据比较函数的结果决定该片段是否通过模板测试。
4. **更新模板值**：如果片段通过了模板测试，还可以根据 `glStencilOp` 函数设置的操作来更新模板缓冲区中的值，例如保持原值、增加、减少或替换为新值等。

### 用途
- **遮罩效果**：可以使用模板测试来创建遮罩，只允许在特定区域内进行绘制。例如，在游戏中可以使用模板测试来限制绘制区域，只在角色的视野范围内进行渲染。
- **轮廓绘制**：通过模板测试可以实现物体轮廓的绘制。先将物体绘制到模板缓冲区中，然后在模板缓冲区的基础上进行轮廓的绘制。
- **多重渲染目标**：在一些复杂的渲染场景中，模板测试可以用于控制不同的渲染目标，实现更精细的渲染效果。

### 基本步骤
以下是一个简单的 OpenGL 模板测试的基本步骤示例：

```c
#include <GL/glut.h>

void init() {
    // 启用模板测试
    glEnable(GL_STENCIL_TEST);
    // 清除模板缓冲区
    glClearStencil(0);
    // 设置模板测试函数
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    // 设置模板测试通过和失败时的操作
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
}

void display() {
    // 清除颜色缓冲区、深度缓冲区和模板缓冲区
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // 绘制一个物体，同时更新模板缓冲区
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();

    // 修改模板测试函数，只绘制模板值为 1 的区域
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    // 绘制另一个物体，只有在模板值为 1 的区域才会被绘制
    glBegin(GL_QUADS);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.2, -0.2);
    glVertex2f(0.2, 0.2);
    glVertex2f(-0.2, 0.2);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Stencil Test");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
```

### 代码解释
1. **初始化**：在 `init` 函数中，启用模板测试，清除模板缓冲区，设置模板测试函数为 `GL_ALWAYS`（总是通过测试），并设置模板测试通过时的操作为 `GL_REPLACE`（将模板缓冲区的值替换为参考值）。
2. **绘制物体**：在 `display` 函数中，首先清除颜色缓冲区、深度缓冲区和模板缓冲区，然后绘制一个三角形，同时更新模板缓冲区。接着修改模板测试函数为 `GL_EQUAL`（相等时通过测试），并绘制一个正方形，只有在模板值为 1 的区域才会被绘制。
3. **主函数**：在 `main` 函数中，初始化 GLUT 库，设置显示模式为双缓冲、RGB 颜色模式和启用模板缓冲区，创建窗口并设置显示回调函数，最后进入主循环。

