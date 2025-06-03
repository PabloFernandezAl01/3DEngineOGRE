#pragma once

#include <ETypes.h>
#include <stack>

#include <ESingleton.h>

/*
* 
* This class handles the scenes.
* User should use this manager to create a new class
* and call the 'changeScene' method to start rendering 
* his new class.
* 
* Actually, the 'changeScene' method does not change
* the scene, it just marks that scene as the new scene to 
* be rendered and change it at the end of the main loop
* with the 'manageScenes' method.
* 
*/

namespace ECS {

	class Scene;

	class SceneManager : public Core::ESingleton<SceneManager> {

	public:

		friend class Engine;

		enum LOAD_MODE : uint8_t {

			/*
			* PUSH --> ADDS THE NEW SCENE ON THE TOP OF THE STACK
			* POP --> REMOVES THE SCENE ON THE TOP OF THE STACK
			* POP_AND_PUSH -> REMOVES THE SCENE ON THE TOP OF THE STACK AND ADDS THE NEW SCENE
			* CLEAR_AND_PUSH -> REMOVES ALL THE SCENES ON THE STACK AND PUSH THE NEW SCENE
			* CLEAR -> REMOVES ALL THE SCENES ON THE STACK AND CLOSE THE GAME
			*/

			PUSH = 0, POP = 1, POP_AND_PUSH = 2, CLEAR_AND_PUSH = 3, CLEAR = 4
		};

		SceneManager() {}

		// Destroys all the scenes in the stack and clear the stack
		~SceneManager();

		// Returns a pointer to the scene on top if the stack is not empty, nullptr otherwise
		Scene* GetCurrentScene();

		// Creates, starts and adds a scene to the stack
		Scene* CreateScene(CRefString sce_name = "New Scene");

		void ChangeScene(Scene* newScene, LOAD_MODE);

		void ResetScene();

		void EmptyScenes();

		// Returns the number of scenes in the stack
		inline int GetNumberOfScenes() { return scenes.size(); }

		/// <summary>
		/// Manage the scenes.
		/// If the user changed the scene in the current iteration, this method actually change it
		/// at the end of the main loop according with the mode.
		/// </summary>
		void ManageScenes();

	private:

		// Remove all the scenes on the stack
		void RemoveAllScenes();

		// Push one scene to the top of the stack
		void PushScene();

		// Pop the scene on top of the stack
		void PopScene();

		// Pop and push
		void PopAndPushScene();

	private:

		std::stack<Scene*> scenes{};

		Scene* scene{};

		LOAD_MODE mode{};

		bool change{};
	};

}

