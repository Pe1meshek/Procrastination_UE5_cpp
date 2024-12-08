/*
Контроллер виджетов уровня

Хранит указатели всех виджетов и управляет ими
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelMenuController.generated.h"

class UWidgetUI;
class UWidgetGamePause;
class UWidgetControl;
class UWidgetLose;
class UWidgetWin;

UCLASS()
class DBCPPTRY17042_API ALevelMenuController : public AActor
{
	GENERATED_BODY()

public:
	// Классы создаваемых Виджетов //
	//
	// UI - т.е выбранный снаряд + меню выбора
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetUI> classWidgetUI;
	//
	// Пауза
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetGamePause> classWidgetGamePause;
	//
	// Управление
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetControl> classWidgetControl;
	//
	// Поражение
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetLose> classWidgetLose;
	//
	// Победа
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<UWidgetWin> classWidgetWin;
	//_____________________________//

protected:
	// Сохранение созданных Виджетов, для дальнейшей работы с ними
	// Поражени и Победу можно не сохранять, т.к после их вызова уровень меняется
	UWidgetUI* WidgetUI;
	UWidgetGamePause* WidgetGamePause;
	UWidgetControl* WidgetControl;

public:	
	ALevelMenuController();

protected:
	virtual void BeginPlay() override;

public:	
	// Открытие/скрытие меню выбора снаряда
	UFUNCTION(BlueprintCallable)
	void InventoryFlip();

	// Открытие/скрытие меню Паузы
	UFUNCTION(BlueprintCallable)
	void PauseUnpause();

	// Скрыть все, открыть Меню Паузы
	void GoToPauseMenu();

	// Скрыть все, открыть Управление
	void GoToControl();

	// Показать экран Поражения
	void LosedGame();

	// Показать экран Победы
	void WonGame();
};
