/*
������ ���������

��������� - ��������� ������� ��������� ��������� ����.
���� ���� �������� � ����, �� ��� ������������� � ��� ��������� (�������)
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusMagnet.generated.h"

class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class DBCPPTRY17042_API APinusMagnet : public APinusBase
{
	GENERATED_BODY()

public:
	// �������� ����
	UPROPERTY(VisibleAnywhere)
	USphereComponent* MagnetPoleCollision;

	// �������� ����
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* MagnetPolePaperFlipbook;

	// �������� ������ ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpeedCompression;

	// ���� ����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double PowerAttraction;

protected:
	// ������ �� ����� ������������� ����
	FTimerHandle TimerHandleMagnetPoleCompression;
	

public:
	APinusMagnet();

	// ��������� (���������������)
	void Activate() override;

protected:
	// ������ ����
	// ���������� ������ ��� ��� ����� ������������� ����
	void MagnetPoleCompression();
};
