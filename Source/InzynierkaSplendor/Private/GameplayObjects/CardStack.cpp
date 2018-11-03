#include "CardStack.h"
#include "UnrealMathUtility.h"
#include "Public/SplendorPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

void ACardStack::BeginPlay()
{
	Super::BeginPlay();
	FGenericPlatformMath::SRandInit(FDateTime::Now().ToUnixTimestamp());
	ShuffleCards();
}
void ACardStack::OnRaycast()
{
	//TODO :: NETWORKING POINT, that thing below works for single atm :<
	ASplendorPlayerController* splendorCont = Cast<ASplendorPlayerController>(this->GetWorld()->GetFirstPlayerController());
	if (splendorCont)
	{
		splendorCont->ToggleInput();
	}
	OnCardStackRequest.Broadcast();
}
void ACardStack::ProcessReservationRequest(ASplendorPlayerController *requestingPlayer)
{
	if (storedCards.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardStack :: No cards on stack"));
	}
}
void ACardStack::ShuffleCards()
{
	// Should shuffle decently enough
	for (uint32 i = storedCards.Num() -1; i > 0; i--)
	{
		int32 index = FMath::FloorToInt(FMath::Rand() * (i + 1) % storedCards.Num());
		FCardStruct temp = storedCards[i];
		storedCards[i] = storedCards[index];
		storedCards[index] = temp;

	}
}