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
        unsigned int indicies[] = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		colorShader = std::make_unique<Shader>("res/shaders/Color.shader");
		textureShader = std::make_unique<Shader>("res/shaders/Complex.shader");
		colorVao = std::make_unique<VertexArray>();
		textureVao = std::make_unique<VertexArray>();
		colorVb = std::make_unique<VertexBuffer>(1000, sizeof(ColorVertex));
		textureVb = std::make_unique<VertexBuffer>(1000, sizeof(TextureVertex));
        VertexBufferLayout colorLayout;
		colorLayout.AddFloat(2);
		colorLayout.AddFloat(4);
		VertexBufferLayout textureLayout;
		textureLayout.AddFloat(2);
		textureLayout.AddFloat(2);

		colorVao->AddBuffer(*colorVb, colorLayout);
		textureVao->AddBuffer(*textureVb, textureLayout);
        index_buffer = std::make_unique<IndexBuffer>(indicies,12);

		proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.f, -1.0f, 1.0f);
		colorShader->Bind();
		textureShader->Bind();
		texture = std::make_unique<Texture>("res/textures/gold-dollar.png");
		textureShader->SetUniform1f("u_Texture", 0);
    }

    TestBatch::~TestBatch()
    {
    }

    void TestBatch::OnUpdate(float deltaTime)
    {
	}

    std::array<ColorVertex, 4> TestBatch::CreateColorQuad(float x, float y, float size) {
        ColorVertex v0;
        v0.position = { x, y + size };
        v0.color = { 1.0f, 1.0f, 0.0f, 1.0f };

		ColorVertex v1;
		v1.position = { x + size, y + size };
		v1.color = { 1.0f, 1.0f, 0.0f, 1.0f };

		ColorVertex v2;
		v2.position = { x + size, y };
		v2.color = { 1.0f, 1.0f, 0.0f, 1.0f };

		ColorVertex v3;
		v3.position = { x, y};
		v3.color = { 1.0f, 1.0f, 0.0f, 1.0f };

		return { v0, v1, v2, v3 };
	}

	std::array<TextureVertex, 4> TestBatch::CreateTextureQuad(float x, float y, float size) {
		TextureVertex v0;
		v0.position = { x, y + size };
		v0.texturePosition = { 0.0f, 1.0f };

		TextureVertex v1;
		v1.position = { x + size, y + size };
		v1.texturePosition = { 1.0f, 1.0f };

		TextureVertex v2;
		v2.position = { x + size, y };
		v2.texturePosition = { 1.0f, 0.0f };

		TextureVertex v3;
		v3.position = { x, y };
		v3.texturePosition = { 0.0f, 0.0f };

		return { v0, v1, v2, v3 };
	}

    void TestBatch::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.5f, 0.0f));
        Renderer renderer;
        renderer.Clear();

		colorVb->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
		glm::mat4 mvp = proj * model;

		ColorVertex colorVertices[8];
		auto q0 = CreateColorQuad(50.0f, 50.0f, 50.0f);
		auto q1 = CreateColorQuad(150.0f, 50.0f, 58.0f);
		memcpy(colorVertices, &q0, q0.size() * sizeof(ColorVertex));
		memcpy(colorVertices + q0.size(), &q1, q1.size() * sizeof(ColorVertex));
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colorVertices), colorVertices);

		colorShader->Bind();
        colorShader->SetUniformMat4f("u_MVP", mvp);
		renderer.Draw(*colorVao, *index_buffer, *colorShader);

		textureVb->Bind();
		TextureVertex textureVertices[4];
		auto q3 = CreateTextureQuad(300.0f, 50.0f, 70.0f);
		memcpy(textureVertices, &q3, q3.size() * sizeof(TextureVertex));
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(textureVertices), textureVertices);

		textureShader->Bind();
		textureShader->SetUniformMat4f("u_MVP", mvp);
		textureShader->SetUniform1f("u_Texture", 0);
		texture->Bind();
		renderer.Draw(*textureVao, *index_buffer, *textureShader);
    }

    void TestBatch::OnImGuiRender()
    {
		ImGui::SliderFloat2("Translation", &translationA.x, 0.0f, 960.0f);
        ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
    }
};
