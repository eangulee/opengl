#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//顶点坐标
in vec2 texCoords;//uv坐标

float specularStrength = 0.5f;//关照强度

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
	float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

//点光源
//衰减公式 f = 1.0/(c1*d^2 + c2*d + c3) 该公式为衰减公式，
//d为点到点光源的距离，常数项c3、一次项c2和二次项c1
//具体取值通常由经验得出，可以参考Ogre3D的Wiki(http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation)提供的参数列表
void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  光照 = 环境光 + 漫反射 + 镜面高光
	*/
	

    // 环境光
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

    // 漫反射 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

    // 镜面光
    vec3 viewDir = normalize(viewPos - pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
	
	//衰减系统
	float distance = length(light.position - pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}