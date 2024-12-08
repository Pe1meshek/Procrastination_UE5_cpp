

#include "WidgetWin.h"
#include "Components/Button.h"
#include "HandlerLevels.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetWin::NativeConstruct()
	{
		Super::NativeConstruct();

		// Привязка функций к кнопкам
		if (ButtonNext)
		{
			ButtonNext->OnClicked.AddDynamic(this, &UWidgetWin::OnButtonNextClicked);
		}
		if (ButtonRestart)
		{
			ButtonRestart->OnClicked.AddDynamic(this, &UWidgetWin::OnButtonRestartClicked);
		}
		if (ButtonExit)
		{
			ButtonExit->OnClicked.AddDynamic(this, &UWidgetWin::OnButtonExitClicked);
		}
	}
///_____________///
///////////////////


//////////////////////
/// Нажатие кнопок ///
///________________///
///
/// Нажатие кнопки перехода на следующий уровень
	void UWidgetWin::OnButtonNextClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToNextLevel();
		}
	}
///
/// Нажатие кнопки перезапуска уровня
	void UWidgetWin::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}

	}
///
/// Нажатие кнопки перехода в главное меню
	void UWidgetWin::OnButtonExitClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToMainMenu();
		}
	}
///________________///
//////////////////////
