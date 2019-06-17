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
    vec3 direction;
	float cutOff;//内圆锥
	float outerCutOff;//外圆锥
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

//聚光灯
void main()
{
	/*Phong lighting model && Blinn-Phong lighting model
	  光照 = 环境光 + 漫反射 + 镜面高光
	*/
    // 环境光
    vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

	vec3 result;
	//float theta = dot(normal(pos - light.positon) , normal(light.direction));
	vec3 lightDir = normalize(light.position - pos);
    
    // check if lighting is inside the spotlight cone
    float theta = dot(lightDir, normalize(-light.direction)); 
	/*
	//硬边缘
	if(theta > light.cutOff){//在内圆锥内时，注意这里是>不是<因为cos在该[0,90]区间为减函数
		// 漫反射 
		vec3 norm = normalize(normal);
		//vec3 lightDir = normalize(-light.direction);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

		// 镜面光
		vec3 viewDir = normalize(viewPos - pos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
		
		result = ambient + diffuse + specular;
	}else{
		result = ambient;
	}*/

	//平滑/软化边缘
	// 漫反射 
	vec3 norm = normalize(normal);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;

	// 镜面光
	vec3 viewDir = normalize(viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, texCoords).rgb;  
	
	//平滑算法(soft edges)
	float epsilon = light.cutOff - light.outerCutOff;//外圆锥的的cos值要比较小
	float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0,1.0);//https://learnopengl-cn.github.io/02%20Lighting/05%20Light%20casters/

	// 将不对环境光做出影响，让它总是能有一点光
	diffuse  *= intensity;
	specular *= intensity;
	
	result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}