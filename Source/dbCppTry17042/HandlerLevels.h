/*
GameInstance
Существует на протяжении всей работы приложения
Хранит в себе уровни и отвечает за их переключение

Не удалось настроить объект так, чтобы уровни хранились в виде массива,
движок ругается на на наличие ссылок на другие уровни.
Умные указатели тоже не помогли :(
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
	// Останки с эксперементов //	
	//_________________________//
	// 
	// Пусть остаются в напоминание о нерешенной задаче
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

	// Имя Уровня Главного меню
	FName NameLevelMainMenu;
	
	// Массив имен Игровых уровней
	TArray<FName> NamesLevels;

	// Флаг
	// если True - Главное меню показывает "заставку"
	bool bTimeToStartSpeache;



public:
	// Местный конструктор, получается
	void Init() override;

	// Переход на Главное меню
	void GoToMainMenu();

	// Переход на следующий уровень
	void GoToNextLevel();

	// Перезагрузка уровня
	void Restart();

	// Переход на Игровой уровень по индексу
	void GoToNumLevel(int32 numLevel);
};
