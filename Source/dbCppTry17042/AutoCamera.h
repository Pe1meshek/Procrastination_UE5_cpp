/*
Камера

Работает в  двух режимах:
1. Управляемая стрелками и колесиком (4 направления (лево/право/вверх/вниз) + zoom (приблизить/отдалдить) )
	+ перемещение с зажатой правой кнопеой мыши

2. Автоматическое расположение в позиции, в которой в область видимоти попадают ключевые объекты
	(игрок, дело, варп)

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
	// Вектор перемещения камереы в каждый момент времени
	FVector CurrentVelocity;
	

	// Скорость перемещения (default 1500)
	float CameraSpeed;


	// Ближайшая и дальняя точка возможной позиции камеры по оси Y //
	const float minCameraZoom = 100.f;
	const float maxCameraZoom = 5000.f;
	//_____________________________________________________________//
	

	// Флаг режима работы камеры
	bool bIsAutoModeEnable;


	// Массив ключевых объектов, которые должны быть в кадре
	TArray<AActor*> CapturedActors;
	

	// Координаты курсора в момент клика ПКМ //
	double MousePointX;
	double MousePointY;
	//_______________________________________//


	// Координаты камеры в момент клика ПКМ
	FVector CameraPoint;

public:	
	AAutoCamera();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	// Перемещение камеры //
	//
	// Влево/Вправо
	void HorizontalMove(float direction);
	//
	// Вверх/Вниз
	void VerticalMove(float direction);
	//
	// Вперед/Назад
	void Zoom(float direction);
	//
	// Движение захватом точки
	//	Захват точки
	void SaveMouseClickPoint();
	//	Движение относительно захваченной точки	 
	void MoveRelativePoint();
	//____________________//


	// Изменение режима работы камеры //
	//
	// Переключение
	void FlipMode();
	//
	// Строгая установка
	void SetAutoMode(bool bAutoModeOn);
	//________________________________//


	// Обращение к PlayerController и установка как viewTarget
	void SetAsMainCamera();


	// Поиск ключевых объектов и заполнение ими массива
	void FillArrayCapturedActors();


	// Захват камерой всех ключевых объектов
	void CaptureActors();
};
