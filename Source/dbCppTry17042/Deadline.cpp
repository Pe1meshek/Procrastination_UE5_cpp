

#include "Deadline.h"
#include "PaperFlipbookComponent.h"
#include "PinusBase.h"
#include "Delo.h"
#include "Kismet/GameplayStatics.h"
#include "LevelMenuController.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	ADeadline::ADeadline() :
		SpeedCompression(1.f),
		DeadlineScale(10.)
	{
		PrimaryActorTick.bCanEverTick = true;

		// Центр Actorа
		SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
		SetRootComponent(SceneComponent);

		// Сфера. Задается в UE
		MashComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MashComponent"));
		MashComponent->SetupAttachment(RootComponent);
		MashComponent->SetCastShadow(false);
		MashComponent->SetRelativeScale3D(FVector(10., 10., 10.));
		MashComponent->SetRelativeRotation(FRotator(0., 0., -90.));

		// Настройки сферы, связанные со взаимодействием с другими объектами (каналами)
		// пусть будет выделено отдельно
		MashComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		MashComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		MashComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		MashComponent->SetGenerateOverlapEvents(true);

		// Декоративная гиена
		FlipbookConmponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("DeadlineVisual"));
		FlipbookConmponent->SetupAttachment(RootComponent);
		FlipbookConmponent->SetRelativeScale3D(FVector(2., 2., 2.));
		FlipbookConmponent->SetRelativeLocation(FVector(-2500., 0., -40.));
		FlipbookConmponent->SetLooping(true);
		FlipbookConmponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void ADeadline::BeginPlay()
	{
		Super::BeginPlay();

		// Связываем функцию проверки с мешом 
		MashComponent->OnComponentEndOverlap.AddDynamic(this, &ADeadline::OverlapCheck);

		// Задаем сфере начальные размеры
		MashComponent->SetRelativeScale3D(FVector(DeadlineScale, DeadlineScale, DeadlineScale));

		// В зависимости от начальных размеров выставляем декоративную гиену
		FlipbookConmponent->SetRelativeLocation(FVector(-250.* DeadlineScale, 0., -40.));
	}
///_______________///
/////////////////////


//////////////////
/// Каждый тик ///
///____________///
/// 
/// Сжимаем сферу и двигаем гиену к ней
///____________///
/// 
	void ADeadline::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);
	
		// Если Сфера не сжата до конца
		if (MashComponent->GetRelativeScale3D().X > 0.05)
		{
			// Сжимаем сферу
			FVector newScale = MashComponent->GetRelativeScale3D() - SpeedCompression * DeltaTime;
			MashComponent->SetRelativeScale3D(newScale);

			// Двигаем декоративную гиену
			FVector newLocation = FlipbookConmponent->GetRelativeLocation();
			newLocation.X += SpeedCompression * KofOfSpeedVisual * DeltaTime;
			FlipbookConmponent->SetRelativeLocation(newLocation);
		}
	}
///____________///
//////////////////


////////////////////////////////////////////////////
/// Проверка объекта, вышедшего за пределы сферы ///
///______________________________________________///
/// 
	void ADeadline::OverlapCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		// Если это снаряд - уничтожаем его
		if (Cast<APinusBase>(OtherActor))
		{
			OtherActor->Destroy();
		}

		// Если это Дело - вызываем конец игры
		if (Cast<ADelo>(OtherActor))
		{
			ALevelMenuController* levelController = Cast<ALevelMenuController>(UGameplayStatics::GetActorOfClass(GetWorld(), ALevelMenuController::StaticClass()));
			if (levelController)
			{
				levelController->LosedGame();
			}
		}
	}
///______________________________________________///
////////////////////////////////////////////////////

