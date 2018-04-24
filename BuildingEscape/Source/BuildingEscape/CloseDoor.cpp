// Copyright Ronan Lina

#include "CloseDoor.h"
#include "Gameframework/Actor.h"
#include "Gameframework/PlayerController.h" //add header file for the GetWorld() to work
#include "Engine/TriggerVolume.h"
#include "Engine/World.h" //add header file for the GetWorld() to work


// Sets default values for this component's properties
UCloseDoor::UCloseDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCloseDoor::BeginPlay()
{
	Super::BeginPlay();
	
	ActorThatCloses = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UCloseDoor::CloseDoor()
{
	//Finding the owner. the current actor with this script(?)
	AActor* Owner = GetOwner();//SetActorRotation(true,90);

							   //Create a rotator	   						
	FRotator NewRotation = FRotator(0.0f, CloseAngle, 0.0f); 
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UCloseDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//polling the trigger volume. checking condition every frame
	if (PressurePlate->IsOverlappingActor(ActorThatCloses)) {
		CloseDoor();
	}
	// ...
}

