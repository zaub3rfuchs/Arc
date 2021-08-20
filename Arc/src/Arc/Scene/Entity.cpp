#include "apch.h"
#include "Entity.h"

namespace ArcEngine {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}