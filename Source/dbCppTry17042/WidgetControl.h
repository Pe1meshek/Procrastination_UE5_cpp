/*
Widget ����������

����� ���������� ����������.
��� �����������
������ ����� ������� ������������ ������ ���� ���������

������������
������ ��-������� ������������ ��� ��������� � ������� ���� � � ������� (�� ����� �����)
� ������ ������ ������ ����������� �����, �� ������ - �����
� ���������� ��� ��� ������ ������
*/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetControl.generated.h"

class UButton;
class AMainMenuController;
class ALevelMenuController;

UCLASS()
class DBCPPTRY17042_API UWidgetControl : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������ ����������� � ������� ����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonMenu;

	// ������ ����������� � ���� �����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBack;

protected:
	// ������ �� ���������� �������� ����
	// ����� ��� ���������� ���������� ������� ���������
	AMainMenuController* MainMenuController = nullptr;

	// ������ �� ���������� ������� ��������
	// ����� ��� ���������� ���������� ������� ���������
	ALevelMenuController* LevelMenuController = nullptr;

public:
	virtual void NativeConstruct() override;

	// ���������� ������ �� ���������� �������� ����
	void AddController(AMainMenuController* mainMenuController);

	// ���������� ������ �� ���������� �������� ������� �������
	void AddController(ALevelMenuController* levelMenuController);

	// ������� ������ ����������� � ������� ����
	UFUNCTION(BlueprintCallable)
	void OnButtonMenuClicked();

	// ������� ������ ����������� � ���� �����
	UFUNCTION(BlueprintCallable)
	void OnButtonBackClicked();
};
