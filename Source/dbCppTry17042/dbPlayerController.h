/*
Контроллер

Обрабатывает нажатия клаиш и вызывает соответсвующие функции объктов
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "dbPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AAutoCamera;
class ALevelMenuController;
class ABladPirat;
struct FInputActionInstance;
class APlaneForCursor;

UCLASS()
class DBCPPTRY17042_API AdbPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Установка через интерфейс UE//
	//
	// Input Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EnhancedInput | Input Mapping")
	UInputMappingContext* InputMappingContext = nullptr;
	//
	// Действие Камера Горизонтальное движение
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraHorizontalMove = nullptr;
	//
	// Действие Камера Вертикальное движение
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraVerticalMove = nullptr;
	//
	// Действие Камера Приближение/Отдаление
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraZoom = nullptr;
	//
	// Действие Камера Переключение режима работы
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraFlipMode = nullptr;
	//
	// Движение камеры захватом точки
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Camera")
	UInputAction* AICameraCapturePoint = nullptr;
	//
	// Действие Инвентарь Открыть/Закрыть
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | UI")
	UInputAction* AIInventoryFlipVisible = nullptr;
	//
	// Действие Пауза
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | UI")
	UInputAction* AIGamePause = nullptr;
	//
	// Действие Пират Движение
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratMoveRight = nullptr;
	//
	// Действие Пират Прыжок
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratJump = nullptr;
	//
	// Действие Пират Создание снаярда
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratSpawnPinus = nullptr;
	//
	// Действие Пират Зарчд пинка
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratStartCharge = nullptr;
	//
	// Действие Пират Пинок
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratKick = nullptr;
	//
	// Действие Пират Активация Снаряда
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | Pirat")
	UInputAction* AIPiratActivatePinus = nullptr;
	//
	// Класс стенки
	// невидимая стена нужна, чтобы проицировать на ней положение курсора, 
	// тем самым выясняя мировые координаты последнего.
	// однако используются 2 копии, перекрывая ось Y, чтобы объекты не вылетали с карты
	UPROPERTY(EditAnywhere, Category = "EnhancedInput | PlaneForCursor")
	TSubclassOf<APlaneForCursor> ClassPlaneForCursor = nullptr;
	//_____________________________//


	// Управляемые объекты //
	//
	// Камера
	// движение + переключение режимов
	AAutoCamera* AutoCamera = nullptr;
	//
	// Контроллер виджетов уровней
	// инвентарь + пауза
	ALevelMenuController* LevelMenuController = nullptr;
	//
	// Главный персонаж
	// движение + создание снярдов + пинок
	ABladPirat* Pirat = nullptr;
	//_____________________//


	// Режимы камеры
	// 0 - Камера автоматического захвата
	// 1 - Управляемая камера
	// 2 - Камера привязанная к персонажу
	int32 CameraMode = 0;

public:
	// Привязка действий к функциям
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;

public:
	// Задать указатель на Камеру для дальнейшего управления
	void SetAutoCamera(AAutoCamera* autoCamera);
	
	// Задать указатель на Контроллер виджетов для дальнейшего управления
	void SetLevelMenuController(ALevelMenuController* levelMenuController);

	// Возвращает мировые координаты курсора
	FVector GetCursorWorldLocation();

protected:
	// Вызов функций Камеры //
	void CameraHorizontalMove(const FInputActionInstance& Instance);
	void CameraVerticalMove(const FInputActionInstance& Instance);
	void CameraSaveMouseClickPoint(const FInputActionInstance& Instance);
	void CameraMoveRelativePoint(const FInputActionInstance& Instance);
	void CameraZoom(const FInputActionInstance& Instance);
	void CameraFlipMode(const FInputActionInstance& Instance);
	//______________________//


	// Вызов функци Контроллера виджетов //
	void InventoryFlipVisible(const FInputActionInstance& Instance);
	void GamePause(const FInputActionInstance& Instance);
	//___________________________________//


	// Вызов функций главного персонажа //
	void PiratMoveRight(const FInputActionInstance& Instance);
	void PiratJump(const FInputActionInstance& Instance);
	void PiratSpawnPinus(const FInputActionInstance& Instance);
	void PiratStartCharge(const FInputActionInstance& Instance);
	void PiratKick(const FInputActionInstance& Instance);
	void PiratActivatePinus(const FInputActionInstance& Instance);
	//__________________________________//
};
