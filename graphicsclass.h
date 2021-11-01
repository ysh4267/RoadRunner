////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
private:
	struct CarModelInfo
	{
		ModelClass* m_carModel;
		XMFLOAT2 worldPosition;
		XMMATRIX worldMatrix;
		XMFLOAT2 maxSize;
		XMFLOAT2 minSize;
		XMFLOAT2 maxPosSize;
		XMFLOAT2 minPosSize;
	};
	
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Frame(int, int, float);
	bool Frame(int, int);

public:
	void PressLeftButton();
	void PressRightButton();
	void PressBackButton();
	void PressFowardButton();
	void PressSpaceButton();
	XMFLOAT3 XMFLOAT3LERP(XMFLOAT3, XMFLOAT3, float);
	bool CheckCubeIntersection(XMFLOAT2*, XMFLOAT2*, XMFLOAT2*, XMFLOAT2*);
	bool IsCollision();
	XMFLOAT2 XMFLOAT2SUM(XMFLOAT2, XMFLOAT2);

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* playerModel;
	ModelClass* mapModel;
	ModelClass* objectModel;
	CarModelInfo carModel[12];

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;

	XMFLOAT3 playerSystemPos;
	XMFLOAT3 playerBackPos;
	XMFLOAT3 playerPos;

	XMFLOAT2 playerMinSize;
	XMFLOAT2 playerMaxSize;
};

#endif