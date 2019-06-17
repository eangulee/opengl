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
    vec3 direction;
	float cutOff;//��Բ׶
	float outerCutOff;//��Բ׶
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

//�۹��
void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  ���� = ������ + ������ + ����߹�
	*/
    // ������
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

	vec3 result;
	//float theta = dot(normal(pos - light.positon) , normal(light.direction));
	vec3 lightDir = normalize(light.position - pos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
	/*
	//Ӳ��Ե
	if(theta > light.cutOff){//����Բ׶��ʱ��ע��������>����<��Ϊcos�ڸ�[0,90]����Ϊ������
		// ������ 
		vec3 norm = normalize(normal);
		//vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

		// �����
		vec3 viewDir = normalize(viewPos - pos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
		
		result = ambient + diffuse + specular;
	}else{
		result = ambient;
	}*/

	//ƽ��/����Ե
	// ������ 
	vec3 norm = normalize(normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

	// �����
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
	
	//ƽ���㷨(soft edges)
	float epsilon = light.cutOff - light.outerCutOff;//��Բ׶�ĵ�cosֵҪ�Ƚ�С
	float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);//https://learnopengl-cn.github.io/02%20Lighting/05%20Light%20casters/

	// �����Ի���������Ӱ�죬������������һ���
	diffuse  *= intensity;
	specular *= intensity;
	
	result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}