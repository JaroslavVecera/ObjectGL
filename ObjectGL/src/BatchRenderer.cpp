#include "BatchRenderer.h"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


void BatchRenderer::FlushColor()
{
	data->colorIb->Bind();
	GLCall(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data->colorIndexCount * sizeof(unsigned int), data->colorIndices));
	data->colorVb->Bind();
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, data->colorVertexCount * sizeof(ColorVertex), data->colorVertices));

	data->colorShader->Bind();
	data->colorShader->SetUniformMat4f("u_MVP", data->proj);
	renderer->Draw(*(data->colorVao), *(data->colorIb), *(data->colorShader), data->colorIndexCount);

	data->colorVertexCount = 0;
	data->colorIndexCount = 0;
}

void BatchRenderer::Init(unsigned int maxBatchVertexCount)
{
	data = new BatchRendererData();
	data->maxBatchVertexCount = maxBatchVertexCount;
	data->maxBatchIndicesCount = 3 * maxBatchVertexCount;
	renderer = new Renderer();

	EnableBlending();
	InitColorRendering();
	setViewSize(std::pair<float, float>(960.0f, 540.0f));

	renderer->Clear();
}

void BatchRenderer::EnableBlending()
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void BatchRenderer::InitColorRendering()
{
	data->colorShader = std::make_unique<Shader>("res/shaders/Color.shader");
	data->colorVao = std::make_unique<VertexArray>();
	data->colorVb = std::make_unique<VertexBuffer>(data->maxBatchVertexCount, sizeof(ColorVertex));
	data->colorVertices = new ColorVertex[data->maxBatchVertexCount];
	data->colorIndices = new unsigned int[data->maxBatchIndicesCount];
	data->colorIb = std::make_unique<IndexBuffer>(data->maxBatchIndicesCount);
	VertexBufferLayout colorLayout;
	colorLayout.AddFloat(2);
	colorLayout.AddFloat(4);
	data->colorVao->AddBuffer(*(data->colorVb), colorLayout);
}

void BatchRenderer::InitTextureRendering()
{
	data->textureShader = std::make_unique<Shader>("res/shaders/Complex.shader");
	data->textureVao = std::make_unique<VertexArray>();
	data->textureVb = std::make_unique<VertexBuffer>(data->maxBatchVertexCount, sizeof(TextureVertex));
	VertexBufferLayout textureLayout;
	textureLayout.AddFloat(2);
	textureLayout.AddFloat(2);
	data->textureVao->AddBuffer(*data->textureVb, textureLayout);
}

BatchRenderer::BatchRenderer()
{
	Init(1000);
}

BatchRenderer::~BatchRenderer()
{
	delete renderer;
	delete data->colorVertices;
	delete data->colorIndices;
	delete data;
}

std::pair<float, float> BatchRenderer::getViewSize()
{
	return viewSize;
}

void BatchRenderer::setViewSize(std::pair<float, float> size)
{
	viewSize = size;
	ChangeProjection(size);
}

void BatchRenderer::Render()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.5f, 0.0f));
	renderer->Clear();
	FlushColor();
}

void BatchRenderer::ChangeProjection(std::pair<float, float> size)
{
    data->proj = glm::ortho(0.0f,size.first, 0.0f, size.second, -1.0f, 1.0f);
}

void BatchRenderer::AddVertices(ColorVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount)
{
	if (data->colorVertexCount + vertexCount > data->maxBatchVertexCount || data->colorIndexCount + indexCount > data->maxBatchIndicesCount)
		FlushColor();
	unsigned int indexOffset = data->colorVertexCount;
	memcpy(data->colorVertices + data->colorVertexCount, vertices, vertexCount * sizeof(ColorVertex));
	for (int i = 0; i < indexCount; i++)
		data->colorIndices[data->colorIndexCount + i] = indices[i] + data->colorVertexCount;
	data->colorIndexCount += indexCount;
	data->colorVertexCount += vertexCount;
}

void BatchRenderer::AddVertices(TextureVertex* vertices, unsigned int vertexCount, unsigned int* indices, unsigned int indexCount, unsigned int textureID)
{

}

