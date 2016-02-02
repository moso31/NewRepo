#include "pch.h"
#include "ZLEasyBuilder.h"

ZLEasyBuilder::ZLEasyBuilder()
{
}

void ZLEasyBuilder::CreateCube(ZLMeshObject *obj, float width)
{
	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT3(-width, -width, -width), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-width, -width,  width), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-width,  width, -width), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-width,  width,  width), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(width, -width, -width), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(width, -width,  width), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(width,  width, -width), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(width,  width,  width), XMFLOAT3(1.0f, 1.0f, 1.0f) },
	};

	for (int i = 0; i < 8; i++)
		obj->m_Verties.push_back(cubeVertices[i]);

	unsigned short cubeIndices[] =
	{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};
	for (int i = 0; i < 36; i++)
		obj->m_Indies.push_back(cubeIndices[i]);

	obj->SetVBIB();
}


void ZLEasyBuilder::CreateHands(ZLMeshObject* objLeft, ZLMeshObject* objRight) {
	this->CreateHand(objLeft, 1.0f, 0.0f, 0.0f, 0.05f);
	this->CreateHand(objRight, -1.0f, 0.0f, 0.0f, 0.05f);
}

void ZLEasyBuilder::CreateHand(ZLMeshObject* obj, float x, float y, float z, float width) {

	VertexPositionColor cubeVertices[] =
	{
		{ XMFLOAT3(-width + x, -width + y, -width + z), XMFLOAT3(0.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(-width + x, -width + y,  width + z), XMFLOAT3(0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-width + x,  width + y, -width + z), XMFLOAT3(0.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(-width + x,  width + y,  width + z), XMFLOAT3(0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(width + x, -width + y, -width + z), XMFLOAT3(1.0f, 0.0f, 0.0f) },
		{ XMFLOAT3(width + x, -width + y,  width + z), XMFLOAT3(1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(width + x,  width + y, -width + z), XMFLOAT3(1.0f, 1.0f, 0.0f) },
		{ XMFLOAT3(width + x,  width + y,  width + z), XMFLOAT3(1.0f, 1.0f, 1.0f) },
	};

	for (int i = 0; i < 8; i++)
		obj->m_Verties.push_back(cubeVertices[i]);

	unsigned short cubeIndices[] =
	{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};
	for (int i = 0; i < 36; i++)
		obj->m_Indies.push_back(cubeIndices[i]);

	obj->SetVBIB();
}
