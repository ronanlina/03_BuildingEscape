// Copyright Ronan Lina

#include "Grabber.h"
#include "Gameframework/PlayerController.h"
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GRABBER REPORTING"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//get player view point
	FVector PlayerViewPointPosition;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointPosition,
		OUT PlayerViewPointRotation
	);
	//LOG each tick
	//while (DeltaTime) {
			UE_LOG(LogTemp, Warning, TEXT("View Point Log: POS: %s ROT: %s"),
			*PlayerViewPointPosition.ToString(), *PlayerViewPointRotation.ToString()); //remember the pointers *
	//}
	//ray-cast out to reach distance

	//see what we hit
	// ...
}

