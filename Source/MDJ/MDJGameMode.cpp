// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MDJ.h"
#include "MDJGameMode.h"
#include "MDJPlayerController.h"
#include "MDJCharacter.h"

AMDJGameMode::AMDJGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMDJPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}