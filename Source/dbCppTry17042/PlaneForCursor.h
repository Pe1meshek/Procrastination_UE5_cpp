/*
Стенка

Изначально создавалась для определения мировых координат курсора мыши
Создается луч под курсором, который должен сталкиваться со стенкой
координаты места столкновения и будут мировыми координатами курсора

Однако теперь стенок создается 2 (за и перед TileMap),
чтобы частично препятствовать вылету объектов за карту
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlaneForCursor.generated.h"

UCLASS()
class DBCPPTRY17042_API APlaneForCursor : public AActor
{
	GENERATED_BODY()

public:
	// Мэш стенки
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MashComponent;

public:
	APlaneForCursor();

};
