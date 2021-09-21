#pragma once

struct Vec2 {
	float x;
	float y;
};

struct Vec3 {
	float x;
	float y;
	float z;
};

struct Vec4 {
	float x;
	float y;
	float z;
	float u;
};

struct ColorVertex {
	Vec2 position;
	Vec4 color;
};

struct TextureVertex {
	Vec2 position;
	Vec2 texturePosition;
};
