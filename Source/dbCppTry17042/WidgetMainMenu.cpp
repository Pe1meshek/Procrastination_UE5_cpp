

#include "WidgetMainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetMainMenu::NativeConstruct()
	{
		Super::NativeConstruct();

		// �������� �������	� �������
		if (ButtonStart)
		{
			ButtonStart->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnButtonStartClicked);
		}
		if (ButtonLevels)
		{
			ButtonLevels->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnButtonLevelsClicked);
		}
		if (ButtonControl)
		{
			ButtonControl->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnButtonControlClicked);
		}
		if (ButtonQuit)
		{
			ButtonQuit->OnClicked.AddDynamic(this, &UWidgetMainMenu::OnButtonQuitClicked);
		}
	}
///_____________///
///////////////////


///////////////
/// ������� ///
///_________///
///
	void UWidgetMainMenu::AddController(AMainMenuController* mainMenuController)
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
/// ������� ������ ������ � ������� ������
	void UWidgetMainMenu::OnButtonStartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToNumLevel(0);
		}
	}
///
/// ������� ������ �������� ���� �������
	void UWidgetMainMenu::OnButtonLevelsClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToLevels();
		}
	}
///
/// ������� ������ �������� ���� ����������
	void UWidgetMainMenu::OnButtonControlClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToControl();
		}
	}
///
/// ������� ������ �������� ����������
	void UWidgetMainMenu::OnButtonQuitClicked()
	{
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
///________________///
//////////////////////
