#include "Animation.h"
#include "Entity.h"
#include "Image.h"

#include <ConsoleManager.h>

void ECS::Animation::Init()
{
	image = entity->GetComponent<ECS::Image>();

	if (image == nullptr) 
	{
		Console::Output::PrintError("Animation Component", "The entity doesn't contain a valid image component.");
		this->active = false;
		return;
	}

	frameWidth = image->GetTextureWidth() / animationColumns;
	frameHeight = image->GetTextureHeight() / animationRows;

	ChangeAnimationFrame();
}

void ECS::Animation::Start() 
{
	ChangeAnimationFrame();
}

void ECS::Animation::Update(float dt)
{
	animationTimer += dt * speed;

	if (animationTimer > 1) {

		AdvanceFrame();
		animationTimer = 0;
	}
}

void ECS::Animation::ChangeAnimationPath(CRefString str, int frame, int animation, int column, int row)
{
	image->LoadTexture(str);

	animationRows = row;
	animationColumns = column;

	frameWidth = image->GetTextureWidth() / animationColumns;
	frameHeight = image->GetTextureHeight() / animationRows;

	currentFrame = frame;
	currentAnimation = animation;

	image->SetSrcRect(currentFrame * frameWidth, currentAnimation * frameHeight, frameWidth, frameHeight);
}

void ECS::Animation::AdvanceFrame()
{
	currentFrame++;
	int maxFrames = animationSheetStyle == (int)AnimationSheet::Horizontal ? animationColumns : animationRows;

	if (currentFrame >= maxFrames || currentFrame >= animationLenght) currentFrame = 0;

	ChangeAnimationFrame();
}

void ECS::Animation::AdvanceAnimation()
{
	currentAnimation++;

	int maxFrames = animationSheetStyle == (int)AnimationSheet::Horizontal ? animationRows : animationColumns;

	if (currentAnimation >= maxFrames) currentAnimation = 0;

	ChangeAnimationFrame();
}

void ECS::Animation::SetFrame(int idx)
{
	currentFrame = idx;

	ChangeAnimationFrame();
}

void ECS::Animation::SetAnimation(int idx)
{
	currentAnimation = idx;

	ChangeAnimationFrame();
}

void ECS::Animation::SetAnimationSpeed(float speed) {
	this->speed = speed;
}

void ECS::Animation::ChangeAnimationFrame()
{
	if (animationSheetStyle == (int)AnimationSheet::Horizontal)
		image->SetSrcRect(currentFrame * frameWidth, currentAnimation * frameHeight, frameWidth, frameHeight);
	else
		image->SetSrcRect(currentAnimation * frameWidth, currentFrame * frameHeight, frameWidth, frameHeight);
}
