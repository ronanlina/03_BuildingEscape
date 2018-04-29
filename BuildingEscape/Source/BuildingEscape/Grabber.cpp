// Copyright Ronan Lina

#include "Grabber.h"
#include "Gameframework/PlayerController.h"
#include "DrawDebugHelpers.h" //for the debug line
#include "Engine/World.h"

#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("GRABBER REPORTING"));


}

void UGrabber::FindPhysicsHandleComponent()
{
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

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("input component found"))
			///Binding the input
			InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::UGrabber::Grab);// where grab is mapped in project settings>input>action mapping
																							//key map, key event, context(?), method
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::UGrabber::Release);
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))
	
		//LINE TRACE and Try and reach any actors with physice body collision channel set
		GetFirstPhysicsBodyInReach();

		//If we hit something then attach a physics handle
		// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released"))

	//Release physics handle
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//get player view point
	FVector PlayerViewPointPosition;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointPosition,
		OUT PlayerViewPointRotation
	);

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

	//identifies which actor was hit
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTOR : %s"), *(ActorHit->GetName()))
	}
	return FHitResult();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
		// Move the object that we're holding

	
}

