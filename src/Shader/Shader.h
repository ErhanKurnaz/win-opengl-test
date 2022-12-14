//
// Created by Erhan Kurnaz on 30/05/2022.
//
#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader {
private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void SetUniform1iv(const std::string& name, int size, int* v0);

private:
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    ShaderProgramSource ParseShader(const std::string &filepath);

    int GetUniformLocation(const std::string& name) const;
};
