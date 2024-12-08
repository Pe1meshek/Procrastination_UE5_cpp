/*
����

������ ��� ����������, ������� ����� �������� ��������� � ����
������ ������ �� �����, ����� ��� ��������� ���� ����� :)
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
	// ��������
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollision;

	// ���������
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

public:	
	ADelo();

protected:
	virtual void BeginPlay() override;
};
