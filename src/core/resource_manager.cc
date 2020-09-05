#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

map<string, Texture2D> ResourceManager::textures_;
map<string, Shader> ResourceManager::shaders_;

Shader ResourceManager::LoadShader(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file, string name){
    shaders_[name] = loadShaderFromFile(vertex_shader_file, fragment_shader_file, geometry_shader_file);
    return shaders_[name];
}

Shader ResourceManager::GetShader(string name){
    return shaders_[name];
}

Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, string name){
    textures_[name] = loadTextureFromFile(file, alpha);
    return textures_[name];
}

Texture2D ResourceManager::GetTexture(string name){
    return textures_[name];
}

void ResourceManager::Clear(){
    for(auto iter : shaders_)
        glDeleteProgram(iter.second.id_);
    for(auto iter : textures_)
        glDeleteTextures(1, &iter.second.id_);
}

Shader ResourceManager::loadShaderFromFile(const char* vertex_shader_file, const char* fragment_shader_file, const char* geometry_shader_file){
    string vertex_code;
    string fragment_code;
    string geometry_code;
    try{
        // 打开文件
        ifstream vertex_file(vertex_shader_file);
        ifstream fragment_file(fragment_shader_file);
        stringstream vertex_stream, fragment_stream;

        vertex_stream << vertex_file.rdbuf();
        fragment_stream << fragment_file.rdbuf();

        // 关闭文件句柄
        vertex_file.close();
        fragment_file.close();

        vertex_code = vertex_stream.str();
        fragment_code = fragment_stream.str();

        if(geometry_shader_file != nullptr){
            ifstream geometry_file(geometry_shader_file);
            stringstream geometry_stream;
            geometry_stream << geometry_file.rdbuf();
            geometry_file.close();
            geometry_code = geometry_stream.str();
        }
    }
    catch(exception e){
        cout << "ERROR::SHADER: Failed to read shader files" << endl;
    }

    const char* vertex_shader_code = vertex_code.c_str();
    const char* fragment_shader_code = fragment_code.c_str();
    const char* geometry_shader_code = geometry_code.c_str();

    Shader shader;
    shader.Compile(vertex_shader_code, fragment_shader_code, geometry_shader_file != nullptr ? geometry_shader_code : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha){
    Texture2D texture;
    if(alpha){
        texture.internal_format_ = GL_RGBA;
        texture.image_format_ = GL_RGBA;
    }
    // 加载图片
    int width, height, nr_components;
    unsigned char* image = stbi_load(file, &width, &height, &nr_components, 0);
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}
