#include "Entity.h"

void Entity::InitComponent()
{
	for (auto& pair : components)
	{
		auto& components = pair.second;
		components->Init();
	}
}

void Entity::UpdateComponent()
{
	for (auto& pair : components)
	{
		auto& components = pair.second;
		components->Update();
	}
}

void Entity::DrawComponent()
{
	for (auto& pair : components)
	{
		auto& components = pair.second;
		components->Draw();
	}
}

void Entity::FinalComponent()
{
	for (auto& pair : components)
	{
		auto& components = pair.second;
		components->Final();
	}
}
