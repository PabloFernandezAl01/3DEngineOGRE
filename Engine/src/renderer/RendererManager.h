#pragma once

#include <ConfigManager.h>
#include <Singleton.h>
#include <ETypes.h>
#include <set>

class SDL_Window;
struct SDL_Renderer;
class SDL_Surface;
struct SDL_Texture;

namespace Renderer {

	class DrawUtils;

	class RendererManager : public Utilities::Singleton<RendererManager> {

		friend Singleton<RendererManager>;

	public:

		~RendererManager();

		bool Valid() override;

		inline SDL_Window* GetWindow() { return window; }
		inline SDL_Renderer* GetRenderer() { return renderer; }

		void ClearRenderer();
		void PresentRenderer();

		// Camera methods
		void AdjustRectToCamera(int* x, int* y, int* w, int* h, CRefVector2 scrollFactor);

		inline Utilities::Vector2D GetCameraPosition() { return cameraPosition; }
		inline float GetCameraScale() { return cameraScale; }

		inline void SetCameraPosition(CRefVector2 position) { cameraPosition = position; }
		inline void SetCameraScale(float scale) { cameraScale = scale; }

		inline void MoveCamera(CRefVector2 distance) { cameraPosition += distance; }
		inline void Zoom(float zoom) { cameraScale += zoom; }

		inline int GetWidth() { return width; }
		inline int GetHeight() { return height; }

		inline const Utilities::Color& GetBackgroundColor() { return bgColor; }

		void ToggleFullScreen();
		void ShowCursor(bool show);
		void ResizeWindow(int w, int h);
		void RenameWindow(CRefString name);
		void RepositionWindow(int x, int y);
		void CenterWindow();
		void SetWindowBordered(bool border);
		bool SetWindowIcon(CRefString path);

		void DrawLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color);
		void DrawSolidLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color);

		void DrawCircle(int centerX, int centerY, int radius, CRefColor color);
		void DrawSolidCircle(int centerX, int centerY, int radius, CRefColor color);

	private:

		RendererManager() {};
		RendererManager(const ConfigData& data);

		bool InitSDL(bool vsync, bool fullscreen, bool showcursor);
		void CloseSDL();

		int width{};
		int height{};

		DrawUtils* drawUtils{};

		SDL_Window* window{}; // the window
		SDL_Renderer* renderer{}; // the renderer

		std::string windowTitle{};

		Utilities::Color bgColor{};

		SDL_Surface* icon{};

		float cameraScale{};
		Utilities::Vector2D cameraPosition{};

		bool valid{};
	};
}
