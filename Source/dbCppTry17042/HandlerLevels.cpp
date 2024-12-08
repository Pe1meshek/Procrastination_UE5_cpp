

#include "HandlerLevels.h"
#include "Kismet/GameplayStatics.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	void UHandlerLevels::Init()
	{
		// �� � �����������.. �� ���������� ��������� ������� ������� UWorld
		// ���������� ������� � ���� ���� ������. �����
	
		// ���������� ��������
		bTimeToStartSpeache = true;
	
		// ��� ������ �������� ����
		NameLevelMainMenu = TEXT("L_MainMenu");

		// ����� ������� �������
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


		// ��������� ������� �_�
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
/// ������� �� ������� ���� ///
///_________________________///
///
	void UHandlerLevels::GoToMainMenu()
	{
		// ��� ������ ���� ��������
		// �� ���� ������ �������� �� �����,
		// ���� ����������� � �������� ����� � ��������� ������
		UGameplayStatics::OpenLevel(this, NameLevelMainMenu);


		// ��������� ������� �_�
		// 
		//if (LevelMainMenu)
		//{
		//	UGameplayStatics::OpenLevelBySoftObjectPtr(this, LevelMainMenu);
		//}
	}
///_________________________///
///////////////////////////////


////////////////////////////////////
/// ������� �� ��������� ������� ///
///______________________________///
///
	void UHandlerLevels::GoToNextLevel()
	{
		// �������� ��� ������������ ������
		FString thisWorld = UGameplayStatics::GetCurrentLevelName(this);

		// ���������� �� ������� �������
		// ��������� �� ����� � ������, �.� ���������� �� ��� ���
		for (int32 i = 0; i < NamesLevels.Num() - 1; i++)
		{
			// ���� ������� ������� � ������� ������
			if (NamesLevels[i] == thisWorld)
			{
				// ��������� ������� ��������� �� ���
				UGameplayStatics::OpenLevel(this, NamesLevels[i + 1]);
				return;
			}
		}

		// ���� ������� �� �������, �� ��������� ������� ����
		UGameplayStatics::OpenLevel(this, NameLevelMainMenu);


		// ��������� ������� �_�
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
/// ������������ ������ ///
///_____________________///
/// 
	void UHandlerLevels::Restart()
	{
		// �������� ��� �������� ������ � �� ���� �� ��������� ����� �������
		UGameplayStatics::OpenLevel(this, FName(UGameplayStatics::GetCurrentLevelName(this)));
	}
///_____________________///
///////////////////////////


/////////////////////////////////////////////
/// ������� �� ������� ������� �� ������� ///
///_______________________________________///
/// 
/// numLevel - ����� ������������� ������ � �������
/// ������ ������� ������������� ������� 0
/// 
	void UHandlerLevels::GoToNumLevel(int32 numLevel)
	{
		// ��������� �����
		if (numLevel < NamesLevels.Num())
		{
			UGameplayStatics::OpenLevel(this, NamesLevels[numLevel]);
		}


		// ��������� ������� �_�
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


