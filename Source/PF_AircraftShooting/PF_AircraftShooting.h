// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPF_AircraftShooting, Log, All);

#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC
//#define FUNC_NAME    TEXT(__func__)
#define FUNC_NAME    *FString(__func__)
#endif

#define print(Format, ...) \
{ \
    FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
	if (Msg == "") \
	{ \
		Msg = FString::Printf(TEXT("%s():%s"), FUNC_NAME, *GetNameSafe(this));\
	} \
	else \
	{ \
		Msg = FString::Printf(TEXT("%s():%s"), FUNC_NAME, *Msg);\
	} \
    if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, *Msg); \
}