/*
���������� �������� ������

������ ��������� ���� �������� � ��������� ���
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMenuController.generated.h"

class UWidgetUI;
class UWidgetGamePause;
class UWidgetControl;
class UWidgetLose;
class UWidgetWin;

UCLASS()
class DBCPPTRY17042_API ALevelMenuController : public AActor
{
	GENERATED_BODY()

public:
	// ������ ����������� �������� //
	//
	// UI - �.� ��������� ������ + ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetUI> classWidgetUI;
	//
	// �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetGamePause> classWidgetGamePause;
	//
	// ����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetControl> classWidgetControl;
	//
	// ���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetLose> classWidgetLose;
	//
	// ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetWin> classWidgetWin;
	//_____________________________//

protected:
	// ���������� ��������� ��������, ��� ���������� ������ � ����
	// �������� � ������ ����� �� ���������, �.� ����� �� ������ ������� ��������
	UWidgetUI* WidgetUI;
	UWidgetGamePause* WidgetGamePause;
	UWidgetControl* WidgetControl;

public:	
	ALevelMenuController();

protected:
	virtual void BeginPlay() override;

public:	
	// ��������/������� ���� ������ �������
	UFUNCTION(BlueprintCallable)
	void InventoryFlip();

	// ��������/������� ���� �����
	UFUNCTION(BlueprintCallable)
	void PauseUnpause();

	// ������ ���, ������� ���� �����
	void GoToPauseMenu();

	// ������ ���, ������� ����������
	void GoToControl();

	// �������� ����� ���������
	void LosedGame();

	// �������� ����� ������
	void WonGame();
};
