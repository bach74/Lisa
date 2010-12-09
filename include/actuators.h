#pragma once

#include "actuator.h"

class Sensors;

/**----------------------------------------------------------------------------
   Maintains actuator collection
 -----------------------------------------------------------------------------*/
class Actuators
{
	public:
		Actuators(NxOgre::Scene* mPhyScene, Sensors* sensors);
		~Actuators();

		friend class ActuatorIterator;

		int size() const { return mActuators.size(); }

		void update(float frameTime);

	private:

		void addActuator(Joint* node);

		std::vector<boost::shared_ptr<Actuator > >::iterator begin() { return mActuators.begin(); }
		std::vector<boost::shared_ptr<Actuator > >::iterator end() { return mActuators.end(); }

		std::vector<boost::shared_ptr<Actuator > > mActuators;

};



/**----------------------------------------------------------------------------
   Actuator iterator

 -----------------------------------------------------------------------------*/
class ActuatorIterator : public boost::iterator_facade<ActuatorIterator, Actuator, boost::forward_traversal_tag>
{
	public:
		ActuatorIterator(Actuators* controllers): mActuators(controllers) { begin(); };
		~ActuatorIterator() {};

		ActuatorIterator& begin();
		bool end();

		const boost::shared_ptr<Actuator >& get() {return *mNode; }

	private:
		ActuatorIterator(): mActuators(NULL) {};

		friend class boost::iterator_core_access;

		void increment()    { ++mNode; }
		bool equal(ActuatorIterator const& other) const;
		Actuator& dereference() const { return *(*mNode); }

		std::vector<boost::shared_ptr<Actuator > >::iterator mNode;
		Actuators* mActuators;
};
