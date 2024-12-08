/*
Космический фон

При создании поварачивается в случайном направленнии, выбирает случайный фон
И начинает вращаться
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "SpaceSphere.generated.h"

UCLASS()
class DBCPPTRY17042_API ASpaceSphere : public AActor
{
	GENERATED_BODY()
	
protected:
	// Мэш (желательно сфера)
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereComponent;

	// Компонент реализующий вращение
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovementComponent;

	// Массив Фонов на выбор 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<UMaterialInstance*> SpaceSkins;

	// Максимальная скорость вращения
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MaxRotationSpeed;


public:	
	ASpaceSphere();

protected:
	virtual void BeginPlay() override;

};
