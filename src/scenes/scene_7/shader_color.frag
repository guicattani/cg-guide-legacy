#version 330 core
struct Material {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;
};


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in vec3 GouradSpecular;

out vec4 FragColor;

uniform bool useTexture;
uniform bool useDiffuseTexture;
uniform bool useSpecularTexture;
uniform bool directionalLightOn;
uniform bool pointLightOn;
uniform bool spotLightOn;
uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight directionalLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

// function prototypes
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = vec3(0.0f);
    if(directionalLightOn)
      result += CalcDirLight(directionalLight, norm, viewDir);
    if(pointLightOn)
      result += CalcPointLight(pointLight, norm, FragPos, viewDir);
    if(spotLightOn)
      result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    // ambient
    vec3 ambient;
    if(useTexture && useDiffuseTexture)
      ambient = light.ambient * texture(material.diffuseTexture, TexCoords).rgb;
    else
      ambient = light.ambient * material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse;
    if(useTexture && useDiffuseTexture)
      diffuse = light.diffuse * diff * texture(material.diffuseTexture, TexCoords).rgb;
    else
      diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 specular;
    if(useTexture && useSpecularTexture)
      specular = light.specular * spec * texture(material.specularTexture, TexCoords).rgb;
    else
      specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular + GouradSpecular;
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // combine results

    // ambient
    vec3 ambient;
    if(useTexture && useDiffuseTexture)
      ambient = light.ambient * texture(material.diffuseTexture, TexCoords).rgb;
    else
      ambient = light.ambient * material.ambient;

    // diffuse
    vec3 diffuse;
    if(useTexture && useDiffuseTexture)
      diffuse = light.diffuse * diff * texture(material.diffuseTexture, TexCoords).rgb;
    else
      diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 specular;
    if(useTexture && useSpecularTexture)
      specular = light.specular * spec * texture(material.specularTexture, TexCoords).rgb;
    else
      specular = light.specular * (spec * material.specular);

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ambient
    vec3 ambient;
    if(useTexture && useDiffuseTexture)
      ambient = light.ambient * texture(material.diffuseTexture, TexCoords).rgb;
    else
      ambient = light.ambient * material.ambient;

    // diffuse
    vec3 diffuse;
    if(useTexture && useDiffuseTexture)
      diffuse = light.diffuse * diff * texture(material.diffuseTexture, TexCoords).rgb;
    else
      diffuse = light.diffuse * (diff * material.diffuse);

    //specular
    vec3 specular;
    if(useTexture && useSpecularTexture)
      specular = light.specular * spec * texture(material.specularTexture, TexCoords).rgb;
    else
      specular = light.specular * (spec * material.specular);

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}