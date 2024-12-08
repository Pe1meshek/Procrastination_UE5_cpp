/*
Widget ������

���������:
������� �� ��������� �������,
������������� �������,
������� � ������� ����
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetWin.generated.h"

class UButton;

UCLASS()
class DBCPPTRY17042_API UWidgetWin : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������ �������� �� ��������� �������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonNext;

	// ������ ����������� ������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonRestart;

	// ������ �������� � ������� ����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;

	virtual void NativeConstruct() override;

	// ������� ������ //
	UFUNCTION(BlueprintCallable)
	void OnButtonNextClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonRestartClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonExitClicked();
	//________________//
};
