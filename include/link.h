#pragma once
#include "boost/iterator/iterator_facade.hpp"

/**-------------------------------------------------------------------------------
	Class Link represents dynamic objects in the simulation.
	It is the abstraction of NxOgre::Actor class, which itself is the abstraction of 
	PhysX NxActor. 
---------------------------------------------------------------------------------*/
class Link
{
	public:
		Link(NxOgre::Actor* actor):mActor(actor),mPrevVelocity(0,0,0),mPrevAngularMomentum(0,0,0) {};
		~Link() {};

		Ogre::String getName() { return mActor->getName(); }
		NxActor* getNxActor() { return mActor->getNxActor(); }

		bool isDynamic() { return mActor->isDynamic(); }
		void clearActorFlag(NxActorFlag flag) { mActor->clearActorFlag(flag); }
		void setGroup(const Ogre::String groupName) { mActor->setGroup(groupName); }
		bool hasActorFlag(NxActorFlag flag) { return mActor->hasActorFlag(flag); }
		void setPrevVelocity(Ogre::Vector3 velocity) { mPrevVelocity=velocity; }
		void setPrevAngularMomentum(Ogre::Vector3 val) { mPrevAngularMomentum = val; }

		Ogre::Vector3 getAngularVelocity() { return mActor->getAngularVelocity(); }
		Ogre::Vector3 getAngularMomentum() { return mActor->getAngularMomentum(); }		// angular momentum L
		Ogre::Vector3 getLinearVelocity() { return mActor->getLinearVelocity(); }
		Ogre::Vector3 getCMassGlobalPosition() {return mActor->getCMassGlobalPosition(); }
		Ogre::Vector3 getLinerAcceleration(float deltaTime) { return (deltaTime!=0.0)?(mActor->getLinearVelocity()-mPrevVelocity)*1.0/deltaTime:Ogre::Vector3(0,0,0); }
		Ogre::Vector3 getAngularMomentumDelta(float deltaTime) { return (deltaTime!=0.0)?(mActor->getAngularMomentum()-mPrevAngularMomentum)*1.0/deltaTime:Ogre::Vector3(0,0,0); }

		void addForce(Ogre::Vector3 force, NxForceMode type) { mActor->addForce(force, type); }
		void addLocalTorque(Ogre::Vector3 torque, NxForceMode type=NX_FORCE) { mActor->addLocalTorque(torque,type); }

		NxReal getMass() { return mActor->getMass(); }
	private:
		Link() {};

		NxOgre::Actor *mActor;
		Ogre::Vector3 mPrevVelocity;
		Ogre::Vector3 mPrevAngularMomentum;

};


class Links
{

	public:
		Links() {};
		~Links() { mLinks.clear(); };

		friend class LinkIterator;

		size_t size() { return mLinks.size(); }
		void add(boost::shared_ptr<Link> link) { mLinks.push_back(link); }

		typedef LinkIterator iterator;

	private:
		std::vector<boost::shared_ptr<Link> >::iterator begin() { return mLinks.begin(); }
		std::vector<boost::shared_ptr<Link> >::iterator end() { return mLinks.end(); }

		std::vector<boost::shared_ptr<Link> > mLinks;
};


class LinkIterator : public boost::iterator_facade<LinkIterator, Link, boost::forward_traversal_tag>
{
	public:
		LinkIterator(Links* links):mLinks(links) { begin();};
		~LinkIterator() {};

		LinkIterator& begin();
		bool end();

	private:
		LinkIterator():mLinks(NULL) {};

		friend class boost::iterator_core_access;

		void increment();
		bool equal(LinkIterator const& other) const;
		Link& dereference() const { return *(*mNode); }

		std::vector<boost::shared_ptr<Link> >::iterator mNode;
		Links* mLinks;
};
