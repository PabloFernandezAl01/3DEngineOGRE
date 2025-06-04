#pragma once

#include "Component.h"
#include "ETypes.h"

namespace Ogre
{
	class Camera;
	class Viewport;
}


namespace ECS
{
	class Camera : public Component
	{
	public:

		enum class ProjectionType { ORTOGRAPHIC, PERSPECTIVE };
		enum class PolygonMode { POINTS = 1, WIREFRAME = 2, SOLID = 3};

		void Init() override;

		// Camera

			// Fov value is recommended to be between 45 and 60 degrees
			inline void SetFovY(float radian) { fovY = radian; }

			// Position of the near clipping plane
			inline void SetNearClipDistance(float distance) { nearClipDistance = distance; }

			// Positio of the far clip distance
			inline void SetFarClipDistance(float distance) { farClipDistance = distance; }

			inline void SetProjectType(const ProjectionType& type) { projectionType = type; }

			inline void SetAutoAspectRatio(bool value) { autoAspectRatio = value; }

			inline void SetAspectRatio(float ratio) { aspectRatio = ratio; }

			inline void SetPolygonMode(const PolygonMode& mode) { polygonMode = mode; }

			inline void SetUseRenderingDistance(bool value) { useRenderingDistance = value; }

			inline void SetRenderingDistance(float distance) { renderingDistance = distance; }

		// Viewport

			inline void SetBackgroundColor(CRefColor color) { backgroundColor = color; }

			// Viewport position and size
			inline void SetViewportDimension(float x, float y, float w, float h) { viewportX = x; viewportY = y; viewportW = w; viewportH = h; }

			// Wether or not to enable overalys for this viewport
			inline void SetOverlaysEnabled(bool value) { overlaysEnabled = value; }

	private:

		Ogre::Camera* camera{};
		Ogre::Viewport* viewport{};
		
		// Camera
		float fovY{60};
		float nearClipDistance{0.1f};
		float farClipDistance{1000.f};
		ProjectionType projectionType;
		bool autoAspectRatio{ true };
		float aspectRatio{};
		PolygonMode polygonMode;
		bool useRenderingDistance{};
		float renderingDistance{1000.f};

		// Viewport
		Core::Color backgroundColor;
		float viewportX{}, viewportY{}, viewportW{}, viewportH{};
		bool overlaysEnabled{ true };

	};
}
