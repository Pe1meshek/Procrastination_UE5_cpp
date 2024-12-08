/*
�������

�����, ������� ���������� ���������, ��������� ��� �������, ������� ������� �� � �������.
���� ���� ������� ������� ����� - ���� ����� ���������.

����� ����� ������ ���� �����������, ���� ���� ��������� ������
������ ��������� �������� - ��� �����, ������� �������������� ������������ � ������ ���������������, ������������ ������� ���� (������� �����)
�� ������ � ������ (������� ���� �������� ������ ���� ������ �����), ��� ����� ��������� �����.
�.� �����, ������ � ������ - ��� ��� �������, ������� �� ������� ������ ���� ��������� ����� ����������� ������.

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deadline.generated.h"

class USceneComponent;
class UPaperFlipbookComponent;

UCLASS()
class DBCPPTRY17042_API ADeadline : public AActor
{
	GENERATED_BODY()
	
protected:
	// ����� ����� = ����� �������
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	// ����� 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MashComponent;

	// ������������ �����
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookConmponent;

	// �������� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpeedCompression;

	// ��������� ������ �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double DeadlineScale;

	// ��� ����������� �������� �������� ������������ ����� �� ��������� ������
	const float KofOfSpeedVisual = 250.f;


public:	
	ADeadline();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	// �������� �������, ��������� �� ������� �����
	UFUNCTION()
	void OverlapCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
