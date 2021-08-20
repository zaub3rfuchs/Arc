#pragma once

#include "Arc.h"
namespace ArcEngine {
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		ArcEngine::OrthographicCameraController m_CameraController;

		// Temp
		Ref<Texture2D> m_CheckerboardTexture;
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult> m_ProfileResults;
		ArcEngine::Ref<Framebuffer> m_Framebuffer;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

}