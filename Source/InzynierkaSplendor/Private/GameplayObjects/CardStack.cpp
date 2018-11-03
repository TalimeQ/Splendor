

#include "CardStack.h"



void ACardStack::OnRaycast()
{
	OnCardStackRequest.Broadcast();
}
