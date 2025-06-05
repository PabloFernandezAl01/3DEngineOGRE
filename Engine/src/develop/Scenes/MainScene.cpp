#include "MainScene.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Light.h"
#include "../Scripts/MyScript.h"

MainScene::MainScene()
{
    //CreateOgre();
    CreateCamera();
    CreateLight();
}

void MainScene::CreateOgre()
{
    Entity* ogre = this->CreateEntity("Ogre");
    auto* tr = ogre->AddComponent<Transform>();
    auto* mesh = ogre->AddComponent<Mesh>();
    auto* script = ogre->AddComponent<MyScript>();
    mesh->SetMeshName("ogrehead.mesh");
}

void MainScene::CreateCamera()
{
    Entity* mainCamera = this->CreateEntity("MainCamera");
    auto* tr = mainCamera->AddComponent<Transform>();
    auto* cam = mainCamera->AddComponent<Camera>();

    tr->SetPosition({ 0, 0, 200 });
    cam->SetNearClipDistance(1);
    cam->SetAutoAspectRatio(true);
    cam->SetProjectionType(Camera::ProjectionType::PERSPECTIVE);
    cam->SetPolygonMode(Camera::PolygonMode::SOLID);
}

void MainScene::CreateLight()
{
    Entity* dirLight = this->CreateEntity("Light");
    auto* tr = dirLight->AddComponent<Transform>();
    auto* light = dirLight->AddComponent<Light>();

    tr->SetPosition({ 20, 80, 50 });
}