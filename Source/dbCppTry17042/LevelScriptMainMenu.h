/*
������ ������ �������� ����

������� ������ �� ���������
���������� ��������
*/
#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelScriptMainMenu.generated.h"

class UWidgetStartSpeache;

UCLASS()
class DBCPPTRY17042_API ALevelScriptMainMenu : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	// ����� ������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartWidget")
	TSubclassOf<UWidgetStartSpeache> classWidgetStart;

protected:
	virtual void BeginPlay() override;
};
