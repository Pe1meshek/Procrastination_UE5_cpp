

#include "LevelMenuController.h"
#include "WidgetUI.h"
#include "dbPlayerController.h"
#include "WidgetGamePause.h"
#include "WidgetControl.h"
#include "WidgetLose.h"
#include "WidgetWin.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	ALevelMenuController::ALevelMenuController() :
		WidgetUI(nullptr),
		WidgetGamePause(nullptr),
		WidgetControl(nullptr)
	{
		// пустота
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void ALevelMenuController::BeginPlay()
	{
		Super::BeginPlay();

		// Создание UI
		if (classWidgetUI)
		{
			WidgetUI = CreateWidget<UWidgetUI>(GetWorld(), classWidgetUI);
			if (WidgetUI)
			{
				WidgetUI->AddToViewport();
			}
		}
	
		// Создание Паузы
		if (classWidgetGamePause)
		{
			WidgetGamePause = CreateWidget<UWidgetGamePause>(GetWorld(), classWidgetGamePause);
			if (WidgetGamePause)
			{
				// Добавили и спрятали
				WidgetGamePause->AddToViewport();
				WidgetGamePause->SetVisibility(ESlateVisibility::Hidden);
			
				// Передаем сссылку на контроллер,
				// чтобы виджет через него мог управлять другими окнами
				WidgetGamePause->AddController(this);
			}
		}

		// Создание Управление
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

		// Передаем контроллеру ссылку, чтобы тот мог управлять данным объектом
		AdbPlayerController* pc = Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController());
		if (pc)
		{
			pc->SetLevelMenuController(this);
		}
	}
///_______________///
/////////////////////


////////////////////////////////////////////
/// Открытие/скрытие меню выбора снаряда ///
///______________________________________///
/// 
	void ALevelMenuController::InventoryFlip()
	{
		if (WidgetUI)
		{
			WidgetUI->FlipBoardVisible();
		}
	}
///______________________________________///
////////////////////////////////////////////


///////////////////////////////////
/// Открытие/скрытие меню Паузы ///
///_____________________________///
/// 
	void ALevelMenuController::PauseUnpause()
	{
		// Если игра на Паузе
		if (GetWorld()->IsPaused())
		{
			// Снимаем с паузы
			GetWorld()->GetFirstPlayerController()->SetPause(false);
			// Прячем все окна
			if (WidgetGamePause)
			{
				WidgetGamePause->SetVisibility(ESlateVisibility::Hidden);
			}
			if (WidgetControl)
			{
				WidgetControl->SetVisibility(ESlateVisibility::Hidden);
			}
		}
		else
		{
			// Иначе
			// Ставим на паузу
			GetWorld()->GetFirstPlayerController()->SetPause(true);
			// Открываем меню Паузы
			if (WidgetGamePause)
			{
				WidgetGamePause->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
///_____________________________///
///////////////////////////////////


///////////////////////////
/// Открытие меню Паузы ///
///_____________________///
/// 
	void ALevelMenuController::GoToPauseMenu()
	{
		if (WidgetGamePause)
		{
			WidgetGamePause->SetVisibility(ESlateVisibility::Visible);
		}
		if (WidgetControl)
		{
			WidgetControl->SetVisibility(ESlateVisibility::Hidden);
		}
	}
///_____________________///
///////////////////////////


///////////////////////////
/// Открытие Управления ///
///_____________________///
/// 
	void ALevelMenuController::GoToControl()
	{
		if (WidgetGamePause)
		{
			WidgetGamePause->SetVisibility(ESlateVisibility::Hidden);
		}
		if (WidgetControl)
		{
			WidgetControl->SetVisibility(ESlateVisibility::Visible);
		}
	}
///_____________________///
///////////////////////////


///////////////////////////////
/// Создание окна Поражения ///
///_________________________///
/// 
	void ALevelMenuController::LosedGame()
	{
		// Ставим на паузу
		GetWorld()->GetFirstPlayerController()->SetPause(true);
	
		// Отключаем управление
		GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());

		// Создаем виджет
		if (classWidgetLose)
		{
			CreateWidget<UWidgetLose>(GetWorld(), classWidgetLose)->AddToViewport();
		}
	}
///_________________________///
///////////////////////////////


////////////////////////////
/// Создание окна Победы ///
///______________________///
/// 
	void ALevelMenuController::WonGame()
	{
		// Ставим на паузу
		GetWorld()->GetFirstPlayerController()->SetPause(true);

		// Отключаем управление
		GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());

		// Создаем виджет
		if (classWidgetWin)
		{
			CreateWidget<UWidgetWin>(GetWorld(), classWidgetWin)->AddToViewport();
		}
	}
///______________________///
////////////////////////////
