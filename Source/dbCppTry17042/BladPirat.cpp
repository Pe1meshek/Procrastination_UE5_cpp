
#include "BladPirat.h"

#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PinusBase.h"
#include "dbPlayerController.h"


///////////////////
/// ����������� ///
///_____________///
/// 
/// ������ ��������� ��������� ����������
///_____________///
/// 
	ABladPirat::ABladPirat() :
		ChargeBarAnimation(nullptr),
		ArrowSprite(nullptr),
		PFAnimationIdle(nullptr),
		PFAnimationRun(nullptr),
		PFAnimationJump(nullptr),
		PFAnimationFall(nullptr),
		PFAnimationGround(nullptr),
		PFAnimationAttack(nullptr),
		PinusControlled(nullptr),
		bIsKickCharging(false),
		bIsCanControl(true),
		bIsGroundAfterFall(false),
		bIsAttack(false),
		KickPower(0),
		SelectedPinusClass(nullptr)
	{
		// ������� � ���������
		GetCapsuleComponent()->SetCapsuleSize(15.f, 27.f);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		// ��������������� �������� ���������
		GetSprite()->SetRelativeLocation(FVector(2., 0., 2.));
		GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// ����� ��������� ���������� �������
		SpawnPinusPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPinusPoint"));
		SpawnPinusPoint->SetupAttachment(RootComponent);
		SpawnPinusPoint->SetRelativeLocation(FVector(25., 0., -20.));

		// ����� ������� ����� (��������)
		ChargeBar = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ChargeBar"));
		ChargeBar->SetupAttachment(RootComponent);
		ChargeBar->SetRelativeLocation(FVector(0., 0., -40.));
		ChargeBar->SetUsingAbsoluteRotation(true);
		ChargeBar->SetVisibility(false);
		ChargeBar->SetLooping(false);
		ChargeBar->SetPlayRate(0.8f);
		ChargeBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// ����� ��� ������
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetRelativeRotation(FRotator(0., -90., 0.));
		SpringArm->SetUsingAbsoluteRotation(true);
		SpringArm->TargetArmLength = 300.0f;
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 3.0f;

		// ������
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetupAttachment(SpringArm);

		// ������� �����
		KickRange = CreateDefaultSubobject<UBoxComponent>(TEXT("KickRange"));
		KickRange->SetupAttachment(RootComponent);
		KickRange->SetRelativeLocation(FVector(20., 0., -20.));
		KickRange->SetBoxExtent(FVector(21., 20., 15.));

		// ����� ������� �����������
		PivotArrow = CreateDefaultSubobject<USceneComponent>(TEXT("PivotArrow"));
		PivotArrow->SetupAttachment(RootComponent);
		PivotArrow->SetRelativeLocation(FVector(25., 0., -20.));

		// ������� ����������� �����
		Arrow = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ArrowDirection"));
		Arrow->SetupAttachment(PivotArrow);
		Arrow->SetRelativeLocation(FVector(30., 0., 0.));
		Arrow->SetRelativeScale3D(FVector(0.05, 0.05, 0.05));
		Arrow->SetVisibility(false);
		Arrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// ��������� ��������� (Character)
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		GetCharacterMovement()->AirControl = 1.f;
		bUseControllerRotationYaw = false;
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
/// ��� ������������� �������� ����� ������� �������� �� �����
///_______________///
/// 
	void ABladPirat::BeginPlay()
	{
		Super::BeginPlay();

		// �������� �� ������ ������������ �� ��� Y
		// �� � �� ������ � ����������������� ������ �������
		GetCapsuleComponent()->SetConstraintMode(EDOFMode::XZPlane);

		// ����������� ���������� ���������. ��� ������ � ������������ - �� ��������
		GetCharacterMovement()->SetWalkableFloorAngle(5.f);

		// ����� �������
		if (ChargeBarAnimation)
		{
			ChargeBar->SetFlipbook(ChargeBarAnimation);
			ChargeBar->Stop();

			ChargeBar->OnFinishedPlaying.AddDynamic(this, &ABladPirat::Kick);
		}

		// ���������
		if (ArrowSprite)
		{
			Arrow->SetSprite(ArrowSprite);
		}

		// ����� ����������� �������� ����� ������ ��������
		// ��� ��� ����� � ��������
		GetSprite()->OnFinishedPlaying.AddDynamic(this, &ABladPirat::DropOneTimeAnim);
	
	
		// ������ ��������� ����� �������
		if (!PinusClasses.IsEmpty())
		{
			SelectedPinusClass = PinusClasses[0];
		}
	}
///_______________///
/////////////////////


//////////////////
/// ������ ��� ///
///____________///
/// 
/// �������� ��������
/// ������� �������
///____________///
/// 
	void ABladPirat::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		// �������� ��������
		StateMachine();
	}
///____________///
//////////////////


/////////////////////////////
/// ��������� �� viewPort ///
///_______________________///
/// 
/// ������, ��� ������ ����.
/// ������� ������, �������� ������������� ����������, ���.
///_______________________///
/// 
	void ABladPirat::SetAsMainCamera()
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
///_______________________///
/////////////////////////////



///////////////////////////
/// �������� � �������� ///
///_____________________///
/// 
/// �������� �����/������ + �������� (��������������)
	void ABladPirat::MoveRight(float direction)
	{
		if (bIsCanControl)
		{
			if (direction != 0.f)
			{
				double rotationZ = direction > 0.f ? 0. : 180.;
				SetActorRotation(FRotator(0., rotationZ, 0.));
			}
			AddMovementInput(FVector(direction, 0., 0.));
		}
	}
///
/// ������
	void ABladPirat::Jump()
	{
		if (bIsCanControl)
		{
			Super::Jump();
		}
	}
///
/// �������� �������
	void ABladPirat::SpawnPinus()
	{
		if (bIsCanControl)
		{
			if (SelectedPinusClass)
			{
				PinusControlled = GetWorld()->SpawnActor<APinusBase>(SelectedPinusClass, SpawnPinusPoint->GetComponentLocation(), FRotator(0., 0., 0.));
			}
		}
	}
///
/// ����� ������� �����
/// �������� ����� � �������
	void ABladPirat::StartCharge()
	{
		if (bIsCanControl)
		{
			bIsKickCharging = true;
			ChargeBar->SetVisibility(true);
			ChargeBar->PlayFromStart();
			ChargeBar->Play();

			Arrow->SetVisibility(true);

			// ��������� ������� ��� ������� �������� ������� �� ����� ������� �����
			GetWorld()->GetTimerManager().SetTimer(TimerHandleSetArrowRotation, this, &ABladPirat::SetArrowPosition, GetWorld()->DeltaTimeSeconds, true);
		}
	}
///
/// ���������� ����� � �������
/// ������ ������� �����(�.� �������� ��������),
/// �� ��� ����� ����� ������� ���������� ���� �������� �����, ����� ���������.
	void ABladPirat::Kick()
	{
		if (bIsCanControl)
		{
			if (bIsKickCharging)
			{
				// ���������� �����
				ChargeBar->SetVisibility(false);
				ChargeBar->Stop();

				// ���������� �������
				Arrow->SetVisibility(false);
			
				// ����������� ���� �����
				KickPower = ChargeBar->GetPlaybackPositionInFrames() + 1;

				bIsKickCharging = false;
				bIsAttack = true;

				// ����� ������� �������� �������
				GetWorld()->GetTimerManager().ClearTimer(TimerHandleSetArrowRotation);
			}
		}
		// ��������� ������� ��� ���������� ����� � ������ ������ ��������
		GetWorld()->GetTimerManager().SetTimer(TimerHandleKickInAttackAnimation, this, &ABladPirat::GiveKickEach, GetWorld()->DeltaTimeSeconds, true);
	}
///_____________________///
///////////////////////////


///////////////////////////////////////////////
/// ��������� ���������� ���������� ������� ///
///_________________________________________///
/// 
	void ABladPirat::ActivatePinus()
	{
		if (PinusControlled)
		{
			PinusControlled->Activate();
		}
	}
///_________________________________________///
///////////////////////////////////////////////


/////////////////////////////////////////////////
/// ������ ����� ������ ������������ �������� ///
///___________________________________________///
/// 
	void ABladPirat::SetSelectedPinusClass(int32 num)
	{
		if (!PinusClasses.IsEmpty())
		{
			if (num >= 0 && num < PinusClasses.Num())
			{
				SelectedPinusClass = PinusClasses[num];
			}
		}
	}
///___________________________________________///
/////////////////////////////////////////////////


////////////////////////
/// ������ ��������� ///
///__________________///
/// 
/// � �������� ����� � ����������� ����������� ����������.
/// ��������� � ���������� ������.
/// 
/// �� ����� ������� ������������� ���� (bIsGroundAfterFall).
/// ����� ��� ��� ������ "��������" �������� (idle ��� run) ��������� 
/// ���� bIsGroundAfterFall � �������� �������� �����������.
///__________________///
/// 
/// ����������� ��������� � ��������� ��������
	void ABladPirat::StateMachine()
	{
		FVector velocity = GetVelocity();

		// �����
		if (bIsAttack)
		{
			if (PFAnimationAttack)
			{
				SetAnimationAndMode(PFAnimationAttack, false, false);
			}
		}
		// ��������������� ��� �����������
		else if (velocity.Length() == 0.)
		{
			if (bIsGroundAfterFall)
			{
				if (PFAnimationGround)
				{
					SetAnimationAndMode(PFAnimationGround, false, false);
				}
			}
			else
			{
				if (PFAnimationIdle)
				{
					SetAnimationAndMode(PFAnimationIdle,true, true);
				}
			}
		}
		else
		{
			// ������
			if (velocity.Z > 0.)
			{
				if (PFAnimationJump)
				{
					SetAnimationAndMode(PFAnimationJump, false, true);
				}
			}
			// �������
			else if (velocity.Z < 0.)
			{
				if (PFAnimationFall)
				{
					SetAnimationAndMode(PFAnimationFall, false, true);
				}
				bIsGroundAfterFall = true;
			}
			// ��� ��� �����������
			else
			{
				if (bIsGroundAfterFall)
				{
					if (PFAnimationGround)
					{
						SetAnimationAndMode(PFAnimationGround, false, false);
					}
				}
				else
				{
					if (PFAnimationRun)
					{
						SetAnimationAndMode(PFAnimationRun, true, true);
					}
				}	
			}
		}
	}
///
/// ��������� ��������
/// anim - ��������������� ��������
/// bIsLoop - true, ���� ����� ���������
/// bIsControl - false, ���� ����� ��������� ����������
	void ABladPirat::SetAnimationAndMode(UPaperFlipbook* anim, bool bIsLoop, bool bIsControl)
	{
		if (GetSprite()->GetFlipbook() != anim)
		{
			GetSprite()->SetFlipbook(anim);
			GetSprite()->SetLooping(bIsLoop);
			GetSprite()->PlayFromStart();
			bIsCanControl = bIsControl;
		}
	}
///
/// ����� �������� � �������
	void ABladPirat::DropOneTimeAnim()
	{
		bIsAttack = false;
		bIsGroundAfterFall = false;
	}
///__________________///
////////////////////////


///////////////////////
/// ������� ������� ///
///_________________///
/// 
/// ������������� ������� � ����������� ��������� �������,
/// �� �� ����� ���������� ���������,
/// �.� ���� �������� �������� �����, �� ������� ����� �������� ����������� 
/// ������ ������ ���������, ���� ������ - �� �������.
/// 
/// ����� ����� �������� �� ����� ������� � ������ ���� - ��� ����� � ��������� 
///_________________///
/// 
	void ABladPirat::SetArrowPosition()
	{
		if (Arrow && PivotArrow)
		{		
			// ����������� ����������� �� ���� ������ � ������������
			AdbPlayerController* dbPlayerController = Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController());
			if (dbPlayerController)
			{
				// �������� �����
				FVector cursorLocation = dbPlayerController->GetCursorWorldLocation();
				FVector arrowLocation = PivotArrow->GetComponentLocation();

				// ���������� �����������, �������� ������� �� �������� ����
				FRotator newRotate = (cursorLocation - arrowLocation).Rotation();
				newRotate.Yaw = 0.;
				newRotate.Roll = 0.;

				// ���� �������� ������� �����
				if (GetActorRotation().Yaw == 180.)
				{
					// ��������� ������� ��� ����������� �����������
					newRotate.Pitch = 180. - newRotate.Pitch;

					// ��������� �������� � ������� �����, ������ ����������� ���������
					if (cursorLocation.X >= arrowLocation.X)
					{
						if (cursorLocation.Z > arrowLocation.Z)
						{
							newRotate.Pitch = 90.;
						}
						else
						{
							newRotate.Pitch = -90.;
						}
					}
				}
				// ���� �������� ������� ������
				else
				{
					// ��������� �������� � ������� �����, ������ ����������� ���������
					if (cursorLocation.X <= arrowLocation.X)
					{
						if (cursorLocation.Z > arrowLocation.Z)
						{
							newRotate.Pitch = 90.;
						}
						else
						{
							newRotate.Pitch = -90.;
						}
					}
				}
				// ������ ���������
				PivotArrow->SetWorldRotation(newRotate);
				//ArrowDirectionOfKick->SetActorRotation(newRotate);
			}
		}
	}
///_________________///
///////////////////////


//////////////////////////////////////////////
/// ������ ������� ���� �������� � ������� ///
///________________________________________///
/// 
	void ABladPirat::GiveKickEach()
	{
		// �������� ����������� ������� � ������������ ��������
		if (bIsAttack && GetSprite()->GetPlaybackPositionInFrames() == 6)
		{
			// ��������� ���� ������������ ��������
			TArray<AActor*> overlappingActors;
			KickRange->GetOverlappingActors(overlappingActors, APinusBase::StaticClass());

			// ��� ������� �������
			for (AActor* Actor : overlappingActors)
			{
				// ��������, ����� �������� ��� ���������
				// ����� ���� � ���� ��������� �������
				APinusBase* tempPinus = Cast<APinusBase>(Actor);
				if (tempPinus)
				{
					// ��������� ����������� ������� � ������
					// ����� ��������� ������ ������ ����, ���� ��������� �������
					FRotator rotator = PivotArrow->GetComponentRotation();
					FVector rotatorInVec = FQuat(rotator).RotateVector(FVector::ForwardVector);
					// ������ ������� �������� ���� �����
					tempPinus->CapsuleCollision->AddImpulse(rotatorInVec * KickPower * 5000);
				}
			}

			// ����� �������
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleKickInAttackAnimation);
			//UE_LOG(LogTemp, Warning, TEXT("Eeeeeeend Kick"));
		}
	}
///________________________________________///
//////////////////////////////////////////////



