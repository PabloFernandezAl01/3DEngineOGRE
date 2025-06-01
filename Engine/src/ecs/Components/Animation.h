#pragma once

#include "Component.h"

#include <RendererManager.h>
#include <ETypes.h>

namespace ECS {

	class Transform;

	class Image;
	class Animation : public Component {

	public:

		enum class AnimationSheet { Horizontal, Vertical };

		Animation() {};
		~Animation() {};

		void Init() override;
		void Start() override;
		void Update(float dt) override;

		void ChangeAnimationPath(CRefString str, int frame, int animation, int column, int row);

		void AdvanceFrame();
		void AdvanceAnimation();

		void SetFrame(int idx);
		void SetAnimation(int idx);

		void SetAnimationSpeed(float speed);

		inline int GetFrame() { return currentFrame; }
		inline int GetAnimation() { return currentAnimation; }

		inline void SetAnimationLenght(int lenght) { animationLenght = lenght; }
		inline int GetAnimationLenght() { return animationLenght; }

	private:

		void ChangeAnimationFrame();

		float speed{1};

		int currentFrame{};
		int currentAnimation{};

		int animationColumns{1};
		int animationRows{1};

		int animationSheetStyle{};
		int animationLenght{};

		int frameWidth{};
		int frameHeight{};

		float animationTimer{};
		Image* image;
	};

}
