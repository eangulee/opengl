#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//��������

float specularStrength = 0.5f;//����ǿ��

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  ���� = ������ + ������ + ����߹�
	*/
    //FragColor = vec4(lightColor * objectColor, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - pos);//���յķ�����

	float diff = max(dot(norm,lightDir), 0);//ͨ�����������յķ�����Ͷ��㷨�ߵļн�
	vec3 diffuse = diff * lightColor;

	//Phong lighting model
	/*vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);//reflect����Ҫ���һ�������Ǵӹ�Դָ��Ƭ��λ�õ�����
	float spec = pow(max(dot(reflectDir,viewDir),0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;*/

	//Blinn-Phong lighting model
	vec3 viewDir = normalize(viewPos - pos);
	vec3 h = normalize(viewDir + lightDir);
	float spec = pow(max(dot(h,norm),0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}