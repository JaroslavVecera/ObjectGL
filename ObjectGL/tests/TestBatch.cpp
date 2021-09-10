#include "TestBatch.h"

#include "Debug.h"
#include "imgui.h"

#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestBatch::TestBatch()
		: translationA(0, 0, 0)
    {

        float positions[] = {
			-50.0f, -50.0f, 0.18f, 0.6f, 0.96f, 1.0f,
			50.0f, -50.0f, 0.18f, 0.6f, 0.96f, 1.0f,
            50.0f, 50.0f, 0.18f, 0.6f, 0.96f, 1.0f,
            -50.0f, 50.0f, 0.18f, 0.6f, 0.96f, 1.0f,

			100.0f, -50.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			150.0f, -50.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            150.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            100.0f, 50.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };
        unsigned int indicies[] = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        shader = std::make_unique<Shader>("res/shaders/Basic.shader");
        vao = std::make_unique<VertexArray>();
        vb = std::make_unique<VertexBuffer>(positions, 8 * 6 * sizeof(float));
        VertexBufferLayout layout;
		layout.AddFloat(2);
		layout.AddFloat(4);
        vao->AddBuffer(*vb, layout);
        index_buffer = std::make_unique<IndexBuffer>(indicies, 12);

		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        shader->Bind();
    }

    TestBatch::~TestBatch()
    {
    }

    void TestBatch::OnUpdate(float deltaTime)
    {
    }

    void TestBatch::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        Renderer renderer;
        renderer.Clear();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
        glm::mat4 mvp = proj * view * model;
        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*vao, *index_buffer, *shader);
    }

    void TestBatch::OnImGuiRender()
    {
		ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
        ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    }
};
