#include <Arc.h>
#include <Arc/Core/EntryPoint.h>

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public ArcEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = ArcEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		ArcEngine::Ref<ArcEngine::VertexBuffer> vertexBuffer = ArcEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		ArcEngine::BufferLayout layout = {
			{ ArcEngine::ShaderDataType::Float3, "a_Position" },
			{ ArcEngine::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		ArcEngine::Ref<ArcEngine::IndexBuffer> indexBuffer = ArcEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA = (ArcEngine::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		ArcEngine::Ref<ArcEngine::VertexBuffer> squareVB = ArcEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ArcEngine::ShaderDataType::Float3, "a_Position" },
			{ ArcEngine::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		ArcEngine::Ref<ArcEngine::IndexBuffer> squareIB = ArcEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
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

		m_Shader = ArcEngine::Shader::Create("VertexColorTriangle", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);		
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = ArcEngine::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
	
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		
		m_Texture = ArcEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_BlendTexture = ArcEngine::Texture2D::Create("assets/textures/Onozuka.png");

		std::dynamic_pointer_cast<ArcEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<ArcEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

}


	void OnUpdate(ArcEngine::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		ArcEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		ArcEngine::RenderCommand::Clear();

		ArcEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<ArcEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<ArcEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				ArcEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
				ArcEngine::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		ArcEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_BlendTexture->Bind();
		ArcEngine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		
		
		//ArcEngine::Renderer::Submit(m_Shader, m_VertexArray);

		ArcEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}


	void OnEvent(ArcEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);

		if (e.GetEventType() == ArcEngine::EventType::WindowResize)
		{
			auto& re = (ArcEngine::WindowResizeEvent&)e;
		}
	}

private:
	ArcEngine::ShaderLibrary m_ShaderLibrary;

	ArcEngine::Ref<ArcEngine::Shader> m_Shader;
	ArcEngine::Ref<ArcEngine::VertexArray> m_VertexArray;

	ArcEngine::Ref<ArcEngine::Shader> m_FlatColorShader;
	ArcEngine::Ref<ArcEngine::VertexArray> m_SquareVA;

	ArcEngine::Ref<ArcEngine::Texture2D> m_Texture, m_BlendTexture;

	//ArcEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraRotationSpeed;
	float m_CameraMoveSpeed = 5.0;

	float deltaTime;

	ArcEngine::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	glm::vec3 m_SquarePosition;
};

class Sandbox : public ArcEngine::Application
{
public:
	Sandbox() 
		: Application()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() 
	{

	}
};

ArcEngine::Application* ArcEngine::CreateApplication()
{
	return new Sandbox();
}