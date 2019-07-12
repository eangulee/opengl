#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{           
     // 采样法线贴图
    vec3 normal = texture(texture_normal1, fs_in.TexCoords).rgb;
    // 转换法向量到[-1,1]范围
    normal = normalize(normal * 2.0 - 1.0);  // 此向量是切线空间中的向量
   
    // 采样漫反射
    vec3 color = texture(texture_diffuse1, fs_in.TexCoords).rgb;
    // 环境光
    vec3 ambient = 0.1 * color;
    // 漫反射
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // 镜面高光
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = vec3(0.2) * spec;
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}