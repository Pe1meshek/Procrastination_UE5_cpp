/*
Widget Уровни

Подсматривает в массив, хранящий в себе уровни (HandlerLevels)
И генерирует кнопки, которые загружают соответствующий уровень
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
	// Кнопка возвращения в Главное меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonMenu;

	// Кнопка Шаблон
	// по её стилю создаются кнопки уровней
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonLevel1;
	
	// Количество кнопок в строке
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 ColumnNum = 7;

	// Горизонтальный отступ между кнопками
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MarginX = 10.f;

	// Вертикальный отступ между кнопками
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MarginY = 10.f;


protected:
	// Ссылка на контроллер Главного меню
	// через нее происходит управление другими виджетами
	AMainMenuController* MainMenuController = nullptr;

	// Массив для кнопок уровней
	TArray<UButton*> ButtonsLevels;

public:
	virtual void NativeConstruct() override;

	// Сохранение ссылки на Контроллер Главного меню
	UFUNCTION(BlueprintCallable)
	void AddController(AMainMenuController* mainMenuController);

	// Нажатие кнопки возвращения в Главное меню
	UFUNCTION(BlueprintCallable)
	void OnButtonMenuClicked();

	// Нажатие кнопки перехода на другой уровень
	UFUNCTION(BlueprintCallable)
	void OnButtonLevelClicked();
};
