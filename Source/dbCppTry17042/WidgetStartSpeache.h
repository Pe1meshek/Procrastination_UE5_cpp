/*
Widget заставки

Запускает появление виджетов (текста и кнопки) с небольшим временным интервалом
И умеет закрываться на кнопку

Создается классом LevelScriptMainMenu
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetStartSpeache.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class DBCPPTRY17042_API UWidgetStartSpeache : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Блоки Текста //
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text0;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text2;
	//______________//

	// Кнопка скрытия виджета
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonContinue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float delay = 0.7f;

	virtual void NativeConstruct() override;

	// Кнопка скрытия виджета
	UFUNCTION(BlueprintCallable)
	void OnButtonLevelClicked();

protected:
	// Делает виджет видимым
	// нужна для удобства
	UFUNCTION(BlueprintCallable)
	void SetVisible(UWidget* widget);
};
