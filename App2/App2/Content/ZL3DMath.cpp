#include "pch.h"
#include "ZL3DMath.h"

using namespace DirectX;

ZL3DMath::ZL3DMath()
{
}

XMFLOAT4 ZL3DMath::FLOAT4xMATRIX(XMFLOAT4 *f, XMMATRIX *m)
{
	XMFLOAT4 ans;

	XMFLOAT4 m1, m2, m3;
	XMStoreFloat4(&m1, m->r[0]);
	XMStoreFloat4(&m2, m->r[1]);
	XMStoreFloat4(&m3, m->r[2]);

	ans.x = f->x * m1.x + f->y * m1.y + f->z * m1.z;
	ans.y = f->x * m2.x + f->y * m2.y + f->z * m2.z;
	ans.z = f->x * m3.x + f->y * m3.y + f->z * m3.z;

	return ans;
}

void ZL3DMath::ZLMatrixRotateAroundAxis(XMMATRIX *pOut, XMFLOAT3 *v1, XMFLOAT3 *v2, float angle)
{
	float a = v2->x - v1->x;
	float b = v2->y - v1->y;
	float c = v2->z - v1->z;

	float x = v1->x;
	float y = v1->y;
	float z = v1->z;

	float aa = a * a;
	float ab = a * b;
	float ac = a * c;
	float bb = b * b;
	float bc = b * c;
	float cc = c * c;

	float xa = x * a;
	float xb = x * b;
	float xc = x * c;
	float ya = y * a;
	float yb = y * b;
	float yc = y * c;
	float za = z * a;
	float zb = z * b;
	float zc = z * c;

	XMFLOAT4 f[4];

	f[0].x = aa + (bb + cc) * cosf(angle);
	f[0].y = ab * (1 - cosf(angle)) - c * sinf(angle);
	f[0].z = ac * (1 - cosf(angle)) + b * sinf(angle);
	f[0].w = (x * (bb + cc) - a * (yb + zc)) * (1 - cosf(angle)) + (yc - zb) * sinf(angle);

	f[1].x = ab * (1 - cosf(angle)) + c * sinf(angle);
	f[1].y = bb + (aa + cc) * cosf(angle);
	f[1].z = bc * (1 - cosf(angle)) - a * sinf(angle);
	f[1].w = (y * (aa + cc) - b * (xa + zc)) * (1 - cosf(angle)) + (za - xc) * sinf(angle);

	f[2].x = ac * (1 - cosf(angle)) - b * sinf(angle);
	f[2].y = bc * (1 - cosf(angle)) + a * sinf(angle);
	f[2].z = cc + (aa + bb) * cosf(angle);
	f[2].w = (z * (aa + bb) - c * (xa + yb)) * (1 - cosf(angle)) + (xb - ya) * sinf(angle);

	f[3] = { 0, 0, 0, 1 };

	for (int i = 0; i < 4; i++)
		pOut->r[i] = XMLoadFloat4(&f[i]);
}

XMFLOAT3 ZL3DMath::RotateAroundAxis(XMFLOAT3 *pos, XMFLOAT3 *v1, XMFLOAT3 *v2, float angle)
{
	//返回pos沿向量v1v2旋转angle度后的坐标。
	XMFLOAT4 temp = { pos->x, pos->y, pos->z, 0.0f };
	XMMATRIX m;
	ZLMatrixRotateAroundAxis(&m, v1, v2, angle);
	temp = FLOAT4xMATRIX(&temp, &m);
	return XMFLOAT3(temp.x, temp.y, temp.z);
}

XMFLOAT3 ZL3DMath::FLOAT3xFLOAT3Cross(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
		);
}

XMFLOAT4 ZL3DMath::FLOAT4xFLOAT4Cross(XMFLOAT4 a, XMFLOAT4 b)
{
	return XMFLOAT4(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0.0f
		);
}

XMFLOAT2 operator+(XMFLOAT2 a, XMFLOAT2 b)
{
	return XMFLOAT2(
		a.x + b.x,
		a.y + b.y
		);
}

XMFLOAT2 operator-(XMFLOAT2 a, XMFLOAT2 b)
{
	return XMFLOAT2(
		a.x - b.x,
		a.y - b.y
		);
}

XMFLOAT3 operator+(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
		);
}

XMFLOAT3 operator-(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
		);
}

XMFLOAT4 operator+(XMFLOAT4 a, XMFLOAT4 b)
{
	return XMFLOAT4(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z,
		a.w + b.w
		);
}

XMFLOAT4 operator-(XMFLOAT4 a, XMFLOAT4 b)
{
	return XMFLOAT4(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z,
		a.w - b.w
		);
}

XMFLOAT3 & operator+=(XMFLOAT3 &a, XMFLOAT3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

XMFLOAT3 & operator-=(XMFLOAT3 &a, XMFLOAT3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

XMFLOAT4 & operator+=(XMFLOAT4 &a, XMFLOAT4 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	a.w += b.w;
	return a;
}

XMFLOAT4 & operator-=(XMFLOAT4 &a, XMFLOAT4 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	a.w += b.w;
	return a;
}

XMFLOAT4 & operator+=(XMFLOAT4 &a, XMFLOAT3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	a.w;
	return a;
}

XMFLOAT4 & operator-=(XMFLOAT4 &a, XMFLOAT3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	a.w;
	return a;
}
