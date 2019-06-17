#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//��������
in vec2 texCoords;//uv����

float specularStrength = 0.5f;//����ǿ��

uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  ���� = ������ + ������ + ����߹�
	*/
    // ������
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

    // ������ 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

    // �����
    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}