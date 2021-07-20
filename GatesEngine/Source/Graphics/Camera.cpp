#include "..\..\Header\Graphics\Camera.h"
#include <DirectXMath.h>

GatesEngine::Camera::Camera()
	: pGraphicsDevice(nullptr)
	, pMainWindow(nullptr)
	, input(Input::GetInstance())
	, cameraBuffer(CBuffer<B2>())
	, viewMatrix(Math::Matrix4x4::Identity())
	, projectionMatrix(Math::Matrix4x4::Identity())
	, position(Math::Vector3(0, 0, 0))
	, direction(Math::Vector3(0, 0, 1))
	, up(Math::Vector3(0, 1, 0))
	, isCreateBuffer(false)
	, yaw(0)
	, pitch(0)
	, moveSpeed(1)
	, rotation(Math::Matrix4x4::Identity())
{
}

GatesEngine::Camera::~Camera()
{
}

void GatesEngine::Camera::Initialize()
{
	viewMatrix = Math::Matrix4x4::Identity();
	projectionMatrix = Math::Matrix4x4::GetPerspectiveMatrix(90, pMainWindow->GetWindowAspect());

	position = Math::Vector3(0, 0, -10);
	direction = Math::Vector3(0, 0, 1);
	up = Math::Vector3(0, 1, 0);
	rotation = Math::Matrix4x4::Identity();
}

void GatesEngine::Camera::Update()
{
	Math::Axis axis = rotation.GetAxis();
	//ƒ}ƒEƒX‚ÌˆÚ“®—Ê‚ðŽæ“¾
	if (input->GetMouse()->GetCheckHitButton(MouseButtons::RIGHT_CLICK))
	{
		input->GetMouse()->SetMouseCursor({ 1920 / 2,1080 / 2 });

		moveSpeed = (input->GetKeyboard()->CheckHitKey(Keys::LSHIFT)) ? 5.0f : 1.0f;

		Math::Vector2 inputValue = input->GetMouse()->GetMouseMove() / 500.0f;

		pitch -= inputValue.y;
		yaw -= inputValue.x;

		float minMaxPitch = Math::ConvertToRadian(89);
		if (pitch > minMaxPitch)pitch = minMaxPitch;
		if (pitch < -minMaxPitch)pitch = -minMaxPitch;

		if (input->GetKeyboard()->CheckHitKey(Keys::W))
		{
			position += axis.z * moveSpeed;
		}
		if (input->GetKeyboard()->CheckHitKey(Keys::S))
		{
			position -= axis.z * moveSpeed;
		}
		if (input->GetKeyboard()->CheckHitKey(Keys::D))
		{
			position += axis.x * moveSpeed;
		}
		if (input->GetKeyboard()->CheckHitKey(Keys::A))
		{
			position -= axis.x * moveSpeed;
		}
		if (input->GetKeyboard()->CheckHitKey(Keys::E))
		{
			position += axis.y * moveSpeed;
		}
		if (input->GetKeyboard()->CheckHitKey(Keys::Q))
		{
			position -= axis.y * moveSpeed;
		}
	}
	if (input->GetMouse()->GetWheelValue() < 0)
	{
		position -= axis.z * 100;
	}
	if (input->GetMouse()->GetWheelValue() > 0)
	{
		position += axis.z * 100;
	}

	direction = Math::Vector3(0, 0, 1);
	rotation = Math::Matrix4x4::RotationX(pitch) * Math::Matrix4x4::RotationY(yaw);
	direction = Math::Matrix4x4::Transform(direction, rotation);

	viewMatrix = Math::Matrix4x4::GetViewMatrixLookTo(position, direction, axis.y);

	//cameraBuffer.Map({ viewMatrix,projectionMatrix });

}

void GatesEngine::Camera::Set()
{
	cameraBuffer.Set();
}

void GatesEngine::Camera::SetGraphicsDevice(GraphicsDevice* device)
{
	if (!isCreateBuffer)
	{
		cameraBuffer.Create(device, 2);
	}
	pGraphicsDevice = device;
	isCreateBuffer = true;
}

void GatesEngine::Camera::SetMainWindow(Window* mainWindow)
{
	pMainWindow = mainWindow;
}

GatesEngine::B2 GatesEngine::Camera::GetData()
{
	B2 data = { viewMatrix,projectionMatrix,position };
	return data;
}