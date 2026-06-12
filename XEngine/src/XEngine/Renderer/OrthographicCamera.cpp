#include "xepch.h"
#include "OrthographicCamera.h"
#include <glm/gtx/transform.hpp>
namespace XEngine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_Rotation(0.0f), m_ProjectionMatrix(glm::ortho(left, right, bottom, top)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		UpdateViewProjectionMatrix();
	}
	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		UpdateViewProjectionMatrix();
	}
	void OrthographicCamera::UpdateViewProjectionMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(transform);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}