
#include "dbPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AutoCamera.h"
#include "LevelMenuController.h"
#include "BladPirat.h"
#include "PlaneForCursor.h"

////////////////////////////////////
/// Привязка действий к функциям ///
///______________________________///
/// 
	void AdbPlayerController::SetupInputComponent()
	{
		Super::SetupInputComponent();

		// Установка Input Mappoing
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}

		// Установка соответсвий
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
		if (EnhancedInputComponent)
		{
			// Управление камерой //
			//
			// Гороизонтальное движение
			if (AICameraHorizontalMove)
			{
				EnhancedInputComponent->BindAction(AICameraHorizontalMove, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraHorizontalMove);
				EnhancedInputComponent->BindAction(AICameraHorizontalMove, ETriggerEvent::Completed, this, &AdbPlayerController::CameraHorizontalMove);
			}
			//
			// Вертикальное движение
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
			// Движение вдоль оси Y (приближение/отдаление)
			if (AICameraZoom)
			{
				EnhancedInputComponent->BindAction(AICameraZoom, ETriggerEvent::Triggered, this, &AdbPlayerController::CameraZoom);
				EnhancedInputComponent->BindAction(AICameraZoom, ETriggerEvent::Completed, this, &AdbPlayerController::CameraZoom);
			}
			//
			// Переключение режимов
			if (AICameraFlipMode)
			{
				EnhancedInputComponent->BindAction(AICameraFlipMode, ETriggerEvent::Started, this, &AdbPlayerController::CameraFlipMode);
			}
			//____________________//
		

			// Управление виджетами //
			//
			// Свернуть/Развернуть инвентарь
			if (AIInventoryFlipVisible)
			{
				EnhancedInputComponent->BindAction(AIInventoryFlipVisible, ETriggerEvent::Started, this, &AdbPlayerController::InventoryFlipVisible);
			}
			// Пауза/Анпауза
			if (AIGamePause)
			{
				EnhancedInputComponent->BindAction(AIGamePause, ETriggerEvent::Started, this, &AdbPlayerController::GamePause);
			}
			//______________________//
		
		
			// Управление персонажем //
			//
			// Движение (влево/вправо)
			if (AIPiratMoveRight)
			{
				EnhancedInputComponent->BindAction(AIPiratMoveRight, ETriggerEvent::Triggered, this, &AdbPlayerController::PiratMoveRight);
				EnhancedInputComponent->BindAction(AIPiratMoveRight, ETriggerEvent::Completed, this, &AdbPlayerController::PiratMoveRight);
			}
			//
			// Прыжжок
			if (AIPiratJump)
			{
				EnhancedInputComponent->BindAction(AIPiratJump, ETriggerEvent::Triggered, this, &AdbPlayerController::PiratJump);
			}
			//
			// Создание снаряда
			if (AIPiratSpawnPinus)
			{
				EnhancedInputComponent->BindAction(AIPiratSpawnPinus, ETriggerEvent::Started, this, &AdbPlayerController::PiratSpawnPinus);
			}
			//
			// Заряд пинка
			if (AIPiratStartCharge)
			{
				EnhancedInputComponent->BindAction(AIPiratStartCharge, ETriggerEvent::Started, this, &AdbPlayerController::PiratStartCharge);
			}
			//
			// Пинок
			if (AIPiratKick)
			{
				EnhancedInputComponent->BindAction(AIPiratKick, ETriggerEvent::Completed, this, &AdbPlayerController::PiratKick);
			}
			//
			// Активация Снаряда
			if (AIPiratActivatePinus)
			{
				EnhancedInputComponent->BindAction(AIPiratActivatePinus, ETriggerEvent::Started, this, &AdbPlayerController::PiratActivatePinus);
			}
			//_______________________//
		}

		// Показываем курсор
		SetShowMouseCursor(true);
	}
///______________________________///
////////////////////////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
/// Т.к изначально невидимая стена была нужна именно для нахождения положения курсора,
/// а данный функционал (нахождения положения курсора) логичнее поместить именно в контроллер,
/// то и создавать невидимую стену должен контроллер.
/// 
/// Однако стен создается 2, дабы препятствовать вылету игровых объектов с карты (ограничение их перемещения по оси Y)
///_______________///
/// 
	void AdbPlayerController::BeginPlay()
	{
		// Создание стенок
		if (ClassPlaneForCursor)
		{
			GetWorld()->SpawnActor<APlaneForCursor>(ClassPlaneForCursor, FVector(0., -25., 0.), FRotator(0., 0., 0.));
			GetWorld()->SpawnActor<APlaneForCursor>(ClassPlaneForCursor, FVector(0., 25., 0.), FRotator(0., 0., 0.));
		}

		// Сохранение ссылки на Персонажа
		// чтобы вызывать его функции в моменты нажатия клавиш
		Pirat = Cast<ABladPirat>(GetPawn());
	}
///_______________///
/////////////////////


////////////////////////////////////
/// Сеттеры управляемых объектов ///
///______________________________///
/// 
/// Сеттер Камеры
	void AdbPlayerController::SetAutoCamera(AAutoCamera* autoCamera)
	{
		if (autoCamera)
		{
			AutoCamera = autoCamera;
		}
	}
///
/// Сеттер Контроллера Виджетов
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
/// Определение мировых координат курсора ///
///_______________________________________///
/// 
/// Мировые координаты курсора нужны персонажу
/// для корректного поворота стрелки направления пинка,
/// для указания вектора запуска снаряда 
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
/// Вызов функций Камеры ///
///______________________///
/// 
/// Горизонтальное перемещение
	void AdbPlayerController::CameraHorizontalMove(const FInputActionInstance& Instance)
	{
		if (AutoCamera)
		{
			AutoCamera->HorizontalMove(Instance.GetValue().Get<float>());
		}
	}
///
/// Вертикальное перемещение
	void AdbPlayerController::CameraVerticalMove(const FInputActionInstance& Instance)
	{
		if (AutoCamera)
		{
			AutoCamera->VerticalMove(Instance.GetValue().Get<float>());
		}
	}
///
/// Сохранение координат курсора и камеры в момент нажатия ПКМ
	void AdbPlayerController::CameraSaveMouseClickPoint(const FInputActionInstance& Instance)
	{
		if (AutoCamera && CameraMode == 1)
		{
			AutoCamera->SaveMouseClickPoint();
		}
	}
///
/// Движение камеры в момент удержания ПКМ
	void AdbPlayerController::CameraMoveRelativePoint(const FInputActionInstance& Instance)
	{
		if (AutoCamera && CameraMode == 1)
		{
			AutoCamera->MoveRelativePoint();
		}
	}
///
/// Приближение/Отдаление
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
/// Переключение режиов камеры ///
///____________________________///
/// 
/// Переключает режим в одну сторону (+1)
/// и устанавливает соответсвующую камеру как viewTarget.
/// 
/// Режимы камер:
/// 0 - Камера автоматического захвата
/// 1 - Управляемая камера
/// 2 - Камера привязанная к персонажу
///____________________________///
/// 
	void AdbPlayerController::CameraFlipMode(const FInputActionInstance& Instance)
	{
		// Переключение режима (+1)
		CameraMode++;
		// Обработка выхода за границы
		if (CameraMode > 2)
		{
			CameraMode = 0;
		}

		// Установка камеры
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
/// Вызов функций Контроллера виджетов ///
///____________________________________///
///
/// Свернуть/Развернуть инвентарь
	void AdbPlayerController::InventoryFlipVisible(const FInputActionInstance& Instance)
	{
		if (LevelMenuController)
		{
			LevelMenuController->InventoryFlip();
		}
	}
///
/// Пауза/Анпауза
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
/// Вызов функций Персонажа ///
///_________________________///
/// 
/// Движение (влево/вправо)
	void AdbPlayerController::PiratMoveRight(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->MoveRight(Instance.GetValue().Get<float>());
		}
	}
///
/// Прыжок
	void AdbPlayerController::PiratJump(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->Jump();
		}
	}
///
/// Создание снаряда
	void AdbPlayerController::PiratSpawnPinus(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->SpawnPinus();
		}
	}
///
/// Начало раряда пинка
	void AdbPlayerController::PiratStartCharge(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->StartCharge();
		}
	}
///
/// Пинок
	void AdbPlayerController::PiratKick(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->Kick();
		}
	}
///
/// Активация
	void AdbPlayerController::PiratActivatePinus(const FInputActionInstance& Instance)
	{
		if (Pirat)
		{
			Pirat->ActivatePinus();
		}
	}
///_________________________///
///////////////////////////////



