

#include "AutoCamera.h"
#include "Camera/CameraComponent.h"
#include "dbPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Delo.h"
#include "Warp.h"
#include "BladPirat.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	AAutoCamera::AAutoCamera() :
		CurrentVelocity(0.,0.,0.),
		CameraSpeed(1500.f),
		bIsAutoModeEnable(true),
		MousePointX(0.),
		MousePointY(0.),
		CameraPoint(0., 0., 0.)
	{
		PrimaryActorTick.bCanEverTick = true;

		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		SetRootComponent(CameraComponent);
	}
///_____________///
///////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void AAutoCamera::BeginPlay()
	{
		Super::BeginPlay();
	
		// �������� ����������� ������ ����������))
		Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController())->SetAutoCamera(this);
	
		// ������ ���� ��� �������� ������
		SetAsMainCamera();

		// ���� �������� ������� � ��������� ��� ����� 
		FillArrayCapturedActors();
	}
///_______________///
/////////////////////


//////////////////
/// ������ ��� ///
///____________///
/// 
/// ������ ������� � ����������� �� ���������� ������
///____________///
/// 
	void AAutoCamera::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		if (bIsAutoModeEnable)
		{
			// ������ �������� ��������
			CaptureActors();
		}
		else
		{
			// ������ �����������
			// (������)
			if (!CurrentVelocity.IsZero())
			{
				FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
				if (NewLocation.Y < minCameraZoom)
				{
					NewLocation.Y = minCameraZoom;
				}
				if (NewLocation.Y > maxCameraZoom)
				{
					NewLocation.Y = maxCameraZoom;
				}
				SetActorLocation(NewLocation);
			}
		}
	}
///____________///
//////////////////


/////////////////////////
/// ������ ���������� ///
/// _________________ ///
/// 
/// �������� ����������� �� ��������� XZ (�����/������/�����/����)
/// ������� �� ������� �� ��� Y.
/// �.� ��� ����� - ��� ���������.
/// �����, ����� ����������� �� ������� ���������.
/// _________________ ///
/// 
/// �������� �� �����������. �������� ������� �� ������� ���������
	void AAutoCamera::HorizontalMove(float direction)
	{
		CurrentVelocity.X = direction * GetActorLocation().Y;
	}
///
/// �������� �� ���������. �������� ������� �� ������� ���������
	void AAutoCamera::VerticalMove(float direction)
	{
		CurrentVelocity.Z = direction * GetActorLocation().Y;
	}
///
/// ����������� / ���������
	void AAutoCamera::Zoom(float direction)
	{
		CurrentVelocity.Y = direction * -CameraSpeed;
	}
///
/// ���������� ��������� ������� � ������ � ������ ������� ���
	void AAutoCamera::SaveMouseClickPoint()
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePointX, MousePointY);
		CameraPoint = GetActorLocation();
	}
///
/// �������� ������ ������������ �������
	void AAutoCamera::MoveRelativePoint()
	{
		double nowCursorX;
		double nowCursorY;
		FVector newLocation = GetActorLocation();

		// ��������� �������� ����������� ������� � nowCursorX � nowCursorY
		GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(nowCursorX, nowCursorY);

		// ���� �������� ������� �� ������� - ������� ������
		if (abs(nowCursorX) > 0.01)
		{
			newLocation.X = CameraPoint.X - (nowCursorX) * GetActorLocation().Y / 20;
		}
		if (abs(nowCursorY) > 0.01)
		{
			newLocation.Z = CameraPoint.Z - (nowCursorY) * GetActorLocation().Y / 20;
		}
		SetActorLocation(newLocation);

		// ��������� ����� ���������
		SaveMouseClickPoint();
	}
///___________________///
/////////////////////////


//////////////////////////////////////
/// ��������� ������ ������ ������ ///
///________________________________///
/// 
/// ������������
	void AAutoCamera::FlipMode()
	{
		bIsAutoModeEnable = !bIsAutoModeEnable;
	}
/// 
/// ������� ���������
	void AAutoCamera::SetAutoMode(bool bAutoModeOn)
	{
		bIsAutoModeEnable = bAutoModeOn;
	}
///________________________________///
//////////////////////////////////////


/////////////////////////////
/// ��������� �� viewPort ///
///_______________________///
/// 
/// ������, ��� ������ ����.
/// ������� ������, �������� ������������� ����������, ���.
///_______________________///
/// 
	void AAutoCamera::SetAsMainCamera()
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
///_______________________///
/////////////////////////////


//////////////////////////////////////////////
/// ���������� ������� ��������� ��������� ///
///________________________________________///
///
	void AAutoCamera::FillArrayCapturedActors()
	{
		// ������� ������, �� ������ ������
		while (!CapturedActors.IsEmpty())
		{
			CapturedActors.Pop();
		}

		// ����� ������ ��������� ������ ������� ����
		ABladPirat* pirat = Cast<ABladPirat>(UGameplayStatics::GetActorOfClass(GetWorld(), ABladPirat::StaticClass()));
		ADelo* delo = Cast<ADelo>(UGameplayStatics::GetActorOfClass(GetWorld(), ADelo::StaticClass()));
		AWarp* warp = Cast<AWarp>(UGameplayStatics::GetActorOfClass(GetWorld(), AWarp::StaticClass()));
	
		// ���� ��� ��� ������� ������� - ��������� �� � ������
		if (pirat && delo && warp)
		{
			CapturedActors.Push(pirat);
			CapturedActors.Push(delo);
			CapturedActors.Push(warp);
		}
	}
///________________________________________///
//////////////////////////////////////////////


/////////////////////////////////////////
/// ������ �������� �������� �������� ///
///___________________________________///
/// 
	void AAutoCamera::CaptureActors()
	{
		// ���� ������� ����� (���������� ��������� �������� ��������)
		float top, bottom, right, left;
		if (!CapturedActors.IsEmpty())
		{
			// ������ ������ �������� ������� ��������, ��� ��� �������� � 0 - �����������
			top = CapturedActors[0]->GetActorLocation().Z;
			bottom = CapturedActors[0]->GetActorLocation().Z;
			right = CapturedActors[0]->GetActorLocation().X;
			left = CapturedActors[0]->GetActorLocation().X;

			// ���������� �� ������� ��������, ���������� �������� � ��������� ����������
			for (auto actor : CapturedActors)
			{
				if (actor->GetActorLocation().Z > top)
				{
					top = actor->GetActorLocation().Z;
				}
				if (actor->GetActorLocation().Z < bottom)
				{
					bottom = actor->GetActorLocation().Z;
				}
				if (actor->GetActorLocation().X > right)
				{
					right = actor->GetActorLocation().X;
				}
				if (actor->GetActorLocation().X < left)
				{
					left = actor->GetActorLocation().X;
				}
			}

			// ������� ��������� ������, � ������ ������� �������� �������� //
			//
			FVector NewLocation;
			//
			// ���� �������� ����� ������������ �� �����������
			NewLocation.X = (right - left) / 2 + left;
			//
			// ���� �������� ����� ������������ �� ���������
			NewLocation.Z = (top - bottom) / 2 + bottom;
			//
			// ���������� ������� �� ��������� � ��������� �� �����������
			// � ���������� ������� �� ���������� �� ���� ���������
			NewLocation.Y = (top - bottom) > (right - left) ? (top - bottom) : (right - left);
			//
			// +50 � ��������� ��� ������� ����������� ������ � ������� ��������
			NewLocation.Y += 50.;
			//
			// ������������� ����������� ��������� ������
			if (NewLocation.Y < 300.)
			{
				NewLocation.Y = 300.;
			}
			//
			// ������ ������� ������
			SetActorLocation(NewLocation);
			//______________________________________________________________//
		}
	}
///___________________________________///
/////////////////////////////////////////

