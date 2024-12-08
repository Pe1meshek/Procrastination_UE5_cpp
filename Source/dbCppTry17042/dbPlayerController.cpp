
#include "dbPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AutoCamera.h"
#include "LevelMenuController.h"
#include "BladPirat.h"
#include "PlaneForCursor.h"

////////////////////////////////////
/// �������� �������� � �������� ///
///______________________________///
/// 
	void AdbPlayerController::SetupInputComponent()
	{
		Super::SetupInputComponent();

		// ��������� Input Mappoing
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		// ��������� �����������
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			// ���������� ������� //
			//
			// ��������������� ��������
			if (AICameraHorizontalMove)
			{
				EnhancedInputComponent->BindAction(AICameraHorizontalMove, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraHorizontalMove);
				EnhancedInputComponent->BindAction(AICameraHorizontalMove, ETriggerEvent::Completed, this, &AdbPlayerController::CameraHorizontalMove);
			}
			//
			// ������������ ��������
			if (AICameraVerticalMove)
			{
				EnhancedInputComponent->BindAction(AICameraVerticalMove, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraVerticalMove);
				EnhancedInputComponent->BindAction(AICameraVerticalMove, ETriggerEvent::Completed, this, &AdbPlayerController::CameraVerticalMove);
			}

			if (AICameraCapturePoint)
			{
				EnhancedInputComponent->BindAction(AICameraCapturePoint, ETriggerEvent::Started, this, &AdbPlayerController::CameraSaveMouseClickPoint);
				EnhancedInputComponent->BindAction(AICameraCapturePoint, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraMoveRelativePoint);
			}

			//
			// �������� ����� ��� Y (�����������/���������)
			if (AICameraZoom)
			{
				EnhancedInputComponent->BindAction(AICameraZoom, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraZoom);
				EnhancedInputComponent->BindAction(AICameraZoom, ETriggerEvent::Completed, this, &AdbPlayerController::CameraZoom);
			}
			//
			// ������������ �������
			if (AICameraFlipMode)
			{
				EnhancedInputComponent->BindAction(AICameraFlipMode, ETriggerEvent::Started, this, &AdbPlayerController::CameraFlipMode);
			}
			//____________________//
		

			// ���������� ��������� //
			//
			// ��������/���������� ���������
			if (AIInventoryFlipVisible)
			{
				EnhancedInputComponent->BindAction(AIInventoryFlipVisible, ETriggerEvent::Started, this, &AdbPlayerController::InventoryFlipVisible);
			}
			// �����/�������
			if (AIGamePause)
			{
				EnhancedInputComponent->BindAction(AIGamePause, ETriggerEvent::Started, this, &AdbPlayerController::GamePause);
			}
			//______________________//
		
		
			// ���������� ���������� //
			//
			// �������� (�����/������)
			if (AIPiratMoveRight)
			{
				EnhancedInputComponent->BindAction(AIPiratMoveRight, ETriggerEvent::Triggered, this, &AdbPlayerController::PiratMoveRight);
				EnhancedInputComponent->BindAction(AIPiratMoveRight, ETriggerEvent::Completed, this, &AdbPlayerController::PiratMoveRight);
			}
			//
			// �������
			if (AIPiratJump)
			{
				EnhancedInputComponent->BindAction(AIPiratJump, ETriggerEvent::Triggered, this, &AdbPlayerController::PiratJump);
			}
			//
			// �������� �������
			if (AIPiratSpawnPinus)
			{
				EnhancedInputComponent->BindAction(AIPiratSpawnPinus, ETriggerEvent::Started, this, &AdbPlayerController::PiratSpawnPinus);
			}
			//
			// ����� �����
			if (AIPiratStartCharge)
			{
				EnhancedInputComponent->BindAction(AIPiratStartCharge, ETriggerEvent::Started, this, &AdbPlayerController::PiratStartCharge);
			}
			//
			// �����
			if (AIPiratKick)
			{
				EnhancedInputComponent->BindAction(AIPiratKick, ETriggerEvent::Completed, this, &AdbPlayerController::PiratKick);
			}
			//
			// ��������� �������
			if (AIPiratActivatePinus)
			{
				EnhancedInputComponent->BindAction(AIPiratActivatePinus, ETriggerEvent::Started, this, &AdbPlayerController::PiratActivatePinus);
			}
			//_______________________//
		}

		// ���������� ������
		SetShowMouseCursor(true);
	}
///______________________________///
////////////////////////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
/// �.� ���������� ��������� ����� ���� ����� ������ ��� ���������� ��������� �������,
/// � ������ ���������� (���������� ��������� �������) �������� ��������� ������ � ����������,
/// �� � ��������� ��������� ����� ������ ����������.
/// 
/// ������ ���� ��������� 2, ���� �������������� ������ ������� �������� � ����� (����������� �� ����������� �� ��� Y)
///_______________///
/// 
	void AdbPlayerController::BeginPlay()
	{
		// �������� ������
		if (ClassPlaneForCursor)
		{
			GetWorld()->SpawnActor<APlaneForCursor>(ClassPlaneForCursor, FVector(0., -25., 0.), FRotator(0., 0., 0.));
			GetWorld()->SpawnActor<APlaneForCursor>(ClassPlaneForCursor, FVector(0., 25., 0.), FRotator(0., 0., 0.));
		}

		// ���������� ������ �� ���������
		// ����� �������� ��� ������� � ������� ������� ������
		Pirat = Cast<ABladPirat>(GetPawn());
	}
///_______________///
/////////////////////


////////////////////////////////////
/// ������� ����������� �������� ///
///______________________________///
/// 
/// ������ ������
	void AdbPlayerController::SetAutoCamera(AAutoCamera* autoCamera)
	{
		if (autoCamera)
		{
			AutoCamera = autoCamera;
		}
	}
///
/// ������ ����������� ��������
	void AdbPlayerController::SetLevelMenuController(ALevelMenuController* levelMenuController)
	{
		if (levelMenuController)
		{
			LevelMenuController = levelMenuController;
		}
	}
///______________________________///
////////////////////////////////////


/////////////////////////////////////////////
/// ����������� ������� ��������� ������� ///
///_______________________________________///
/// 
/// ������� ���������� ������� ����� ���������
/// ��� ����������� �������� ������� ����������� �����,
/// ��� �������� ������� ������� ������� 
///_______________________________________///
/// 
	FVector AdbPlayerController::GetCursorWorldLocation()
	{
		FHitResult hitResult;
		GetHitResultUnderCursor(ECollisionChannel::ECC_WorldStatic, false, hitResult);
		return FVector(hitResult.Location.X, 0., hitResult.Location.Z);
	}
///_______________________________________///
/////////////////////////////////////////////


////////////////////////////
/// ����� ������� ������ ///
///______________________///
/// 
/// �������������� �����������
	void AdbPlayerController::CameraHorizontalMove(const FInputActionInstance& Instance)
	{
		if (AutoCamera)
		{
			AutoCamera->HorizontalMove(Instance.GetValue().Get<float>());
		}
	}
///
/// ������������ �����������
	void AdbPlayerController::CameraVerticalMove(const FInputActionInstance& Instance)
	{
		if (AutoCamera)
		{
			AutoCamera->VerticalMove(Instance.GetValue().Get<float>());
		}
	}
///
/// ���������� ��������� ������� � ������ � ������ ������� ���
	void AdbPlayerController::CameraSaveMouseClickPoint(const FInputActionInstance& Instance)
	{
		if (AutoCamera && CameraMode == 1)
		{
			AutoCamera->SaveMouseClickPoint();
		}
	}
///
/// �������� ������ � ������ ��������� ���
	void AdbPlayerController::CameraMoveRelativePoint(const FInputActionInstance& Instance)
	{
		if (AutoCamera && CameraMode == 1)
		{
			AutoCamera->MoveRelativePoint();
		}
	}
///
/// �����������/���������
	void AdbPlayerController::CameraZoom(const FInputActionInstance& Instance)
	{
		if (AutoCamera)
		{
			AutoCamera->Zoom(Instance.GetValue().Get<float>());
		}
	}
///______________________///
////////////////////////////


//////////////////////////////////
/// ������������ ������ ������ ///
///____________________________///
/// 
/// ����������� ����� � ���� ������� (+1)
/// � ������������� �������������� ������ ��� viewTarget.
/// 
/// ������ �����:
/// 0 - ������ ��������������� �������
/// 1 - ����������� ������
/// 2 - ������ ����������� � ���������
///____________________________///
/// 
	void AdbPlayerController::CameraFlipMode(const FInputActionInstance& Instance)
	{
		// ������������ ������ (+1)
		CameraMode++;
		// ��������� ������ �� �������
		if (CameraMode > 2)
		{
			CameraMode = 0;
		}

		// ��������� ������
		switch (CameraMode)
		{
			case 0: 
				if (AutoCamera)
				{
					AutoCamera->SetAsMainCamera();
					AutoCamera->SetAutoMode(true);
				}
				break;

			case 1:
				if (AutoCamera)
				{
					AutoCamera->SetAsMainCamera();
					AutoCamera->SetAutoMode(false);
				}
				break;

			case 2:
				if (Pirat)
				{
					Pirat->SetAsMainCamera();
				}
				break;
		}
	}
///____________________________///
//////////////////////////////////


//////////////////////////////////////////
/// ����� ������� ����������� �������� ///
///____________________________________///
///
/// ��������/���������� ���������
	void AdbPlayerController::InventoryFlipVisible(const FInputActionInstance& Instance)
	{
		if (LevelMenuController)
		{
			LevelMenuController->InventoryFlip();
		}
	}
///
/// �����/�������
	void AdbPlayerController::GamePause(const FInputActionInstance& Instance)
	{
		if (LevelMenuController)
		{
			LevelMenuController->PauseUnpause();
		}
	}
///____________________________________///
//////////////////////////////////////////


///////////////////////////////
/// ����� ������� ��������� ///
///_________________________///
/// 
/// �������� (�����/������)
	void AdbPlayerController::PiratMoveRight(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->MoveRight(Instance.GetValue().Get<float>());
		}
	}
///
/// ������
	void AdbPlayerController::PiratJump(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->Jump();
		}
	}
///
/// �������� �������
	void AdbPlayerController::PiratSpawnPinus(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->SpawnPinus();
		}
	}
///
/// ������ ������ �����
	void AdbPlayerController::PiratStartCharge(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->StartCharge();
		}
	}
///
/// �����
	void AdbPlayerController::PiratKick(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->Kick();
		}
	}
///
/// ���������
	void AdbPlayerController::PiratActivatePinus(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->ActivatePinus();
		}
	}
///_________________________///
///////////////////////////////



