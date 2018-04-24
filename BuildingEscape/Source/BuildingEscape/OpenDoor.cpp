// Copyright Ronan Lina

#include "OpenDoor.h"
#include "Gameframework/Actor.h"
#include "Gameframework/PlayerController.h" //add header file for the GetWorld() to work
#include "Engine/TriggerVolume.h"
#include "Engine/World.h" //add header file for the GetWorld() to work


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//OpenDoor();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{
	//Finding the owner. the current actor with this script(?)
	AActor* Owner = GetOwner();//SetActorRotation(true,90);

	//Create a rotator	   								    //Implements a container for rotation information 
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f); //Rotator object instantiation w/ parameters
															//pitch = y, yaw = z, roll = x
	//Set door rotation 									//Owner->SetActorEnableCollision(true);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//polling the trigger volume. checking condition every frame
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
	}
	// ...
}

