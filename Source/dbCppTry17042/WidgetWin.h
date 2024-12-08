/*
Widget Победы

Позволяет:
перейти на следующий уровень,
перезапустить уровень,
перейти в Главное меню
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
	// Кнопка перехода на следующий уровень
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonNext;

	// Кнопка перезапуска уровня
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonRestart;

	// Кнопка перехода в главное меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;

	virtual void NativeConstruct() override;

	// Нажатие кнопок //
	UFUNCTION(BlueprintCallable)
	void OnButtonNextClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonRestartClicked();

	UFUNCTION(BlueprintCallable)
	void OnButtonExitClicked();
	//________________//
};
