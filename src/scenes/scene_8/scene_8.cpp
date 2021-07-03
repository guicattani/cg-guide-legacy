#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif


void Scene8::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat vertices[] = {
      // positions        // normals          //texture coords
      -1.0f,-1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Left Side // -X
      -1.0f,-1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,	-1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Left Side

       1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f, // Back Side // -Z
      -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
       1.0f, 1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
      -1.0f,-1.0f,-1.0f,   0.0f, 0.0f,-1.0f,  1.0f, 0.0f, // Back Side

       1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f, // Bottom Side // -Y
      -1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
       1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
      -1.0f,-1.0f, 1.0f,   0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
      -1.0f,-1.0f,-1.0f,   0.0f,-1.0f, 0.0f,  1.0f, 1.0f, // Bottom Side

      -1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f, // Front Side // +Z
      -1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
       1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
       1.0f,-1.0f, 1.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, // Front Side

       1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f, // Right Side // +X
       1.0f,-1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       1.0f, 1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
       1.0f,-1.0f,-1.0f,   1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
       1.0f,-1.0f, 1.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, // Right Side

       1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // Top Side // +Y
       1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
       1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
      -1.0f, 1.0f,-1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f // Top Side
    };

  GLuint VBO_vertices_id, VAO_cube_id, VAO_light_cube_id;
  glGenVertexArrays(1, &VAO_cube_id);
  glGenBuffers(1, &VBO_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_cube_id);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coordinates attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  SceneObject cube;
  cube.name = "Cube";
  cube.first_index = (void *)0;
  cube.num_indices = 36;
  cube.rendering_mode = GL_TRIANGLES;
  cube.vertex_array_object_id = VAO_cube_id;
  this->virtualScene["cube"] = cube;
  glEnableVertexAttribArray(0);

}


void Scene8::Render()
{
  
  int display_w, display_h;
  glfwGetFramebufferSize(g_Window, &display_w, &display_h);

  this->shaders["scene"].use();
  glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem

  //first camera
  glViewport(0, 0, display_w/2, display_h);
  this->camera->Enable((float) (display_w/2)/display_h);
  this->camera->UpdateShaderUniforms(this->shaders["scene"]);

  model = Matrix_Translate(1.0f, 0.0f, 1.0f);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);
  DrawVirtualObject(this->virtualScene["sphere"]);

  model = Matrix_Translate(-1.0f, 0.0f, 1.0f);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);
  DrawVirtualObject(this->virtualScene["sphere"]);

  //second camera
  glViewport(display_w/2, 0, display_w/2, display_h);
  this->second_camera->Enable((float) (display_w/2)/display_h);
  this->second_camera->UpdateShaderUniforms(this->shaders["scene"]);

  model = Matrix_Translate(1.0f, 0.0f, 1.0f);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);
  DrawVirtualObject(this->virtualScene["sphere"]);

  model = Matrix_Translate(-1.0f, 0.0f, 1.0f);
  shaders["scene"].setMat4("model", model);
  shaders["scene"].setInt("object_id", 0);
  DrawVirtualObject(this->virtualScene["sphere"]);
}