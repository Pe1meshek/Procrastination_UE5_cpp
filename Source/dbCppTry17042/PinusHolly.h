/*
������ ������

��������� - ���������� ����������
��� ������������ � ����� ������ ����������� ���
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusHolly.generated.h"


UCLASS()
class DBCPPTRY17042_API APinusHolly : public APinusBase
{
	GENERATED_BODY()

public:
	// ���� ������������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float PushPower;

public:
	APinusHolly();

	// ��������� (���������������)
	void Activate() override;

protected:
	void BeginPlay() override;

	// ������������ � �����
	UFUNCTION()
	void HitDelo(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
