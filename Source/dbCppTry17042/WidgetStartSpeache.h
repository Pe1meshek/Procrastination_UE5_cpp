/*
Widget ��������

��������� ��������� �������� (������ � ������) � ��������� ��������� ����������
� ����� ����������� �� ������

��������� ������� LevelScriptMainMenu
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
	// ����� ������ //
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text0;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text1;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text2;
	//______________//

	// ������ ������� �������
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonContinue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float delay = 0.7f;

	virtual void NativeConstruct() override;

	// ������ ������� �������
	UFUNCTION(BlueprintCallable)
	void OnButtonLevelClicked();

protected:
	// ������ ������ �������
	// ����� ��� ��������
	UFUNCTION(BlueprintCallable)
	void SetVisible(UWidget* widget);
};
