// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MDJ.h"
#include "MDJPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"

AMDJPlayerController::AMDJPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AMDJPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	/*if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}*/
}

void AMDJPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AMDJPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMDJPlayerController::MoveRight);
	InputComponent->BindAction("Action", IE_Pressed, this, &AMDJPlayerController::ActionStart);
	InputComponent->BindAction("Action", IE_Released, this, &AMDJPlayerController::ActionEnd);


	/*
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMDJPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMDJPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMDJPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMDJPlayerController::MoveToTouchLocation);
	*/
	}


void AMDJPlayerController::MoveForward(float Value)
{
	APawn* const Controller = GetPawn();
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		Controller->AddMovementInput(Direction, Value);
	}
}

void AMDJPlayerController::MoveRight(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("yo"));
	APawn* const Controller = GetPawn();
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		Controller->AddMovementInput(Direction, Value);
	}
}

void AMDJPlayerController::ActionStart()
{

	UE_LOG(LogTemp, Warning, TEXT("Queijo"));
}

void AMDJPlayerController::ActionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("FIAMBRE"));
}





////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////            RECICLAGEM         ///////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

void AMDJPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMDJPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMDJPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMDJPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMDJPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}