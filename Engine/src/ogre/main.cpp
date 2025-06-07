//#include <Ogre.h>
//#include <OgreApplicationContextBase.h>
//#include <OgreRoot.h>
//#include <OgreSceneManager.h>
//#include <OgreRenderWindow.h>
//#include <OgreEntity.h>
//#include <OgreCamera.h>
//#include <OgreViewport.h>
//#include <OgreConfigFile.h>
//#include <OgreWindowEventUtilities.h>
//#include <OgreColourValue.h>
//
//int main()
//{
//	Ogre::Root* root = new Ogre::Root();
//
//	auto& renderers = root->getAvailableRenderers();
//	root->setRenderSystem(renderers[1]);
//
//	Ogre::RenderWindow* renderWindow = root->initialise(true);
//
//	Ogre::ConfigFile cf;
//	cf.load("resources.cfg");
//
//	auto settingsBySection = cf.getSettingsBySection();
//
//	for (const auto& [sectionName, settings] : settingsBySection)
//	{
//		for (const auto& [type, path] : settings)
//		{
//			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(path, type, sectionName);
//		}
//	}
//
//	Ogre::SceneManager* sceneManager = root->createSceneManager();
//    sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
//
//    // register our scene with the RTSS
//    /*RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
//    shadergen->addSceneManager(sceneManager);*/
//
//	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
//
//	// Mesh
//	Ogre::Entity* ent = sceneManager->createEntity("ogrehead.mesh");
//	Ogre::SceneNode* node = sceneManager->getRootSceneNode()->createChildSceneNode();
//	node->attachObject(ent);
//
//	// Camera
//	Ogre::Camera* cam = sceneManager->createCamera("MainCam");
//	Ogre::SceneNode* camNode = sceneManager->getRootSceneNode()->createChildSceneNode();
//	camNode->attachObject(cam);
//	camNode->lookAt({ 0, 0, -1 }, Ogre::Node::TS_WORLD);
//	camNode->setPosition({ 0, 0, 200 });
//	cam->setNearClipDistance(5);
//	cam->setAutoAspectRatio(true);
//	Ogre::Viewport* viewport = renderWindow->addViewport(cam);
//
//	// Light
//	Ogre::Light* light = sceneManager->createLight("Light");
//	Ogre::SceneNode* lightNode = sceneManager->getRootSceneNode()->createChildSceneNode();
//	lightNode->attachObject(light);
//	lightNode->setPosition({ 20, 80, 50 });
//
//    while (!renderWindow->isClosed())
//    {
//        Ogre::WindowEventUtilities::messagePump();
//
//        if (!root->renderOneFrame())
//            break;
//    }
//}
























/*-------------------------------------------------------------------------
This source file is a part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/


Copyright (c) 2000-2013 Torus Knot Software Ltd
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE
-------------------------------------------------------------------------*/

//! [fullsource]

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class BasicTutorial1
    : public ApplicationContext
    , public InputListener
{
public:
    BasicTutorial1();
    virtual ~BasicTutorial1() {}

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


BasicTutorial1::BasicTutorial1()
    : ApplicationContext("OgreTutorialApp")
{
}


void BasicTutorial1::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    // -- tutorial section start --
    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    scnMgr->setDisplaySceneNodes(true);
    //! [turnlights]

    //! [newlight]
    Light* light = scnMgr->createLight("MainLight");
    light->setType(Ogre::Light::LT_POINT);
    SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(5,5,0);
    //! [lightpos]

    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    camNode->setPosition(0, 0, 220);

    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
    //! [camera]

    //! [entity1]
    Entity* ogreEntity = scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    ogreNode->attachObject(ogreEntity);
    //! [entity1]

    //! [entity2]
    Entity* ogreEntity2 = scnMgr->createEntity("ogrehead.mesh");
    SceneNode* ogreNode2 = scnMgr->getRootSceneNode()->createChildSceneNode(Vector3(84, 48, 0));
    ogreNode2->attachObject(ogreEntity2);
    //! [entity2]

    ////! [entity3]
    //Entity* ogreEntity3 = scnMgr->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    //ogreNode3->setPosition(0, 104, 0);
    //ogreNode3->setScale(2, 1.2, 1);
    //ogreNode3->attachObject(ogreEntity3);
    ////! [entity3]

    ////! [entity4]
    //Entity* ogreEntity4 = scnMgr->createEntity("ogrehead.mesh");
    //SceneNode* ogreNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
    //ogreNode4->setPosition(-84, 48, 0);
    //ogreNode4->roll(Degree(-90));
    //ogreNode4->attachObject(ogreEntity4);
    //! [entity4]

    // -- tutorial section end --
}


bool BasicTutorial1::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char** argv)
{
    try
    {
        BasicTutorial1 app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

//! [fullsource]

