#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Pos;

uniform sampler2D texture1;
uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    float ratio = 1.00 / 1.52;//refract ratio(折射率)
	vec3 viewDir = normalize(Pos - cameraPos);
	vec3 R = refract(viewDir, normalize(Normal),ratio);
	vec4 color = texture(texture1,TexCoords);
    FragColor = vec4(texture(skybox,R).rgb, 1.0);// * color;
}