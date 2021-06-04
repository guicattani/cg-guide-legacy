#version 330 core
struct Material {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 GouradSpecular;

out vec4 FragColor;

uniform bool useTexture;
uniform bool useDiffuseTexture;
uniform bool useSpecularTexture;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient;
    if(useTexture && useDiffuseTexture)
      ambient = light.ambient * texture(material.diffuseTexture, TexCoords).rgb;
    else
      ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse;
    if(useTexture && useDiffuseTexture)
      diffuse = light.diffuse * diff * texture(material.diffuseTexture, TexCoords).rgb;
    else
      diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular;
    if(useTexture && useSpecularTexture)
      specular = light.specular * spec * texture(material.specularTexture, TexCoords).rgb;
    else
      specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular + GouradSpecular;
    FragColor = vec4(result, 1.0);
}
