
#include "WidgetGamePause.h"
#include "Components/Button.h"
#include "LevelMenuController.h"
#include "HandlerLevels.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetGamePause::NativeConstruct()
	{
		Super::NativeConstruct();

		// �������� ������ � ��������
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
/// ������� ///
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
/// ������� ������ ///
///________________///
///
/// ������� ������ ������������ � ����
	void UWidgetGamePause::OnButtonContinueClicked()
	{
		GetWorld()->GetFirstPlayerController()->SetPause(false);
		SetVisibility(ESlateVisibility::Hidden);
	}
///
/// ������� ������ �����������
	void UWidgetGamePause::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}
	}
///
/// ������� ������ ����������
	void UWidgetGamePause::OnButtonControlClicked()
	{
		if (LevelMenuController)
		{
			LevelMenuController->GoToControl();
		}
	}
///
/// ������� ������ �������� � ������� ����
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

