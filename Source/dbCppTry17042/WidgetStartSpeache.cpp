


#include "WidgetStartSpeache.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UWidgetStartSpeache::NativeConstruct()
	{
		Super::NativeConstruct();

		ButtonContinue->IsFocusable = false;

		// Привязываем функцию к кнопке
		if (ButtonContinue)
		{
			ButtonContinue->OnClicked.AddDynamic(this, &UWidgetStartSpeache::OnButtonLevelClicked);
		}

		// Помещаем все блоки текста и Кнопку в массив
		// для удобства т.к с ними происходят одни и те же действия
		TArray<UWidget*> widgets;
		widgets.Add(Text0);
		widgets.Add(Text1);
		widgets.Add(Text2);
		widgets.Add(ButtonContinue);

		FTimerDelegate* TimerDel;
		FTimerHandle* TimerHandle;

		// Проходимся по массиву
		for (int32 i = 0; i < widgets.Num(); i++)
		{
			// Прячем каждый виджет
			widgets[i]->SetVisibility(ESlateVisibility::Hidden);
			TimerDel = new FTimerDelegate();
			TimerHandle = new FTimerHandle();

			// Запускаем функцию появления спустя одинаковый интервал времени
			TimerDel->BindUFunction(this, FName("SetVisible"), widgets[i]);
			GetWorld()->GetTimerManager().SetTimer(*TimerHandle, *TimerDel, delay*(i+1), false);
		}
	}
///_____________///
///////////////////


//////////////////////
/// Нажатие кнопок ///
///________________///
///
	void UWidgetStartSpeache::OnButtonLevelClicked()
	{
		this->RemoveFromViewport();
	}
///________________///
//////////////////////


// Функция появления
void UWidgetStartSpeache::SetVisible(UWidget* widget)
{
	widget->SetVisibility(ESlateVisibility::Visible);
}
