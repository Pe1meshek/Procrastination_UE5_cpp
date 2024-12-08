

#include "LevelMenuController.h"
#include "WidgetUI.h"
#include "dbPlayerController.h"
#include "WidgetGamePause.h"
#include "WidgetControl.h"
#include "WidgetLose.h"
#include "WidgetWin.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	ALevelMenuController::ALevelMenuController() :
		WidgetUI(nullptr),
		WidgetGamePause(nullptr),
		WidgetControl(nullptr)
	{
		// �������
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void ALevelMenuController::BeginPlay()
	{
		Super::BeginPlay();

		// �������� UI
		if (classWidgetUI)
		{
			WidgetUI = CreateWidget<UWidgetUI>(GetWorld(), classWidgetUI);
			if (WidgetUI)
			{
				WidgetUI->AddToViewport();
			}
		}
	
		// �������� �����
		if (classWidgetGamePause)
		{
			WidgetGamePause = CreateWidget<UWidgetGamePause>(GetWorld(), classWidgetGamePause);
			if (WidgetGamePause)
			{
				// �������� � ��������
				WidgetGamePause->AddToViewport();
				WidgetGamePause->SetVisibility(ESlateVisibility::Hidden);
			
				// �������� ������� �� ����������,
				// ����� ������ ����� ���� ��� ��������� ������� ������
				WidgetGamePause->AddController(this);
			}
		}

		// �������� ����������
		if (classWidgetControl)
		{
			WidgetControl = CreateWidget<UWidgetControl>(GetWorld(), classWidgetControl);
			if (WidgetControl)
			{
				// �������� � ��������
				WidgetControl->AddToViewport();
				WidgetControl->SetVisibility(ESlateVisibility::Hidden);

				// �������� ������� �� ����������,
				// ����� ������ ����� ���� ��� ��������� ������� ������
				WidgetControl->AddController(this);
			}
		}

		// �������� ����������� ������, ����� ��� ��� ��������� ������ ��������
		AdbPlayerController* pc = Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController());
		if (pc)
		{
			pc->SetLevelMenuController(this);
		}
	}
///_______________///
/////////////////////


////////////////////////////////////////////
/// ��������/������� ���� ������ ������� ///
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
/// ��������/������� ���� ����� ///
///_____________________________///
/// 
	void ALevelMenuController::PauseUnpause()
	{
		// ���� ���� �� �����
		if (GetWorld()->IsPaused())
		{
			// ������� � �����
			GetWorld()->GetFirstPlayerController()->SetPause(false);
			// ������ ��� ����
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
			// �����
			// ������ �� �����
			GetWorld()->GetFirstPlayerController()->SetPause(true);
			// ��������� ���� �����
			if (WidgetGamePause)
			{
				WidgetGamePause->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
///_____________________________///
///////////////////////////////////


///////////////////////////
/// �������� ���� ����� ///
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
/// �������� ���������� ///
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
/// �������� ���� ��������� ///
///_________________________///
/// 
	void ALevelMenuController::LosedGame()
	{
		// ������ �� �����
		GetWorld()->GetFirstPlayerController()->SetPause(true);
	
		// ��������� ����������
		GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());

		// ������� ������
		if (classWidgetLose)
		{
			CreateWidget<UWidgetLose>(GetWorld(), classWidgetLose)->AddToViewport();
		}
	}
///_________________________///
///////////////////////////////


////////////////////////////
/// �������� ���� ������ ///
///______________________///
/// 
	void ALevelMenuController::WonGame()
	{
		// ������ �� �����
		GetWorld()->GetFirstPlayerController()->SetPause(true);

		// ��������� ����������
		GetWorld()->GetFirstPlayerController()->DisableInput(GetWorld()->GetFirstPlayerController());

		// ������� ������
		if (classWidgetWin)
		{
			CreateWidget<UWidgetWin>(GetWorld(), classWidgetWin)->AddToViewport();
		}
	}
///______________________///
////////////////////////////
