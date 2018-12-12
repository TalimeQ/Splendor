

#pragma once

#include "CoreMinimal.h"
#include "GameplayObjects/TokenStruct.h"
#include "GameFramework/Actor.h"
#include "PatronCardVisualizer.generated.h"


UCLASS()
class INZYNIERKASPLENDOR_API APatronCardVisualizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatronCardVisualizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Held to properly visualise stuffs,
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Replicated)
		int prestigeGained;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly,Replicated)
		FTokenStruct bonusParamsToShow;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent)
		// Implemented in blueprints, this class helps visualize player what they need in order to get a card, the act itself is managed by gamemode/state
	void VisualizeCard();
	virtual void VisualizeCard_Implementation();
	
	
};
