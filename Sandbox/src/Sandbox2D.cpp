#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f), m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = ArcEngine::Texture2D::Create("assets/textures/Checkerboard.png");

	ArcEngine::FramebufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_Framebuffer = ArcEngine::Framebuffer::Create(fbSpec);
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(ArcEngine::Timestep ts)
{
	ARC_PROFILE_FUNCTION();
	// Update
	m_CameraController.OnUpdate(ts);


	ArcEngine::Renderer2D::ResetStats();
	// Preperation
	{
		ARC_PROFILE_SCOPE("Renderer Prep");
		m_Framebuffer->Bind();
		ArcEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ArcEngine::RenderCommand::Clear();
	}
	// Render
	{

		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		ARC_PROFILE_SCOPE("Renderer Draw");
		ArcEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		ArcEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		ArcEngine::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		ArcEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { m_SquareColor });
		ArcEngine::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 20.0f);
		ArcEngine::Renderer2D::DrawQuad({ -0.5f, -0.5f, 0.0f }, { 1.0f, 1.0f }, m_CheckerboardTexture, 10.0f);
		ArcEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		ArcEngine::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		ArcEngine::Renderer2D::EndScene();

		ArcEngine::Renderer2D::BeginScene(m_CameraController.GetCamera());

		
		for (float y = -5; y < 5; y += 0.5f)
		{
			for (float x = -5; x < 5; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				ArcEngine::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		ArcEngine::Renderer2D::EndScene();
		m_Framebuffer->Unbind();
	}
}

void Sandbox2D::OnImGuiRender()
{
	ARC_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = ArcEngine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::Image((void*)textureID, ImVec2{ 1280, 720 });
	ImGui::End();
	
}

void Sandbox2D::OnEvent(ArcEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}