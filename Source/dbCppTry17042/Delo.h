/*
Дело

Объект без гравитации, который нужно запинать снарядами в Варп
Делать ничего не умеет, кроме как пролетать мимо Варпа :)
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Delo.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;

UCLASS()
class DBCPPTRY17042_API ADelo : public AActor
{
	GENERATED_BODY()

public:
	// Коллизия
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	// Текстурка
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

public:	
	ADelo();

protected:
	virtual void BeginPlay() override;
};
