#pragma once

#include "PawnEventInterface.generated.h"

UINTERFACE(BlueprintType)
class PF_AIRCRAFTSHOOTING_API UPawnEventInterface : public UInterface
{
	GENERATED_BODY()
};

class PF_AIRCRAFTSHOOTING_API IPawnEventInterface
{
	GENERATED_BODY()

public:
	virtual void AddScore(int32 AddScoreValue) {}
};