#pragma once
#include <QtGui/QVector3D>
#include <QtCore/QtMath>
#include <QtGui/QMatrix4x4>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	TURN_RIGHT,
	TURN_LEFT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.005f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	QVector3D Position;
	QVector3D Front;
	QVector3D Up;
	QVector3D Right;
	QVector3D WorldUp;

	float Yaw;
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;


	Camera(const QVector3D& position = { 0.0f, 0.0f, 0.0f },
		const QVector3D& up = { 0.0f, 1.0f, 0.0f },
		float yaw = YAW, float pitch = PITCH)
		: Position(position),
		Front(QVector3D(0.0f, 0.0f, -1.0f)),
		WorldUp(up),
		Yaw(yaw),
		Pitch(pitch),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		updateCameraVectors();
	}
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: Position(QVector3D(posX, posY, posZ)),
		Front(QVector3D(0.0f, 0.0f, -1.0f)),
		WorldUp(QVector3D(upX, upY, upZ)),
		Yaw(yaw),
		Pitch(pitch),
		MovementSpeed(SPEED),
		MouseSensitivity(SENSITIVITY),
		Zoom(ZOOM)
	{
		updateCameraVectors();
	}
	QMatrix4x4 GetViewMatrix()
	{
		QMatrix4x4 matrix;
		matrix.setToIdentity();
		matrix.lookAt(Position, Position + Front, Up);
		return matrix;
	}
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		const float velocity = MovementSpeed * deltaTime;
		const float turn_sensitivity = MouseSensitivity * 130;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
		if (direction == TURN_LEFT)
			Yaw -= velocity * turn_sensitivity;
		if (direction == TURN_RIGHT)
			Yaw += velocity * turn_sensitivity;
		updateCameraVectors();
	}
	void ProcessMouseMovement(float x_offset, float y_offset, bool constrainPitch = true)
	{
		x_offset *= MouseSensitivity;
		y_offset *= MouseSensitivity;

		Yaw += x_offset;
		Pitch += y_offset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Euler angles
		updateCameraVectors();
	}
	void ProcessMouseScroll(int delta)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= delta / 10;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}
private:
	void updateCameraVectors()
	{
		QVector3D front;
		front.setX(qCos(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)));
		front.setY(qSin(qDegreesToRadians(Pitch)));
		front.setZ(qSin(qDegreesToRadians(Yaw)) * qCos(qDegreesToRadians(Pitch)));
		Front = front.normalized();
		Right = QVector3D::crossProduct(Front, WorldUp).normalized();
		Up = QVector3D::crossProduct(Right, Front).normalized();
	}
};
