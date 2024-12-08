/*
Widget UI

Реализует меню выбора снаряда
Имеет кнопку-шаблон, по которой генерируются остальные кнопки-ячейки меню выбора
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetUI.generated.h"

class UButton;
class UImage;

UCLASS()
class DBCPPTRY17042_API UWidgetUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// Кнопка-шаблон
	// отображает выбранный снаряд
	// по нажатию сворачивает/разворачивает меню
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSelected;

	// Картинка-шаблон
	// используется как фон для все ячеек
	UPROPERTY(meta = (BindWidget))
	UImage* ImageCase;

	// Массив текстур элементов 
	// для каждого элемента создается ячейка инвентаря (кнопка)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<UTexture2D*> ItemImages;

	// Количествол ячеек в строке
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 InventoryColumnNum = 3;


protected:
	// Массив ячеек (кнопок)
	TArray<UButton*> ButtonsPinusBoard;
	
	// Массив фонов под ячейки
	TArray<UImage*> ImagesBoard;

	// Состояниие инвентаря
	// true - если развернут
	bool bIsBoardVisible = false;

protected:
	virtual void NativeConstruct() override;

public:
	// Свернуть/развернуть инвентарь
	UFUNCTION()
	void SetBoardVisible(bool boardVisible);

	// Переключить состояние инвентаря
	UFUNCTION()
	void FlipBoardVisible();
	
	// Нажатие на ячейку инвентаря
	UFUNCTION()
	void OnItemPinusClicked();

};
