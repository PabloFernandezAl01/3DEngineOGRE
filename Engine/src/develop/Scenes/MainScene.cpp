#include "MainScene.h"
#include "Scene.h"
#include "Entity.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/Camera.h"
#include "Components/Light.h"
#include "Components/PlaneMesh.h"
#include "Components/Animator.h"
#include "../Scripts/CameraController.h"
#include "../Scripts/MyScript.h"
#include "../Scripts/ConfigScene.h"
#include "../Scripts/CharacterController.h"

MainScene::MainScene()
{
    CreateObjects();
    CreateCamera();
    CreateLights();
}

void MainScene::CreateObjects()
{
    // CONFIG SCENE
    Entity* configSceneEnt = this->CreateEntity("ConfigScene");
    configSceneEnt->AddComponent<Transform>();
    configSceneEnt->AddComponent<ConfigScene>();

    // SIMBAD
    Entity* sinbadEnt = this->CreateEntity("Simbad");
    auto* sinnbadEntTr = sinbadEnt->AddComponent<Transform>();
    auto* sinbadMesh = sinbadEnt->AddComponent<Mesh>();
    auto* sinbadAnimator = sinbadEnt->AddComponent<Animator>();
    auto* characterController = sinbadEnt->AddComponent<CharacterController>();

    sinbadMesh->SetMeshName("Sinbad.mesh");
    sinbadMesh->SetCastShadows(true);

    sinnbadEntTr->SetScale({ 1, 1, 1 });
    sinnbadEntTr->SetPosition({0, 5, 0});

    // PLANE
    Entity* planeEnt = this->CreateEntity("MeshPlane");
    auto* planeTr = planeEnt->AddComponent<Transform>();
    auto* planeMesh = planeEnt->AddComponent<PlaneMesh>();

    planeMesh->SetName("ground");
    planeMesh->SetNormal({ 0, 1, 0 });
    planeMesh->SetDistanceFromOrigin({});
    planeMesh->SetSize({ 150, 150 });
    planeMesh->SetSegments({ 20, 20 });
    planeMesh->SetUTile(5);
    planeMesh->SetVTile(5);
    planeMesh->SetUpVector({ 0, 0, 1 });

    planeMesh->SetMaterial("Examples/Rockwall");
}

void MainScene::CreateCamera()
{
    Entity* cameraRoot = this->CreateEntity("CameraRoot"); // Yaw rotation
    auto* cameraRootTr = cameraRoot->AddComponent<Transform>();
    cameraRootTr->SetPosition({ 0, 20, 20 });

    Entity* mainCamera = this->CreateEntity("MainCamera", cameraRoot); // Pitch rotation

    auto* mainCameraTr = mainCamera->AddComponent<Transform>();
    auto* cam = mainCamera->AddComponent<Camera>();
    mainCamera->AddComponent<CameraController>();

    cam->SetNearClipDistance(1);
    cam->SetAutoAspectRatio(true);
    cam->SetFarClipDistance(0);
    cam->SetBackgroundColor({ 0.9, 0.9, 0.9 });
}

void MainScene::CreateLights()
{
    // DIRECTIONAL
    Entity* lightEnt = this->CreateEntity("DirLight");
    auto* lightEntTr = lightEnt->AddComponent<Transform>();
    auto* dirLight = lightEnt->AddComponent<Light>();

    lightEntTr->SetOrientation(Quaternion::FromEulerAngles({ 315, 0, 0 }));
    lightEntTr->SetPosition({ 0, 200, 100 });

    dirLight->SetType(Light::LightType::DIRECTIONAL);
    dirLight->SetDiffuse({ 1.0, 1.0, 1.0 });
    dirLight->SetSpecular({ 1.0, 1.0, 1.0 });

    // POINT
    /*Entity* pointLightEnt = this->CreateEntity("Point");
    auto* pointLightEntTr = pointLightEnt->AddComponent<Transform>();
    auto* pointlight = pointLightEnt->AddComponent<Light>();

    pointLightEntTr->SetPosition({100, 200, 0});

    pointlight->SetType(Light::LightType::POINT);
    pointlight->SetDiffuse({ 1.0, 0, 0 });
    pointlight->SetSpecular({ 1.0, 0, 0 });*/

    // SPOTLIGHT
    /*Entity* spotLightEnt = this->CreateEntity("Spot");
    auto* spotLightEntTr = spotLightEnt->AddComponent<Transform>();
    auto* spotlight = spotLightEnt->AddComponent<Light>();

    spotLightEntTr->SetPosition({ -200, 200, 0 });
    spotLightEntTr->SetOrientation(Quaternion::FromEulerAngles({315, -90, 0}));

    spotlight->SetType(Light::LightType::SPOTLIGHT);
    spotlight->SetDiffuse({ 0, 1.0, 0 });
    spotlight->SetSpecular({ 0, 1.0, 0 });
    spotlight->SetSpotLightInnerAngle(35);
    spotlight->SetSpotLightOuterAngle(50);*/
}