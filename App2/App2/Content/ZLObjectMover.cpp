#include "pch.h"
#include "ZLObjectMover.h"

ZLObjectMover::ZLObjectMover()
{

}

void ZLObjectMover::rotation(ZLMeshObject *obj, float x, float y, float z)
{
	XMMATRIX m = XMMatrixRotationRollPitchYaw(z, x, y);
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::rotation(ZLMeshObject *obj, XMFLOAT3 v)
{
	XMMATRIX m = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&v));
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::rotation(ZLMeshObject *obj, FXMVECTOR v)
{
	XMMATRIX m = XMMatrixRotationRollPitchYawFromVector(v);
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::revolutionAroundAxis(ZLMeshObject * obj, XMFLOAT3 axis, XMFLOAT3 r)
{
	XMMATRIX m;
	m = XMMatrixTranslation(axis.z, axis.x, axis.y);
	m *= XMMatrixRotationRollPitchYaw(r.z, r.x, r.y);
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::translation(ZLMeshObject * obj, float x, float y, float z) {
	XMMATRIX m = XMMatrixTranslation(x, y, z);
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::translation(ZLMeshObject * obj, XMFLOAT3 v)
{
	XMMATRIX m = XMMatrixTranslationFromVector(XMLoadFloat3(&v));
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}

void ZLObjectMover::translation(ZLMeshObject * obj, FXMVECTOR v) {
	XMMATRIX m = XMMatrixTranslationFromVector(v);
	XMStoreFloat4x4(&obj->m_Model, XMMatrixTranspose(m));
}