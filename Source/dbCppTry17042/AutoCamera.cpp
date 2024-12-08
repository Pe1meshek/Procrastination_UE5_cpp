

#include "AutoCamera.h"
#include "Camera/CameraComponent.h"
#include "dbPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Delo.h"
#include "Warp.h"
#include "BladPirat.h"


///////////////////
/// Конструктор ///
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
/// Начало работы ///
///_______________///
/// 
	void AAutoCamera::BeginPlay()
	{
		Super::BeginPlay();
	
		// Передаем контроллеру объект управления))
		Cast<AdbPlayerController>(GetWorld()->GetFirstPlayerController())->SetAutoCamera(this);
	
		// Задаем себя как основная камера
		SetAsMainCamera();

		// Ищем основные объекты и заполняем ими масив 
		FillArrayCapturedActors();
	}
///_______________///
/////////////////////


//////////////////
/// Каждый тик ///
///____________///
/// 
/// Меняет позицию в зависимости от выбранного режима
///____________///
/// 
	void AAutoCamera::Tick(float DeltaTime)
	{
		Super::Tick(DeltaTime);

		if (bIsAutoModeEnable)
		{
			// Захват ключевых объектов
			CaptureActors();
		}
		else
		{
			// Ручное перемещение
			// (старое)
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
/// Ручное управление ///
/// _________________ ///
/// 
/// Скорость перемещения по плоскости XZ (влево/вправо/вверх/вниз)
/// зависит от позиции по оси Y.
/// Т.е чем ближе - тем медленнее.
/// Нужно, чтобы отдалившись не ползать черепахой.
/// _________________ ///
/// 
/// Движение по горизонтали. Скорость зависит от степени отдаления
	void AAutoCamera::HorizontalMove(float direction)
	{
		CurrentVelocity.X = direction * GetActorLocation().Y;
	}
///
/// Движение по вертикали. Скорость зависит от степени отдаления
	void AAutoCamera::VerticalMove(float direction)
	{
		CurrentVelocity.Z = direction * GetActorLocation().Y;
	}
///
/// Приближение / отдаление
	void AAutoCamera::Zoom(float direction)
	{
		CurrentVelocity.Y = direction * -CameraSpeed;
	}
///
/// Сохранение координат курсора и камеры в момент нажатия ПКМ
	void AAutoCamera::SaveMouseClickPoint()
	{
		GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePointX, MousePointY);
		CameraPoint = GetActorLocation();
	}
///
/// Движение камеры относительно курсора
	void AAutoCamera::MoveRelativePoint()
	{
		double nowCursorX;
		double nowCursorY;
		FVector newLocation = GetActorLocation();

		// Сохраняем скорость перемещения курсора в nowCursorX и nowCursorY
		GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(nowCursorX, nowCursorY);

		// Если скорость курсора не нулевая - двигаем камеру
		if (abs(nowCursorX) > 0.01)
		{
			newLocation.X = CameraPoint.X - (nowCursorX) * GetActorLocation().Y / 20;
		}
		if (abs(nowCursorY) > 0.01)
		{
			newLocation.Z = CameraPoint.Z - (nowCursorY) * GetActorLocation().Y / 20;
		}
		SetActorLocation(newLocation);

		// Сохраняем новое положение
		SaveMouseClickPoint();
	}
///___________________///
/////////////////////////


//////////////////////////////////////
/// Изменение режима работы камеры ///
///________________________________///
/// 
/// Переключение
	void AAutoCamera::FlipMode()
	{
		bIsAutoModeEnable = !bIsAutoModeEnable;
	}
/// 
/// Строгая установка
	void AAutoCamera::SetAutoMode(bool bAutoModeOn)
	{
		bIsAutoModeEnable = bAutoModeOn;
	}
///________________________________///
//////////////////////////////////////


/////////////////////////////
/// Установка во viewPort ///
///_______________________///
/// 
/// Удобно, при чтении кода.
/// Больших заслуг, учитывая одностройчное содержание, нет.
///_______________________///
/// 
	void AAutoCamera::SetAsMainCamera()
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	}
///_______________________///
/////////////////////////////


//////////////////////////////////////////////
/// Заполнение массива ключевыми объектами ///
///________________________________________///
///
	void AAutoCamera::FillArrayCapturedActors()
	{
		// Очищаем массив, на всякий случай
		while (!CapturedActors.IsEmpty())
		{
			CapturedActors.Pop();
		}

		// Берем первый найденный объект каждого типа
		ABladPirat* pirat = Cast<ABladPirat>(UGameplayStatics::GetActorOfClass(GetWorld(), ABladPirat::StaticClass()));
		ADelo* delo = Cast<ADelo>(UGameplayStatics::GetActorOfClass(GetWorld(), ADelo::StaticClass()));
		AWarp* warp = Cast<AWarp>(UGameplayStatics::GetActorOfClass(GetWorld(), AWarp::StaticClass()));
	
		// Если все три объекта найдены - сохраняем их в массив
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
/// Захват куамерой основных объектов ///
///___________________________________///
/// 
	void AAutoCamera::CaptureActors()
	{
		// Ищем крайние точки (экстремумы координат ключевых объектов)
		float top, bottom, right, left;
		if (!CapturedActors.IsEmpty())
		{
			// Сперва вносим значения первого элемента, ибо при равнение к 0 - некорректно
			top = CapturedActors[0]->GetActorLocation().Z;
			bottom = CapturedActors[0]->GetActorLocation().Z;
			right = CapturedActors[0]->GetActorLocation().X;
			left = CapturedActors[0]->GetActorLocation().X;

			// Проходимся по массиву объектов, сравниваем значения и сохраняем экстремумы
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

			// Рассчет Координат камеры, с учетом захвата ключевых объектов //
			//
			FVector NewLocation;
			//
			// Ищем середину между экстремумами по горизонтали
			NewLocation.X = (right - left) / 2 + left;
			//
			// Ищем середину между экстремумами по вертикали
			NewLocation.Z = (top - bottom) / 2 + bottom;
			//
			// Сравниваем разброс по вертикали с разбросом по горизонтали
			// и отдаляемся камерой на наибольший из двух разбросов
			NewLocation.Y = (top - bottom) > (right - left) ? (top - bottom) : (right - left);
			//
			// +50 к отдалению для лучшего отображения нижних и верхних объектов
			NewLocation.Y += 50.;
			//
			// Устанавливаем минимальное отдаление камеры
			if (NewLocation.Y < 300.)
			{
				NewLocation.Y = 300.;
			}
			//
			// Задаем позицию камере
			SetActorLocation(NewLocation);
			//______________________________________________________________//
		}
	}
///___________________________________///
/////////////////////////////////////////

