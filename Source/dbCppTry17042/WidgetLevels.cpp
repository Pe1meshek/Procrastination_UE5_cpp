

#include "WidgetLevels.h"
#include "Components/Button.h"
#include "MainMenuController.h"
#include "HandlerLevels.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Styling/SlateBrush.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetLevels::NativeConstruct()
	{
		Super::NativeConstruct();
		
		// ������ ������-������
		ButtonLevel1->IsFocusable = false;
		ButtonLevel1->SetVisibility(ESlateVisibility::Hidden);


		UCanvasPanel* canvas = Cast<UCanvasPanel>(GetRootWidget());
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());

		const UCanvasPanelSlot* originalButtonSlot = Cast<UCanvasPanelSlot>(ButtonLevel1->Slot);

		// �������� ������
		if (canvas && handlerLevels)
		{
			for (int32 i = 0; i < handlerLevels->NamesLevels.Num(); i++)
			{
				UButton* newButton = nullptr;
				UCanvasPanelSlot* newSlot = nullptr;
				FVector2D newSlotPosition;

				newButton = NewObject<UButton>(this, UButton::StaticClass());
				newButton->SetStyle(ButtonLevel1->GetStyle());
				newButton->SetVisibility(ESlateVisibility::Visible);
				newButton->IsFocusable = false;

				newSlot = canvas->AddChildToCanvas(newButton);
				newSlot->SetAnchors(originalButtonSlot->GetAnchors());
				newSlot->SetSize(originalButtonSlot->GetSize());
				newSlot->SetAlignment(originalButtonSlot->GetAlignment());

				newSlotPosition.X = originalButtonSlot->GetPosition().X + (newSlot->GetSize().X + MarginX) * ((i) % ColumnNum);
				newSlotPosition.Y = originalButtonSlot->GetPosition().Y + (newSlot->GetSize().Y + MarginY) * ((i) / ColumnNum);
				newSlot->SetPosition(newSlotPosition);

				UTextBlock* newTextBlock = nullptr;
				newTextBlock = NewObject<UTextBlock>(this, UTextBlock::StaticClass());
				newTextBlock->SetText(FText::FromString(FString::FromInt(i+1)));
				newButton->SetContent(newTextBlock);

				ButtonsLevels.Push(newButton);
			}
		}

		// �������� ������� � �������
		if (ButtonMenu)
		{
			ButtonMenu->OnClicked.AddDynamic(this, &UWidgetLevels::OnButtonMenuClicked);
		}
		for (UButton* pinusBoard : ButtonsLevels)
		{
			pinusBoard->OnClicked.AddDynamic(this, &UWidgetLevels::OnButtonLevelClicked);
		}
	}
///_____________///
///////////////////


///////////////
/// ������� ///
///_________///
/// 
	void UWidgetLevels::AddController(AMainMenuController* mainMenuController)
	{
		if (mainMenuController)
		{
			MainMenuController = mainMenuController;
		}
	}
///_________///
///////////////


//////////////////////
/// ������� ������ ///
///________________///
///
/// ������ ����������� � ������� ����
	void UWidgetLevels::OnButtonMenuClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToMainMenu();
		}
	}
///
/// ������ �������� �� ��������������� �������
	void UWidgetLevels::OnButtonLevelClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());

		for (int32 i = 0; i < ButtonsLevels.Num(); i++)
		{
			if (ButtonsLevels[i]->IsHovered())
			{
				if (handlerLevels)
				{
					handlerLevels->GoToNumLevel(i);
				}
				break;
			}
		}
	}
///________________///
//////////////////////