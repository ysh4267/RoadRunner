////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	playerModel = 0;
	mapModel = 0;
	mapModel2 = 0;
	objectModel = 0;
	for (int i = 0; i < 12; i++)
		carModel[i].m_carModel = 0;

	skyDome = 0;
	skyDomeShader = 0;

	m_LightShader = 0;
	m_Light = 0;

	m_TextureShader = 0;
	m_Bitmap = 0;

	fuelImg = 0;
	whiteBox = 0;
	redBox = 0;

	m_Text = 0;
	playerPos = XMFLOAT3(2.2f, 0, 2.0f);
	playerSystemPos = XMFLOAT3(2.2f, 0, 0);
	playerBackPos = XMFLOAT3(2.2f, 0, 0);

	playerMaxSize = XMFLOAT2(2.0f, 3.0f);
	playerMinSize = XMFLOAT2(-2.0f, -3.0f);

	mapZpos1 = 0.0f;
	mapZpos2 = 100.0f;
	fuelGauge = 0.0f;
	exSpeed = 0.0f;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	XMMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// Create the player model object.
	playerModel = new ModelClass;
	if (!playerModel)
	{
		return false;
	}

	// Initialize the player model object.
	result = playerModel->Initialize(m_D3D->GetDevice(), L"./data/car.obj", L"./data/Car_08.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the player model object.", L"Error", MB_OK);
		return false;
	}

	// Create the map model object.
	mapModel = new ModelClass;
	if (!mapModel)
	{
		return false;
	}
	// Create the map model object.
	mapModel2 = new ModelClass;
	if (!mapModel2)
	{
		return false;
	}

	// Initialize the map model object.
	result = mapModel->Initialize(m_D3D->GetDevice(), L"./data/road.obj", L"./data/road.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the map model object.", L"Error", MB_OK);
		return false;
	}
	// Initialize the map model object.
	result = mapModel2->Initialize(m_D3D->GetDevice(), L"./data/road.obj", L"./data/road.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the map model object.", L"Error", MB_OK);
		return false;
	}

	for (int i = 0; i < 12; i++)
	{
		// Create the car model object.
		carModel[i].m_carModel = new ModelClass;
		if (!playerModel)
		{
			return false;
		}

		XMFLOAT2 carMaxSize = XMFLOAT2(2.0f, 2.5f);
		XMFLOAT2 carMinSize = XMFLOAT2(-2.0f, -2.5f);
		XMFLOAT2 truckMaxSize = XMFLOAT2(2.0f, 4.5f);
		XMFLOAT2 truckMinSize = XMFLOAT2(-2.0f, -4.5f);
		XMFLOAT2 busMaxSize = XMFLOAT2(2.0f, 7.0f);
		XMFLOAT2 busMinSize = XMFLOAT2(-2.0f, -7.0f);

		// Initialize the car model object.
		switch (i)
		{
		case 0:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car.obj", L"./data/Car_07.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 1:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car.obj", L"./data/Car_08.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 2:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car.obj", L"./data/Car_09.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 3:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car2.obj", L"./data/Car_01.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 4:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car2.obj", L"./data/Car_02.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 5:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/car2.obj", L"./data/Car_03.dds");
			carModel[i].maxSize = carMaxSize;
			carModel[i].minSize = carMinSize;
			break;
		case 6:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/truck.obj", L"./data/Car_04.dds");
			carModel[i].maxSize = truckMaxSize;
			carModel[i].minSize = truckMinSize;
			break;
		case 7:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/truck.obj", L"./data/Car_05.dds");
			carModel[i].maxSize = truckMaxSize;
			carModel[i].minSize = truckMinSize;
			break;
		case 8:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/truck.obj", L"./data/Car_06.dds");
			carModel[i].maxSize = truckMaxSize;
			carModel[i].minSize = truckMinSize;
			break;
		case 9:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/bus.obj", L"./data/Car_10.dds");
			carModel[i].maxSize = busMaxSize;
			carModel[i].minSize = busMinSize;
			break;
		case 10:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/bus.obj", L"./data/Car_11.dds");
			carModel[i].maxSize = busMaxSize;
			carModel[i].minSize = busMinSize;
			break;
		case 11:
			result = carModel[i].m_carModel->Initialize(m_D3D->GetDevice(), L"./data/bus.obj", L"./data/Car_12.dds");
			carModel[i].maxSize = busMaxSize;
			carModel[i].minSize = busMinSize;
			break;
		default:
			break;
		}
		if (!result)
		{
			MessageBox(hwnd, L"Could not initialize the car model object.", L"Error", MB_OK);
			return false;
		}

	}

	skyDome = new SkyDomeClass;
	if (!skyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = skyDome->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	skyDomeShader = new SkyDomeShaderClass;
	if (!skyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = skyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	//	m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetDiffuseColor(0.5f, 0.5f, 0.5f, 1.0f);
	//	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	//	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	//	m_Light->SetDirection(1.0f, 0.0f, 0.0f);
	m_Light->SetDirection(1.0f, -1.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/bgDarkGreen.dds", 800, 600);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	fuelImg = new BitmapClass;
	if (!fuelImg)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = fuelImg->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/fuel.dds", 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	redBox = new BitmapClass;
	if (!redBox)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = redBox->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/red.dds", 300, 30);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	whiteBox = new BitmapClass;
	if (!whiteBox)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = whiteBox->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/white.dds", 500, 30);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}


	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(playerPos.x + 0.0f, playerPos.y + 20.0f, playerPos.z + -13.0f);
	m_Camera->SetRotation(45.0f, 0.0f, 0.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	InitCarObjectPos();

	std::srand(static_cast<unsigned int>(std::time(0)));

	return true;
}

void GraphicsClass::PressLeftButton() {
	if (abs(playerPos.x - playerSystemPos.x) > 0.6f) return;
	if (playerSystemPos.x < -7.0) return;

	playerBackPos = playerSystemPos;
	playerSystemPos.x += -5.0f;
}

void GraphicsClass::PressRightButton() {
	if (abs(playerPos.x - playerSystemPos.x) > 0.6f) return;
	if (playerSystemPos.x > 7.0) return;

	playerBackPos = playerSystemPos;
	playerSystemPos.x += 5.0f;
}

void GraphicsClass::PressSpaceButton() {
	if (fuelGauge < 499) return;
	usingBooster = true;
}

void GraphicsClass::PressFowardButton() {
	//if (abs(playerPos.z - playerSystemPos.z) > 0.01f) return;
	//playerBackPos = playerSystemPos;
	//playerSystemPos.z += 1.0f;
}

void GraphicsClass::PressBackButton() {
	//if (abs(playerPos.z - playerSystemPos.z) > 0.01f) return;
	//playerBackPos = playerSystemPos;
	//playerSystemPos.z -= 1.0f;
}

bool GraphicsClass::CheckCubeIntersection(XMFLOAT2* vMin1, XMFLOAT2* vMax1, XMFLOAT2* vMin2, XMFLOAT2* vMax2)
{
	if (vMin1->x <= vMax2->x && vMax1->x >= vMin2->x &&
		vMin1->y <= vMax2->y && vMax1->y >= vMin2->y)
		return true;
	return false;
}

bool GraphicsClass::IsCollision() {
	for (auto object : carModel) {
		if (CheckCubeIntersection(new XMFLOAT2(playerPos.x - 1.0f, playerPos.z - 2.5f), new XMFLOAT2(playerPos.x + 1.0f, playerPos.z + 2.5f), &object.minPosSize, &object.maxPosSize)) {
			return true;
		}
	}

	return false;
}

XMFLOAT2 GraphicsClass::XMFLOAT2SUM(XMFLOAT2 aF, XMFLOAT2 bF) {
	return XMFLOAT2(aF.x + bF.x, aF.y + bF.y);
}

void GraphicsClass::Shutdown()
{
	// Release the player model object.
	if (playerModel)
	{
		playerModel->Shutdown();
		delete playerModel;
		playerModel = 0;
	}

	// Release the map model object.
	if (mapModel)
	{
		mapModel->Shutdown();
		delete mapModel;
		mapModel = 0;
	}
	// Release the map model object.
	if (mapModel2)
	{
		mapModel2->Shutdown();
		delete mapModel2;
		mapModel2 = 0;
	}

	for (int i = 0; i < 12; i++)
	{
		// Release the map model object.
		if (carModel[i].m_carModel)
		{
			carModel[i].m_carModel->Shutdown();
			delete carModel[i].m_carModel;
			carModel[i].m_carModel = 0;
		}
		carModel[i].m_carModel = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (skyDome)
	{
		skyDome->Shutdown();
		delete skyDome;
		skyDome = 0;
	}

	// Release the sky dome object.
	if (skyDomeShader)
	{
		skyDomeShader->Shutdown();
		delete skyDomeShader;
		skyDomeShader = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the bitmap object.
	if (fuelImg)
	{
		fuelImg->Shutdown();
		delete fuelImg;
		fuelImg = 0;
	}

	// Release the bitmap object.
	if (redBox)
	{
		redBox->Shutdown();
		delete redBox;
		redBox = 0;
	}

	// Release the bitmap object.
	if (whiteBox)
	{
		whiteBox->Shutdown();
		delete whiteBox;
		whiteBox = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.
//	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}

bool GraphicsClass::Frame(int mouseX, int mouseY)
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	//// Set the location of the mouse.
	//result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	//if (!result)
	//{
	//	return false;
	//}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

XMFLOAT3 GraphicsClass::XMFLOAT3LERP(XMFLOAT3 movF, XMFLOAT3 targetF, float t) {
	return XMFLOAT3(movF.x * (1.0f - t) + (targetF.x * t), movF.y * (1.0f - t) + (targetF.y * t), movF.z * (1.0f - t) + (targetF.z * t));
}

void GraphicsClass::InitCarObjectPos() {
	//-7.8, -2.8, 2.2, 7.2
	for (int i = 0; i < 12; i++)
	{
		carModel[i].worldPosition.x = -7.8f;
		carModel[i].worldPosition.y = -50.0f;
	}

	carModel[0].worldPosition.x = -7.8f;
	carModel[0].worldPosition.y = 4.0f;
	carModel[1].worldPosition.x = -2.8f;
	carModel[1].worldPosition.y = 125.0f;
	carModel[2].worldPosition.x = 7.2f;
	carModel[2].worldPosition.y = 91.0f;
	carModel[3].worldPosition.x = 2.2f;
	carModel[3].worldPosition.y = 104.0f;
	carModel[4].worldPosition.x = -2.8f;
	carModel[4].worldPosition.y = 76.0f;
	carModel[5].worldPosition.x = 2.2f;
	carModel[5].worldPosition.y = 29.0f;
	carModel[6].worldPosition.x = -7.8f;
	carModel[6].worldPosition.y = 59.0f;
	carModel[7].worldPosition.x = -2.8f;
	carModel[7].worldPosition.y = 35.0f;
	carModel[8].worldPosition.x = -7.8f;
	carModel[8].worldPosition.y = 99.0f;
	carModel[9].worldPosition.x = -7.8f;
	carModel[9].worldPosition.y = 8.0f;
	carModel[10].worldPosition.x = 2.2f;
	carModel[10].worldPosition.y = 134.0f;
	carModel[11].worldPosition.x = 7.2f;
	carModel[11].worldPosition.y = 71.0f;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	XMMATRIX playerWorldMatrix, UIMatrix, UIViewMatrix, mapWorldMatrix, mapWorldMatrix2, skyDomeMatrix;
	XMFLOAT3 cameraPosition;
	bool result;

	mapSpeed = 0.5f;
	carObjectSpeed = 0.2f;

	mapZpos1 -= (mapSpeed + exSpeed);
	mapZpos2 -= (mapSpeed + exSpeed);

	if (mapZpos1 < -70.0f) mapZpos1 = 120.0f;
	if (mapZpos2 < -70.0f) mapZpos2 = 120.0f;

	if (usingBooster) 
	{
		fuelGauge -= 2;
		if (fuelGauge <= 0)
		{
			fuelGauge = 0.0f;
			usingBooster = false;
		}
	}
	else if (fuelGauge >= 500) 
	{ 
		fuelGauge = 500; 
	}
	else 
	{
		fuelGauge++; 
	}

	if (usingBooster) exSpeed = 0.5f;
	else exSpeed = 0.0f;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	m_Camera->SetPosition(playerPos.x + 0.0f, playerPos.y + 20.0f, playerPos.z + -13.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	playerPos = XMFLOAT3LERP(playerPos, playerSystemPos, 0.1f);
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_Camera->GetViewMatrix(UIViewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetWorldMatrix(UIMatrix);
	m_D3D->GetWorldMatrix(playerWorldMatrix);
	m_D3D->GetWorldMatrix(mapWorldMatrix);
	m_D3D->GetWorldMatrix(mapWorldMatrix2);
	m_D3D->GetWorldMatrix(skyDomeMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);

	cameraPosition = m_Camera->GetPosition();

	if (IsCollision()) {
		playerSystemPos = playerBackPos;
	}

	UIViewMatrix = XMMatrixTranslation(0, 0, m_Camera->GetPosition().z + 30.0f);
	UIMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(m_Camera->GetRotation().x), XMConvertToRadians(m_Camera->GetRotation().y), XMConvertToRadians(m_Camera->GetRotation().z));
	playerWorldMatrix = XMMatrixMultiply(XMMatrixTranslation(playerPos.x, playerPos.y, playerPos.z), XMMatrixRotationY(XMConvertToRadians(0)));
	skyDomeMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn off back face culling.
	m_D3D->TurnOffCulling();

	skyDome->Render(m_D3D->GetDeviceContext());
	skyDomeShader->Render(m_D3D->GetDeviceContext(), skyDome->GetIndexCount(), skyDomeMatrix, viewMatrix, projectionMatrix,
		skyDome->GetApexColor(), skyDome->GetCenterColor());

	m_D3D->TurnOnCulling();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	//worldMatrix = XMMatrixRotationY(rotation);

	// Put the player model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	playerModel->Render(m_D3D->GetDeviceContext());

	// Render the player model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), playerModel->GetIndexCount(),
		playerWorldMatrix, viewMatrix, projectionMatrix,
		playerModel->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	mapWorldMatrix = XMMatrixTranslation(0.0f, -1.0f, mapZpos1);
	mapWorldMatrix2 = XMMatrixTranslation(0.0f, -1.0f, mapZpos2);

	// Put the map model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	mapModel->Render(m_D3D->GetDeviceContext());

	// Render the map model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), mapModel->GetIndexCount(),
		mapWorldMatrix, viewMatrix, projectionMatrix,
		mapModel->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	mapWorldMatrix = XMMatrixTranslation(0.0f, -1.0f, 0.0f);

	// Put the map model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	mapModel2->Render(m_D3D->GetDeviceContext());

	// Render the map model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), mapModel2->GetIndexCount(),
		mapWorldMatrix2, viewMatrix, projectionMatrix,
		mapModel2->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	for (int i = 0; i < 12; i++)
	{
		// Put the map model vertex and index buffers on the graphics pipeline to prepare them for drawing.
		carModel[i].m_carModel->Render(m_D3D->GetDeviceContext());
		carModel[i].worldPosition = XMFLOAT2(carModel[i].worldPosition.x, carModel[i].worldPosition.y - (carObjectSpeed + exSpeed));
		if (carModel[i].worldPosition.y < -20) carModel[i].worldPosition.y = 140.0f;
		carModel[i].worldMatrix = XMMatrixMultiply(XMMatrixTranslation(carModel[i].worldPosition.x, 0, carModel[i].worldPosition.y), XMMatrixRotationY(XMConvertToRadians(0.0f)));
		carModel[i].maxPosSize = XMFLOAT2SUM(carModel[i].maxSize, carModel[i].worldPosition);
		carModel[i].minPosSize = XMFLOAT2SUM(carModel[i].minSize, carModel[i].worldPosition);
		// Render the map model using the light shader.
		result = m_LightShader->Render(m_D3D->GetDeviceContext(), carModel[i].m_carModel->GetIndexCount(),
			carModel[i].worldMatrix, viewMatrix, projectionMatrix,
			carModel[i].m_carModel->GetTexture(),
			m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
			m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

		if (!result)
		{
			return false;
		}
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), UIViewMatrix * UIMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	UIViewMatrix = XMMatrixTranslation(75, 0, -55);

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = whiteBox->Render(m_D3D->GetDeviceContext(), 0, -5);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), UIViewMatrix, UIViewMatrix * UIMatrix, orthoMatrix, whiteBox->GetTexture());
	if (!result)
	{
		return false;
	}

	// Create the bitmap object.
	redBox = new BitmapClass;
	if (!redBox)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = redBox->Initialize(m_D3D->GetDevice(), 800, 600, L"./data/red.dds", fuelGauge, 30);
	if (!result)
	{
		return false;
	}

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = redBox->Render(m_D3D->GetDeviceContext(), 0, -5);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), UIViewMatrix, UIViewMatrix * UIMatrix, orthoMatrix, redBox->GetTexture());
	if (!result)
	{
		return false;
	}

	//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = fuelImg->Render(m_D3D->GetDeviceContext(), 0, -5);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), UIViewMatrix, UIViewMatrix * UIMatrix, orthoMatrix, fuelImg->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	redBox->Shutdown();
	delete redBox;
	redBox = 0;

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}