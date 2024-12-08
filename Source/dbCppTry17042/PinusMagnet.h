/*
Снаряд Магнитный

Активация - ненадолго создает небольшое магнитное поле.
если Дело попадает в поле, то оно притягивается к его источнику (снаряду)
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusMagnet.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class DBCPPTRY17042_API APinusMagnet : public APinusBase
{
	GENERATED_BODY()

public:
	// Коллизия поля
	UPROPERTY(VisibleAnywhere)
	USphereComponent* MagnetPoleCollision;

	// Анимация поля
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* MagnetPolePaperFlipbook;

	// Скорость сжатия поля
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpeedCompression;

	// Сила притяжения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double PowerAttraction;

protected:
	// Таймер на время существования поля
	FTimerHandle TimerHandleMagnetPoleCompression;
	

public:
	APinusMagnet();

	// Активация (переопределение)
	void Activate() override;

protected:
	// Сжатие поля
	// вызывается каждый тип все время существования поля
	void MagnetPoleCompression();
};
