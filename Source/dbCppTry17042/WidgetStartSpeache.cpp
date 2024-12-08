


#include "WidgetStartSpeache.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UWidgetStartSpeache::NativeConstruct()
	{
		Super::NativeConstruct();

		ButtonContinue->IsFocusable = false;

		// ����������� ������� � ������
		if (ButtonContinue)
		{
			ButtonContinue->OnClicked.AddDynamic(this, &UWidgetStartSpeache::OnButtonLevelClicked);
		}

		// �������� ��� ����� ������ � ������ � ������
		// ��� �������� �.� � ���� ���������� ���� � �� �� ��������
		TArray<UWidget*> widgets;
		widgets.Add(Text0);
		widgets.Add(Text1);
		widgets.Add(Text2);
		widgets.Add(ButtonContinue);

		FTimerDelegate* TimerDel;
		FTimerHandle* TimerHandle;

		// ���������� �� �������
		for (int32 i = 0; i < widgets.Num(); i++)
		{
			// ������ ������ ������
			widgets[i]->SetVisibility(ESlateVisibility::Hidden);
			TimerDel = new FTimerDelegate();
			TimerHandle = new FTimerHandle();

			// ��������� ������� ��������� ������ ���������� �������� �������
			TimerDel->BindUFunction(this, FName("SetVisible"), widgets[i]);
			GetWorld()->GetTimerManager().SetTimer(*TimerHandle, *TimerDel, delay*(i+1), false);
		}
	}
///_____________///
///////////////////


//////////////////////
/// ������� ������ ///
///________________///
///
	void UWidgetStartSpeache::OnButtonLevelClicked()
	{
		this->RemoveFromViewport();
	}
///________________///
//////////////////////


// ������� ���������
void UWidgetStartSpeache::SetVisible(UWidget* widget)
{
	widget->SetVisibility(ESlateVisibility::Visible);
}
