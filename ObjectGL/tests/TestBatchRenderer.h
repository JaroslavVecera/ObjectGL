#pragma once

#include "Test.h"
#include "Math.h"
#include "BatchRenderer.h"
#include <array>


namespace test
{
	class TestBatchRenderer : public Test
	{
	public:
		TestBatchRenderer();
		~TestBatchRenderer();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		BatchRenderer renderer;
		glm::vec2 trianglePointA;
		glm::vec2 trianglePointB;
		glm::vec2 trianglePointC;

		std::array<ColorVertex, 4> CreateColorQuad(float x, float y, float size, Vec4 color);
	};
};
