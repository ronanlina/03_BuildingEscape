// Copyright Ronan Lina

#include "OpenDoor.h"
#include "Gameframework/Actor.h"


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

	AActor* Owner = GetOwner();//SetActorRotation(true,90);

	//Implements a container for rotation information 
	FRotator NewRotation = FRotator(0.0f, 90.0f, 0.0f); //Rotator object instantiation w/ parameters
	//							pitch = y, yaw = z, roll = x
	//Owner->SetActorEnableCollision(true);
	Owner->SetActorRotation(NewRotation);
	// ...
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
