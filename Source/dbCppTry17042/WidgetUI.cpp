
#include "WidgetUI.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateBrush.h"
#include "BladPirat.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetUI::NativeConstruct()
	{
		Super::NativeConstruct();

		SetIsFocusable(false);

		// Не работает :(  Пришлось менять ручками в UE5
		ButtonSelected->IsFocusable = false;

		UCanvasPanel* canvas = Cast<UCanvasPanel>(GetRootWidget());
		UButton* newButton = nullptr;
		UImage* newImage = nullptr;
		UCanvasPanelSlot* newSlot = nullptr;

		// Шаблоны по которым создаются ячейки
		const UCanvasPanelSlot* originalImageSlot = Cast<UCanvasPanelSlot>(ImageCase->Slot);
		const UCanvasPanelSlot* originalButtonSlot = Cast<UCanvasPanelSlot>(ButtonSelected->Slot);

		// Стиль кнопки, отображающей выбранный снаряд
		if (!ItemImages.IsEmpty())
		{
			FButtonStyle tempStyle = ButtonSelected->GetStyle();
			tempStyle.Normal.SetResourceObject(ItemImages[0]);
			tempStyle.Hovered.SetResourceObject(ItemImages[0]);
			tempStyle.Pressed.SetResourceObject(ItemImages[0]);
			ButtonSelected->SetStyle(tempStyle);
		}
	
		// Создание ячеек инвентаря
		if (canvas)
		{
			for (int32 i = 0; i < ItemImages.Num(); i++)
			{
				// Создание фона
				newImage = NewObject<UImage>(this, UImage::StaticClass());
				newImage->SetBrush(ImageCase->GetBrush());
				newImage->SetVisibility(ESlateVisibility::Hidden);

				// Копируем основные параметры фона-шаблона
				newSlot = canvas->AddChildToCanvas(newImage);
				newSlot->SetAnchors(originalImageSlot->GetAnchors());
				newSlot->SetSize(originalImageSlot->GetSize());
				newSlot->SetAlignment(originalImageSlot->GetAlignment());

				// Считаем расположение
				FVector2D newSlotPosition;
				newSlotPosition.X = originalImageSlot->GetPosition().X + newSlot->GetSize().X * (i % InventoryColumnNum);
				newSlotPosition.Y = originalImageSlot->GetPosition().Y + newSlot->GetSize().Y * (i / InventoryColumnNum + 1);
				newSlot->SetPosition(newSlotPosition);

				// Создание кнопки
				newButton = NewObject<UButton>(this, UButton::StaticClass());
				newButton->SetStyle(ButtonSelected->GetStyle());
				newButton->SetVisibility(ESlateVisibility::Hidden);
				newButton->IsFocusable = false;

				// Стили нажатия, наведения на кнопку
				FButtonStyle tempStyle = ButtonSelected->GetStyle();
				tempStyle.Normal.SetResourceObject(ItemImages[i]);
				tempStyle.Hovered.SetResourceObject(ItemImages[i]);
				tempStyle.Pressed.SetResourceObject(ItemImages[i]);
				newButton->SetStyle(tempStyle);

				// Копируем основные параметры кнопки-шаблона
				newSlot = canvas->AddChildToCanvas(newButton);
				newSlot->SetAnchors(originalButtonSlot->GetAnchors());
				newSlot->SetSize(originalButtonSlot->GetSize());
				newSlot->SetAlignment(originalButtonSlot->GetAlignment());
				newSlot->SetPosition(newSlotPosition);

				// добавляем в массивы
				ImagesBoard.Push(newImage);
				ButtonsPinusBoard.Push(newButton);
			}
		}

		// Привязка функций к кнопкам
		if (ButtonSelected)
		{
			ButtonSelected->OnClicked.AddDynamic(this, &UWidgetUI::FlipBoardVisible);
		}
		for (UButton* pinusBoard : ButtonsPinusBoard)
		{
			pinusBoard->OnClicked.AddDynamic(this, &UWidgetUI::OnItemPinusClicked);
		}
	}
///_____________///
///////////////////


/////////////////
/// Инвентарь ///
///___________///
/// 
/// Свернуть/развернуть инвентарь
	void UWidgetUI::SetBoardVisible(bool boardVisible)
	{
		bIsBoardVisible = boardVisible;
		for (auto imageBoard : ImagesBoard)
		{
			imageBoard->SetVisibility(boardVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
		for (auto pinusBoard : ButtonsPinusBoard)
		{
			pinusBoard->SetVisibility(boardVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
		}
	}
///
/// Переключить состояние инвентаря
	void UWidgetUI::FlipBoardVisible()
	{
		SetBoardVisible(!bIsBoardVisible);
	}
///___________///
/////////////////


///////////////////////////////////
/// Нажатие на ячейку инвентаря ///
///_____________________________///
/// 
	void UWidgetUI::OnItemPinusClicked()
	{
		// Обходим все кнопки-ячейки
		for (int32 i = 0; i < ButtonsPinusBoard.Num(); i++)
		{
			// Ищем ту, на которую наведен курсор
			if (ButtonsPinusBoard[i]->IsHovered())
			{
				// Передаем её номер в массике Игруку
				// как указание выбранного снаряда
				ABladPirat* bladPirat = Cast<ABladPirat>(GetWorld()->GetFirstPlayerController()->GetPawn());
				if (bladPirat)
				{
					bladPirat->SetSelectedPinusClass(i);
				}

				// Меням стиль кнопки-отображалки на стиль выбранной ячейки
				ButtonSelected->SetStyle(ButtonsPinusBoard[i]->GetStyle());
				break;
			}
		}
		FlipBoardVisible();
	}
///_____________________________///
///////////////////////////////////

