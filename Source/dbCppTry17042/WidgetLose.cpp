

#include "WidgetLose.h"
#include "Components/Button.h"
#include "HandlerLevels.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetLose::NativeConstruct()
	{
		Super::NativeConstruct();

		// �������� ������� � �������
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
/// ������� ������ ///
///________________///
///
/// ������� ������ ������������
	void UWidgetLose::OnButtonRestartClicked()
	{
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels)
		{
			handlerLevels->Restart();
		}
	}
///
/// ������� ������ �������� � ������� ����
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
