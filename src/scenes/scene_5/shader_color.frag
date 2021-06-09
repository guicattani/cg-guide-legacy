#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec3 GouradSpecular;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float ambientStrength;
uniform float phongSpecularStrength;
uniform float diffuseStrength;

void main()
{
    //Ambient
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    //Diffuse
    //If the angle between both vectors is greater than 90 degrees then the result of
    //the dot product will actually become negative and we end up with a negative diffuse component.
    //For that reason we use the max function that returns the highest of both its
    //parameters to make sure the diffuse component (and thus the colors) never become negative.
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * diffuseStrength;

    //Phong Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = phongSpecularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular + GouradSpecular) * objectColor;
    FragColor = vec4(result, 1.0);
}
