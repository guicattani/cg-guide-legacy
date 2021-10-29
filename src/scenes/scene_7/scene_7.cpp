#include <iostream>
#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

using namespace glm;

void Scene7::BuildTrianglesAndAddToVirtualScene()
{
  // This is not using EBO
  GLfloat cube_vertices[] = {
      // positions        // normals          //texture coords
      -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Left Side // -X
      -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Left Side

      1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, // Back Side // -Z
      -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // Back Side

      1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Bottom Side // -Y
      -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
      -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // Bottom Side

      -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Front Side // +Z
      -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Front Side

      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Right Side // +X
      1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Right Side

      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top Side // +Y
      1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f // Top Side
  };

  GLfloat plane_vertices[] = {
      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top Side // +Y
      1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f // Top Side
  };

  GLfloat pyramid_vertices[] = {
      // positions        // normals
      1.0f, -1.0f, 1.0f, -0.5f, 0.0f, 0.5f, // Front Side // +Z
      0.0f, 1.0f, 0.0f, -0.5f, 0.0f, 0.5f,
      -1.0f, -1.0f, 1.0f, -0.5f, 0.0f, 0.5f, // Front Side

      -1.0f, -1.0f, 1.0f, -0.5f, 0.0f, 0.5f, // Right Side // -X
      0.0f, 1.0f, 0.0f, -0.5f, 0.0f, 0.5f,
      -1.0f, -1.0f, -1.0f, -0.5f, 0.0f, 0.5f, // Right Side

      1.0f, -1.0f, -1.0f, 0.5f, 0.0f, 0.5f, // Left Side // +X
      0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f,
      1.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.5f, // Left Side

      -1.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.5f, // Back Side // -Z
      0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f,
      1.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.5f, // Back Side

      1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, // Bottom Side First // -Y
      -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, // Bottom Side

      1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, // Bottom Side Second // -Y
      1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
      -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Bottom Side
  };

  GLuint VBO_cube_vertices_id, VBO_plane_vertices_id, VBO_pyramid_vertices_id,
      VAO_plane_id, VAO_cube_id, VAO_light_cube_id, VAO_light_pyramid_id;
  glGenVertexArrays(1, &VAO_cube_id);
  glGenBuffers(1, &VBO_cube_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_cube_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_cube_id);
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coordinates attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  SceneObject cube;
  cube.name = "Cube";
  cube.first_index = (void *)0;
  cube.num_indices = 36;
  cube.rendering_mode = GL_TRIANGLES;
  cube.vertex_array_object_id = VAO_cube_id;
  this->virtualScene["cube"] = cube;
  glEnableVertexAttribArray(0);

  // load texture
  this->material->diffuseTextureId = LoadTextureImage("../data/container2.png");
  this->material->specularTextureId = LoadTextureImage("../data/container2_specular.png");

  this->shaders["color_shader"].use();
  this->shaders["color_shader"].setInt("material.diffuseTexture", 0);
  this->shaders["color_shader"].setInt("material.specularTexture", 1);

  // light VAO
  glGenVertexArrays(1, &VAO_light_cube_id);
  glBindVertexArray(VAO_light_cube_id);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_cube_vertices_id);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);

  SceneObject light_cube;
  light_cube.name = "Light Cube";
  light_cube.first_index = (void *)0;
  light_cube.num_indices = 36;
  light_cube.rendering_mode = GL_TRIANGLES;
  light_cube.vertex_array_object_id = VAO_light_cube_id;
  this->virtualScene["light_cube"] = light_cube;
  glEnableVertexAttribArray(0);

  // pyramid light VAO
  glGenVertexArrays(1, &VAO_light_pyramid_id);
  glGenBuffers(1, &VBO_pyramid_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_pyramid_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(pyramid_vertices), pyramid_vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_light_pyramid_id);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  SceneObject light_pyramid;
  light_pyramid.name = "Light Pyramid";
  light_pyramid.first_index = (void *)0;
  light_pyramid.num_indices = 18;
  light_pyramid.rendering_mode = GL_TRIANGLES;
  light_pyramid.vertex_array_object_id = VAO_light_pyramid_id;
  this->virtualScene["light_pyramid"] = light_pyramid;
  glEnableVertexAttribArray(0);

  //plane
  glGenVertexArrays(1, &VAO_plane_id);
  glGenBuffers(1, &VBO_plane_vertices_id);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_plane_vertices_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertices), plane_vertices, GL_STATIC_DRAW);

  glBindVertexArray(VAO_plane_id);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  // normal attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coordinates attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  SceneObject plane;
  plane.name = "plane";
  plane.first_index = (void *)0;
  plane.num_indices = 6;
  plane.rendering_mode = GL_TRIANGLES;
  plane.vertex_array_object_id = VAO_plane_id;
  this->virtualScene["plane"] = plane;
  glEnableVertexAttribArray(0);
}

void Scene7::Render()
{
  this->camera->Enable();

  // directional light
  glm::mat4 model = glm::mat4(1.0f);

  if (this->directionalLightOn)
  {
    this->shaders["light_shader"].use();
    this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);

    vec4 forward_vector = vec4(0.0f, 0.0f, 1.0f, 0.0f);
    vec4 look_at_vector = vec4(this->directional_light->direction, 0.0f);
    float dot_product = dotproduct(look_at_vector, forward_vector);
    float y_angle = atan2(look_at_vector.x, dot_product);

    // TODO: get some help to understand why we need to rotate look at vector here and not in Y
    vec4 up_vector = vec4(0.0f, 1.0f, 0.0f, 0.0f);
    look_at_vector = look_at_vector * Matrix_Rotate_Y(y_angle);
    dot_product = dotproduct(look_at_vector, up_vector);
    float x_angle = atan2(look_at_vector.z, dot_product);

    //negating direction shows the light cube properly, since now we have direction and not possition
    model = glm::translate(model, -this->directional_light->direction) * Matrix_Rotate_Y(y_angle) * Matrix_Rotate_X(x_angle);
    model = glm::scale(model, glm::vec3(0.4f)); // a smaller cube
    this->shaders["light_shader"].setVec3("color", this->directional_light->ambient + this->directional_light->diffuse);
    this->shaders["light_shader"].setMat4("model", model);

    DrawVirtualObject(this->virtualScene["cylinder"]);
  }

  // point light
  if (this->pointLightOn)
  {
    this->shaders["light_shader"].use();
    this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);
    model = glm::mat4(1.0f);
    model = glm::translate(model, this->point_light->position);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    this->shaders["light_shader"].setVec3("color", this->point_light->ambient + this->point_light->diffuse);
    this->shaders["light_shader"].setMat4("model", model);

    glBindVertexArray(this->virtualScene["light_cube"].vertex_array_object_id);
    glDrawArrays(this->virtualScene["light_cube"].rendering_mode, 0, this->virtualScene["light_cube"].num_indices);
  }

  // spot light
  if (this->spotLightOn)
  {
    this->shaders["light_shader"].use();
    this->camera->UpdateShaderUniforms(this->shaders["light_shader"]);
    model = glm::mat4(1.0f);
    model = glm::translate(model, this->spot_light->position);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    this->shaders["light_shader"].setVec3("color", this->spot_light->ambient + this->spot_light->diffuse);
    this->shaders["light_shader"].setMat4("model", model);

    glBindVertexArray(this->virtualScene["light_pyramid"].vertex_array_object_id);
    glDrawArrays(this->virtualScene["light_pyramid"].rendering_mode, 0, this->virtualScene["light_pyramid"].num_indices);
  }

  this->shaders["color_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["color_shader"]);

  this->shaders["color_shader"].setBool("directionalLightOn", this->directionalLightOn);
  this->shaders["color_shader"].setVec3("directionalLight.direction", this->directional_light->direction);
  this->shaders["color_shader"].setVec3("directionalLight.ambient", this->directional_light->ambient);
  this->shaders["color_shader"].setVec3("directionalLight.diffuse", this->directional_light->diffuse);
  this->shaders["color_shader"].setVec3("directionalLight.specular", this->directional_light->specular);

  this->shaders["color_shader"].setBool("pointLightOn", this->pointLightOn);
  this->shaders["color_shader"].setVec3("pointLight.position", this->point_light->position);
  this->shaders["color_shader"].setVec3("pointLight.ambient", this->point_light->ambient);
  this->shaders["color_shader"].setVec3("pointLight.diffuse", this->point_light->diffuse);
  this->shaders["color_shader"].setVec3("pointLight.specular", this->point_light->specular);
  this->shaders["color_shader"].setFloat("pointLight.constant", this->point_light->constant);
  this->shaders["color_shader"].setFloat("pointLight.linear", this->point_light->linear);
  this->shaders["color_shader"].setFloat("pointLight.quadratic", this->point_light->quadratic);

  this->shaders["color_shader"].setBool("spotLightOn", this->spotLightOn);
  this->shaders["color_shader"].setVec3("spotLight.position", this->spot_light->position);
  this->shaders["color_shader"].setVec3("spotLight.direction", this->spot_light->direction);
  this->shaders["color_shader"].setVec3("spotLight.ambient", this->spot_light->ambient);
  this->shaders["color_shader"].setVec3("spotLight.diffuse", this->spot_light->diffuse);
  this->shaders["color_shader"].setVec3("spotLight.specular", this->spot_light->specular);
  this->shaders["color_shader"].setFloat("spotLight.constant", this->spot_light->constant);
  this->shaders["color_shader"].setFloat("spotLight.linear", this->spot_light->linear);
  this->shaders["color_shader"].setFloat("spotLight.quadratic", this->spot_light->quadratic);
  this->shaders["color_shader"].setFloat("spotLight.cutOff", cos(radians(this->spot_light->cutOff)));
  this->shaders["color_shader"].setFloat("spotLight.outerCutOff", cos(radians(this->spot_light->outerCutOff)));

  // material properties
  this->shaders["color_shader"].setVec3("material.ambient", this->material->ambient);
  this->shaders["color_shader"].setVec3("material.diffuse", this->material->diffuse);
  this->shaders["color_shader"].setVec3("material.specular", this->material->specular); // specular lighting doesn't have full effect on this object's material
  this->shaders["color_shader"].setFloat("material.shininess", this->material->shininess);
  this->shaders["color_shader"].setFloat("gouradSpecularStrength", this->gouradSpecularStrength);

  model = glm::mat4(1.0f);
  this->shaders["color_shader"].setMat4("model", model);

  //textures
  this->shaders["color_shader"].setBool("useTexture", this->useTexture);
  if (this->useTexture)
  {
    this->shaders["color_shader"].setBool("useDiffuseTexture", this->useDiffuseTexture);
    this->shaders["color_shader"].setBool("useSpecularTexture", this->useSpecularTexture);
  }
  // bind diffuse map
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, this->material->diffuseTextureId);

  // bind specular map
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, this->material->specularTextureId);

  glBindVertexArray(this->virtualScene["cube"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["cube"].rendering_mode, 0, this->virtualScene["cube"].num_indices);

  this->shaders["plane_shader"].use();
  this->camera->UpdateShaderUniforms(this->shaders["plane_shader"]);
  model = glm::mat4(1.0f);
  model = glm::translate(model, vec3(0.0f, -1.2f, 0.0f));
  model = glm::scale(model, glm::vec3(6.0f));
  this->shaders["plane_shader"].setVec3("color", vec3(0.3f, 0.3f, 0.3f));
  this->shaders["plane_shader"].setMat4("model", model);

  glBindVertexArray(this->virtualScene["plane"].vertex_array_object_id);
  glDrawArrays(this->virtualScene["plane"].rendering_mode, 0, this->virtualScene["plane"].num_indices);
}
