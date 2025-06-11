#pragma once
#include "../Component/Base/Component.h"
#include "../Component/Base/Common_Component.h"

/// <summary>
/// Entityクラス:複数のComponentを動的に保持・管理するエンティティクラス
/// </summary>
class Entity
{
private:
	//各Componentを型名文字列で管理(型名 -> Componentのポインタ)
	std::unordered_map<std::string, std::shared_ptr<Component>> components;

protected:
	//任意の型Tのコンポーネントを作成・追加するテンプレート関数
	//引数はそのままTのコンストラクタに渡す
	template<typename T, typename... Args>
	void AddComponent(Args&&... _args)
	{
		//typeid(T).name()をキーにしてコンポーネントを格納
		components[typeid(T).name()] = std::make_shared<T>(std::forward<Args>(_args)...);
	}

	// 型 T のコンポーネントを取得するテンプレート関数
	// 共有ポインタを dynamic_pointer_cast でキャストして返す
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		// マップから型名に対応するコンポーネントを検索
		auto it = components.find(typeid(T).name());
		if (it != components.end())
		{
			// 共有ポインタのキャスト
			return std::dynamic_pointer_cast<T>(it->second);
		}
		// 見つからなかった場合は nullptr を返す
		return nullptr;
	}

	void InitComponent();

	void UpdateComponent();

	void DrawComponent();

	void FinalComponent();

};

