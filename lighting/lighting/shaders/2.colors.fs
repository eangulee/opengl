#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//顶点坐标

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //FragColor = vec4(lightColor * objectColor, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - pos);//光照的反方向

	float diff = max(dot(norm,lightDir), 0);//通过点积计算光照的反方向和顶点法线的夹角
	vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}