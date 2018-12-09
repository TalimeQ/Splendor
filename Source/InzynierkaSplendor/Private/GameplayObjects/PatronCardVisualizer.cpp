

#include "PatronCardVisualizer.h"
#include "UnrealNetwork.h"

// Sets default values
APatronCardVisualizer::APatronCardVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void APatronCardVisualizer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatronCardVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APatronCardVisualizer::VisualizeCard_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Card Visualized"));

}
void APatronCardVisualizer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APatronCardVisualizer,bonusParamsToShow);
	DOREPLIFETIME(APatronCardVisualizer,prestigeGained);
}