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
	float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

//���Դ
//˥����ʽ f = 1.0/(c1*d^2 + c2*d + c3) �ù�ʽΪ˥����ʽ��
//dΪ�㵽���Դ�ľ��룬������c3��һ����c2�Ͷ�����c1
//����ȡֵͨ���ɾ���ó������Բο�Ogre3D��Wiki(http://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation)�ṩ�Ĳ����б�
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
	
	//˥��ϵͳ
	float distance = length(light.position - pos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}