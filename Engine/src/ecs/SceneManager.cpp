#include "SceneManager.h"
#include "Scene.h"

namespace ECS {

	SceneManager::~SceneManager() 
	{
		RemoveAllScenes();
	}

	Scene* SceneManager::GetCurrentScene() 
	{
		if (scenes.empty()) 
			return nullptr;

		return scenes.top();
	}

	Scene* SceneManager::CreateScene(CRefString sce_name) 
	{
		return new Scene(sce_name);
	}

	void SceneManager::ChangeScene(Scene* newScene, int m) 
	{
		this->scene = newScene;
		mode = (LOAD_MODE) m;
		change = true;
	}

	void SceneManager::ResetScene() 
	{
		ChangeScene(scene, LOAD_MODE::POP_AND_PUSH);
	}

	void SceneManager::ManageScenes() 
	{
		if (change) 
		{
			switch (mode) {

			case PUSH:
				PushScene();
				break;

			case POP:
				PopScene();
				break;

			case POP_AND_PUSH:
				PopAndPushScene();
				break;

			case CLEAR_AND_PUSH:
				RemoveAllScenes();
				PushScene();
				break;

			case CLEAR:
				RemoveAllScenes();
				break;

			default:
				break;
			}
		}

		change = false;
	}

	void SceneManager::PushScene() 
	{
		if (scenes.size() > 0) 
			scenes.top()->OnSceneDown();

		if (scene != nullptr) {

			scenes.push(scene);
			scenes.top()->Start();
		}
	}

	void SceneManager::PopScene() 
	{
		if (scenes.size() > 0) 
		{
			scenes.top()->OnDestroy();
			delete scenes.top();
			scenes.pop();

			if (scenes.size() > 0) 
				scenes.top()->OnSceneUp();
		}
	}

	void SceneManager::PopAndPushScene() 
	{
		if (scenes.size() > 0) 
		{
			scenes.top()->OnDestroy();
			delete scenes.top();
			scenes.pop();

			scenes.push(scene);
			scenes.top()->Start();
		}
	}

	void SceneManager::RemoveAllScenes() 
	{
		auto size = scenes.size();
		for (int i = 0; i < size; i++) 
		{
			scenes.top()->OnDestroy();
			delete scenes.top();
			scenes.pop();
		}
	}

	void SceneManager::EmptyScenes()
	{
		ChangeScene(nullptr, LOAD_MODE::CLEAR);
	}
}
