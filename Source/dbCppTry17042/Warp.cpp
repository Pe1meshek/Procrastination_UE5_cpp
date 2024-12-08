

#include "Warp.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Delo.h"
#include "Kismet/GameplayStatics.h"
#include "LevelMenuController.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	AWarp::AWarp()
	{
		// Коллизия
		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		SetRootComponent(SphereComponent);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		SphereComponent->SetGenerateOverlapEvents(true);
		SphereComponent->SetSphereRadius(20.f);

		// Текстурка
		PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
		PaperFlipbookComponent->SetupAttachment(RootComponent);
		PaperFlipbookComponent->SetLooping(true);
		PaperFlipbookComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void AWarp::BeginPlay()
	{
		Super::BeginPlay();
	
		// Привязка функции пересечения к событию пересечения
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AWarp::OnOverlapBegin);
	}
///_______________///
/////////////////////


///////////////////////////////
/// Пересечение с объектами ///
///_________________________///
/// 
	void AWarp::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
	{
		// Если пересекаемый объект - Дело
		if (Cast<ADelo>(OtherActor))
		{
			ALevelMenuController* levelController = Cast<ALevelMenuController>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelMenuController::StaticClass()));
			if (levelController)
			{
				// Вызываем экран Победы
				levelController->WonGame();
			}
		}
	}
///_________________________///
///////////////////////////////

