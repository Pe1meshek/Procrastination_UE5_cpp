
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
/// Конструктор ///
///_____________///
/// 
/// Задаем начальные настройки комонентам
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
		// Капсула с коллизией
		GetCapsuleComponent()->SetCapsuleSize(15.f, 27.f);
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

		// Воспроизводимая анимация персонажа
		GetSprite()->SetRelativeLocation(FVector(2., 0., 2.));
		GetSprite()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Точка появления созданного снаряда
		SpawnPinusPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPinusPoint"));
		SpawnPinusPoint->SetupAttachment(RootComponent);
		SpawnPinusPoint->SetRelativeLocation(FVector(25., 0., -20.));

		// Шкала зарядки пинка (Анимация)
		ChargeBar = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ChargeBar"));
		ChargeBar->SetupAttachment(RootComponent);
		ChargeBar->SetRelativeLocation(FVector(0., 0., -40.));
		ChargeBar->SetUsingAbsoluteRotation(true);
		ChargeBar->SetVisibility(false);
		ChargeBar->SetLooping(false);
		ChargeBar->SetPlayRate(0.8f);
		ChargeBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Плечо для камеры
		SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->SetRelativeRotation(FRotator(0., -90., 0.));
		SpringArm->SetUsingAbsoluteRotation(true);
		SpringArm->TargetArmLength = 300.0f;
		SpringArm->bEnableCameraLag = true;
		SpringArm->CameraLagSpeed = 3.0f;

		// Камера
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		CameraComponent->SetupAttachment(SpringArm);

		// Область пинка
		KickRange = CreateDefaultSubobject<UBoxComponent>(TEXT("KickRange"));
		KickRange->SetupAttachment(RootComponent);
		KickRange->SetRelativeLocation(FVector(20., 0., -20.));
		KickRange->SetBoxExtent(FVector(21., 20., 15.));

		// Пивот стрелки направления
		PivotArrow = CreateDefaultSubobject<USceneComponent>(TEXT("PivotArrow"));
		PivotArrow->SetupAttachment(RootComponent);
		PivotArrow->SetRelativeLocation(FVector(25., 0., -20.));

		// Стрелка направления пинка
		Arrow = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ArrowDirection"));
		Arrow->SetupAttachment(PivotArrow);
		Arrow->SetRelativeLocation(FVector(30., 0., 0.));
		Arrow->SetRelativeScale3D(FVector(0.05, 0.05, 0.05));
		Arrow->SetVisibility(false);
		Arrow->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Настройки персонажа (Character)
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		GetCharacterMovement()->AirControl = 1.f;
		bUseControllerRotationYaw = false;
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
/// Без установленной анимации Шкала зарядки работать не будет
///_______________///
/// 
	void ABladPirat::BeginPlay()
	{
		Super::BeginPlay();

		// Персонаж не должен перемещаться по оси Y
		// но я не уверен в работоспособности данной функции
		GetCapsuleComponent()->SetConstraintMode(EDOFMode::XZPlane);

		// Максимально проходимая ступенька. При вызове в конструкторе - не работает
		GetCharacterMovement()->SetWalkableFloorAngle(5.f);

		// Шкала зарядки
		if (ChargeBarAnimation)
		{
			ChargeBar->SetFlipbook(ChargeBarAnimation);
			ChargeBar->Stop();

			ChargeBar->OnFinishedPlaying.AddDynamic(this, &ABladPirat::Kick);
		}

		// Стрелочка
		if (ArrowSprite)
		{
			Arrow->SetSprite(ArrowSprite);
		}

		// Сброс одноразовых анимаций после каждой анимации
		// ибо так проще и надежнее
		GetSprite()->OnFinishedPlaying.AddDynamic(this, &ABladPirat::DropOneTimeAnim);
	
	
		// Задать начальный класс снаряда
		if (!PinusClasses.IsEmpty())
		{
			SelectedPinusClass = PinusClasses[0];
		}
	}
///_______________///
/////////////////////


//////////////////
/// Каждый тик ///
///____________///
/// 
/// Контроль анимаций
/// Поворот стрелки
///____________///
/// 
	void ABladPirat::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		// Контроль анимаций
		StateMachine();
	}
///____________///
//////////////////


/////////////////////////////
/// Установка во viewPort ///
///_______________________///
/// 
/// Удобно, при чтении кода.
/// Больших заслуг, учитывая одностройчное содержание, нет.
///_______________________///
/// 
	void ABladPirat::SetAsMainCamera()
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
///_______________________///
/////////////////////////////



///////////////////////////
/// Движение и действия ///
///_____________________///
/// 
/// Движение Влево/Вправо + развород (отзеркаливание)
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
/// Прыжок
	void ABladPirat::Jump()
	{
		if (bIsCanControl)
		{
			Super::Jump();
		}
	}
///
/// Создание снаряда
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
/// Старт зарядки Шкалы
/// включает Шкалу и Стрелку
	void ABladPirat::StartCharge()
	{
		if (bIsCanControl)
		{
			bIsKickCharging = true;
			ChargeBar->SetVisibility(true);
			ChargeBar->PlayFromStart();
			ChargeBar->Play();

			Arrow->SetVisibility(true);

			// Установка таймера для задания поворота стрелки во время зарядки пинка
			GetWorld()->GetTimerManager().SetTimer(TimerHandleSetArrowRotation, this, &ABladPirat::SetArrowPosition, GetWorld()->DeltaTimeSeconds, true);
		}
	}
///
/// Выключение Шкалы и Стрелки
/// Запуск события Пинка(т.е задавать импульсы),
/// но для этого нужно поймать конкретный кадр анимации Пинка, иначе некрасиво.
	void ABladPirat::Kick()
	{
		if (bIsCanControl)
		{
			if (bIsKickCharging)
			{
				// Выключение Шкалы
				ChargeBar->SetVisibility(false);
				ChargeBar->Stop();

				// Выключение Стрелки
				Arrow->SetVisibility(false);
			
				// Определение силы удара
				KickPower = ChargeBar->GetPlaybackPositionInFrames() + 1;

				bIsKickCharging = false;
				bIsAttack = true;

				// Сброс таймера поворота стрелки
				GetWorld()->GetTimerManager().ClearTimer(TimerHandleSetArrowRotation);
			}
		}
		// Установка таймера для реализации пинка в нужный момент анимации
		GetWorld()->GetTimerManager().SetTimer(TimerHandleKickInAttackAnimation, this, &ABladPirat::GiveKickEach, GetWorld()->DeltaTimeSeconds, true);
	}
///_____________________///
///////////////////////////


///////////////////////////////////////////////
/// Активация последнего созданного Снаряда ///
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
/// Задать номер класса создаваемого Снаяряда ///
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
/// Машина состояний ///
///__________________///
/// 
/// в анмациях Атаки и Приземления выключается управление.
/// пригоится в реализации смерти.
/// 
/// во время падения устанавливаем флаг (bIsGroundAfterFall).
/// перед тем как играть "наземные" анимации (idle или run) проверяем 
/// флаг bIsGroundAfterFall и включаем анимацию Приземления.
///__________________///
/// 
/// Определение состояния и включение анимации
	void ABladPirat::StateMachine()
	{
		FVector velocity = GetVelocity();

		// Атака
		if (bIsAttack)
		{
			if (PFAnimationAttack)
			{
				SetAnimationAndMode(PFAnimationAttack, false, false);
			}
		}
		// Ничегонеделание или Приземление
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
			// Прыжок
			if (velocity.Z > 0.)
			{
				if (PFAnimationJump)
				{
					SetAnimationAndMode(PFAnimationJump, false, true);
				}
			}
			// Падение
			else if (velocity.Z < 0.)
			{
				if (PFAnimationFall)
				{
					SetAnimationAndMode(PFAnimationFall, false, true);
				}
				bIsGroundAfterFall = true;
			}
			// Бег или Приземление
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
/// Включение анимации
/// anim - устанавливаемая анимация
/// bIsLoop - true, если нужно зациклить
/// bIsControl - false, если нужно отключить управление
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
/// Сброс анимаций с флагами
	void ABladPirat::DropOneTimeAnim()
	{
		bIsAttack = false;
		bIsGroundAfterFall = false;
	}
///__________________///
////////////////////////


///////////////////////
/// Поворот стрелки ///
///_________________///
/// 
/// Разворачивает стрелку в направлении положения курсора,
/// НО не может пересекать персонажа,
/// т.е если персонаж повернут влево, то стрелка может занимать направления 
/// только левого полукруга, если вправо - то правого.
/// 
/// нужно чтобы персонаж не пинал снаряды в самого себя - это криво и нелогично 
///_________________///
/// 
	void ABladPirat::SetArrowPosition()
	{
		if (Arrow && PivotArrow)
		{		
			// Определение направления по двум точкам в пространстве
			AdbPlayerController* dbPlayerController = Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController());
			if (dbPlayerController)
			{
				// Получаем точки
				FVector cursorLocation = dbPlayerController->GetCursorWorldLocation();
				FVector arrowLocation = PivotArrow->GetComponentLocation();

				// Определяем направление, отсекаем поворот по ненужным осям
				FRotator newRotate = (cursorLocation - arrowLocation).Rotation();
				newRotate.Yaw = 0.;
				newRotate.Roll = 0.;

				// Если персонаж смотрит Влево
				if (GetActorRotation().Yaw == 180.)
				{
					// добавляем градусы для корректного отображения
					newRotate.Pitch = 180. - newRotate.Pitch;

					// упираемся стрелкой в крайние точки, вместо пересечения персонажа
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
				// Если персонаж смотрит Вправо
				else
				{
					// упираемся стрелкой в крайние точки, вместо пересечения персонажа
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
				// Задаем положение
				PivotArrow->SetWorldRotation(newRotate);
				//ArrowDirectionOfKick->SetActorRotation(newRotate);
			}
		}
	}
///_________________///
///////////////////////


//////////////////////////////////////////////
/// Задать импульс всем снарядам в области ///
///________________________________________///
/// 
	void ABladPirat::GiveKickEach()
	{
		// Ожидание подходящего момента в соответствии анимации
		if (bIsAttack && GetSprite()->GetPlaybackPositionInFrames() == 6)
		{
			// Получение всех пересекаемых снарядов
			TArray<AActor*> overlappingActors;
			KickRange->GetOverlappingActors(overlappingActors, APinusBase::StaticClass());

			// Для каждого снаряда
			for (AActor* Actor : overlappingActors)
			{
				// Приводим, чтобы получить его компонент
				// чтобы было к чему приложить импульс
				APinusBase* tempPinus = Cast<APinusBase>(Actor);
				if (tempPinus)
				{
					// Переводим направление стрелки в вектор
					// чтобы отправить снаряд именно туда, куда указывает стрелка
					FRotator rotator = PivotArrow->GetComponentRotation();
					FVector rotatorInVec = FQuat(rotator).RotateVector(FVector::ForwardVector);
					// Задаем импульс учитывая Силу Пинка
					tempPinus->CapsuleCollision->AddImpulse(rotatorInVec * KickPower * 5000);
				}
			}

			// Сброс таймера
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleKickInAttackAnimation);
			//UE_LOG(LogTemp, Warning, TEXT("Eeeeeeend Kick"));
		}
	}
///________________________________________///
//////////////////////////////////////////////



