/*
Главный управляемый персонаж

Умеет бегать, прыгать, создавать снаряды и пинать их
Имеет свою камеру
Машина состояни с переключением анимаций реализована тут
*/
#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "BladPirat.generated.h"

class USceneComponent;
class UPaperFlipbookComponent;
class UPaperSpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UBoxComponent;
class UPaperFlipbook;
class UPaperSprite;
class APinusBase;
class AdbPlayerController;

UCLASS()
class DBCPPTRY17042_API ABladPirat : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Компоненты //
	//
	// Точка создания снаряда
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPinusPoint;
	//
	// Шкала силы пинка
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* ChargeBar;
	//
	// Плечо для камеры
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	//
	// Камера
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	//
	// Область пинания
	// пинаются только те снаряды, которые попадают в данную область
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* KickRange;
	//
	// Пивот Стрелки направления пинка
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PivotArrow;
	//
	// Стрелак направления пинка
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* Arrow;
	//____________//


	// Установка через интерфейс UE //
	//
	// Анимация Шкалы силы удара
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | ChargeBar")
	UPaperFlipbook* ChargeBarAnimation;
	//
	// Анимация Стрелки
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | Arrow")
	UPaperSprite* ArrowSprite;
	//
	// Анимация Ничегонеделанья
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationIdle;
	//
	// Анимация Бега
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationRun;
	//
	// Анимация Прыжка
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationJump;
	//
	// Анимация Падения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationFall;
	//
	// Анимация Приземления
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationGround;
	//
	// Анирмация Пинка
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationAttack;
	//
	// Классы создаваемых снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | PinusClasses")
	TArray<TSubclassOf<APinusBase>> PinusClasses;
	//______________________________//


	// Последний созданный снаряд
	APinusBase* PinusControlled;


protected:
	// Заряд удара в данный момент
	bool bIsKickCharging;

	// Вкл/выкл управления
	// нужно для реализации Пинка и Приземления
	// пригодится в случае Смерти
	bool bIsCanControl;

	// Нужно ли включить анимацию Приземления
	bool bIsGroundAfterFall;

	// Атакует ли персонаж в данный момент
	bool bIsAttack;

	// Сила Пинка
	// соответствует номуру фрейма на котором прервалась анимация Шкалы заряда
	int32 KickPower;

	// Нужен для запуска Пинка во время проигрывания анимации Пинка в определенный момент
	FTimerHandle TimerHandleKickInAttackAnimation;

	// Нужен для поворота стрелки во время заряда Пинка
	FTimerHandle TimerHandleSetArrowRotation;

	// Выбранный класс для создания Снаряда
	TSubclassOf<APinusBase> SelectedPinusClass;

public:
	ABladPirat();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// Обращение к PlayerController и установка как viewTarget
	void SetAsMainCamera();


	// Управление и действия //
	//
	// Движение (влево/вправо)
	void MoveRight(float direction);
	//
	// Прыжок 
	// используется готовый (вшитый), но его нужно отключать
	// воэтому перегрузка
	void Jump() override;
	//
	// Создание снаряда
	void SpawnPinus();
	//
	// Запуск зарядки Пинка
	void StartCharge();
	//
	// Пинок
	UFUNCTION()
	void Kick();
	//_______________________//

	//Активация Снаряда
	void ActivatePinus();

	// Задать номер класса создаваемого Снаяряда
	void SetSelectedPinusClass(int32 num);


protected:
	// Машина состояний //
	//
	// Определение состояния и запуск анимации
	void StateMachine();
	//
	// Запуск анимации с установкой ключевых настроек 
	// anim - устанавливаемая анимация
	// bIsLoop - true, если нужно зациклить
	// bIsControl - false, если нужно отключить управление
	void SetAnimationAndMode(UPaperFlipbook* anim, bool bIsLoop, bool bIsControl);
	//
	// Сброс состояний
	// нужен для сброса состояний атаки и приземления 
	UFUNCTION()
	void DropOneTimeAnim();
	//__________________//


	// Задание положения стрелки направления пинка
	void SetArrowPosition();


	// Добавление импульса всем снарядам в области
	void GiveKickEach();
};
