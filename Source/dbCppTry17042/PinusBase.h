/*
����������� ������

��������� ������� ��������� ���� ��������

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
	// ��������
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleCollision;

	// ���������
	UPROPERTY(VisibleAnywhere)
	UPaperSpriteComponent* SpriteComponent;

protected:
	// ���������� ���������
	int32 NumOfActivations;

public:	
	APinusBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// ������� ���������
	virtual void Activate();

};
