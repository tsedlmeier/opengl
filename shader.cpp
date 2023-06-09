#include "shader.h"

#include <fstream>
#include <iostream>


Shader::Shader(const char* vert_filename, const char* frag_filename) {
    shader_id = create_shader(vert_filename, frag_filename);
}

Shader::~Shader() {
    glDeleteProgram(shader_id);
}

void Shader::bind() {
    glUseProgram(shader_id);
}
void Shader::unbind() {
    glUseProgram(0);
}

void Shader::use_shader() {
    glUseProgram(shader_id);
}

void Shader::pass_uniform1f(float val, const char* name) {
    GLint uniform_location = glGetUniformLocation(shader_id, name);
    glUniform1f(uniform_location , val);
}

GLuint Shader::compile(std::string shader_src, GLenum type) {
    GLuint id = glCreateShader(type);
    const char* src = shader_src.c_str();
    glShaderSource(id, 1, &src, 0);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result != GL_TRUE) {
        int len = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
        char* message = new char[len];
        glGetShaderInfoLog(id, len, &len, message);
        std::cout << "Shader compile error: " << message << std::endl;
        delete[] message;
        return 0;
    }
    return id;
}

std::string Shader::parse(const char* filename){
    FILE* file = fopen(filename, "rb");
    if(file == nullptr)
    {
        std::cout << filename << " not found" << std::endl;
        return 0;
    }

    std::string conts;
    fseek(file, 0, SEEK_END);
    size_t fs = ftell(file);
    rewind(file);
    conts.resize(fs);

    fread(&conts[0], 1, fs, file);
    fclose(file);

    return conts;
}

GLuint Shader::create_shader(const char* vert_filename, const char* frag_filename) {
    std::string vert_src = parse(vert_filename);
    std::string frag_src = parse(frag_filename);

    GLuint program = glCreateProgram();
    GLuint vs = compile(vert_src, GL_VERTEX_SHADER);
    GLuint fs = compile(frag_src, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);

    return program;
}

