


#include "PinusHolly.h"
#include "Components/CapsuleComponent.h"
#include "Delo.h"
#include "Components/BoxComponent.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
/// Тут все как у родителя
/// 
	APinusHolly::APinusHolly() : 
		APinusBase(),
		PushPower(5000.f)
	{
		// Включение генерации собитий столкновений
		CapsuleCollision->SetNotifyRigidBodyCollision(true);
	}
///_____________///
///////////////////


//////////////////
/// Акстивация ///
///____________///
///
/// Отключение гравитации
/// 
	void APinusHolly::Activate()
	{
		// Если есть активации
		if (NumOfActivations > 0)
		{
			// Вычитаем одну активацию
			NumOfActivations--;

			// Выключаем гравитацию
			CapsuleCollision->SetEnableGravity(false);
		}
	}
///____________///
//////////////////


/////////////////////
/// Начало работы ///
///_______________///
/// 
	void APinusHolly::BeginPlay()
	{
		Super::BeginPlay();

		// Привязываем функцию столкновения к событию столкновения
		CapsuleCollision->OnComponentHit.AddDynamic(this, &APinusHolly::HitDelo);
	}
///_______________///
/////////////////////


////////////////////
/// Столкновение ///
///______________///
/// 
	void APinusHolly::HitDelo(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
	{
		// Если объект столкновения - Дело
		ADelo* delo = Cast<ADelo>(OtherActor);
		if (delo)
		{
			// Считаем вектор толчка
			FVector direction =  delo->BoxCollision->GetComponentLocation() - CapsuleCollision->GetComponentLocation();
		
			// Нормализуем
			direction.Normalize();

			// Прикладываем импульс заданной силы в посчитанном направлении
			delo->BoxCollision->AddImpulse(direction * PushPower);
		}
	}
///______________///
////////////////////

