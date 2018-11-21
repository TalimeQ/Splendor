

#include "ChatGameMode.h"
#include "InzynierkaSplendor.h"
#include "ChatHUD.h"
#include "ChatPlayerState.h"

AChatGameMode::AChatGameMode() { // assign our custom classes above their parents 
	HUDClass = AChatHUD::StaticClass(); 
	PlayerStateClass = AChatPlayerState::StaticClass();

/* use this is you wish to extend the c++ into a bp and assign the bp to the class static 
ConstructorHelpers::FClassFinder<AMyHUD> hudclassobj(TEXT("Blueprint'/MyHUD.MyHUD_C'")); 
if (hudclassobj.Class != NULL) HUDClass = hudclassobj.Class;

static ConstructorHelpers::FClassFinder<AMyPlayerState> psclassobj(TEXT("Blueprint'/MyPlayerState.MyPlayerState_C'")); 
if (psclassobj.Class != NULL) PlayerStateClass = psclassobj.Class;
*/
}