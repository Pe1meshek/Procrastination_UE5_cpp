

#include "MainMenuController.h"
#include "WidgetMainMenu.h"
#include "WidgetLevels.h"
#include "WidgetControl.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	AMainMenuController::AMainMenuController() :
		WidgetMainMenu(nullptr),
		WidgetLevels(nullptr),
		WidgetControl(nullptr)
	{
		// Пусто
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void AMainMenuController::BeginPlay()
	{
		Super::BeginPlay();
	
		// Создание Главного меню
		if (classWidgetMainMenu)
		{
			WidgetMainMenu = CreateWidget<UWidgetMainMenu>(GetWorld(), classWidgetMainMenu);
			if (WidgetMainMenu)
			{
				// Добавили
				WidgetMainMenu->AddToViewport();

				// Передаем сссылку на контроллер,
				// чтобы виджет через него мог управлять другими окнами
				WidgetMainMenu->AddController(this);
			}
		}

		// Создание меню Уровней
		if (classWidgetLevels)
		{
			WidgetLevels = CreateWidget<UWidgetLevels>(GetWorld(), classWidgetLevels);
			if (WidgetLevels)
			{
				// Добавили и спрятали
				WidgetLevels->AddToViewport();
				WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
			
				// Передаем сссылку на контроллер,
				// чтобы виджет через него мог управлять другими окнами
				WidgetLevels->AddController(this);
			}
		}
	
		// Создание Управления
		if (classWidgetControl)
		{
			WidgetControl = CreateWidget<UWidgetControl>(GetWorld(), classWidgetControl);
			if (WidgetControl)
			{
				// Добавили и спрятали
				WidgetControl->AddToViewport();
				WidgetControl->SetVisibility(ESlateVisibility::Hidden);

				// Передаем сссылку на контроллер,
				// чтобы виджет через него мог управлять другими окнами
				WidgetControl->AddController(this);
			}
		}
	}
///_______________///
/////////////////////



/////////////////////////////////
/// Открыть/закрытие Виджетов ///
///___________________________///
///
/// Открытие Главного меню
	void AMainMenuController::GoToMainMenu()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Visible);
		WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
		WidgetControl->SetVisibility(ESlateVisibility::Hidden);
	}
///
/// Открытие меню Уровней
	void AMainMenuController::GoToLevels()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Hidden);
		WidgetLevels->SetVisibility(ESlateVisibility::Visible);
		WidgetControl->SetVisibility(ESlateVisibility::Hidden);
	}
///
/// Открытие Управления
	void AMainMenuController::GoToControl()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Hidden);
		WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
		WidgetControl->SetVisibility(ESlateVisibility::Visible);
	}
///___________________________///
/////////////////////////////////

