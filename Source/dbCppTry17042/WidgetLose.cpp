

#include "WidgetLose.h"
#include "Components/Button.h"
#include "HandlerLevels.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetLose::NativeConstruct()
	{
		Super::NativeConstruct();

		// Привязка функций к кнопкам
		if (ButtonRestart)
		{
			ButtonRestart->OnClicked.AddDynamic(this, &UWidgetLose::OnButtonRestartClicked);
		}
		if (ButtonExit)
		{
			ButtonExit->OnClicked.AddDynamic(this, &UWidgetLose::OnButtonExitClicked);
		}
	}
///_____________///
///////////////////


//////////////////////
/// Нажатие кнопок ///
///________________///
///
/// Нажатие кнопки перезагрузки
	void UWidgetLose::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}
	}
///
/// Нажатие кнопки перехода в Главное меню
	void UWidgetLose::OnButtonExitClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToMainMenu();
		}
	}
///________________///
//////////////////////
