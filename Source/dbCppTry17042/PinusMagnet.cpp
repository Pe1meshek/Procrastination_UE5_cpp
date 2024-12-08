

#include "PinusMagnet.h"
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "Delo.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// ����������� ///
///_____________///
/// 
/// ��� ��� ��� � ��������
/// + ���������� ����� � ��������� 
/// 
	APinusMagnet::APinusMagnet() : 
		APinusBase(),
		SpeedCompression(750.f),
		PowerAttraction(5000.)
	{
		// ��������
		MagnetPoleCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MagnetPoleCollision"));
		MagnetPoleCollision->SetupAttachment(RootComponent);
		MagnetPoleCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		MagnetPoleCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		MagnetPoleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		MagnetPoleCollision->SetGenerateOverlapEvents(true);
		MagnetPoleCollision->SetSphereRadius(500.f);
		MagnetPoleCollision->SetVisibility(false);

		// ���������
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
/// ���������� ///
///____________///
///
/// ������� ��������� ���� (�����)
/// 
	void APinusMagnet::Activate()
	{
		// ���� ���� ���������
		if (NumOfActivations > 0)
		{
			// �������� ���� ���������
			NumOfActivations--;
		
			// ������ ������ ����� � ��������� ��������
			MagnetPolePaperFlipbook->SetVisibility(true);
			MagnetPoleCollision->SetVisibility(true);
			MagnetPoleCollision->SetSphereRadius(500.f);
			MagnetPolePaperFlipbook->PlayFromStart();
			MagnetPolePaperFlipbook->Play();

			// ��������� ������� ������ ���
			GetWorld()->GetTimerManager().SetTimer(TimerHandleMagnetPoleCompression, this, &APinusMagnet::MagnetPoleCompression, GetWorld()->DeltaTimeSeconds, true);
		}
	}
///____________///
//////////////////


///////////////////
/// ������ ���� ///
///_____________///
/// 
	void APinusMagnet::MagnetPoleCompression()
	{
		// ��������� ��� ������������ ������� ���� ����
		TArray<AActor*> overlapActors;
		MagnetPoleCollision->GetOverlappingActors(overlapActors, ADelo::StaticClass());
		
		// ���������� �� ������� �� ���
		for (auto actor : overlapActors)
		{
			ADelo* deloActor = Cast<ADelo>(actor);
			if (deloActor)
			{
				// ���������� ������ �������������
				FVector direction = CapsuleCollision->GetComponentLocation() - deloActor->BoxCollision->GetComponentLocation();
				
				// �����������
				direction.Normalize();

				// ������ ������� ����������
				deloActor->BoxCollision->AddImpulse(direction * PowerAttraction);
			}
		}

		// ������� ����� �� ��������� ��������
		// �������� ����� ���������, ����� � �������
		if (MagnetPoleCollision->GetUnscaledSphereRadius() > 30.f)
		{
			MagnetPoleCollision->SetSphereRadius( MagnetPoleCollision->GetUnscaledSphereRadius() - (SpeedCompression * GetWorld()->DeltaTimeSeconds) );
		}
		else
		{
			// �����, ���� ����� �������� ������� �������,
			// �� ������������� � ������ ��������
			MagnetPolePaperFlipbook->Stop();
			MagnetPolePaperFlipbook->SetVisibility(false);
			MagnetPoleCollision->SetVisibility(false);
			
			// ��������� ���� ������ ������ �������
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleMagnetPoleCompression);
		}
	}
///_____________///
///////////////////
