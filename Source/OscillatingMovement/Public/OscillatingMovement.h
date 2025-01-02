// MaxEstLa - Oscillating Movement Component - ALL RIGHTS RESERVED 2025

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FOscillatingMovementModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
