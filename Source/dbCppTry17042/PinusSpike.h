/*
������ ��������

��������� - ������� ������� ������� ������ ����, ������������� � ������ �������
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusSpike.generated.h"


UCLASS()
class DBCPPTRY17042_API APinusSpike : public APinusBase
{
	GENERATED_BODY()

public:
	// ����� ����������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<APinusBase> ClassSpikes;

	// ���������� ����������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 NumSpikes;

	// ���� ������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double SpikePower;
	
	// ������ �������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double SpikeSpawnRadius;

public:
	APinusSpike();

	// ��������� (���������������)
	void Activate() override;
};
