#ifndef CLASS_HEADER_SCENE
#define CLASS_HEADER_SCENE
#include "scene.h"
#endif

const float Scene2::pi = 3.14159265358979323846;
const int Scene2::zero_vertices = 32;
const int Scene2::one_vertices = 4;

const int Scene2::num_of_digits = 4;

const float Scene2::zero_up_radius_small = 0.2;
const float Scene2::zero_up_radius_big = 0.3;
const float Scene2::zero_side_radius_small = 0.1;
const float Scene2::zero_side_radius_big = 0.2;

GLuint Scene2::BuildTriangles(int seconds, bool isAOne, int digitLocation)
{
    float angle = (2*this->pi)/(this->zero_vertices);

    int sizeOfArray = 0;
    if(isAOne)
        sizeOfArray = this->one_vertices;
    else
        sizeOfArray = this->zero_vertices;

    GLfloat NDC_coefficients[sizeOfArray*4*4];

    float translation = 0.75f - 0.5f*digitLocation;
    int i;
    if(isAOne)
    {
        NDC_coefficients[0] = -0.05f-translation;
        NDC_coefficients[1] = float(-this->zero_up_radius_big);
        NDC_coefficients[2] = 0.0f;
        NDC_coefficients[3] = 1.0f; //0

        NDC_coefficients[4] = 0.05f-translation;
        NDC_coefficients[5] = float(-this->zero_up_radius_big);
        NDC_coefficients[6] = 0.0f;
        NDC_coefficients[7] = 1.0f; //0


        for (i = 2  ; i < this->one_vertices; i++)
        {

            if(i%2==0)  //even
            {
                NDC_coefficients[i*4] = -0.05f-translation; //x
                NDC_coefficients[i*4+1] = float(-this->zero_up_radius_big+((this->zero_up_radius_big*2)/this->one_vertices)*i  ); //y
                NDC_coefficients[i*4+2] = 0.0f;
                NDC_coefficients[i*4+3] = 1.0f;
            }
            else  //odd
            {
                NDC_coefficients[i*4] = 0.05f-translation; //x
                NDC_coefficients[i*4+1] = float(-this->zero_up_radius_big+((this->zero_up_radius_big*2)/this->one_vertices)*i); //y
                NDC_coefficients[i*4+2] = 0.0f;
                NDC_coefficients[i*4+3] = 1.0f;
            }

            //printf("\nx=%f",NDC_coefficients[i*4+1]);
            //printf("\ny=%f",NDC_coefficients[i*4+2]);

        }
        NDC_coefficients[i*4] = -0.1f-translation; //x
        NDC_coefficients[i*4+1] = float(-this->zero_up_radius_big+((this->zero_up_radius_big*2)/this->one_vertices)*(i-2) ); //y
        NDC_coefficients[i*4+2] = 0.0f;
        NDC_coefficients[i*4+3] = 1.0f;
    }

    else
    {
        for (i = 0; i < this->zero_vertices; i++)
        {

            if(i%2==0)  //even
            {
                NDC_coefficients[i*4] = float(this->zero_side_radius_small*cos(angle*i)-translation); //x
                NDC_coefficients[i*4+1] = float(this->zero_up_radius_small*sin(angle*i)); //y
                NDC_coefficients[i*4+2] = 0.0f;
                NDC_coefficients[i*4+3] = 1.0f;
            }
            else  //odd
            {
                NDC_coefficients[i*4] = float(this->zero_up_radius_small*cos(angle*i)-translation); //x
                NDC_coefficients[i*4+1] = float(this->zero_up_radius_big*sin(angle*i)); //y
                NDC_coefficients[i*4+2] = 0.0f;
                NDC_coefficients[i*4+3] = 1.0f;
            }
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
    GLfloat color_coefficients[sizeOfArray*4];

    if(isAOne)
    {
        for (i = 0; i < this->one_vertices; i++)
        {

            color_coefficients[i*4] = 0.0f; //x
             color_coefficients[i*4+1] = 0.0f; //y
            color_coefficients[i*4+2] = 1.0f;
            color_coefficients[i*4+3] = 1.0f;

        }
    }
    else
    {
        for (i = 0; i < this->zero_vertices; i++)
        {
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


    GLubyte indices[sizeOfArray*3];
    if(isAOne)
    {
        for (i = 0; i < this->one_vertices-2; i++)
        {
            indices[i*3] = i;
            indices[i*3+1] = i+1;
            indices[i*3+2] = i+2;
            //printf("%i,%i,%i,\n",indices[i*3],indices[i*3+1],indices[i*3+2]);
        }

    }

    else
    {
        for (i = 0; i < this->zero_vertices-2; i++)
        {
            indices[i*3] = i;
            indices[i*3+1] = i+1;
            indices[i*3+2] = i+2;
            //printf("%i,%i,%i, //%i \n",indices[i*3],indices[i*3+1],indices[i*3+2], i);
        }
        indices[this->zero_vertices*3-6]= i;
        indices[this->zero_vertices*3-5]= i+1;
        indices[this->zero_vertices*3-4]= 0;

        indices[this->zero_vertices*3-3]= i+1;
        indices[this->zero_vertices*3-2]= 0;
        indices[this->zero_vertices*3-1]= 1;

    }


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
  this->seconds = (int)glfwGetTime();
  this->shader.use();
  this->camera->Enable();
  this->camera->UpdateShaderUniforms(this->shader);

  bool binary[4];
  int index;
  int sizeOfArray = 0;
  for(index = 0; index < 4; index++)
  {
      if(this->seconds & 1)
      {
          binary[index] = true;
          sizeOfArray += sizeOfArray + this->one_vertices;
      }
      else
      {
          binary[index] = false;
          sizeOfArray += sizeOfArray + this->zero_vertices;
      }
      this->seconds >>= 1;
  }

  for (index =  0; index < this->num_of_digits; index++)
  {

      // Constru�mos a representa��o de um tri�ngulo
      GLuint vertex_array_object_id = BuildTriangles(seconds % 16, binary[3-index],index);

      // "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
      // v�rtices apontados pelo VAO criado pela fun��o BuildTriangles(). Veja
      // coment�rios detalhados dentro da defini��o de BuildTriangles().
      glBindVertexArray(vertex_array_object_id);


      // Pedimos para a GPU rasterizar os v�rtices apontados pelo VAO como
      // tri�ngulos.
      //
      //                +--- Veja slide 178 do documento "Aula_04_Modelagem_Geometrica_3D.pdf".
      //                |          +--- O array "indices[]" cont�m 6 �ndices (veja fun��o BuildTriangles()).
      //                |          |  +--- Os �ndices s�o do tipo "GLubyte" (8 bits sem sinal)
      //                |          |  |                 +--- V�rtices come�am em indices[0] (veja fun��o BuildTriangles()).
      //                |          |  |                 |
      //                V          V  V                 V
      glDrawElements(GL_TRIANGLE_STRIP, sizeOfArray*3, GL_UNSIGNED_BYTE, 0);

      //each circle has vertices*3

      // "Desligamos" o VAO, evitando assim que opera��es posteriores venham a
      // alterar o mesmo. Isso evita bugs.
      glBindVertexArray(0);

  }
}