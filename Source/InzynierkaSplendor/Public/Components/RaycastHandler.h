

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaycastHandler.generated.h"

class APlayerPawn;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INZYNIERKASPLENDOR_API URaycastHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URaycastHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Raycast(FVector mousePos, FVector mouseDir);
	

private:
	void InitializePawn();
	APlayerPawn* playerPawn;
};
