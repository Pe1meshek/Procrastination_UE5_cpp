

#include "WidgetMainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetMainMenu::NativeConstruct()
	{
		Super::NativeConstruct();

		// Привязка функций	к кнопкам
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
/// Сеттеры ///
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
/// Нажатие кнопок ///
///________________///
///
/// Нажатие кнопки начала с первого уровня
	void UWidgetMainMenu::OnButtonStartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToNumLevel(0);
		}
	}
///
/// Нажатие кнопки открытия меню Уровней
	void UWidgetMainMenu::OnButtonLevelsClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToLevels();
		}
	}
///
/// Нажатие кнопки открытия окна Управления
	void UWidgetMainMenu::OnButtonControlClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToControl();
		}
	}
///
/// Нажатие кнопки закрытия приложения
	void UWidgetMainMenu::OnButtonQuitClicked()
	{
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
///________________///
//////////////////////
