#pragma once
#include "vertexBuffer.h"

#include <string>

struct Shader {
    Shader(const char* vert_filename, const char* frag_filename);
    virtual ~Shader();

    void bind();
    void unbind();
    void use_shader();
    void pass_uniform1f(float val, const char* name);

private:
    GLuint compile(std::string shader_src, GLenum type);
    std::string parse(const char* filename);
    GLuint create_shader(const char* vert_filename, const char* frag_filename);

    GLuint shader_id;

};

