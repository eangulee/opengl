#version 330 core
out vec4 FragColor;
in vec3 normal;
in vec3 pos;//顶点坐标

float specularStrength = 0.5f;//关照强度

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  光照 = 环境光 + 漫反射 + 镜面高光
	*/
    //FragColor = vec4(lightColor * objectColor, 1.0);
	float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - pos);//光照的反方向

	float diff = max(dot(norm,lightDir), 0);//通过点积计算光照的反方向和顶点法线的夹角
	vec3 diffuse = diff * lightColor;

	//Phong lighting model
	/*vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);//reflect函数要求第一个向量是从光源指向片段位置的向量
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