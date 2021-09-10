#include "TestTexture.h"

#include "Debug.h"
#include "imgui.h"

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestTexture::TestTexture()
		: translationA(200, 200, 0), translationB(400, 200, 0)
    {

        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,
            50.0f, -50.0f, 1.0f, 0.0f,
            50.0f, 50.0f, 1.0f, 1.0f,
            -50.0f, 50.0f, 0.0f, 1.0f,
        };
        unsigned int indicies[] = { 0, 1, 2, 2, 3, 0 };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        shader = std::make_unique<Shader>("res/shaders/Simple.shader");
        vao = std::make_unique<VertexArray>();
        vb = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
		layout.AddFloat(2);
		layout.AddFloat(2);
        vao->AddBuffer(*vb, layout);
        index_buffer = std::make_unique<IndexBuffer>(indicies, 6);

		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        shader->Bind();
        shader->SetUniform4f("u_Color", 50.0f, 50.0f, 50.0f, 50.0f);
        texture = std::make_unique<Texture>("res/textures/gold-dollar.png");
        shader->SetUniform1f("u_Texture", 0);
    }

    TestTexture::~TestTexture()
    {
    }

    void TestTexture::OnUpdate(float deltaTime)
    {
    }

    void TestTexture::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        Renderer renderer;

        texture->Bind();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*vao, *index_buffer, *shader);

		model = glm::translate(glm::mat4(1.0f), translationB);
		mvp = proj * view * model;
		shader->Bind();
		shader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*vao, *index_buffer, *shader);
    }

    void TestTexture::OnImGuiRender()
    {
		ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
        ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    }
};
