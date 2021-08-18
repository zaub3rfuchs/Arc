#pragma once

#include "Arc.h"


class Sandbox2D : public ArcEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnFixedUpdate(ArcEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(ArcEngine::Event& e) override;
private:
	ArcEngine::OrthographicCameraController m_CameraController;

	// Temp
	ArcEngine::Ref<ArcEngine::VertexArray> m_SquareVA;
	ArcEngine::Ref<ArcEngine::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};