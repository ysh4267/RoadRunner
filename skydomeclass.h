////////////////////////////////////////////////////////////////////////////////
// Filename: skydomeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYDOMECLASS_H_
#define _SKYDOMECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: SkyDomeClass
////////////////////////////////////////////////////////////////////////////////
class SkyDomeClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};
	// The VertexType for the sky dome only requires position.We generate the colors based on the height of the sky dome.

	struct VertexType
	{
		XMFLOAT3 position;
	};

public:
	SkyDomeClass();
	SkyDomeClass(const SkyDomeClass&);
	~SkyDomeClass();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	// GetApexColorand GetCenterColor are the two helper functions that retrieve the two colors for the sky dome gradient during rendering.

	XMFLOAT4 GetApexColor();
	XMFLOAT4 GetCenterColor();

private:
	bool LoadSkyDomeModel(const WCHAR*);
	void ReleaseSkyDomeModel();

	bool InitializeBuffers(ID3D11Device*);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	XMFLOAT4 m_apexColor, m_centerColor;
};

#endif
