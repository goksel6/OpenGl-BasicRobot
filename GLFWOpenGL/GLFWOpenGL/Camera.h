//#pragma once
//#include <vector>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include<glm/glm.hpp>
//#include <glm/glc/matrix_transform.hpp>
//
//enum Camera_Movement
//{
//	FORWARD,
//	BACKWARD,
//	LEFT,
//	RIGHT
//};
//
//const GLfloat YAW = -90.f;
//const GLfloat PITCH = 0.0f;
//const GLfloat SPEED = 6.0f;
//const GLfloat SENSITIVITY = 0.25f;
//const GLfloat ZOOM = 45.0f;
//
//class Camera
//{
//public:
//	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
//	{
//		this->position = position;
//		this->worldUp = up;
//		this->yaw = yaw;
//		this->pitch = pitch;
//		this->updateCameraVectors();
//	}
//	Camera(GLfloat posx, GLfloat posy, GLfloat posz, GLfloat upx, GLfloat upy, GLfloat upz, GLfloat yaw, GLfloat pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mauseSensitivity(SENSITIVITY), zoom(ZOOM)
//	{
//		this->position = glm::vec3(posx,posy,posz);
//		this->worldUp = glm::vec3(upx, upy, upz);
//		this->yaw = yaw;
//		this->pitch = pitch;
//		this->updateCameraVectors();
//	}
//	glm::mat4 GetViewMatrix()
//	{
//		return glm::lookAt(this->position, this->position + this->front, this->up);
//	}
//	void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
//	{
//		GLfloat velocity = this->movementSpeed + deltaTime;
//	}
//};
