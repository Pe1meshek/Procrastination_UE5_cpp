

#include "PinusBase.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	APinusBase::APinusBase() :
		NumOfActivations(1)
	{
		PrimaryActorTick.bCanEverTick = true;

		// Коллизия
		CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
		SetRootComponent(CapsuleCollision);
		CapsuleCollision->SetCapsuleSize(20.f, 50.f);
		CapsuleCollision->SetSimulatePhysics(true);
		CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		CapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CapsuleCollision->BodyInstance.bUseCCD = true;

		// Текстурка
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PinusSkin"));
		SpriteComponent->SetupAttachment(CapsuleCollision);
		SpriteComponent->SetRelativeLocation(FVector(0., 0., -5.));
		SpriteComponent->SetRelativeRotation(FRotator(45., 0., 0.));
		SpriteComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
		SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Масштаб 
		SetActorScale3D(FVector(0.1,0.1,0.1));
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void APinusBase::BeginPlay()
	{
		Super::BeginPlay();

		// Нельзя выставлять в конструкторе, Движок ругается,
		// поэтому данные настройки здесь
		CapsuleCollision->SetConstraintMode(EDOFMode::XZPlane);
		CapsuleCollision->SetMassOverrideInKg("CapsuleCollision", 20.f);
	}
///_______________///
/////////////////////


// Оставляю на случай, если наследники будут использовать
void APinusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Активация реалиовывается каждым наследником индивидульано
void APinusBase::Activate()
{
}