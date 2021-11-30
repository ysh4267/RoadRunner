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
#include "skydomeclass.h"
#include "skydomeshaderclass.h"

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
		XMFLOAT2 flyingPosition;
		XMMATRIX worldMatrix;
		XMFLOAT2 maxSize;
		XMFLOAT2 minSize;
		XMFLOAT2 maxPosSize;
		XMFLOAT2 minPosSize;
		bool isFlying;
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
	void InitCarObjectPos();
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	ModelClass* playerModel;
	ModelClass* mapModel;
	ModelClass* mapModel2;
	ModelClass* objectModel;
	CarModelInfo carModel[12];

	SkyDomeClass* skyDome;
	SkyDomeShaderClass* skyDomeShader;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;

	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	BitmapClass* fuelImg;
	BitmapClass* whiteBox;
	BitmapClass* redBox;

	TextClass* m_Text;

	XMFLOAT3 playerSystemPos;
	XMFLOAT3 playerBackPos;
	XMFLOAT3 playerPos;

	XMFLOAT2 playerMinSize;
	XMFLOAT2 playerMaxSize;

	float mapZpos1, mapZpos2;
	float fuelGauge;
	bool usingBooster;
	float mapSpeed = 0.5f;
	float carObjectSpeed = 0.2f;
	float exSpeed = 0.0f;
	float score = 0.0f;
	int objectNum = 0;
	int life = 3;

	float invincibility = 0;
};

#endif