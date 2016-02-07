#pragma once

class ZL3DMath {
public:
	ZL3DMath();
	XMFLOAT4 FLOAT4xMATRIX(XMFLOAT4 *f, XMMATRIX *m);
	void ZLMatrixRotateAroundAxis(XMMATRIX * pOut, XMFLOAT3 * v1, XMFLOAT3 * v2, float angle);
	XMFLOAT3 RotateAroundAxis(XMFLOAT3 * pos, XMFLOAT3 * v1, XMFLOAT3 * p2, float angle);
	XMFLOAT3 FLOAT3xFLOAT3Cross(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT4 FLOAT4xFLOAT4Cross(XMFLOAT4 a, XMFLOAT4 b);

	friend XMFLOAT2 operator + (XMFLOAT2 a, XMFLOAT2 b);
	friend XMFLOAT2 operator - (XMFLOAT2 a, XMFLOAT2 b);

	friend XMFLOAT3 operator + (XMFLOAT3 a, XMFLOAT3 b);
	friend XMFLOAT3 operator - (XMFLOAT3 a, XMFLOAT3 b);

	friend XMFLOAT4 operator + (XMFLOAT4 a, XMFLOAT4 b);
	friend XMFLOAT4 operator - (XMFLOAT4 a, XMFLOAT4 b);

	friend XMFLOAT3 &operator += (XMFLOAT3 &a, XMFLOAT3 b);
	friend XMFLOAT3 &operator -= (XMFLOAT3 &a, XMFLOAT3 b);

	friend XMFLOAT4 &operator += (XMFLOAT4 &a, XMFLOAT3 b);
	friend XMFLOAT4 &operator -= (XMFLOAT4 &a, XMFLOAT3 b);

	friend XMFLOAT4 &operator += (XMFLOAT4 &a, XMFLOAT4 b);
	friend XMFLOAT4 &operator -= (XMFLOAT4 &a, XMFLOAT4 b);
};