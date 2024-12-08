/*
Widget UI

��������� ���� ������ �������
����� ������-������, �� ������� ������������ ��������� ������-������ ���� ������
*/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetUI.generated.h"

class UButton;
class UImage;

UCLASS()
class DBCPPTRY17042_API UWidgetUI : public UUserWidget
{
	GENERATED_BODY()

public:
	// ������-������
	// ���������� ��������� ������
	// �� ������� �����������/������������� ����
	UPROPERTY(meta = (BindWidget))
	UButton* ButtonSelected;

	// ��������-������
	// ������������ ��� ��� ��� ��� �����
	UPROPERTY(meta = (BindWidget))
	UImage* ImageCase;

	// ������ ������� ��������� 
	// ��� ������� �������� ��������� ������ ��������� (������)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<UTexture2D*> ItemImages;

	// ����������� ����� � ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 InventoryColumnNum = 3;


protected:
	// ������ ����� (������)
	TArray<UButton*> ButtonsPinusBoard;
	
	// ������ ����� ��� ������
	TArray<UImage*> ImagesBoard;

	// ���������� ���������
	// true - ���� ���������
	bool bIsBoardVisible = false;

protected:
	virtual void NativeConstruct() override;

public:
	// ��������/���������� ���������
	UFUNCTION()
	void SetBoardVisible(bool boardVisible);

	// ����������� ��������� ���������
	UFUNCTION()
	void FlipBoardVisible();
	
	// ������� �� ������ ���������
	UFUNCTION()
	void OnItemPinusClicked();

};
