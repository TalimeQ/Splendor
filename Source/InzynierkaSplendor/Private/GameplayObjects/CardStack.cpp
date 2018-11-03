#include "CardStack.h"
#include "Public/SplendorPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"




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

}