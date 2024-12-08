/*
Widget �����

����������� �� ����� �����, ���������:
������������� �������,
��������� � ������� ����,
������� ���� ����������.
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetGamePause.generated.h"

class UButton;
class ALevelMenuController;

UCLASS()
class DBCPPTRY17042_API UWidgetGamePause : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������ ������������ � ����
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonContinue;

	// ������ �����������
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonRestart;

	// ������ �������� ���� ����������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonControl;

	// ������ �������� � ������� ����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;

protected:
	// ������ �� ���������� �������� ����
	// ����� ��� ���������� ���������� ������� ���������
	ALevelMenuController* LevelMenuController = nullptr;
	
public:
	virtual void NativeConstruct() override;

	// ���������� ������ �� ����������
	void AddController(ALevelMenuController* levelMenuController);

	// ������� ������ //
	UFUNCTION(BlueprintCallable)
	void OnButtonContinueClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonRestartClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonControlClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonExitClicked();
	//________________//

};
