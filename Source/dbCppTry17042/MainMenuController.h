/*
Контроллер виджетов Главного меню

Хранит указатели всех виджетов и управляет ими
*/


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuController.generated.h"

class UWidgetMainMenu;
class UWidgetLevels;
class UWidgetControl;

UCLASS()
class DBCPPTRY17042_API AMainMenuController : public AActor
{
	GENERATED_BODY()

public:
	// Классы создаваемых Виджетов //
	//
	// Главное меню
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetMainMenu> classWidgetMainMenu;
	//
	// Меню уровней
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetLevels> classWidgetLevels;
	//
	// Управление
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetControl> classWidgetControl;
	//_____________________________//

protected:
	// Сохранение созданных Виджетов, для дальнейшей работы с ними
	UWidgetMainMenu* WidgetMainMenu;
	UWidgetLevels* WidgetLevels;
	UWidgetControl* WidgetControl;

public:	
	AMainMenuController();

protected:
	virtual void BeginPlay() override;

public:	
	// Скрыть все, открыть Главное меню
	UFUNCTION(BlueprintCallable)
	void GoToMainMenu();

	// Скрыть все, открыть меню Уровней	
	UFUNCTION(BlueprintCallable)
	void GoToLevels();

	// Скрыть все, открыть Управление	
	UFUNCTION(BlueprintCallable)
	void GoToControl();

};
