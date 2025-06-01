#include "DrawUtils.h"
#include <SDL_image.h>
#include "RendererManager.h"

Renderer::DrawUtils::DrawUtils(RendererManager* renderer, SDL_Renderer* SDLRenderer) : renderer(renderer), SDLRenderer(SDLRenderer) {}

void Renderer::DrawUtils::DrawLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color)
{
	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, 255);

	// Vector perpendicular (normal)
	float dx = x2 - x1;
	float dy = y2 - y1;
	float length = std::sqrt(dx * dx + dy * dy);
	if (length == 0) return;

	dx /= length;
	dy /= length;

	// Perpendicular vector (normal)
	float nx = -dy * (thickness / 2.0f);
	float ny = dx * (thickness / 2.0f);

	// Define the 4 corners of the thick line as a quad
	SDL_FPoint points[4] = {
		{ x1 + nx, y1 + ny },
		{ x1 - nx, y1 - ny },
		{ x2 - nx, y2 - ny },
		{ x2 + nx, y2 + ny },
	};

	// Ajustar cada punto a la cámara
	for (auto& point : points) {
		int px = static_cast<int>(point.x);
		int py = static_cast<int>(point.y);
		renderer->AdjustRectToCamera(&px, &py, nullptr, nullptr, { 1, 1 });
		point.x = static_cast<float>(px);
		point.y = static_cast<float>(py);
	}

	// Dibujar el "quad" como dos triángulos (usando líneas)
	SDL_RenderDrawLineF(SDLRenderer, points[0].x, points[0].y, points[1].x, points[1].y);
	SDL_RenderDrawLineF(SDLRenderer, points[1].x, points[1].y, points[2].x, points[2].y);
	SDL_RenderDrawLineF(SDLRenderer, points[2].x, points[2].y, points[3].x, points[3].y);
	SDL_RenderDrawLineF(SDLRenderer, points[3].x, points[3].y, points[0].x, points[0].y);
}

void Renderer::DrawUtils::DrawSolidLine(int x1, int y1, int x2, int y2, int thickness, CRefColor color)
{
	SDL_Vertex verts[4];

	// Calcular vector dirección normalizado
	float dx = static_cast<float>(x2 - x1);
	float dy = static_cast<float>(y2 - y1);
	float len = std::sqrt(dx * dx + dy * dy);
	if (len == 0) return;

	dx /= len;
	dy /= len;

	// Vector perpendicular (normal)
	float nx = -dy * (thickness / 2.0f);
	float ny = dx * (thickness / 2.0f);

	// Puntos del rectángulo
	SDL_FPoint p1 = { x1 + nx, y1 + ny };
	SDL_FPoint p2 = { x1 - nx, y1 - ny };
	SDL_FPoint p3 = { x2 - nx, y2 - ny };
	SDL_FPoint p4 = { x2 + nx, y2 + ny };

	// Ajuste a cámara
	auto adjust = [&](SDL_FPoint& p)
		{
			int px = static_cast<int>(p.x);
			int py = static_cast<int>(p.y);
			renderer->AdjustRectToCamera(&px, &py, nullptr, nullptr, { 1,1 });
			p.x = static_cast<float>(px);
			p.y = static_cast<float>(py);
		};

	adjust(p1); adjust(p2); adjust(p3); adjust(p4);

	SDL_Color sdlColor = { color.r, color.g, color.b, 255 };

	// Triángulo 1: p1, p2, p3
	verts[0] = { p1, sdlColor, {0, 0} };
	verts[1] = { p2, sdlColor, {0, 0} };
	verts[2] = { p3, sdlColor, {0, 0} };
	// Triángulo 2: p1, p3, p4
	verts[3] = { p4, sdlColor, {0, 0} };

	int indices[] = { 0, 1, 2, 0, 2, 3 };

	SDL_RenderGeometry(SDLRenderer, nullptr, verts, 4, indices, 6);
}

void Renderer::DrawUtils::DrawCircle(int centerX, int centerY, int radius, CRefColor color)
{
	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, 255);

	const int32_t diameter = radius * 2;
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - diameter;

	auto drawAdjustedPoint = [&](int x, int y) {
		renderer->AdjustRectToCamera(&x, &y, nullptr, nullptr, { 1, 1 });
		SDL_RenderDrawPoint(SDLRenderer, x, y);
		};

	while (x >= y) {
		drawAdjustedPoint(centerX + x, centerY - y);
		drawAdjustedPoint(centerX + x, centerY + y);
		drawAdjustedPoint(centerX - x, centerY - y);
		drawAdjustedPoint(centerX - x, centerY + y);
		drawAdjustedPoint(centerX + y, centerY - x);
		drawAdjustedPoint(centerX + y, centerY + x);
		drawAdjustedPoint(centerX - y, centerY - x);
		drawAdjustedPoint(centerX - y, centerY + x);

		if (error <= 0) {
			y++;
			error += ty;
			ty += 2;
		}
		else {
			x--;
			tx += 2;
			error += (tx - diameter);
		}
	}
}

void Renderer::DrawUtils::DrawSolidCircle(int centerX, int centerY, int radius, CRefColor color)
{
	SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, 255);

	const int32_t diameter = radius * 2;
	int x = radius - 1;
	int y = 0;
	int tx = 1;
	int ty = 1;
	int error = tx - diameter;

	auto drawHorizontalLine = [&](int cx, int cy, int length)
		{
			int xStart = cx - length;
			int xEnd = cx + length;
			for (int x = xStart; x <= xEnd; ++x)
			{
				int adjX = x;
				int adjY = cy;
				renderer->AdjustRectToCamera(&adjX, &adjY, nullptr, nullptr, { 1, 1 });
				SDL_RenderDrawPoint(SDLRenderer, adjX, adjY);
			}
		};

	while (x >= y) {
		// Dibuja líneas horizontales simétricas para rellenar cada "banda"
		drawHorizontalLine(centerX, centerY + y, x);
		drawHorizontalLine(centerX, centerY - y, x);
		drawHorizontalLine(centerX, centerY + x, y);
		drawHorizontalLine(centerX, centerY - x, y);

		if (error <= 0) {
			y++;
			error += ty;
			ty += 2;
		}
		else {
			x--;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
