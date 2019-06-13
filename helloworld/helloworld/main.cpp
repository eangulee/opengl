#include "main.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
//using namespace std; //加上这句

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
//常量
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//顶点着色器
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"void main()\n"
"{\n"
" gl_Position = vect4(pos.x, pos.y, pos.z, 1.0);\n"
"}\-";	//千万别忘记这个\0

//片元着色器代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";	//千万别忘记这个\0

//triangle
float vertices[] = {
	-1.0f, -0.5f, 0.0f,		//左
	0.5f, -0.5f, 0.0f,		//右
	0.0f, 0.5f, 0.0f		//上
};

//rect
float rectVertices[] = {
0.5f, 0.5f, 0.0f,   //右上角
0.5f, -0.5f, 0.0f,  //右下角
-0.5f, -0.5f, 0.0f, //左下角
-0.5f, 0.5f, 0.0f   //左上角
};
//vertex index array
unsigned int indices[] = {
0, 1, 3,    //第一个三角形
1, 2, 3 //第二个三角形
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
	//初始化glfw窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //指定OpenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用OpenGL的核心模式（可编程渲染管道的模式）

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWorld", NULL, NULL); //创建窗口
	if (window == NULL) {
		std::cout << "Failed to created GLFW window" << std::endl;
		glfwTerminate();//如果出错，则终止进程
		return -1;
	}
	glfwMakeContextCurrent(window); //将窗口的上下文环境设置为当前主线程的上下文环境

	//初始化glad`
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	//注册窗口回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//渲染循环
	while (!glfwWindowShouldClose(window)) //检查是否关闭窗口
	{
		processInput(window);//处理输入事件

		//渲染
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f); //设置清屏颜色(黄色)
		glClear(GL_COLOR_BUFFER_BIT); //清屏

		glfwSwapBuffers(window); //将显示缓存和离屏缓存交换（显示离屏缓存中的内容）
		glfwPollEvents(); //将检查是否有事件触发（例如鼠标输入和键盘输入事件）
	}
	glfwTerminate();//终止进程
	return 0;
}

//绘制一个三角形
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

	//创建、编译着色器程序
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//指定shader源地址
	glCompileShader(vertexShader);//编译着色器

	//fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建 fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//指定shader源地址
	glCompileShader(fragmentShader);//编译着色器

	//链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//释放着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VBO 顶点缓存对象（Vertex Buffer Object，简称VBO）
	//VAO 顶点数组对象（Vertex Array Object）
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

		glUseProgram(shaderProgram);//使用shader program

		/*
		* 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
		* 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
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

//绘制矩形
int drawRect() 
{
	//初始化glfw窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //指定OpenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用OpenGL的核心模式（可编程渲染管道的模式）

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HelloWorld", NULL, NULL); //创建窗口
	if (window == NULL) {
		std::cout << "Failed to created GLFW window" << std::endl;
		glfwTerminate();//如果出错，则终止进程
		return -1;
	}
	glfwMakeContextCurrent(window); //将窗口的上下文环境设置为当前主线程的上下文环境
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建、编译着色器程序
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//指定shader源地址
	glCompileShader(vertexShader);//编译着色器

	//fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);//创建 fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//指定shader源地址
	glCompileShader(fragmentShader);//编译着色器

	//链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	//释放着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//VBO 顶点缓存对象（Vertex Buffer Object，简称VBO）
	//VAO 顶点数组对象（Vertex Array Object）
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectVertices), rectVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	
	//EBO 元素缓存对象（Element Buffer Object，简称EBO）
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);//使用shader program

		/*
		* 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
		* 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
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
	//glViewport(0,0,width,height);  //调整OpenGL视口区域
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //检查Esc键有没有按下
		glfwSetWindowShouldClose(window, true); //设置窗口关闭
}