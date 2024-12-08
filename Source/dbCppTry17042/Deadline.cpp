

#include "Deadline.h"
#include "PaperFlipbookComponent.h"
#include "PinusBase.h"
#include "Delo.h"
#include "Kismet/GameplayStatics.h"
#include "LevelMenuController.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	ADeadline::ADeadline() :
		SpeedCompression(1.f),
		DeadlineScale(10.)
	{
		PrimaryActorTick.bCanEverTick = true;

		// ����� Actor�
		SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
		SetRootComponent(SceneComponent);

		// �����. �������� � UE
		MashComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MashComponent"));
		MashComponent->SetupAttachment(RootComponent);
		MashComponent->SetCastShadow(false);
		MashComponent->SetRelativeScale3D(FVector(10., 10., 10.));
		MashComponent->SetRelativeRotation(FRotator(0., 0., -90.));

		// ��������� �����, ��������� �� ��������������� � ������� ��������� (��������)
		// ����� ����� �������� ��������
		MashComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		MashComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		MashComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		MashComponent->SetGenerateOverlapEvents(true);

		// ������������ �����
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
/// ������ ������ ///
///_______________///
/// 
	void ADeadline::BeginPlay()
	{
		Super::BeginPlay();

		// ��������� ������� �������� � ����� 
		MashComponent->OnComponentEndOverlap.AddDynamic(this, &ADeadline::OverlapCheck);

		// ������ ����� ��������� �������
		MashComponent->SetRelativeScale3D(FVector(DeadlineScale, DeadlineScale, DeadlineScale));

		// � ����������� �� ��������� �������� ���������� ������������ �����
		FlipbookConmponent->SetRelativeLocation(FVector(-250.* DeadlineScale, 0., -40.));
	}
///_______________///
/////////////////////


//////////////////
/// ������ ��� ///
///____________///
/// 
/// ������� ����� � ������� ����� � ���
///____________///
/// 
	void ADeadline::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);
	
		// ���� ����� �� ����� �� �����
		if (MashComponent->GetRelativeScale3D().X > 0.05)
		{
			// ������� �����
			FVector newScale = MashComponent->GetRelativeScale3D() - SpeedCompression * DeltaTime;
			MashComponent->SetRelativeScale3D(newScale);

			// ������� ������������ �����
			FVector newLocation = FlipbookConmponent->GetRelativeLocation();
			newLocation.X += SpeedCompression * KofOfSpeedVisual * DeltaTime;
			FlipbookConmponent->SetRelativeLocation(newLocation);
		}
	}
///____________///
//////////////////


////////////////////////////////////////////////////
/// �������� �������, ��������� �� ������� ����� ///
///______________________________________________///
/// 
	void ADeadline::OverlapCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
	{
		// ���� ��� ������ - ���������� ���
		if (Cast<APinusBase>(OtherActor))
		{
			OtherActor->Destroy();
		}

		// ���� ��� ���� - �������� ����� ����
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

