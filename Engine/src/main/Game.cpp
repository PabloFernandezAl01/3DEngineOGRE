#include "Game.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"

using namespace ECS;

ECS::Scene* Game::CreateGameScene()
{
    Scene* mScene = new Scene("GameScene");

    Entity* ent = mScene->CreateEntity("Ogre");
    auto* tr = ent->AddComponent<Transform>();
    auto* mesh = ent->AddComponent<Mesh>();
    mesh->SetMeshName("ogrehead.mesh");

    return mScene;
}

void MyScript::Init()
{
    tr = entity->GetComponent<Transform>();
}

void MyScript::Update(float dt)
{

}
