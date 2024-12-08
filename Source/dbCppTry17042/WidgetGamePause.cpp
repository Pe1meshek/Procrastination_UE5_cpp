
#include "WidgetGamePause.h"
#include "Components/Button.h"
#include "LevelMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetGamePause::NativeConstruct()
	{
		Super::NativeConstruct();

		// Привязка кнопок к функциям
		if (ButtonContinue)
		{
			ButtonContinue->OnClicked.AddDynamic(this, &UWidgetGamePause::OnButtonContinueClicked);
		}
		if (ButtonRestart)
		{
			ButtonRestart->OnClicked.AddDynamic(this, &UWidgetGamePause::OnButtonRestartClicked);
		}
		if (ButtonControl)
		{
			ButtonControl->OnClicked.AddDynamic(this, &UWidgetGamePause::OnButtonControlClicked);
		}
		if (ButtonExit)
		{
			ButtonExit->OnClicked.AddDynamic(this, &UWidgetGamePause::OnButtonExitClicked);
		}
	}
///_____________///
///////////////////


///////////////
/// Сеттеры ///
///_________///
/// 
	void UWidgetGamePause::AddController(ALevelMenuController* levelMenuController)
	{
		if (levelMenuController)
		{
			LevelMenuController = levelMenuController;
		}
	}
///_________///
///////////////


//////////////////////
/// Нажатие кнопок ///
///________________///
///
/// Нажатие кнопки возвращщения в игру
	void UWidgetGamePause::OnButtonContinueClicked()
	{
		GetWorld()->GetFirstPlayerController()->SetPause(false);
		SetVisibility(ESlateVisibility::Hidden);
	}
///
/// Нажатие кнопкм Перезапуска
	void UWidgetGamePause::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}
	}
///
/// Нажатие кнопки Управления
	void UWidgetGamePause::OnButtonControlClicked()
	{
		if (LevelMenuController)
		{
			LevelMenuController->GoToControl();
		}
	}
///
/// Нажатие кнопки перехода в Главное меню
	void UWidgetGamePause::OnButtonExitClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToMainMenu();
		}
	}
///________________///
//////////////////////

