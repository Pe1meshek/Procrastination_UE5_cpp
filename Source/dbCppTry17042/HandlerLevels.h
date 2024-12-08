/*
GameInstance
���������� �� ���������� ���� ������ ����������
������ � ���� ������ � �������� �� �� ������������

�� ������� ��������� ������ ���, ����� ������ ��������� � ���� �������,
������ �������� �� �� ������� ������ �� ������ ������.
����� ��������� ���� �� ������� :(
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HandlerLevels.generated.h"


UCLASS()
class DBCPPTRY17042_API UHandlerLevels : public UGameInstance
{
	GENERATED_BODY()

public:

	/////////////////////////////	
	// ������� � ������������� //	
	//_________________________//
	// 
	// ����� �������� � ����������� � ���������� ������
	// 	
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | MainMenu")
	//UWorld* LevelMainMenu;
	//TSoftObjectPtr<UWorld> LevelMainMenu;
	//TWeakObjectPtr<UWorld> LevelMainMenu;
	//
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup | Levels")
	//TArray<UWorld*> Levels;
	//TArray<TSoftObjectPtr<UWorld>> Levels;
	//TArray<TWeakObjectPtr<UWorld>> Levels;
	//_________________________//
	/////////////////////////////	

	// ��� ������ �������� ����
	FName NameLevelMainMenu;
	
	// ������ ���� ������� �������
	TArray<FName> NamesLevels;

	// ����
	// ���� True - ������� ���� ���������� "��������"
	bool bTimeToStartSpeache;



public:
	// ������� �����������, ����������
	void Init() override;

	// ������� �� ������� ����
	void GoToMainMenu();

	// ������� �� ��������� �������
	void GoToNextLevel();

	// ������������ ������
	void Restart();

	// ������� �� ������� ������� �� �������
	void GoToNumLevel(int32 numLevel);
};
