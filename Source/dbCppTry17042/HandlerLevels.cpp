

#include "HandlerLevels.h"
#include "Kismet/GameplayStatics.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
	void UHandlerLevels::Init()
	{
		// Ну и диииииииичь.. не получается адекватно хранить объекты UWorld
		// приходится хранить в виде имен файлов. АЦТОЙ
	
		// Показываем заставку
		bTimeToStartSpeache = true;
	
		// Имя Уровня Главного меню
		NameLevelMainMenu = TEXT("L_MainMenu");

		// Имена игровых уровней
		NamesLevels.Add(TEXT("L_Level1"));
		NamesLevels.Add(TEXT("L_Level2"));
		NamesLevels.Add(TEXT("L_Level3"));
		NamesLevels.Add(TEXT("L_Level4"));
		NamesLevels.Add(TEXT("L_Level5"));
		NamesLevels.Add(TEXT("L_Level6"));
		NamesLevels.Add(TEXT("L_Level7"));
		NamesLevels.Add(TEXT("L_Level8"));
		NamesLevels.Add(TEXT("L_Level9"));
		NamesLevels.Add(TEXT("L_Level10"));
		NamesLevels.Add(TEXT("L_Level11"));
		NamesLevels.Add(TEXT("L_Level12"));
		NamesLevels.Add(TEXT("L_Level13"));
		NamesLevels.Add(TEXT("L_Level14"));


		// Нерабочие останки Т_Т
		// 
		//if (LevelMainMenu->GetWorld())
		//{
		//	NameLevelMainMenu = LevelMainMenu->GetWorld()->GetFName();
		//}
		// 
		//for (auto level : Levels)
		//{
		//	if (level->GetWorld())
		//	{
		//		UE_LOG(LogTemp, Warning, TEXT("kav"));
		//		NamesLevels.Add(level->GetWorld()->GetFName());
		//	}
		//}
		//UE_LOG(LogTemp, Warning, TEXT("kavkavkav"));
	}
///_____________///
///////////////////


///////////////////////////////
/// Переход на Главное меню ///
///_________________________///
///
	void UHandlerLevels::GoToMainMenu()
	{
		// Тут должна быть проверка
		// не хочу делать проверку по имени,
		// хочу разобраться с массивом миров и проверять ссылку
		UGameplayStatics::OpenLevel(this, NameLevelMainMenu);


		// Нерабочие останки Т_Т
		// 
		//if (LevelMainMenu)
		//{
		//	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelMainMenu);
		//}
	}
///_________________________///
///////////////////////////////


////////////////////////////////////
/// Переход на следующий уровень ///
///______________________________///
///
	void UHandlerLevels::GoToNextLevel()
	{
		// Получаем имя загруженного уровня
		FString thisWorld = UGameplayStatics::GetCurrentLevelName(this);

		// Проходимся по массиву уровней
		// последний не берем в расчет, т.к следующего за ним нет
		for (int32 i = 0; i < NamesLevels.Num() - 1; i++)
		{
			// Если нашелся уровень с такимже именем
			if (NamesLevels[i] == thisWorld)
			{
				// Загружаем уровень следующий за ним
				UGameplayStatics::OpenLevel(this, NamesLevels[i + 1]);
				return;
			}
		}

		// Если сходств не нашлось, то загружаем Главное меню
		UGameplayStatics::OpenLevel(this, NameLevelMainMenu);


		// Нерабочие останки Т_Т
		// 
		//for (int32 i = 0; i < Levels.Num()-1; i++)
		//{
		//	if (Levels[i])
		//	{
		//		if (Levels[i]->GetName() == thisWorld)
		//		{
		//			if (Levels[i+1])
		//			{
		//				UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[i+1]);
		//				return;
		//			}
		//		}
		//	}
		//}
		// 
		//if (LevelMainMenu)
		//{
		//	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelMainMenu);
		//}
	}
///______________________________///
////////////////////////////////////


///////////////////////////
/// Перезагрузка уровня ///
///_____________________///
/// 
	void UHandlerLevels::Restart()
	{
		// Получаем имя текущего уровня и по нему же загружаем новый уровень
		UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
	}
///_____________________///
///////////////////////////


/////////////////////////////////////////////
/// Переход на Игровой уровень по индексу ///
///_______________________________________///
/// 
/// numLevel - номер интересующего уровня в массиве
/// первый уровень соответствует индексу 0
/// 
	void UHandlerLevels::GoToNumLevel(int32 numLevel)
	{
		// Проверяем номер
		if (numLevel < NamesLevels.Num())
		{
			UGameplayStatics::OpenLevel(this, NamesLevels[numLevel]);
		}


		// Нерабочие останки Т_Т
		// 
		//if (numLevel < Levels.Num())
		//{
		//	if (Levels[numLevel])
		//	{
		//		UGameplayStatics::OpenLevelBySoftObjectPtr(this, Levels[numLevel]);
		//	}
		//}
	}
///_______________________________________///
/////////////////////////////////////////////


