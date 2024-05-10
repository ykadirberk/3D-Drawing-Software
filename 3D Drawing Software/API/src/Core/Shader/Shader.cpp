#include <sstream>
#include <fstream>
#include <iostream>

#include "Shader.h"
#include "../CoreGL.h"

namespace dra {

    Shader::Shader(const std::string& filepath)
        : m_FilePath(filepath), m_RendererID(0)
    {
        auto source = ParseShader(filepath);

        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        m_RendererID = shader;
    }

    Shader::~Shader() {
        Unbind();
        GLCall(glDeleteProgram(m_RendererID));
    }

    ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
        std::ifstream stream(filepath);
        enum class ShaderType {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };


        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos) {
                    type = ShaderType::FRAGMENT;
                }

            }
            else {
                ss[(int)type] << line << '\n';
            }
        }
        return { ss[0].str(), ss[1].str() };
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << "Failed to compile " <<
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << std::endl;
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        // TODO: Error handling.

        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        unsigned int program = glCreateProgram();
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    void Shader::Bind() const {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& name, int value) {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniformMat4f(const std::string& name, const Matrix4<float>& matrix) {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix.data[0]));
        /*for (int i = 0;i < 16;i++) {
            std::cout << i << "=" << matrix.data[i] << std::endl;
        }*/

        //__debugbreak();
    }


    int Shader::GetUniformLocation(const std::string& name) const {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
            return m_UniformLocationCache[name];
        }
        GLCall(int location = glGetUniformLocation(m_RendererID, name.data()));
        m_UniformLocationCache[name] = location;
        return location;
    }
}