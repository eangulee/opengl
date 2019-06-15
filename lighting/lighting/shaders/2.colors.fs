#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//��������

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - pos);//���յķ�����

	float diff = max(dot(norm,lightDir), 0);//ͨ�����������յķ�����Ͷ��㷨�ߵļн�
	vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}