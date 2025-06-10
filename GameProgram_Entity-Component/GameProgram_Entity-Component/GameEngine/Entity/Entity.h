#pragma once
#include "../Component/Base/Component.h"
#include "../Component/Base/Common_Component.h"

class Entity
{
private:
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

public:
protected:

	template<typename T, typename... Args>
	void AddComponent(Args&&... _args)
	{
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(_args)...);
	}

	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	void InitComponent();

	void UpdateComponent();

	void DrawComponent();

	void FinalComponent();



};

