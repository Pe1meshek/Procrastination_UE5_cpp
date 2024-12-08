/*
Widget Паузы

Запускается во время паузы, позволяет:
перезапустить уровень,
вернуться в Главное меню,
открыть окно Управления.
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
	// Кнопка возвращщения в игру
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonContinue;

	// Кнопка Перезапуска
	UPROPERTY(meta=(BindWidget))
	UButton* ButtonRestart;

	// Кнопка открытия окна Управления
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonControl;

	// Кнопка перехода в Главное меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonExit;

protected:
	// Ссылка на контроллер Главного меню
	// через нее происходит управление другими виджетами
	ALevelMenuController* LevelMenuController = nullptr;
	
public:
	virtual void NativeConstruct() override;

	// Сохранение ссылки на Контроллер
	void AddController(ALevelMenuController* levelMenuController);

	// Нажатие Кнопок //
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
