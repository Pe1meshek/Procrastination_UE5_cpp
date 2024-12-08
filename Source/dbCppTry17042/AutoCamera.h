/*
������

�������� �  ���� �������:
1. ����������� ��������� � ��������� (4 ����������� (����/�����/�����/����) + zoom (����������/���������) )
	+ ����������� � ������� ������ ������� ����

2. �������������� ������������ � �������, � ������� � ������� �������� �������� �������� �������
	(�����, ����, ����)

*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutoCamera.generated.h"

class UCameraComponent;

UCLASS()
class DBCPPTRY17042_API AAutoCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

protected:
	// ������ ����������� ������� � ������ ������ �������
	FVector CurrentVelocity;
	

	// �������� ����������� (default 1500)
	float CameraSpeed;


	// ��������� � ������� ����� ��������� ������� ������ �� ��� Y //
	const float minCameraZoom = 100.f;
	const float maxCameraZoom = 5000.f;
	//_____________________________________________________________//
	

	// ���� ������ ������ ������
	bool bIsAutoModeEnable;


	// ������ �������� ��������, ������� ������ ���� � �����
	TArray<AActor*> CapturedActors;
	

	// ���������� ������� � ������ ����� ��� //
	double MousePointX;
	double MousePointY;
	//_______________________________________//


	// ���������� ������ � ������ ����� ���
	FVector CameraPoint;

public:	
	AAutoCamera();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	// ����������� ������ //
	//
	// �����/������
	void HorizontalMove(float direction);
	//
	// �����/����
	void VerticalMove(float direction);
	//
	// ������/�����
	void Zoom(float direction);
	//
	// �������� �������� �����
	//	������ �����
	void SaveMouseClickPoint();
	//	�������� ������������ ����������� �����	 
	void MoveRelativePoint();
	//____________________//


	// ��������� ������ ������ ������ //
	//
	// ������������
	void FlipMode();
	//
	// ������� ���������
	void SetAutoMode(bool bAutoModeOn);
	//________________________________//


	// ��������� � PlayerController � ��������� ��� viewTarget
	void SetAsMainCamera();


	// ����� �������� �������� � ���������� ��� �������
	void FillArrayCapturedActors();


	// ������ ������� ���� �������� ��������
	void CaptureActors();
};
