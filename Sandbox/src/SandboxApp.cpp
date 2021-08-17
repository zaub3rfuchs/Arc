#include <Arc.h>

#include "imgui/imgui.h"

class ExampleLayer : public ArcEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(ArcEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<ArcEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(ArcEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		ArcEngine::BufferLayout layout = {
			{ ArcEngine::ShaderDataType::Float3, "a_Position" },
			{ ArcEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<ArcEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(ArcEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(ArcEngine::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<ArcEngine::VertexBuffer> squareVB;
		squareVB.reset(ArcEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ArcEngine::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<ArcEngine::IndexBuffer> squareIB;
		squareIB.reset(ArcEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			uniform mat4 u_ViewProjection;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new ArcEngine::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			uniform mat4 u_ViewProjection;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);		
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new ArcEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}


	void OnUpdate() override
	{

		if (ArcEngine::Input::IsKeyPressed(ARC_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		if (ArcEngine::Input::IsKeyPressed(ARC_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		if (ArcEngine::Input::IsKeyPressed(ARC_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;
		if (ArcEngine::Input::IsKeyPressed(ARC_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		ArcEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ArcEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0.0f);

		ArcEngine::Renderer::BeginScene(m_Camera);

		ArcEngine::Renderer::Submit(m_BlueShader, m_SquareVA);
		ArcEngine::Renderer::Submit(m_Shader, m_VertexArray);

		ArcEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}


	void OnEvent(ArcEngine::Event& e) override
	{
		
	}

private:
	std::shared_ptr<ArcEngine::Shader> m_Shader;
	std::shared_ptr<ArcEngine::VertexArray> m_VertexArray;

	std::shared_ptr<ArcEngine::Shader> m_BlueShader;
	std::shared_ptr<ArcEngine::VertexArray> m_SquareVA;

	ArcEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraRotationSpeed;
	float m_CameraMoveSpeed = 0.1;
};

class Sandbox : public ArcEngine::Application
{
public:
	Sandbox() 
		: Application()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication()
{
	return new Sandbox();
}