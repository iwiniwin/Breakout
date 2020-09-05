#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
using namespace std;

#include "texture.h"
#include "shader.h"

class ResourceManager
{
private:
    ResourceManager(){};
    static Shader loadShaderFromFile(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file = nullptr);
    static Texture2D loadTextureFromFile(const char* file, bool alpha);
public:
    static map<string, Shader> shaders_;
    static map<string, Texture2D> textures_;

    // 加载shader
    static Shader LoadShader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file, string name);

    // 根据name获取一个shader
    static Shader GetShader(string name);

    // 加载纹理
    static Texture2D LoadTexture(const char* file, bool alpha, string name);

    // 根据name获取一个纹理
    static Texture2D GetTexture(string name);

    // 清理所有已分配资源
    static void Clear();
};

#endif