#include "main.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
//using namespace std; //�������

main::main()
{
}


main::~main()
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
int createWindow();
int drawTriangle();
int drawRect();
//����
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//������ɫ��
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main()\n"
"{\n"
" gl_Position = vect4(pos.x, pos.y, pos.z, 1.0);\n"
"}\-";	//ǧ����������\0

//ƬԪ��ɫ������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";	//ǧ����������\0

//triangle
float vertices[] = {
	-1.0f, -0.5f, 0.0f,		//��
	0.5f, -0.5f, 0.0f,		//��
	0.0f, 0.5f, 0.0f		//��
};

//rect
float rectVertices[] = {
0.5f, 0.5f, 0.0f,   //���Ͻ�
0.5f, -0.5f, 0.0f,  //���½�
-0.5f, -0.5f, 0.0f, //���½�
-0.5f, 0.5f, 0.0f   //���Ͻ�
};
//vertex index array
unsigned int indices[] = {
0, 1, 3,    //��һ��������
1, 2, 3 //�ڶ���������
};

int main()
{
	//createWindow();
	//drawTriangle();
	drawRect();
	return 0;
}

int createWindow()
{
	std::cout << "hello world!" << std::endl;
	//��ʼ��glfw����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ָ��OpenGL�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //ָ��OpenGL���Ӱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ���ģʽ��

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWorld", NULL, NULL); //��������
	if (window == NULL) {
		std::cout << "Failed to created GLFW window" << std::endl;
		glfwTerminate();//�����������ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window); //�����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���

	//��ʼ��glad`
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	//ע�ᴰ�ڻص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window)) //����Ƿ�رմ���
	{
		processInput(window);//���������¼�

		//��Ⱦ
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f); //����������ɫ(��ɫ)
		glClear(GL_COLOR_BUFFER_BIT); //����

		glfwSwapBuffers(window); //����ʾ������������潻������ʾ���������е����ݣ�
		glfwPollEvents(); //������Ƿ����¼������������������ͼ��������¼���
	}
	glfwTerminate();//��ֹ����
	return 0;
}

//����һ��������
int drawTriangle()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//������������ɫ������
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//����vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//ָ��shaderԴ��ַ
	glCompileShader(vertexShader);//������ɫ��

	//fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//���� fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//ָ��shaderԴ��ַ
	glCompileShader(fragmentShader);//������ɫ��

	//������ɫ��
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//�ͷ���ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VBO ���㻺�����Vertex Buffer Object�����VBO��
	//VAO �����������Vertex Array Object��
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);//ʹ��shader program

		/*
		* ������һ��ϰ�ߣ�����Ĳ��������Զ����浽��VAO�У�����ֻ��Ҫ�󶨾Ϳ���
		* ���Ҫ��ʾ�Ķ�����ͬ��Ҳֻ��Ҫ������󶨲�ͬ�Ķ����Ϳ�����ʾ
		*/
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

//���ƾ���
int drawRect() 
{
	//��ʼ��glfw����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //ָ��OpenGL�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //ָ��OpenGL���Ӱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ���ģʽ��

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWorld", NULL, NULL); //��������
	if (window == NULL) {
		std::cout << "Failed to created GLFW window" << std::endl;
		glfwTerminate();//�����������ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window); //�����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//������������ɫ������
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//����vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//ָ��shaderԴ��ַ
	glCompileShader(vertexShader);//������ɫ��

	//fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//���� fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//ָ��shaderԴ��ַ
	glCompileShader(fragmentShader);//������ɫ��

	//������ɫ��
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//�ͷ���ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VBO ���㻺�����Vertex Buffer Object�����VBO��
	//VAO �����������Vertex Array Object��
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	
	//EBO Ԫ�ػ������Element Buffer Object�����EBO��
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);//ʹ��shader program

		/*
		* ������һ��ϰ�ߣ�����Ĳ��������Զ����浽��VAO�У�����ֻ��Ҫ�󶨾Ϳ���
		* ���Ҫ��ʾ�Ķ�����ͬ��Ҳֻ��Ҫ������󶨲�ͬ�Ķ����Ϳ�����ʾ
		*/
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0,0,width,height);  //����OpenGL�ӿ�����
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //���Esc����û�а���
		glfwSetWindowShouldClose(window, true); //���ô��ڹر�
}