/*
Снаряд Шипастый

Активация - создает базовые снаряды вокруг себя, разлитающиеся в разные стороны
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
	// Класс создаваемых снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<APinusBase> ClassSpikes;

	// Количество создаваемых снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	int32 NumSpikes;

	// Сила разлета снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double SpikePower;
	
	// Радиус создания снарядов
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double SpikeSpawnRadius;

public:
	APinusSpike();

	// Активация (переопределение)
	void Activate() override;
};
