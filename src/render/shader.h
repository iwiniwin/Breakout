#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"


class Shader
{
public:
    unsigned int id_;
    Shader() {};

    // 激活当前的shader程序
    Shader& Use();

    // 编译shader
    void Compile(const char* vertex_source, const char* fragment_source, const char* geometry_source = nullptr);

    void SetFloat(const char* name, float value, bool use_shader = false);
    void SetInteger(const char* name, int value, bool use_shader = false);
    void SetVector2f(const char* name, float x, float y, bool use_shader = false);
    void SetVector2f(const char* name, const glm::vec2& value, bool use_shader = false);
    void SetVector3f(const char* name, float x, float y, float z, bool use_shader = false);
    void SetVector3f(const char* name, const glm::vec3& value, bool use_shader = false);
    void SetVector4f(const char* name, float x, float y, float z, float w, bool use_shader = false);
    void SetVector4f(const char* name, const glm::vec4& value, bool use_shader = false);
    void SetMatrix3(const char* name, const glm::mat3& matrix, bool use_shader = false);
    void SetMatrix4(const char* name, const glm::mat4& matrix, bool use_shader = false);

private:
    // 检查是否有编译或链接错误
    void checkCompileErrors(unsigned int object, std::string type);
};

#endif