/*
������

���������� ����������� ��� ����������� ������� ��������� ������� ����
��������� ��� ��� ��������, ������� ������ ������������ �� �������
���������� ����� ������������ � ����� �������� ������������ �������

������ ������ ������ ��������� 2 (�� � ����� TileMap),
����� �������� �������������� ������ �������� �� �����
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
	// ��� ������
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MashComponent;

public:
	APlaneForCursor();

};
