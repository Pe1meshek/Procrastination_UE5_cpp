/*
Widget Поражения

Позволяет:
перезапустить уровень,
перейти в Главное меню
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetLose.generated.h"

class UButton;

UCLASS()
class DBCPPTRY17042_API UWidgetLose : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Кнопка перезапуска уровня
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonRestart;

	// Кнопка перехода в Главное меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;

	virtual void NativeConstruct() override;

	// Нажатие кнопок //
	UFUNCTION(BlueprintCallable)
	void OnButtonRestartClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonExitClicked();
	//________________//
};
