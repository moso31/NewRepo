#pragma once
#include "ZLMeshObject.h"

class ZLEasyBuilder {
public:
	ZLEasyBuilder();
	void CreateCube(ZLMeshObject* obj, float width);
	void CreateHands(ZLMeshObject* objLeft, ZLMeshObject* objRight);
	void CreateHand(ZLMeshObject* obj, float x, float y, float z, float width);
	~ZLEasyBuilder() {
	}

private:
};