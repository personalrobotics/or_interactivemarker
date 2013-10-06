/*
 * KinBodyVisual.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: mklingen
 */

#include "../Converters.h"

#include "KinBodyVisual.h"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreMesh.h>

#include "LinkVisual.h"

namespace superviewer
{

    KinBodyVisual::KinBodyVisual(Ogre::SceneManager* sceneManager, Ogre::SceneNode* parentNode, OpenRAVE::KinBodyPtr kinBody) :
            m_kinBody(kinBody), m_sceneManager(sceneManager), m_parentNode(parentNode)
    {
        m_sceneNode = m_parentNode->createChildSceneNode();
        m_sceneNode->setPosition(kinBody->GetTransform().trans.x, kinBody->GetTransform().trans.y, kinBody->GetTransform().trans.z);
        m_sceneNode->setOrientation(converters::ToOgreQuaternion(kinBody->GetTransform().rot));
        CreateParts();
    }

    KinBodyVisual::~KinBodyVisual()
    {
        if(m_sceneNode)
        {
            m_sceneManager->destroySceneNode(m_sceneNode);
            m_sceneNode = NULL;
        }

        for(size_t i = 0; i < m_links.size(); i++)
        {
            delete m_links[i];
        }

    }


    void KinBodyVisual::UpdateTransforms()
    {
        m_sceneNode->setPosition(converters::ToOgreVector(m_kinBody->GetTransform().trans));
        m_sceneNode->setOrientation(converters::ToOgreQuaternion(m_kinBody->GetTransform().rot));
        for(size_t i = 0; i < m_kinBody->GetLinks().size(); i++)
        {
            LinkVisual* visual = m_links.at(i);
            OpenRAVE::KinBody::LinkPtr link = m_kinBody->GetLinks().at(i);

            OpenRAVE::Transform relativeTransform = m_kinBody->GetTransform().inverse() * link->GetTransform();

            visual->GetSceneNode()->setPosition(converters::ToOgreVector(relativeTransform.trans));
            visual->GetSceneNode()->setOrientation(converters::ToOgreQuaternion(relativeTransform.rot));
        }
    }

    void KinBodyVisual::CreateParts()
    {
        for(size_t i = 0; i < m_kinBody->GetLinks().size(); i++)
        {
            LinkVisual* linkVisual = new LinkVisual(this, m_kinBody->GetLinks().at(i), m_sceneNode, m_sceneManager);
            m_links.push_back(linkVisual);
        }
    }

} /* namespace superviewer */
