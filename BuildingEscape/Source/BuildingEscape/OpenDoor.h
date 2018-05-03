// Copyright Ronan Lina

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent); // creates a new class. operations performed by the blue print.

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

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnOpen; // a blueprint event

	UPROPERTY(BlueprintAssignable)
		FDoorEvent OnClose;
private:

	UPROPERTY(EditAnywhere)//MACROS. always check UE4 docs for more MACRO infos.
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		float TriggerMass;

	//UPROPERTY(EditAnywhere)
		AActor* ActorThatOpens; //pawn inherits from actor
		AActor* Owner;

		float GetTotalMassOfActorsOnPlate();
};
