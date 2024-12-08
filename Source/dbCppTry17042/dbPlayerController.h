/*
����������

������������ ������� ����� � �������� �������������� ������� �������
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "dbPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AAutoCamera;
class ALevelMenuController;
class ABladPirat;
struct FInputActionInstance;
class APlaneForCursor;

UCLASS()
class DBCPPTRY17042_API AdbPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// ��������� ����� ��������� UE//
	//
	// Input Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput | Input Mapping")
	UInputMappingContext* InputMappingContext = nullptr;
	//
	// �������� ������ �������������� ��������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraHorizontalMove = nullptr;
	//
	// �������� ������ ������������ ��������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraVerticalMove = nullptr;
	//
	// �������� ������ �����������/���������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraZoom = nullptr;
	//
	// �������� ������ ������������ ������ ������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraFlipMode = nullptr;
	//
	// �������� ������ �������� �����
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraCapturePoint = nullptr;
	//
	// �������� ��������� �������/�������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | UI")
	UInputAction* AIInventoryFlipVisible = nullptr;
	//
	// �������� �����
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | UI")
	UInputAction* AIGamePause = nullptr;
	//
	// �������� ����� ��������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratMoveRight = nullptr;
	//
	// �������� ����� ������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratJump = nullptr;
	//
	// �������� ����� �������� �������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratSpawnPinus = nullptr;
	//
	// �������� ����� ����� �����
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratStartCharge = nullptr;
	//
	// �������� ����� �����
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratKick = nullptr;
	//
	// �������� ����� ��������� �������
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratActivatePinus = nullptr;
	//
	// ����� ������
	// ��������� ����� �����, ����� ������������ �� ��� ��������� �������, 
	// ��� ����� ������� ������� ���������� ����������.
	// ������ ������������ 2 �����, ���������� ��� Y, ����� ������� �� �������� � �����
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | PlaneForCursor")
	TSubclassOf<APlaneForCursor> ClassPlaneForCursor = nullptr;
	//_____________________________//


	// ����������� ������� //
	//
	// ������
	// �������� + ������������ �������
	AAutoCamera* AutoCamera = nullptr;
	//
	// ���������� �������� �������
	// ��������� + �����
	ALevelMenuController* LevelMenuController = nullptr;
	//
	// ������� ��������
	// �������� + �������� ������� + �����
	ABladPirat* Pirat = nullptr;
	//_____________________//


	// ������ ������
	// 0 - ������ ��������������� �������
	// 1 - ����������� ������
	// 2 - ������ ����������� � ���������
	int32 CameraMode = 0;

public:
	// �������� �������� � ��������
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

public:
	// ������ ��������� �� ������ ��� ����������� ����������
	void SetAutoCamera(AAutoCamera* autoCamera);
	
	// ������ ��������� �� ���������� �������� ��� ����������� ����������
	void SetLevelMenuController(ALevelMenuController* levelMenuController);

	// ���������� ������� ���������� �������
	FVector GetCursorWorldLocation();

protected:
	// ����� ������� ������ //
	void CameraHorizontalMove(const FInputActionInstance& Instance);
	void CameraVerticalMove(const FInputActionInstance& Instance);
	void CameraSaveMouseClickPoint(const FInputActionInstance& Instance);
	void CameraMoveRelativePoint(const FInputActionInstance& Instance);
	void CameraZoom(const FInputActionInstance& Instance);
	void CameraFlipMode(const FInputActionInstance& Instance);
	//______________________//


	// ����� ������ ����������� �������� //
	void InventoryFlipVisible(const FInputActionInstance& Instance);
	void GamePause(const FInputActionInstance& Instance);
	//___________________________________//


	// ����� ������� �������� ��������� //
	void PiratMoveRight(const FInputActionInstance& Instance);
	void PiratJump(const FInputActionInstance& Instance);
	void PiratSpawnPinus(const FInputActionInstance& Instance);
	void PiratStartCharge(const FInputActionInstance& Instance);
	void PiratKick(const FInputActionInstance& Instance);
	void PiratActivatePinus(const FInputActionInstance& Instance);
	//__________________________________//
};
