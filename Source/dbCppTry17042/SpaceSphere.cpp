

#include "SpaceSphere.h"

///////////////////
/// Конструктор ///
///_____________///
/// 
	ASpaceSphere::ASpaceSphere() :
		MaxRotationSpeed(3.f)
	{
		SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootSphere"));
		SphereComponent->SetCastShadow(false);

		RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));

		SetRootComponent(SphereComponent);
	}
///_____________///
///////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void ASpaceSphere::BeginPlay()
	{
		Super::BeginPlay();
	
		// Выбираем случайный фон
		if (!SpaceSkins.IsEmpty())
		{
			int32 numRandomSkin = FMath::RandRange(0, SpaceSkins.Num() - 1);
			SphereComponent->SetMaterial(0, SpaceSkins[numRandomSkin]);
		}

		// Поворачиваемся в случайно направлении
		const float pitch = FMath::FRandRange(-180.f, 180.f);
		const float yaw = FMath::FRandRange(-180.f, 180.f);
		const float roll = FMath::FRandRange(-180.f, 180.f);
		SetActorRotation(FRotator(pitch, yaw, roll));

		// Начинаем вращаться в случайном направленини
		const float rotationPitch = FMath::FRandRange(-MaxRotationSpeed, MaxRotationSpeed);
		const float rotationYaw = FMath::FRandRange(-MaxRotationSpeed, MaxRotationSpeed);
		const float rotationRoll = FMath::FRandRange(-MaxRotationSpeed, MaxRotationSpeed);
		RotatingMovementComponent->RotationRate = FRotator(rotationPitch, rotationYaw, rotationRoll);
	}
///_______________///
/////////////////////



