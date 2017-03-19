#ifndef EJECT_FUEL_H
#define EJECT_FUEL_H

#include <Commands/Shooter/RunShooter.h>
#include "../../CommandBase.h"
#include "Robot.h"

class EjectFuel: public Command {
public:
	EjectFuel();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
	double speedAtShooterError(double e);
};

#endif  // EXAMPLE_COMMAND_H
