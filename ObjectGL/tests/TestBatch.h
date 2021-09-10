#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"


namespace test
{
	class TestBatch : public Test
	{
	public:
		TestBatch();
		~TestBatch();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vb;
		std::unique_ptr <IndexBuffer> index_buffer;
		std::unique_ptr <Shader> shader;
		glm::mat4 proj;
		glm::mat4 view;
		glm::vec3 translationA;
	};
};
