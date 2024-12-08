/*
���������� �������� �������� ����

������ ��������� ���� �������� � ��������� ���
*/


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuController.generated.h"

class UWidgetMainMenu;
class UWidgetLevels;
class UWidgetControl;

UCLASS()
class DBCPPTRY17042_API AMainMenuController : public AActor
{
	GENERATED_BODY()

public:
	// ������ ����������� �������� //
	//
	// ������� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetMainMenu> classWidgetMainMenu;
	//
	// ���� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetLevels> classWidgetLevels;
	//
	// ����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetClasses")
	TSubclassOf<UWidgetControl> classWidgetControl;
	//_____________________________//

protected:
	// ���������� ��������� ��������, ��� ���������� ������ � ����
	UWidgetMainMenu* WidgetMainMenu;
	UWidgetLevels* WidgetLevels;
	UWidgetControl* WidgetControl;

public:	
	AMainMenuController();

protected:
	virtual void BeginPlay() override;

public:	
	// ������ ���, ������� ������� ����
	UFUNCTION(BlueprintCallable)
	void GoToMainMenu();

	// ������ ���, ������� ���� �������	
	UFUNCTION(BlueprintCallable)
	void GoToLevels();

	// ������ ���, ������� ����������	
	UFUNCTION(BlueprintCallable)
	void GoToControl();

};
