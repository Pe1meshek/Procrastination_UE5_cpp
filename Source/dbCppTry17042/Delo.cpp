
#include "Delo.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"


///////////////////
/// Конструктор ///
///_____________///
///
	ADelo::ADelo()
	{
		PrimaryActorTick.bCanEverTick = true;

		// Коллизия
		BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
		BoxCollision->SetupAttachment(RootComponent);
		BoxCollision->SetBoxExtent(FVector(16., 2., 19.));
		BoxCollision->SetSimulatePhysics(true);
		BoxCollision->SetEnableGravity(false);
		BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//BoxCollision->SetNotifyRigidBodyCollision(true);

		// Текстурка
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DeloSkin"));
		SpriteComponent->SetupAttachment(BoxCollision);
		SpriteComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
		SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void ADelo::BeginPlay()
	{
		Super::BeginPlay();

		// Нельзя выставлять в конструкторе, Движок ругается,
		// поэтому данные настройки здесь
		BoxCollision->SetConstraintMode(EDOFMode::XZPlane);
		BoxCollision->SetMassOverrideInKg("BoxCollision", 100.f);
	}
///_______________///
/////////////////////

