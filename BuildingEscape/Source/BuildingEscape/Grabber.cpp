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
}

FVector UGrabber::GetLineTraceEnd() 
{
	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointPosition,
		OUT PlayerViewPointRotation
	);

	//Line Trace End formula
	return PlayerViewPointPosition + (PlayerViewPointRotation.Vector() * Reach);
}

void UGrabber::FindPhysicsHandleComponent()
{
	//finds physics handle component existing in the current pawn/blueprint
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error,TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent != nullptr)
	{
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
		//LINE TRACE and Try and reach any actors with physice body collision channel set
		auto HitResult = GetFirstPhysicsBodyInReach();
		auto ComponentToGrab = HitResult.GetComponent();
		auto ActorHit = HitResult.GetActor();

		//If we hit something then attach a physics handle
		if(ActorHit){
			//attach physics handle
				PhysicsHandle->GrabComponent(
				ComponentToGrab,//what was hit
				NAME_None,// the "bone"
				ComponentToGrab->GetOwner()->GetActorLocation(),//actor location 
				true //allow the rotation
				);
		}
}

void UGrabber::Release()
{
		PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//setup query params
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//line trace/ray-cast out to reach distance
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointPosition,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//identifies which actor was hit
	AActor* ActorHit = Hit.GetActor();

	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACTOR : %s"), *(ActorHit->GetName()))
	}
	return Hit; //returns what was hit
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
		// Move the object that we're holding
}

