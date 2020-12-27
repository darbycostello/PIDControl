
#pragma once

#include "CoreMinimal.h"

class FPIDControl : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

