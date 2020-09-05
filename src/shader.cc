#include "shader.h"

#include <iostream>

using namespace std;

Shader& Shader::Use(){
    glUseProgram(id_);
    return *this;
}

void Shader::Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source){
    unsigned vertex, fragment, geometry;

    // 编译顶点着色器
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_source, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // 编译片段着色器
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_source, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // 如果提供了几何着色器，则编译几何着色器
    if(geometry_source != nullptr){
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &geometry_source, NULL);
        glCompileShader(geometry);
        checkCompileErrors(geometry, "GEOMETRY");
    }

    // shader程序
    id_ = glCreateProgram();
    glAttachShader(id_, vertex);
    glAttachShader(id_, fragment);
    if(geometry_source != nullptr)
        glAttachShader(id_, geometry);
    glLinkProgram(id_);  
    checkCompileErrors(id_, "PROGRAM");

    // 链接完成后，删除着色器
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometry_source != nullptr)
        glDeleteShader(geometry);
}

void Shader::SetFloat(const char* name, float value, bool use_shader){
    if(use_shader)
        Use();
    glUniform1f(glGetUniformLocation(id_, name), value);
}

void Shader::SetInteger(const char* name, int value, bool use_shader){
    if(use_shader)
        Use();
    glUniform1i(glGetUniformLocation(id_, name), value);
}

void Shader::SetVector2f(const char* name, float x, float y, bool use_shader){
    if(use_shader)
        Use();
    glUniform2f(glGetUniformLocation(id_, name), x, y);
}

void Shader::SetVector2f(const char* name, const glm::vec2& value, bool use_shader){
    if(use_shader)
        Use();
    glUniform2f(glGetUniformLocation(id_, name), value.x, value.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool use_shader){
    if(use_shader)
        Use();
    glUniform3f(glGetUniformLocation(id_, name), x, y, z);
}

void Shader::SetVector3f(const char* name, const glm::vec3& value, bool use_shader){
    if(use_shader)
        Use();
    glUniform3f(glGetUniformLocation(id_, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool use_shader){
    if(use_shader)
        Use();
    glUniform4f(glGetUniformLocation(id_, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, const glm::vec4& value, bool use_shader){
    if(use_shader)
        Use();
    glUniform4f(glGetUniformLocation(id_, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix3(const char* name, const glm::mat3& matrix, bool use_shader){
    if(use_shader)
        Use();
    glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool use_shader){
    if(use_shader)
        Use();
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type){
    int success;
    char info_log[1024];
    if(type != "PROGRAM"){
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(object, 1024, NULL, info_log);
            cout << "ERROR::Shader: Compile-time error: Type: " << type << "\n"
            << info_log << "\n -- --------------------------------------------------- -- "
            << endl;
        }
    }else{
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(object, 1024, NULL, info_log);
            cout << "ERROR::Shader: Link-time error: Type: " << type << "\n"
                << info_log << "\n -- --------------------------------------------------- -- "
                << endl;
        }
    }
}