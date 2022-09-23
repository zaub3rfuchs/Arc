#pragma once
#include "Arc/Renderer/Camera.h"

namespace ArcEngine {

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void	SetPerspective(float verticalFOV, float nearClip, float farClip);	
		void	SetOrthographic(float size, float nearClip, float farClip);

		void	SetViewportSize(uint32_t width, uint32_t height)	{ ARC_CORE_ASSERT(width > 0 && height > 0); m_AspectRatio = (float)width / (float)height; CalculateProjection(); }
		void	SetBackgroundColor(glm::vec4 bgColor)				{ m_BackgroundColor = bgColor; }
		float	GetPerspectiveVerticalFOV() const					{ return m_PerspectiveFOV; }
		void	SetPerspectiveVerticalFOV(float verticalFov)		{ m_PerspectiveFOV = verticalFov; CalculateProjection(); }
		float	GetPerspectiveNearClip() const						{ return m_PerspectiveNear; }
		void	SetPerspectiveNearClip(float nearClip)				{ m_PerspectiveNear = nearClip; CalculateProjection(); }
		float	GetPerspectiveFarClip() const						{ return m_PerspectiveFar; }
		void	SetPerspectiveFarClip(float farClip)				{ m_PerspectiveFar = farClip; CalculateProjection(); }

		float	GetOrthographicSize() const							{ return m_OrthographicSize; }
		void	SetOrthographicSize(float size)						{ m_OrthographicSize = size; CalculateProjection(); }
		float	GetOrthographicNearClip() const						{ return m_OrthographicNear; }
		void	SetOrthographicNearClip(float nearClip)				{ m_OrthographicNear = nearClip; CalculateProjection(); }
		float	GetOrthographicFarClip() const						{ return m_OrthographicFar; }
		void	SetOrthographicFarClip(float farClip)				{ m_OrthographicFar = farClip; CalculateProjection(); }

		void	SetProjectionType(ProjectionType type)				{ m_ProjectionType = type; CalculateProjection(); }
		
		glm::vec4		GetBackgroundColor()						{ return m_BackgroundColor; }
		ProjectionType	GetProjectionType() const					{ return m_ProjectionType; }
	private:
		void	CalculateProjection();
	private:
		ProjectionType	m_ProjectionType = ProjectionType::Orthographic;
		glm::vec4		m_BackgroundColor = { 0.2f, 0.2f, 0.7f, 1.0f };

		float		m_PerspectiveFOV = glm::radians(45.0f);
		float		m_PerspectiveNear = 0.01f;
		float		m_PerspectiveFar = 1000.0f;

		float		m_OrthographicSize = 10.0f;
		float		m_OrthographicNear = -1.0f;
		float		m_OrthographicFar = 1.0f;

		float		m_AspectRatio = 0.0f;
	};
}
