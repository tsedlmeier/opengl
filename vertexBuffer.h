#pragma once
#include <GL/glew.h>
#define GLEW_STATIC


struct Vertex {
  float x;
  float y;
  float z;

  // float r;
  // float g;
  // float b;
  // float a;
};


struct VertexBuffer{
  VertexBuffer(void* data, uint32_t n_verts) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // use buffer
    glBufferData(GL_ARRAY_BUFFER, n_verts * sizeof(Vertex), data , GL_STATIC_DRAW); // fill buffer

    glEnableVertexAttribArray(0); // xyz
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex,x)); // 3 floats xyz
    // glEnableVertexAttribArray(1); // rgba
    // glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex,r)); // 3 floats xyz
  }

  ~VertexBuffer(){
    glDeleteBuffers(1, &buffer_id);
  }

  void bind() {
    glBindVertexArray(vao); // use buffer
  } 

  void unbind() {
    glBindVertexArray(0); // use buffer
  }

private:
  GLuint buffer_id;
  GLuint vao; // vertex array objects

};
