#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

const float Scene2::pi = 3.14159265358979323846;
const int Scene2::zero_vertices = 32;
const int Scene2::one_vertices = 32;

const float Scene2::zero_up_radius_small = 0.8;
const float Scene2::zero_up_radius_big = 1;
const float Scene2::zero_side_radius_small = 0.4;
const float Scene2::zero_side_radius_big = 0.8;


const char *Scene2::shader_vertex_filepath = "../src/scene_2_shader_vertex.glsl";
const char *Scene2::shader_fragment_filepath = "../src/scene_2_shader_fragment.glsl";

GLuint Scene2::BuildTriangles()
{
    float angle = (2*this->pi)/(this->zero_vertices);

    GLfloat NDC_coefficients[this->zero_vertices*4];

    NDC_coefficients[0] = 0.0f;
    NDC_coefficients[1] = 0.0f;
    NDC_coefficients[2] = 0.0f;
    NDC_coefficients[3] = 1.0f; //0

    int i;
    for (i = 0; i < this->zero_vertices; i++){

        if(i%2==0){ //even
            NDC_coefficients[i*4] = float(this->zero_side_radius_small*cos(angle*i)); //x
            NDC_coefficients[i*4+1] = float(this->zero_up_radius_small*sin(angle*i)); //y
            NDC_coefficients[i*4+2] = 0.0f;
            NDC_coefficients[i*4+3] = 1.0f;
        }
        else{ //odd
            NDC_coefficients[i*4] = float(this->zero_up_radius_small*cos(angle*i)); //x
            NDC_coefficients[i*4+1] = float(this->zero_up_radius_big*sin(angle*i)); //y
            NDC_coefficients[i*4+2] = 0.0f;
            NDC_coefficients[i*4+3] = 1.0f;
        }

    }
    GLuint VBO_NDC_coefficients_id;
    glGenBuffers(1, &VBO_NDC_coefficients_id);

    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);

    glBindVertexArray(vertex_array_object_id);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_NDC_coefficients_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(NDC_coefficients), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(NDC_coefficients), NDC_coefficients);
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLfloat color_coefficients[this->zero_vertices*4];

    for (i = 0; i < this->zero_vertices; i++){
        if(i%2==0){ //even
            color_coefficients[i*4] = 1.0f; //x
            color_coefficients[i*4+1] = 0.0f; //y
            color_coefficients[i*4+2] = 0.0f;
            color_coefficients[i*4+3] = 1.0f;
        }
        else{ //odd
            color_coefficients[i*4] = 1.0f; //x
            color_coefficients[i*4+1] = 0.0f; //y
            color_coefficients[i*4+2] = 0.0f;
            color_coefficients[i*4+3] = 1.0f;
        }

    }

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);
    location = 1; // "(location = 1)" em "shader_vertex.glsl"
    number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLubyte indices[this->zero_vertices*3];// = { 0,1,2, 2,1,3 }; // GLubyte: valores entre 0 e 255 (8 bits sem sinal).


    for (i = 0; i < this->zero_vertices-2; i++){
        indices[i*3] = i;
        indices[i*3+1] = i+1;
        indices[i*3+2] = i+2;
    }
    indices[this->zero_vertices*3-6]= i;
    indices[this->zero_vertices*3-5]= i+1;
    indices[this->zero_vertices*3-4]= 0;

    indices[this->zero_vertices*3-3]= i+1;
    indices[this->zero_vertices*3-2]= 0;
    indices[this->zero_vertices*3-1]= 1;


    // Criamos um buffer OpenGL para armazenar os �ndices acima
    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    // "Ligamos" o buffer. Note que o tipo agora � GL_ELEMENT_ARRAY_BUFFER.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);

    // Alocamos mem�ria para o buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);

    // Copiamos os valores do array indices[] para dentro do buffer.
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBindVertexArray(0);

    return vertex_array_object_id;
}


void Scene2::Render()
{
  GLuint vertex_array_object_id = this->BuildTriangles();

  glBindVertexArray(vertex_array_object_id);
  glDrawElements(GL_TRIANGLE_STRIP, this->zero_vertices*3, GL_UNSIGNED_BYTE, 0);
  glBindVertexArray(0);
}