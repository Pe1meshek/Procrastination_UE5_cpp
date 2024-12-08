

#include "PinusBase.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	APinusBase::APinusBase() :
		NumOfActivations(1)
	{
		PrimaryActorTick.bCanEverTick = true;

		// ��������
		CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
		SetRootComponent(CapsuleCollision);
		CapsuleCollision->SetCapsuleSize(20.f, 50.f);
		CapsuleCollision->SetSimulatePhysics(true);
		CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		CapsuleCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
		CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		CapsuleCollision->BodyInstance.bUseCCD = true;

		// ���������
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PinusSkin"));
		SpriteComponent->SetupAttachment(CapsuleCollision);
		SpriteComponent->SetRelativeLocation(FVector(0., 0., -5.));
		SpriteComponent->SetRelativeRotation(FRotator(45., 0., 0.));
		SpriteComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
		SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// ������� 
		SetActorScale3D(FVector(0.1,0.1,0.1));
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void APinusBase::BeginPlay()
	{
		Super::BeginPlay();

		// ������ ���������� � ������������, ������ ��������,
		// ������� ������ ��������� �����
		CapsuleCollision->SetConstraintMode(EDOFMode::XZPlane);
		CapsuleCollision->SetMassOverrideInKg("CapsuleCollision", 20.f);
	}
///_______________///
/////////////////////


// �������� �� ������, ���� ���������� ����� ������������
void APinusBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// ��������� �������������� ������ ����������� �������������
void APinusBase::Activate()
{
}