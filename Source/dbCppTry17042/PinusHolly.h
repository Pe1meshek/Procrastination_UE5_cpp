/*
Снаряд Святой

Активация - выключение графитации
При столкновении с Делом сильно отталкивает его
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusHolly.generated.h"


UCLASS()
class DBCPPTRY17042_API APinusHolly : public APinusBase
{
	GENERATED_BODY()

public:
	// Сила отталкивания Дела
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float PushPower;

public:
	APinusHolly();

	// Активация (переопределение)
	void Activate() override;

protected:
	void BeginPlay() override;

	// Столкновение с Делом
	UFUNCTION()
	void HitDelo(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
