

#include "PinusMagnet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Delo.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
/// Тут все как у родителя
/// + сужающаяся сфера с анимацией 
/// 
	APinusMagnet::APinusMagnet() : 
		APinusBase(),
		SpeedCompression(750.f),
		PowerAttraction(5000.)
	{
		// Коллизия
		MagnetPoleCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetPoleCollision"));
		MagnetPoleCollision->SetupAttachment(RootComponent);
		MagnetPoleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		MagnetPoleCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		MagnetPoleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		MagnetPoleCollision->SetGenerateOverlapEvents(true);
		MagnetPoleCollision->SetSphereRadius(500.f);
		MagnetPoleCollision->SetVisibility(false);

		// Текстурка
		MagnetPolePaperFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MagnetPolePaperFlipbook"));
		MagnetPolePaperFlipbook->SetupAttachment(RootComponent);
		MagnetPolePaperFlipbook->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MagnetPolePaperFlipbook->SetRelativeLocation(FVector(30., 0., 30.));
		MagnetPolePaperFlipbook->SetRelativeScale3D(FVector(10., 10., 10.));
		MagnetPolePaperFlipbook->Stop();
		MagnetPolePaperFlipbook->SetPlayRate(-1.f);
		MagnetPolePaperFlipbook->SetVisibility(false);
	}
///_____________///
///////////////////


//////////////////
/// Акстивация ///
///____________///
///
/// Создает магнитное поле (сферу)
/// 
	void APinusMagnet::Activate()
	{
		// Если есть активации
		if (NumOfActivations > 0)
		{
			// Вычитаем одну активацию
			NumOfActivations--;
		
			// Задаем размер сферы и запускаем анимацию
			MagnetPolePaperFlipbook->SetVisibility(true);
			MagnetPoleCollision->SetVisibility(true);
			MagnetPoleCollision->SetSphereRadius(500.f);
			MagnetPolePaperFlipbook->PlayFromStart();
			MagnetPolePaperFlipbook->Play();

			// Запускаем функцию каждый тик
			GetWorld()->GetTimerManager().SetTimer(TimerHandleMagnetPoleCompression, this, &APinusMagnet::MagnetPoleCompression, GetWorld()->DeltaTimeSeconds, true);
		}
	}
///____________///
//////////////////


///////////////////
/// Сжатие поля ///
///_____________///
/// 
	void APinusMagnet::MagnetPoleCompression()
	{
		// Сохраняем все пересекаемые объекты типа Дело
		TArray<AActor*> overlapActors;
		MagnetPoleCollision->GetOverlappingActors(overlapActors, ADelo::StaticClass());
		
		// Проходимся по каждому из них
		for (auto actor : overlapActors)
		{
			ADelo* deloActor = Cast<ADelo>(actor);
			if (deloActor)
			{
				// Определяем вектор притиягивания
				FVector direction = CapsuleCollision->GetComponentLocation() - deloActor->BoxCollision->GetComponentLocation();
				
				// Нормализуем
				direction.Normalize();

				// Задаем импульс притяжения
				deloActor->BoxCollision->AddImpulse(direction * PowerAttraction);
			}
		}

		// Сжимаем сферу до некторого значения
		// значение взято примерное, почти с потолка
		if (MagnetPoleCollision->GetUnscaledSphereRadius() > 30.f)
		{
			MagnetPoleCollision->SetSphereRadius( MagnetPoleCollision->GetUnscaledSphereRadius() - (SpeedCompression * GetWorld()->DeltaTimeSeconds) );
		}
		else
		{
			// Иначе, если сфера достигла сжатого размера,
			// то останавливаем и прячем анимацию
			MagnetPolePaperFlipbook->Stop();
			MagnetPolePaperFlipbook->SetVisibility(false);
			MagnetPoleCollision->SetVisibility(false);
			
			// Прерываем цикл вызова данной функции
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleMagnetPoleCompression);
		}
	}
///_____________///
///////////////////
