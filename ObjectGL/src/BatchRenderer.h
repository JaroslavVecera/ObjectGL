#pragma once

#include "Vertex.h"
#include <vector>
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

struct BatchRendererData {
	unsigned int maxBatchVertexCount = 0;
	std::unique_ptr<VertexArray> colorVao;
	std::unique_ptr<VertexArray> textureVao;
	std::unique_ptr<VertexBuffer> colorVb;
	std::unique_ptr<VertexBuffer> textureVb;
	std::unique_ptr<IndexBuffer> colorIb;
	unsigned int* colorIndices;
	std::unique_ptr <Shader> colorShader;
	std::unique_ptr <Shader> textureShader;
	glm::mat4 proj;
	ColorVertex* colorVertices;
	unsigned int colorVertexCount = 0;
	unsigned int maxBatchIndicesCount = 0;
	unsigned int colorIndexCount = 0;
};

class BatchRenderer {
private:
	BatchRendererData* data;
	Renderer* renderer;
	std::pair<float, float> viewSize;

	void FlushColor();
	void Init(unsigned int maxBatchVertexCount);
	void EnableBlending();
	void InitColorRendering();
	void InitTextureRendering();
	void ChangeProjection(std::pair<float, float> size);
public:
	BatchRenderer();
	~BatchRenderer();

	std::pair<float, float> getViewSize();
	void setViewSize(std::pair<float, float> size);
	void Render();
	void AddVertices(ColorVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount);
	void AddVertices(TextureVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, unsigned int textureID);
};