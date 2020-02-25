//
// Created by fab on 23/02/2020.
//


#include <fstream>
#include <sstream>
#include <iostream>

#include "../../../headers/rendering/helper/Shader.hpp"

Shader::Shader(const char *path) : path(path)
{
    load();
}

void Shader::load()
{
    std::string s = path;
    s += "vs.glsl";
    std::ifstream i(s);

    GLuint vertexShader = 0, fragmentShader = 0;
    int compiledShader;
    char infoLog[512];

    //compiling vertex shader
    if (i.good())
    {
        std::stringstream buf;
        std::string vertexCode;

        buf << i.rdbuf();

        vertexCode = buf.str();

        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char *code = vertexCode.c_str();
        glShaderSource(vertexShader, 1, &code, NULL);
        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiledShader);

        if (!compiledShader)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    } else
    {
        std::cout << "The path for the vertex shader is incorrect " << s << std::endl;
    }

    s = path;
    s += "fs.glsl";
    i.close();

    i.open(s);

    //compiling frag shader
    if (i.good())
    {
        std::stringstream buf;
        std::string fragmentCode;

        buf << i.rdbuf();

        fragmentCode = buf.str();

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *code = fragmentCode.c_str();
        glShaderSource(fragmentShader, 1, &code, NULL);
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiledShader);

        if (!compiledShader)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    } else
    {
        std::cout << "The path for the fragment shader is incorrect " << s << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    //checking linking phase
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &compiledShader);

    if (!compiledShader)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &compiledShader);

    if (!compiledShader)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::VALIDATION_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    i.close();


}

void Shader::reload()
{
    glDeleteProgram(shaderProgram);
    load();
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

void Shader::setMatrix4(const std::string &name, glm::mat4 &m)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &m[0][0]);
}

void Shader::setInt(const std::string &name, int i)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1i(location, i);
}

void Shader::setFloat(const std::string &name, float f1)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform1f(location, f1);
}
