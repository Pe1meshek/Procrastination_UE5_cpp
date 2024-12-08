

#include "WidgetControl.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuController.h"
#include "LevelMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetControl::NativeConstruct()
	{
		Super::NativeConstruct();

		// Привязка функций к кнопкам
		if (ButtonMenu)
		{
			ButtonMenu->OnClicked.AddDynamic(this, &UWidgetControl::OnButtonMenuClicked);
		}
		if (ButtonBack)
		{
			ButtonBack->OnClicked.AddDynamic(this, &UWidgetControl::OnButtonBackClicked);
		}

		// Отображение разных кнопок, в зависимости от загруженного уровня
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
/// Сеттеры ///
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
/// Нажатие кнопок ///
///________________///
///
/// Кнопка возвращения в Главное меню
	void UWidgetControl::OnButtonMenuClicked()
	{
		if (MainMenuController)
		{
			MainMenuController->GoToMainMenu();
		}
	}
///
/// Кнопка возвращения в Меню Паузы
	void UWidgetControl::OnButtonBackClicked()
	{
		if (LevelMenuController)
		{
			LevelMenuController->GoToPauseMenu();
		}
	}
///________________///
//////////////////////