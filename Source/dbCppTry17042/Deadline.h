/*
Дедлайн

Сфера, которая постепенно сжимается, уничтожая все снаряды, которые выходят за её границы.
Если Дело покинет границы сферы - игра будет проиграна.

Гиена слева должна быть анимарована, пока лишь статичный спрайт
Вообще концепция дедлайна - это линия, которая переплетениями складывается в силует околотакойгиены, наматывающей кусочек себя (границы сферы)
на бабину с ручкой (которые тоже являются частью этой единой ЛИНИИ), тем самым затягивая петлю.
Т.е Гиена, бабина и кольцо - это все Дедлайн, который по задумке должен быть нарисован одной непрерывной линией.

*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Deadline.generated.h"

class USceneComponent;
class UPaperFlipbookComponent;

UCLASS()
class DBCPPTRY17042_API ADeadline : public AActor
{
	GENERATED_BODY()
	
protected:
	// Центр сферы = центр объекта
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	// Сфера 
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MashComponent;

	// Декоративная гиена
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* FlipbookConmponent;

	// Скорость сжатия сферы
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	float SpeedCompression;

	// Стартовый размер сферы
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	double DeadlineScale;

	// коф связывающий скорость движения декоративной гиены со скоростью сжатия
	const float KofOfSpeedVisual = 250.f;


public:	
	ADeadline();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


protected:
	// Проверка объекта, вышедшего за пределы сферы
	UFUNCTION()
	void OverlapCheck(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
