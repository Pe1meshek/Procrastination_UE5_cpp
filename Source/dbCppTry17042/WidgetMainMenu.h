/*
Widget Главного меню

Позволяет:
начать с первого уровня,
открыть меню уровней,
открыть окно упрравления,
зактыть приложение
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
	// Кнопка старта
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonStart;

	// Кнопка уровней
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLevels;

	// Кнопка управления
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonControl;

	// Кнопка выхода
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonQuit;

private:
	// Ссылка на контроллер Главного меню
	// через нее происходит управление другими виджетами
	AMainMenuController* MainMenuController = nullptr;

public:
	virtual void NativeConstruct() override;

	// Нажатие Кнопок //
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
