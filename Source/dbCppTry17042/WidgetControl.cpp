

#include "WidgetControl.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuController.h"
#include "LevelMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetControl::NativeConstruct()
	{
		Super::NativeConstruct();

		// �������� ������� � �������
		if (ButtonMenu)
		{
			ButtonMenu->OnClicked.AddDynamic(this, &UWidgetControl::OnButtonMenuClicked);
		}
		if (ButtonBack)
		{
			ButtonBack->OnClicked.AddDynamic(this, &UWidgetControl::OnButtonBackClicked);
		}

		// ����������� ������ ������, � ����������� �� ������������ ������
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			if (UGameplayStatics::GetCurrentLevelName(this) == handlerLevels->NameLevelMainMenu)
			{
				ButtonBack->SetVisibility(ESlateVisibility::Hidden);
			}
			else
			{
				ButtonMenu->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
///_____________///
///////////////////


///////////////
/// ������� ///
///_________///
/// 
	void UWidgetControl::AddController(AMainMenuController* mainMenuController)
	{
		if (mainMenuController)
		{
			MainMenuController = mainMenuController;
		}
	}
///
	void UWidgetControl::AddController(ALevelMenuController* levelMenuController)
	{
		if (levelMenuController)
		{
			LevelMenuController = levelMenuController;
		}
	}
///_________///
///////////////


//////////////////////
/// ������� ������ ///
///________________///
///
/// ������ ����������� � ������� ����
	void UWidgetControl::OnButtonMenuClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToMainMenu();
		}
	}
///
/// ������ ����������� � ���� �����
	void UWidgetControl::OnButtonBackClicked()
	{
		if (LevelMenuController)
		{
			LevelMenuController->GoToPauseMenu();
		}
	}
///________________///
//////////////////////