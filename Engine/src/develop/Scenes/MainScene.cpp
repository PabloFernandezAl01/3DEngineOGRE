#include "MainScene.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Light.h"

MainScene::MainScene()
{
    CreateOgre();
    CreateCamera();
    CreateLight();
}

void MainScene::CreateOgre()
{
    Entity* ogre = this->CreateEntity("Ogre");
    auto* tr = ogre->AddComponent<Transform>();
    auto* mesh = ogre->AddComponent<Mesh>();
    mesh->SetMeshName("ogrehead.mesh");
}

void MainScene::CreateCamera()
{
    Entity* mainCamera = this->CreateEntity("MainCamera");
    auto* tr = mainCamera->AddComponent<Transform>();
    auto* cam = mainCamera->AddComponent<Camera>();

    tr->SetPosition({ 0, 0, 15 });
    cam->SetNearClipDistance(5);
    cam->SetAutoAspectRatio(true);
}

void MainScene::CreateLight()
{
    Entity* dirLight = this->CreateEntity("Light");
    auto* tr = dirLight->AddComponent<Transform>();
    auto* light = dirLight->AddComponent<Light>();

    tr->SetPosition({ 0, 10, 15 });
}