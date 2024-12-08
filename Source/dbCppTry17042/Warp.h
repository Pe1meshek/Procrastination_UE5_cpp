/*
����

�������� � ���������
��� ����������� � �������� ���� �������� ����� ������
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
	// ��������
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	// ���������
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* PaperFlipbookComponent;


public:	
	AWarp();

protected:
	virtual void BeginPlay() override;

protected:
	// ����������� � ���������
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
