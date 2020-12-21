//
// Created by fab on 23/02/2020.
//


#include <fstream>
#include <sstream>
#include <iostream>

#include "../../../headers/rendering/helper/Shader.hpp"
//TODO: make this a map
std::vector<Shader*> Shader::shadersLoaded = std::vector<Shader*>();

Shader::Shader(const char *path) : path(path)
{
    load();
    shadersLoaded.push_back(this);

    std::cout << "Loaded " << path << std::endl;
}

//TODO: make this more modular, don't repeat the loading code
void Shader::load()
{
    std::string s = path;
    s += "vs.glsl";
    std::ifstream i(s);

    GLuint vertexShader = 0, fragmentShader = 0, geometryShader = 0;
    int compiledShader;
    char infoLog[1024];

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
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        std::cout << "The path for the vertex shader is incorrect " << s << std::endl;
    }

    i.close();

    s = path;
    s += "fs.glsl";


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
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        std::cout << "The path for the fragment shader is incorrect " << s << std::endl;
    }

    i.close();

    s = path;
    s += "gs.glsl";

    //compiling geometry shader
    if (i.good())
    {
        std::stringstream buf;
        std::string geometryCode;

        buf << i.rdbuf();

        geometryCode = buf.str();

        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        const char *code = geometryCode.c_str();
        glShaderSource(geometryShader, 1, &code, NULL);
        glCompileShader(geometryShader);

        glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &compiledShader);

        if (!compiledShader)
        {
            glGetShaderInfoLog(geometryShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        std::cout << "The path for the geometry shader is incorrect " << s << std::endl;
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
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
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
    std::cout << "Reloading " << path << std::endl;
    load();
}

void Shader::use()
{
    glUseProgram(shaderProgram);
}

void Shader::setMatrix4(const std::string &name, glm::mat4& m)
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

void Shader::setVec2(const char *name, glm::vec2 val)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glUniform2f(location, val.x, val.y);
}

void Shader::setVec3(const char *name, glm::vec3& vec)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setVec4(const char *name, glm::vec4 &vec)
{
    GLint location = glGetUniformLocation(shaderProgram, name);
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setFloat3(const std::string &name, float f1, float f2, float f3)
{
    GLint location = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3f(location, f1, f2, f3);
}

void Shader::reloadShaders()
{
    for(Shader* s : shadersLoaded)
    {
        s->reload();
    }
}








