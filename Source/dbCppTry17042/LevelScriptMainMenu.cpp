

#include "LevelScriptMainMenu.h"
#include "WidgetStartSpeache.h"
#include "HandlerLevels.h"


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void ALevelScriptMainMenu::BeginPlay()
	{
		// Уничтожение игрока
		GetWorld()->GetFirstPlayerController()->GetPawn()->Destroy();
	
		// Устанавливакем Фокус, чтобы не совершать лишний клик для взаимодействия с виджетами
		GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeGameAndUI());

		// Проверяем, нужно ли показывать Заставку
		UHandlerLevels* handlerLevels = Cast<UHandlerLevels>(GetWorld()->GetGameInstance());
		if (handlerLevels->bTimeToStartSpeache)
		{
			// Создаем виджет
			if (classWidgetStart)
			{
				UWidgetStartSpeache* widgetStart = CreateWidget<UWidgetStartSpeache>(GetWorld(), classWidgetStart);
				if (widgetStart)
				{
					widgetStart->AddToViewport();
				}
			}

			// Меняем флаг заставки
			handlerLevels->bTimeToStartSpeache = false;
		}
	}
///_______________///
/////////////////////
