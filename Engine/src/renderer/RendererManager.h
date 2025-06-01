#pragma once

#include <ConfigManager.h>
#include <Singleton.h>

namespace Renderer {

	class RendererManager : public Core::Singleton<RendererManager> {

		friend Singleton<RendererManager>;

	public:

		~RendererManager();

		bool Valid() override;

		void ClearRenderer();
		void PresentRenderer();

	private:

		RendererManager() {};
		RendererManager(const ConfigData& data);

		std::string windowTitle{};

		bool valid{};
	};
}
