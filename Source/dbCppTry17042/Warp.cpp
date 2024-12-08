

#include "Warp.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Delo.h"
#include "Kismet/GameplayStatics.h"
#include "LevelMenuController.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	AWarp::AWarp()
	{
		// ��������
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		SetRootComponent(SphereComponent);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		SphereComponent->SetGenerateOverlapEvents(true);
		SphereComponent->SetSphereRadius(20.f);

		// ���������
		PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
		PaperFlipbookComponent->SetupAttachment(RootComponent);
		PaperFlipbookComponent->SetLooping(true);
		PaperFlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void AWarp::BeginPlay()
	{
		Super::BeginPlay();
	
		// �������� ������� ����������� � ������� �����������
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AWarp::OnOverlapBegin);
	}
///_______________///
/////////////////////


///////////////////////////////
/// ����������� � ��������� ///
///_________________________///
/// 
	void AWarp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
	{
		// ���� ������������ ������ - ����
		if (Cast<ADelo>(OtherActor))
		{
			ALevelMenuController* levelController = Cast<ALevelMenuController>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelMenuController::StaticClass()));
			if (levelController)
			{
				// �������� ����� ������
				levelController->WonGame();
			}
		}
	}
///_________________________///
///////////////////////////////

