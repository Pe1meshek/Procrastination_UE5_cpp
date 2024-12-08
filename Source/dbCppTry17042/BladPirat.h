/*
������� ����������� ��������

����� ������, �������, ��������� ������� � ������ ��
����� ���� ������
������ �������� � ������������� �������� ����������� ���
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
	// ���������� //
	//
	// ����� �������� �������
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SpawnPinusPoint;
	//
	// ����� ���� �����
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* ChargeBar;
	//
	// ����� ��� ������
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	//
	// ������
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	//
	// ������� �������
	// �������� ������ �� �������, ������� �������� � ������ �������
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* KickRange;
	//
	// ����� ������� ����������� �����
	UPROPERTY(VisibleAnywhere)
	USceneComponent* PivotArrow;
	//
	// ������� ����������� �����
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* Arrow;
	//____________//


	// ��������� ����� ��������� UE //
	//
	// �������� ����� ���� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | ChargeBar")
	UPaperFlipbook* ChargeBarAnimation;
	//
	// �������� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | Arrow")
	UPaperSprite* ArrowSprite;
	//
	// �������� ���������������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationIdle;
	//
	// �������� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationRun;
	//
	// �������� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationJump;
	//
	// �������� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationFall;
	//
	// �������� �����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationGround;
	//
	// ��������� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | HeroAnimation")
	UPaperFlipbook* PFAnimationAttack;
	//
	// ������ ����������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | PinusClasses")
	TArray<TSubclassOf<APinusBase>> PinusClasses;
	//______________________________//


	// ��������� ��������� ������
	APinusBase* PinusControlled;


protected:
	// ����� ����� � ������ ������
	bool bIsKickCharging;

	// ���/���� ����������
	// ����� ��� ���������� ����� � �����������
	// ���������� � ������ ������
	bool bIsCanControl;

	// ����� �� �������� �������� �����������
	bool bIsGroundAfterFall;

	// ������� �� �������� � ������ ������
	bool bIsAttack;

	// ���� �����
	// ������������� ������ ������ �� ������� ���������� �������� ����� ������
	int32 KickPower;

	// ����� ��� ������� ����� �� ����� ������������ �������� ����� � ������������ ������
	FTimerHandle TimerHandleKickInAttackAnimation;

	// ����� ��� �������� ������� �� ����� ������ �����
	FTimerHandle TimerHandleSetArrowRotation;

	// ��������� ����� ��� �������� �������
	TSubclassOf<APinusBase> SelectedPinusClass;

public:
	ABladPirat();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;


	// ��������� � PlayerController � ��������� ��� viewTarget
	void SetAsMainCamera();


	// ���������� � �������� //
	//
	// �������� (�����/������)
	void MoveRight(float direction);
	//
	// ������ 
	// ������������ ������� (������), �� ��� ����� ���������
	// ������� ����������
	void Jump() override;
	//
	// �������� �������
	void SpawnPinus();
	//
	// ������ ������� �����
	void StartCharge();
	//
	// �����
	UFUNCTION()
	void Kick();
	//_______________________//

	//��������� �������
	void ActivatePinus();

	// ������ ����� ������ ������������ ��������
	void SetSelectedPinusClass(int32 num);


protected:
	// ������ ��������� //
	//
	// ����������� ��������� � ������ ��������
	void StateMachine();
	//
	// ������ �������� � ���������� �������� �������� 
	// anim - ��������������� ��������
	// bIsLoop - true, ���� ����� ���������
	// bIsControl - false, ���� ����� ��������� ����������
	void SetAnimationAndMode(UPaperFlipbook* anim, bool bIsLoop, bool bIsControl);
	//
	// ����� ���������
	// ����� ��� ������ ��������� ����� � ����������� 
	UFUNCTION()
	void DropOneTimeAnim();
	//__________________//


	// ������� ��������� ������� ����������� �����
	void SetArrowPosition();


	// ���������� �������� ���� �������� � �������
	void GiveKickEach();
};
