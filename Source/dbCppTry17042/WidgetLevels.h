/*
Widget ������

������������� � ������, �������� � ���� ������ (HandlerLevels)
� ���������� ������, ������� ��������� ��������������� �������
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetLevels.generated.h"

class UButton;
class UTextBlock;
class AMainMenuController;

UCLASS()
class DBCPPTRY17042_API UWidgetLevels : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������ ����������� � ������� ����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonMenu;

	// ������ ������
	// �� � ����� ��������� ������ �������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLevel1;
	
	// ���������� ������ � ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 ColumnNum = 7;

	// �������������� ������ ����� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MarginX = 10.f;

	// ������������ ������ ����� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MarginY = 10.f;


protected:
	// ������ �� ���������� �������� ����
	// ����� ��� ���������� ���������� ������� ���������
	AMainMenuController* MainMenuController = nullptr;

	// ������ ��� ������ �������
	TArray<UButton*> ButtonsLevels;

public:
	virtual void NativeConstruct() override;

	// ���������� ������ �� ���������� �������� ����
	UFUNCTION(BlueprintCallable)
	void AddController(AMainMenuController* mainMenuController);

	// ������� ������ ����������� � ������� ����
	UFUNCTION(BlueprintCallable)
	void OnButtonMenuClicked();

	// ������� ������ �������� �� ������ �������
	UFUNCTION(BlueprintCallable)
	void OnButtonLevelClicked();
};
