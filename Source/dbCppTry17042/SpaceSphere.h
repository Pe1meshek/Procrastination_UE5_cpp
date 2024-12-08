/*
����������� ���

��� �������� �������������� � ��������� ������������, �������� ��������� ���
� �������� ���������
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
	// ��� (���������� �����)
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SphereComponent;

	// ��������� ����������� ��������
	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovementComponent;

	// ������ ����� �� ����� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TArray<UMaterialInstance*> SpaceSkins;

	// ������������ �������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float MaxRotationSpeed;


public:	
	ASpaceSphere();

protected:
	virtual void BeginPlay() override;

};
