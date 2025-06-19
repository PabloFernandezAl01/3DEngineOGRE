#include "MainScene.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Light.h"
#include "../Scripts/CameraController.h"
#include "../Scripts/MyScript.h"

MainScene::MainScene()
{
    CreateObjects();
    CreateCamera();
    CreateLight();
}

void MainScene::CreateObjects()
{
    Entity* face = this->CreateEntity("Ogre");
    face->AddComponent<Transform>();
    auto* mesh = face->AddComponent<Mesh>();
    mesh->SetMeshName("facial.mesh");

    Entity* cube = this->CreateEntity("Cube", face);
    auto* tr = cube->AddComponent<Transform>();
    cube->AddComponent<MyScript>();
    tr->SetPosition({ 0, -50, 0 });
    tr->SetScale({ 0.3f, 0.3f, 0.3f });
    //tr->SetOrientation(Quaternion::FromEulerAngles({ 0, 45, 0 }));
    auto* mesh2 = cube->AddComponent<Mesh>();
    mesh2->SetMeshName("cube.mesh");
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
    cam->SetFarClipDistance(10000);
}

void MainScene::CreateLight()
{
    Entity* dirLight = this->CreateEntity("Light");
    auto* tr = dirLight->AddComponent<Transform>();
    auto* light = dirLight->AddComponent<Light>();

    light->SetType(Light::LightType::DIRECTIONAL);
    light->SetDiffuse({ 1, 1, 1 });

    tr->SetPosition({ 0, 0, 50 });
}