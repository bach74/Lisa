// =============================================================================
//  misc.cpp   version:  1.0
//  
//  Copyright (C) 2007 by Bach - All Rights Reserved
// 
// =============================================================================

#include "stdafx.h"
#include "misc.h"


std::string getStringFromResource(UINT resourceID)
{
	CAtlString s;
	s.LoadString(resourceID);
	return std::string(s);
}

/*std::wstring getStringFromResourceW(UINT resourceID)
{
	CAtlString s;
	s.LoadString(resourceID);
	return std::string(s);
}*/

/*void createColourCube()
{
	/// Create the mesh via the MeshManager
	Ogre::MeshPtr msh = MeshManager::getSingleton().createManual("ColourCube", "General");

	/// Create one submesh
	SubMesh* sub = msh->createSubMesh();

	const float sqrt13 = 0.577350269f; // sqrt(1/3)

	/// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
	const size_t nVertices = 8;

	const size_t vbufCount = 3*2*nVertices;

	float vertices[vbufCount] =
		{
			-100.0,100.0,-100.0,        //0 position
			-sqrt13,sqrt13,-sqrt13,     //0 normal
			100.0,100.0,-100.0,         //1 position
			sqrt13,sqrt13,-sqrt13,      //1 normal
			100.0,-100.0,-100.0,        //2 position
			sqrt13,-sqrt13,-sqrt13,     //2 normal
			-100.0,-100.0,-100.0,       //3 position
			-sqrt13,-sqrt13,-sqrt13,    //3 normal
			-100.0,100.0,100.0,         //4 position
			-sqrt13,sqrt13,sqrt13,      //4 normal
			100.0,100.0,100.0,          //5 position
			sqrt13,sqrt13,sqrt13,       //5 normal
			100.0,-100.0,100.0,         //6 position
			sqrt13,-sqrt13,sqrt13,      //6 normal
			-100.0,-100.0,100.0,        //7 position
			-sqrt13,-sqrt13,sqrt13,     //7 normal
		};

	RenderSystem* rs = Root::getSingleton().getRenderSystem();

	RGBA colours[nVertices];

	RGBA *pColour = colours;

	// Use render system to convert colour value since colour packing varies
	rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
	rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
	rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
	rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour
	rs->convertColourValue(ColourValue(1.0,0.0,1.0), pColour++); //4 colour
	rs->convertColourValue(ColourValue(1.0,1.0,1.0), pColour++); //5 colour
	rs->convertColourValue(ColourValue(0.0,1.0,1.0), pColour++); //6 colour
	rs->convertColourValue(ColourValue(0.0,0.0,1.0), pColour++); //7 colour

	/// Define 12 triangles (two triangles per cube face)
	/// The values in this table refer to vertices in the above table
	const size_t ibufCount = 36;

	unsigned short faces[ibufCount] =
		{
			0,2,3,
			0,1,2,
			1,6,2,
			1,5,6,
			4,6,5,
			4,7,6,
			0,7,4,
			0,3,7,
			0,5,1,
			0,4,5,
			2,7,3,
			2,6,7
		};

	/// Create vertex data structure for 8 vertices shared between submeshes
	msh->sharedVertexData = new VertexData();
	msh->sharedVertexData->vertexCount = nVertices;

	/// Create declaration (memory format) of vertex data
	VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;

	size_t offset = 0;

	// 1st buffer
	decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
	decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
	offset += VertexElement::getTypeSize(VET_FLOAT3);

	/// Allocate vertex buffer of the requested number of vertices (vertexCount)
	/// and bytes per vertex (offset)
	HardwareVertexBufferSharedPtr vbuf =
		HardwareBufferManager::getSingleton().createVertexBuffer(
			offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the vertex data to the card
	vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

	/// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
	VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding;

	bind->setBinding(0, vbuf);

	// 2nd buffer
	offset = 0;
	decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
	offset += VertexElement::getTypeSize(VET_COLOUR);

	/// Allocate vertex buffer of the requested number of vertices (vertexCount)
	/// and bytes per vertex (offset)
	vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
			   offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the vertex data to the card
	vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);
	/// Set vertex buffer binding so buffer 1 is bound to our colour buffer
	bind->setBinding(1, vbuf);
	/// Allocate index buffer of the requested number of vertices (ibufCount)
	HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
										createIndexBuffer(
											HardwareIndexBuffer::IT_16BIT,
											ibufCount,
											HardwareBuffer::HBU_STATIC_WRITE_ONLY);

	/// Upload the index data to the card
	ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);
	/// Set parameters of the submesh
	sub->useSharedVertices = true;
	sub->indexData->indexBuffer = ibuf;
	sub->indexData->indexCount = ibufCount;
	sub->indexData->indexStart = 0;
	/// Set bounding information (for culling)
	msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
	msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));
	/// Notify Mesh object that it has been loaded
	msh->load();

	//    // Create a mesh
	//   MaterialPtr material = MaterialManager::getSingleton().create(
	//    "Test/ColourTest", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//   material->getTechnique(0)->getPass(0)->setVertexColourTracking(TVC_AMBIENT);
	//   createColourCube();
	//   Entity* thisEntity = mSceneMgr->createEntity("cc", "ColourCube");
	//   thisEntity->setMaterialName("Test/ColourTest");
	//   SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//   thisSceneNode->scale(0.04,0.04,0.04);
	//   thisSceneNode->setPosition(pppos);
	//   thisSceneNode->attachObject(thisEntity);

}*/

void DumpNodes(std::stringstream &ss, Ogre::Node *n, int level)
{
	for (int i = 0; i < level; i++)
	{
		ss << " ";
	}

	ss << "SceneNode: " << n->getName() << std::endl;

	Ogre::SceneNode::ObjectIterator object_it = ((Ogre::SceneNode *)n)->getAttachedObjectIterator();
	Ogre::Node::ChildNodeIterator node_it = n->getChildIterator();

	Ogre::MovableObject *m;

	while (object_it.hasMoreElements())
	{
		for (int i = 0; i < level + 2; i++)
		{
			ss << " ";
		}

		m = object_it.getNext();
		ss << m->getMovableType() << ": " << m->getName() << std::endl;
	}

	while (node_it.hasMoreElements())
	{
		DumpNodes(ss, node_it.getNext(), level + 2);
	}
}


std::string DumpNodes(Ogre::Node *n)
{
	std::stringstream ss;
	ss << std::endl << "Node Hierarchy:" << std::endl;
	DumpNodes(ss, n, 0);
	return ss.str();
}
