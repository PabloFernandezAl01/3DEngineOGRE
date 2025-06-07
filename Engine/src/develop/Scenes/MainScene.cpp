#include "MainScene.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Light.h"
#include "../Scripts/CameraController.h"

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
    mesh->SetMeshName("WoodPallet.mesh");

    tr->SetPosition({ 0, 0, 0 });
}

void MainScene::CreateCamera()
{
    Entity* cameraRoot = this->CreateEntity("CameraRoot"); // Yaw rotation
    auto* tr = cameraRoot->AddComponent<Transform>();
    tr->SetPosition({ 0, 0, 200 });

    Entity* mainCamera = this->CreateEntity("MainCamera", cameraRoot); // Pitch rotation

    mainCamera->AddComponent<Transform>();
    auto* cam = mainCamera->AddComponent<Camera>();
    mainCamera->AddComponent<CameraController>();

    cam->SetNearClipDistance(1);
    cam->SetAutoAspectRatio(true);
}

void MainScene::CreateLight()
{
    Entity* dirLight = this->CreateEntity("Light");
    auto* tr = dirLight->AddComponent<Transform>();
    auto* light = dirLight->AddComponent<Light>();

    light->SetType(Light::LightType::DIRECTIONAL);
    light->SetDiffuse({ 1, 1, 0 });

    tr->SetPosition({ 0, 0, 50 });
}