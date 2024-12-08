
#include "WidgetUI.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Styling/SlateBrush.h"
#include "BladPirat.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetUI::NativeConstruct()
	{
		Super::NativeConstruct();

		SetIsFocusable(false);

		// �� �������� :(  �������� ������ ������� � UE5
		ButtonSelected->IsFocusable = false;

		UCanvasPanel* canvas = Cast<UCanvasPanel>(GetRootWidget());
		UButton* newButton = nullptr;
		UImage* newImage = nullptr;
		UCanvasPanelSlot* newSlot = nullptr;

		// ������� �� ������� ��������� ������
		const UCanvasPanelSlot* originalImageSlot = Cast<UCanvasPanelSlot>(ImageCase->Slot);
		const UCanvasPanelSlot* originalButtonSlot = Cast<UCanvasPanelSlot>(ButtonSelected->Slot);

		// ����� ������, ������������ ��������� ������
		if (!ItemImages.IsEmpty())
		{
			FButtonStyle tempStyle = ButtonSelected->GetStyle();
			tempStyle.Normal.SetResourceObject(ItemImages[0]);
			tempStyle.Hovered.SetResourceObject(ItemImages[0]);
			tempStyle.Pressed.SetResourceObject(ItemImages[0]);
			ButtonSelected->SetStyle(tempStyle);
		}
	
		// �������� ����� ���������
		if (canvas)
		{
			for (int32 i = 0; i < ItemImages.Num(); i++)
			{
				// �������� ����
				newImage = NewObject<UImage>(this, UImage::StaticClass());
				newImage->SetBrush(ImageCase->GetBrush());
				newImage->SetVisibility(ESlateVisibility::Hidden);

				// �������� �������� ��������� ����-�������
				newSlot = canvas->AddChildToCanvas(newImage);
				newSlot->SetAnchors(originalImageSlot->GetAnchors());
				newSlot->SetSize(originalImageSlot->GetSize());
				newSlot->SetAlignment(originalImageSlot->GetAlignment());

				// ������� ������������
				FVector2D newSlotPosition;
				newSlotPosition.X = originalImageSlot->GetPosition().X + newSlot->GetSize().X * (i % InventoryColumnNum);
				newSlotPosition.Y = originalImageSlot->GetPosition().Y + newSlot->GetSize().Y * (i / InventoryColumnNum + 1);
				newSlot->SetPosition(newSlotPosition);

				// �������� ������
				newButton = NewObject<UButton>(this, UButton::StaticClass());
				newButton->SetStyle(ButtonSelected->GetStyle());
				newButton->SetVisibility(ESlateVisibility::Hidden);
				newButton->IsFocusable = false;

				// ����� �������, ��������� �� ������
				FButtonStyle tempStyle = ButtonSelected->GetStyle();
				tempStyle.Normal.SetResourceObject(ItemImages[i]);
				tempStyle.Hovered.SetResourceObject(ItemImages[i]);
				tempStyle.Pressed.SetResourceObject(ItemImages[i]);
				newButton->SetStyle(tempStyle);

				// �������� �������� ��������� ������-�������
				newSlot = canvas->AddChildToCanvas(newButton);
				newSlot->SetAnchors(originalButtonSlot->GetAnchors());
				newSlot->SetSize(originalButtonSlot->GetSize());
				newSlot->SetAlignment(originalButtonSlot->GetAlignment());
				newSlot->SetPosition(newSlotPosition);

				// ��������� � �������
				ImagesBoard.Push(newImage);
				ButtonsPinusBoard.Push(newButton);
			}
		}

		// �������� ������� � �������
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
/// ��������� ///
///___________///
/// 
/// ��������/���������� ���������
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
/// ����������� ��������� ���������
	void UWidgetUI::FlipBoardVisible()
	{
		SetBoardVisible(!bIsBoardVisible);
	}
///___________///
/////////////////


///////////////////////////////////
/// ������� �� ������ ��������� ///
///_____________________________///
/// 
	void UWidgetUI::OnItemPinusClicked()
	{
		// ������� ��� ������-������
		for (int32 i = 0; i < ButtonsPinusBoard.Num(); i++)
		{
			// ���� ��, �� ������� ������� ������
			if (ButtonsPinusBoard[i]->IsHovered())
			{
				// �������� � ����� � ������� ������
				// ��� �������� ���������� �������
				ABladPirat* bladPirat = Cast<ABladPirat>(GetWorld()->GetFirstPlayerController()->GetPawn());
				if (bladPirat)
				{
					bladPirat->SetSelectedPinusClass(i);
				}

				// ����� ����� ������-����������� �� ����� ��������� ������
				ButtonSelected->SetStyle(ButtonsPinusBoard[i]->GetStyle());
				break;
			}
		}
		FlipBoardVisible();
	}
///_____________________________///
///////////////////////////////////

