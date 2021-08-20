#pragma once

#include "Arc.h"

class Sandbox2D : public ArcEngine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(ArcEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(ArcEngine::Event& e) override;
private:
	ArcEngine::OrthographicCameraController m_CameraController;

	// Temp
	ArcEngine::Ref<ArcEngine::Texture2D> m_CheckerboardTexture;
	ArcEngine::Ref<ArcEngine::VertexArray> m_SquareVA;
	ArcEngine::Ref<ArcEngine::Shader> m_FlatColorShader;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
	ArcEngine::Ref<ArcEngine::Framebuffer> m_Framebuffer;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};