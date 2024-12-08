
#include "Delo.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"


///////////////////
/// ����������� ///
///_____________///
///
	ADelo::ADelo()
	{
		PrimaryActorTick.bCanEverTick = true;

		// ��������
		BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
		BoxCollision->SetupAttachment(RootComponent);
		BoxCollision->SetBoxExtent(FVector(16., 2., 19.));
		BoxCollision->SetSimulatePhysics(true);
		BoxCollision->SetEnableGravity(false);
		BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//BoxCollision->SetNotifyRigidBodyCollision(true);

		// ���������
		SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("DeloSkin"));
		SpriteComponent->SetupAttachment(BoxCollision);
		SpriteComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
		SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void ADelo::BeginPlay()
	{
		Super::BeginPlay();

		// ������ ���������� � ������������, ������ ��������,
		// ������� ������ ��������� �����
		BoxCollision->SetConstraintMode(EDOFMode::XZPlane);
		BoxCollision->SetMassOverrideInKg("BoxCollision", 100.f);
	}
///_______________///
/////////////////////

