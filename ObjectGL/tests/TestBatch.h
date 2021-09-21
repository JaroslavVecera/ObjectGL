#pragma once

#include "Test.h"

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "array"
#include "Math.h"
#include "Vertex.h"


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
		std::unique_ptr<VertexArray> colorVao;
		std::unique_ptr<VertexArray> textureVao;
		std::unique_ptr<VertexBuffer> colorVb;
		std::unique_ptr<VertexBuffer> textureVb;
		std::unique_ptr <IndexBuffer> index_buffer;
		std::unique_ptr <Shader> colorShader;
		std::unique_ptr <Shader> textureShader;
		glm::mat4 proj;
		std::unique_ptr<Texture> texture;
		glm::vec3 translationA;
		std::array<ColorVertex, 4> CreateColorQuad(float x, float y, float size);
		std::array<TextureVertex, 4> CreateTextureQuad(float x, float y, float size);
	};
};
