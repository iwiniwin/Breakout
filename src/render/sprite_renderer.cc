#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader){
    shader_ = shader;
    intRenderData();
}

SpriteRenderer::~SpriteRenderer(){
    glDeleteVertexArrays(1, &quad_vao_);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color){
    shader_.Use();
    glm::mat4 model(1.0f);

    // 正常情况下应该是先缩放，再旋转，再位移，但是矩阵乘法是从右到左的，所以这里顺序正好反过来

    // 5. 移动到指定位置
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // 4. 还原之前为旋转做的位移
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));

    // 3. 2D游戏，围绕z轴旋转
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));

    // 2. 将中心点（即锚点）移动到纹理中心，以便旋转是围绕中心进行的
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    // 1. 先缩放
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader_.SetMatrix4("model", model);
    shader_.SetVector3f("spriteColor", color);

    // 绑定纹理
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    // 绘制方形
    glBindVertexArray(quad_vao_);
    /*
        绘制函数
        参数1，指明打算绘制的OpenGL图元类型
        参数2，指定了顶点数组的起始索引
        参数3，指定打算绘制多少个顶点
    */
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::intRenderData(){
    unsigned int vbo;
    float vertices[] = {
        // Pos     // TexCoords
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &quad_vao_);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*
        glBufferData专门用来把用户定义的数据复制到当前绑定缓冲中
        参数1，目标缓冲的类型
        参数2，指定传输数据的大小（以字节为单位）
        参数3，希望发送的实际数据
        参数4，指定了显卡如何管理给定的数据
            GL_STATIC_DRAW : 数据不会或几乎不会被改变
            GL_DYNAMIC_DRAW : 数据会被改变很多
            GL_STREAM_DRAW : 数据每次绘制时都会改变
    */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quad_vao_);
    // 以顶点属性位置值作为参数，启用顶点属性
    glEnableVertexAttribArray(0);
    /*
        设置顶点属性指针
        告诉OpengGL如何解析顶点数据，如何把顶点数据链接到顶点着色器的顶点属性上
        参数1，指定要配置的顶点属性索引，对应顶点着色器中的layout(location = x)
        参数2，指定顶点属性的大小，这里是4个float值
        参数3，指定数据的类型
        参数4，定义是否希望数据被标准化，如果设置为GL_TRUE，所有数据都会被映射到0（对于有符号数据是-1）到1之间
        参数5，指定步长stride，说明连续的顶点属性组之间的间隔，简单说就是整个属性第二次出现的地方到整个数组0位置之间有多少字节
        参数6， 表示该属性数据在缓冲中起始位置的偏移量
    */
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}