// Copyright Ronan Lina

#include "Grabber.h"
#include "Gameframework/PlayerController.h"
#include "DrawDebugHelpers.h"
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

	//finds physics handle component existing in the current pawn/blueprint
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{

	}
	else
	{
		UE_LOG(LogTemp, Error,TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}

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
	/*UE_LOG(LogTemp, Warning, TEXT("View Point Log: POS: %s ROT: %s"),
		*PlayerViewPointPosition.ToString(),
		*PlayerViewPointRotation.ToString())*/ //remember the pointers *

	FVector LineTraceEnd = PlayerViewPointPosition + (PlayerViewPointRotation.Vector() * Reach); 
	//Draw red trace
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointPosition,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	//setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	//line trace/ray-cast out to reach distance
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointPosition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTOR : %s"), *(ActorHit->GetName()))
	}

	/*GetWorld()->LineTraceSingleByObjectType*/
	//see what we hit
	// ...
}

