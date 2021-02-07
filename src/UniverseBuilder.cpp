// universeBuilder.cpp : définit le point d'entrée de l'application.
//


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>
#include <glm/common.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <UB/imgui/Utils.hpp>

#include <UB/Graphics/IndexBuffer.hpp>
#include <UB/Graphics/VertexArray.hpp>
#include <UB/Graphics/VertexBuffer.hpp>
#include <UB/Graphics/VertexBufferLayout.hpp>
#include <UB/Graphics/Shader.hpp>


#include <ft2build.h>
#include FT_FREETYPE_H

#include <windows.h>

void left_rotate_by_one(float arr[], int n)
{

	/* Shift operation to the left */
	int temp = arr[0], i;
	for (i = 0; i < n - 1; i++)
		arr[i] = arr[i + 1];
	arr[i] = temp;
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "ERROR while initializing glfw" << std::endl;
		abort;
	}
	glfwWindowHint(GLFW_SAMPLES, 16);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	unsigned int glewInitResult;

	glewInitResult = glewInit();
	std::cout << (GLenum)glewInitResult << std::endl;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);



	
	// Setup Dear ImGui context


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();


	// Setup Platform/Renderer bindings


	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();


	// Setup Dear ImGui style
	//ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	Style();

	auto font_default = io.Fonts->AddFontDefault();


	float locs[24] = {
		-1., -1., -1., // 0
		1.,  -1., -1., // 1
		-1.,  1., -1., // 2
		1.,   1., -1., // 3
		-1., -1.,  1., // 4
		1.,  -1.,  1., // 5
		-1.,  1.,  1., // 6
		1.,   1.,  1.  // 7
	};
	unsigned int indexes[] = {
		0, 1, 2,
		1, 2, 3,
		0, 1, 4,
		1, 4, 5,
		0, 2, 4,
		2, 4, 6,
		1, 3, 5,
		3, 5, 7,
		4, 5, 7,
		4, 7, 6,
		2, 3, 6,
		3, 6, 7
	};



	UB::VertexBuffer vb(locs, 24*sizeof(float));
	UB::VertexArray va;
	UB::IndexBuffer ib(indexes, sizeof(indexes)/sizeof(indexes[0]));
	UB::VertexBufferLayout vbl;

	ib.debugPrint();

	vbl.Push<float>(3);

	va.bind();
	va.addBuffer(vb, vbl);
	va.unbind();

	UB::Shader shader("Shaders/basic.glsl");
	shader.compile();
	INFO({ "Shader successfully compiled" });
	


	float sliderValue(0.5f);

	bool my_tool_active;
	float my_color[4];
	float my_values[50] = { 0.f };


	int frameCount(0);
	double previousTime(0);
	float rotation(180);
	float pos[3] = { 0.f, 0.f, 0.f };
	float scale(1.f);
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 projection = glm::perspective(glm::radians(30.f), 4.0f / 3.0f, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(glm::vec3(-4, -4, 3), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

		glm::mat4 position = glm::translate(glm::mat4(1.f), glm::vec3(pos[0], pos[1], pos[2]));
		glm::mat4 model = position * glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.f), glm::vec3(0.5*scale, 0.5*scale, 0.5*scale));
		glm::mat4 MVPmatrix = projection * view * model;

		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		double currentTime = glfwGetTime();
		frameCount++;
		if (currentTime - previousTime >= 0.2)
		{
			int n = sizeof(my_values) / sizeof(my_values[0]);
			left_rotate_by_one(my_values, n);
			my_values[n-1] = frameCount/0.2f;

			frameCount = 0;
			previousTime = currentTime;
		}
		my_values[0] = 0.f;

		ImGui::Begin("Stats", &my_tool_active);

		ImGui::PlotHistogram("Frame Times", my_values, IM_ARRAYSIZE(my_values));

		char s[50] = "";
		sprintf(s, "%i", (int)my_values[49]);
		ImGui::Text(s);
		ImGui::SliderFloat("rotation", &rotation, 0, 360);
		//ImGui::SliderFloat3("position", pos, 0.f, 1.f);
		ImGui::DragFloat3("position", pos, 0.1f);
		ImGui::DragFloat("scale", &scale, 0.01f, -2, 2);
		ImGui::End();
		

		glUseProgram(0);
		ImGui::Render();


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		va.bind();
		ib.bind();

		shader.bind();
		shader.setUniformMat4f("u_projection", MVPmatrix);
		shader.setUniform3f("u_color", 1.f, 1.f, 1.f);

		GLCall(glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(indexes[0]), GL_UNSIGNED_INT, nullptr));

		va.unbind();
		ib.unbind();
		shader.unbind();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		/*
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		*/
	};
	return 0;
}