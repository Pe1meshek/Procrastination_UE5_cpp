

#include "WidgetWin.h"
#include "Components/Button.h"
#include "HandlerLevels.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetWin::NativeConstruct()
	{
		Super::NativeConstruct();

		// �������� ������� � �������
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
/// ������� ������ ///
///________________///
///
/// ������� ������ �������� �� ��������� �������
	void UWidgetWin::OnButtonNextClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->GoToNextLevel();
		}
	}
///
/// ������� ������ ����������� ������
	void UWidgetWin::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}

	}
///
/// ������� ������ �������� � ������� ����
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
