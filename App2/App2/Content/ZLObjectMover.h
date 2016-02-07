#pragma once
#include "ZLMeshObject.h"

class ZLObjectMover {
public:
	ZLObjectMover();
	~ZLObjectMover()
	{

	}
	void rotation(ZLMeshObject *obj, float x, float y, float z);
	void rotation(ZLMeshObject *obj, XMFLOAT3 v);
	void rotation(ZLMeshObject *obj, FXMVECTOR v);

	void revolutionAroundAxis(ZLMeshObject * obj, XMFLOAT3 t, XMFLOAT3 r);

	void translation(ZLMeshObject *obj, float x, float y, float z);
	void translation(ZLMeshObject *obj, XMFLOAT3 v);
	void translation(ZLMeshObject *obj, FXMVECTOR v);

private:
	ZLMeshObject *m_obj;
};