#include "TestBatchRenderer.h"

#include "Debug.h"
#include "imgui.h"

namespace test
{
	TestBatchRenderer::TestBatchRenderer() :
		trianglePointA(250.0, 0.0),
		trianglePointB(500.0, 0.0),
		trianglePointC(370.0, 100.0)
	{
		
	}


	TestBatchRenderer::~TestBatchRenderer()
	{

	}


	void TestBatchRenderer::OnUpdate(float deltaTime)
	{

	}


	void TestBatchRenderer::OnRender()
	{
		auto q0 = CreateColorQuad(150, 150, 100, { 1.0, 0.5, 0.0, 1.0 });
		auto q1 = CreateColorQuad(250, 450, 200, { 1.0, 0.0, 0.5, 1.0 });
		unsigned int qIndices[] = { 0, 1, 2, 2, 3, 0 };
		renderer.AddVertices(q0.data(), 4, qIndices, 6);
		renderer.AddVertices(q1.data(), 4, qIndices, 6);

		std::array<ColorVertex, 3> triangle;
		ColorVertex a;
		a.position.x = trianglePointA[0];
		a.position.y = trianglePointA[1];
		a.color = { 1.0, 1.0, 1.0, 1.0 };

		ColorVertex b;
		b.position.x = trianglePointB[0];
		b.position.y = trianglePointB[1];
		b.color = { 1.0, 1.0, 1.0, 1.0 };

		ColorVertex c;
		c.position.x = trianglePointC[0];
		c.position.y = trianglePointC[1];
		c.color = { 1.0, 1.0, 1.0, 1.0 };
		
		triangle[0] = a;
		triangle[1] = b;
		triangle[2] = c;

		unsigned int tIndices[] = { 0, 1, 2 };

		renderer.AddVertices(triangle.data(), 3, tIndices, 3);

		renderer.Render();
	}


	void TestBatchRenderer::OnImGuiRender()
	{
		ImGui::Text("%.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate);
		ImGui::SliderFloat2("Point A", &trianglePointA.x, 0.0f, 960.0f);
		ImGui::SliderFloat2("Point B", &trianglePointB.x, 0.0f, 960.0f);
		ImGui::SliderFloat2("Point C", &trianglePointC.x, 0.0f, 960.0f);
	}

	std::array<ColorVertex, 4> TestBatchRenderer::CreateColorQuad(float x, float y, float size, Vec4 color) {
		ColorVertex v0;
		v0.position = { x, y + size };
		v0.color = color;

		ColorVertex v1;
		v1.position = { x + size, y + size };
		v1.color = color;

		ColorVertex v2;
		v2.position = { x + size, y };
		v2.color = color;

		ColorVertex v3;
		v3.position = { x, y };
		v3.color = color;

		return { v0, v1, v2, v3 };
	}

};
