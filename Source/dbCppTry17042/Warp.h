/*
Варп

Анимация с коллизией
При пересечении с объектом Дело вызывает экран победы
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Warp.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class DBCPPTRY17042_API AWarp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Коллизия
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	// Текстурка
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* PaperFlipbookComponent;


public:	
	AWarp();

protected:
	virtual void BeginPlay() override;

protected:
	// Пересечение с объектами
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
