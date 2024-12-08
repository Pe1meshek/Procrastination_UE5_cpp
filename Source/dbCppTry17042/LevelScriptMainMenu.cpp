

#include "LevelScriptMainMenu.h"
#include "WidgetStartSpeache.h"
#include "HandlerLevels.h"


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void ALevelScriptMainMenu::BeginPlay()
	{
		// ����������� ������
		GetWorld()->GetFirstPlayerController()->GetPawn()->Destroy();
	
		// �������������� �����, ����� �� ��������� ������ ���� ��� �������������� � ���������
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());

		// ���������, ����� �� ���������� ��������
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels->bTimeToStartSpeache)
		{
			// ������� ������
			if (classWidgetStart)
			{
				UWidgetStartSpeache* widgetStart = CreateWidget<UWidgetStartSpeache>(GetWorld(), classWidgetStart);
				if (widgetStart)
				{
					widgetStart->AddToViewport();
				}
			}

			// ������ ���� ��������
			handlerLevels->bTimeToStartSpeache = false;
		}
	}
///_______________///
/////////////////////
