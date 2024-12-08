/*
Widget �������� ����

���������:
������ � ������� ������,
������� ���� �������,
������� ���� �����������,
������� ����������
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetMainMenu.generated.h"

class UButton;
class AMainMenuController;

UCLASS()
class DBCPPTRY17042_API UWidgetMainMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������ ������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonStart;

	// ������ �������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLevels;

	// ������ ����������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonControl;

	// ������ ������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;

private:
	// ������ �� ���������� �������� ����
	// ����� ��� ���������� ���������� ������� ���������
	AMainMenuController* MainMenuController = nullptr;

public:
	virtual void NativeConstruct() override;

	// ������� ������ //
	UFUNCTION(BlueprintCallable)
	void AddController(AMainMenuController* mainMenuController);

	UFUNCTION(BlueprintCallable)
	void OnButtonStartClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonLevelsClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonControlClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonQuitClicked();
	//________________//
};
