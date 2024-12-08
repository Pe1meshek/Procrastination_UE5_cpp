/*
Widget Упарвления

Здесь отображено управление.
Без функционала
Вместо этого виджета потенциально должны быть Настройки

Единственное
Виджет по-разному отображается при открытиии в главном меню и в игровом (на паузе когда)
В первом случае кнопка возвращения слева, во втором - снизу
В реализации это две разные кнопки
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
	// Кнопка возвращения в Главное меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonMenu;

	// Кнопка аозвращения в Меню Паузы
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonBack;

protected:
	// Ссылка на контроллер Главного меню
	// через нее происходит управление другими виджетами
	AMainMenuController* MainMenuController = nullptr;

	// Ссылка на контроллер Игровых Виджетов
	// через нее происходит управление другими виджетами
	ALevelMenuController* LevelMenuController = nullptr;

public:
	virtual void NativeConstruct() override;

	// Сохранение ссылки на Контроллер Главного меню
	void AddController(AMainMenuController* mainMenuController);

	// Сохранение ссылки на Контроллер виджетов Игровых уровней
	void AddController(ALevelMenuController* levelMenuController);

	// Нажатие кнопки возвращения в Главное меню
	UFUNCTION(BlueprintCallable)
	void OnButtonMenuClicked();

	// Нажатие кнопки возвращения в Меню Паузы
	UFUNCTION(BlueprintCallable)
	void OnButtonBackClicked();
};
