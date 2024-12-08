
#include "PlaneForCursor.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	APlaneForCursor::APlaneForCursor()
	{
		MashComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootPlane"));
		SetRootComponent(MashComponent);
	
		// Стенка должна быть невидимой, естесна
		MashComponent->SetVisibility(false);

		// Настройка коллизии
		MashComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	}
///_____________///
///////////////////
