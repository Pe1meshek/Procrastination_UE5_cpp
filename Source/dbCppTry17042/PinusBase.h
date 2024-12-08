/*
Стандартный снаряд

Реализует Базовые настройки всех снарядов

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PinusBase.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class DBCPPTRY17042_API APinusBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Коллизия
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleCollision;

	// Текстурка
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

protected:
	// Количество активаций
	int32 NumOfActivations;

public:	
	APinusBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// Функция активации
	virtual void Activate();

};
