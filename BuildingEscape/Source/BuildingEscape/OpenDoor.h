// Copyright Ronan Lina

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();

	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)//MACROS. always check UE4 docs for more MACRO infos.
		float OpenAngle = 45.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlateOpen;

	UPROPERTY(EditAnywhere)
		ATriggerVolume*	PressurePlateClose;

	UPROPERTY(EditAnywhere)
		float	DoorCloseDelay = 1.0f;

		float	LastDoorOpenTime;

	//UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens; //pawn inherits from actor
		AActor* Owner;
};
