#include "RendererManager.h"
#include "ConsoleManager.h"
#include "Texture.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "DrawUtils.h"

namespace Renderer {

	RendererManager::RendererManager(const ConfigData& data) 
	{
		windowTitle = data.windowTitle;
		width = data.windowSize.GetX();  height = data.windowSize.GetY();

		this->bgColor = Utilities::Color::CreateColor(data.bgColor);

		valid = InitSDL(data.vsync, data.fullscreen, data.showCursor);

		drawUtils = new DrawUtils(this, renderer);
	}

	bool RendererManager::Valid() 
	{
		return valid;
	}

	RendererManager::~RendererManager()
	{
		SDL_FreeSurface(icon);
		icon = nullptr;

		delete drawUtils;

		CloseSDL();
	}

	bool RendererManager::InitSDL(bool vsync, bool fullscreen, bool showcursor)
	{
		// Initialize SDL
		int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);

		if (sdlInit_ret < 0) 
		{
			Console::Output::PrintError("SDL Initialization", SDL_GetError());
			return false;
		}

		// Create window
		int fullscreenEnable = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
		window = SDL_CreateWindow(windowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width, height, fullscreen | SDL_WINDOW_OPENGL);

		if (window == nullptr)
		{
			SDL_Quit();

			Console::Output::PrintError("SDL Initialization (Window Creation)", SDL_GetError());
			return false;
		}

		// Create the renderer
		int vsyncEnable = vsync ? SDL_RENDERER_PRESENTVSYNC : 0;
		renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | vsyncEnable);

		if (window == nullptr)
		{
			SDL_DestroyWindow(window); window = nullptr;
			SDL_Quit();

			Console::Output::PrintError("SDL Initialization (Renderer Creation)", SDL_GetError());
			return false;
		}

		// Initialize SDL_image
		int imgInit_ret = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

		if (imgInit_ret == 0) 
		{
			SDL_DestroyWindow(window); window = nullptr;
			SDL_DestroyRenderer(renderer); renderer = nullptr;
			SDL_Quit();

			Console::Output::PrintError("SDL Initialization (IMG Library)", "Error in the initialization of the SDL image library.");
			return false;
		}

		// Initialize SDL_TTF (True Type Font)
		int ttfInit_ret = TTF_Init();

		if (ttfInit_ret == -1)
		{
			IMG_Quit();
			SDL_DestroyWindow(window); window = nullptr;
			SDL_DestroyRenderer(renderer); renderer = nullptr;
			SDL_Quit();

			Console::Output::PrintError("SDL Initialization (TTF Library)", "Error in the initialization of the SDL font library.");
			return false;
		}

		ShowCursor(showcursor);

		return true;
	}

	void RendererManager::CloseSDL()
	{
		SDL_DestroyWindow(window); window = nullptr;
		SDL_DestroyRenderer(renderer); renderer = nullptr;
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}

	void RendererManager::ToggleFullScreen()
	{
		auto flags = SDL_GetWindowFlags(window);

		if (flags & SDL_WINDOW_FULLSCREEN)
		{
			if (SDL_SetWindowFullscreen(window, 0) < 0)
				Console::Output::PrintError("Window FullScreen Error", SDL_GetError());
		}
		else
			if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
				Console::Output::PrintError("Window FullScreen Error", SDL_GetError());
	}

	void RendererManager::ResizeWindow(int w, int h)
	{
		if (w <= 0 || h <= 0) 
		{
			Console::Output::PrintError("Invalid size parameters", "The provided height and width must be greater than zero.");
			return;
		}

		SDL_SetWindowSize(window, w, h);
	}

	void RendererManager::RenameWindow(CRefString name)
	{
		SDL_SetWindowTitle(window, name.c_str());
	}

	void RendererManager::RepositionWindow(int x, int y)
	{
		SDL_SetWindowPosition(window, x, y);
	}

	void RendererManager::ShowCursor(bool show)
	{
		if (SDL_ShowCursor(show) < 0)
			Console::Output::PrintError("Show cursor error", SDL_GetError());
	}

	void RendererManager::ClearRenderer() 
	{
		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);
		SDL_RenderClear(renderer);
	}

	void RendererManager::PresentRenderer()
	{
		SDL_RenderPresent(renderer);
	}

	void RendererManager::AdjustRectToCamera(int* x, int* y, int* w, int* h, CRefVector2 scrollFactor)
	{
		auto camPos = GetCameraPosition();
		float camScale = GetCameraScale();

		int winW = Renderer::RendererManager::Instance()->GetWidth();
		int winH = Renderer::RendererManager::Instance()->GetHeight();

		// Invertir la posición Y
		*y *= -1;

		// Mover las coordenadas al centro de la pantalla
		*x += winW * 0.5f;
		*y += winH * 0.5f;

		// Calcular el desplazamiento de la cámara
		*x -= camPos.GetX() * scrollFactor.GetX();
		*y += camPos.GetY() * scrollFactor.GetY();

		// Aplicar la escala de la cámara
		*x *= camScale;
		*y *= camScale;

		// Ajustar el tamaño de los objetos de acuerdo a la escala de la cámara
		if (w) *w *= camScale;
		if (h) *h *= camScale;

		// Centrar las coordenadas finales
		*x += (winW * 0.5f) - (winW * 0.5f * camScale);
		*y += (winH * 0.5f) - (winH * 0.5f * camScale);
	}

	bool RendererManager::SetWindowIcon(CRefString path) 
	{
		icon = IMG_Load(path.c_str());

		if (icon == nullptr) {
			Console::Output::PrintError("Window icon", "Could not change window icon. Error loading file <" + path + ">");
			return false;
		}

		SDL_SetWindowIcon(window, icon);
	}

	void RendererManager::DrawLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color)
	{
		drawUtils->DrawLine(x1, y1, x2, y2, thickness, color);
	}

	void RendererManager::DrawSolidLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color)
	{
		drawUtils->DrawSolidLine(x1, y1, x2, y2, thickness, color);
	}

	void RendererManager::DrawCircle(int centerX, int centerY, int radius, CRefColor color)
	{
		drawUtils->DrawCircle(centerX, centerY, radius, color);
	}

	void RendererManager::DrawSolidCircle(int centerX, int centerY, int radius, CRefColor color)
	{
		drawUtils->DrawSolidCircle(centerX, centerY, radius, color);
	}

	void RendererManager::SetWindowBordered(bool border)
	{
		SDL_SetWindowBordered(window, (SDL_bool)border);
	}

	void RendererManager::CenterWindow()
	{
		SDL_Rect rect;
		SDL_GetDisplayBounds(0, &rect);

		int windowWidth, windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		int x = (rect.w / 2  - windowWidth / 2 );
		int y = (rect.h / 2  - windowHeight / 2 );

		SDL_SetWindowPosition(window, x, y);
	}

}