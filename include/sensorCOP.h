#pragma once
#include "sensor.h"
#include "contactReporter.h"

/**-------------------------------------------------------------------------------
	SensorCOP

	First vector is COP position, following vectors are support polygon extremes
---------------------------------------------------------------------------------*/
class SensorCOP : public SensorVectors
{
	public:
		SensorCOP(Simulation* simulation);
		~SensorCOP(void);

	protected:
		virtual void update();

	private:
		std::vector<boost::shared_ptr<MyContactReporter> >  mContactReporters;		
};
