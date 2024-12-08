

#include "MainMenuController.h"
#include "WidgetMainMenu.h"
#include "WidgetLevels.h"
#include "WidgetControl.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	AMainMenuController::AMainMenuController() :
		WidgetMainMenu(nullptr),
		WidgetLevels(nullptr),
		WidgetControl(nullptr)
	{
		// �����
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void AMainMenuController::BeginPlay()
	{
		Super::BeginPlay();
	
		// �������� �������� ����
		if (classWidgetMainMenu)
		{
			WidgetMainMenu = CreateWidget<UWidgetMainMenu>(GetWorld(), classWidgetMainMenu);
			if (WidgetMainMenu)
			{
				// ��������
				WidgetMainMenu->AddToViewport();

				// �������� ������� �� ����������,
				// ����� ������ ����� ���� ��� ��������� ������� ������
				WidgetMainMenu->AddController(this);
			}
		}

		// �������� ���� �������
		if (classWidgetLevels)
		{
			WidgetLevels = CreateWidget<UWidgetLevels>(GetWorld(), classWidgetLevels);
			if (WidgetLevels)
			{
				// �������� � ��������
				WidgetLevels->AddToViewport();
				WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
			
				// �������� ������� �� ����������,
				// ����� ������ ����� ���� ��� ��������� ������� ������
				WidgetLevels->AddController(this);
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
	}
///_______________///
/////////////////////



/////////////////////////////////
/// �������/�������� �������� ///
///___________________________///
///
/// �������� �������� ����
	void AMainMenuController::GoToMainMenu()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Visible);
		WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
		WidgetControl->SetVisibility(ESlateVisibility::Hidden);
	}
///
/// �������� ���� �������
	void AMainMenuController::GoToLevels()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Hidden);
		WidgetLevels->SetVisibility(ESlateVisibility::Visible);
		WidgetControl->SetVisibility(ESlateVisibility::Hidden);
	}
///
/// �������� ����������
	void AMainMenuController::GoToControl()
	{
		WidgetMainMenu->SetVisibility(ESlateVisibility::Hidden);
		WidgetLevels->SetVisibility(ESlateVisibility::Hidden);
		WidgetControl->SetVisibility(ESlateVisibility::Visible);
	}
///___________________________///
/////////////////////////////////

