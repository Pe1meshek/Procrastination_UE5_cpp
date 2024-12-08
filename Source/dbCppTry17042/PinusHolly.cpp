


#include "PinusHolly.h"
#include "Components/CapsuleComponent.h"
#include "Delo.h"
#include "Components/BoxComponent.h"


///////////////////
/// ����������� ///
///_____________///
/// 
/// ��� ��� ��� � ��������
/// 
	APinusHolly::APinusHolly() : 
		APinusBase(),
		PushPower(5000.f)
	{
		// ��������� ��������� ������� ������������
		CapsuleCollision->SetNotifyRigidBodyCollision(true);
	}
///_____________///
///////////////////


//////////////////
/// ���������� ///
///____________///
///
/// ���������� ����������
/// 
	void APinusHolly::Activate()
	{
		// ���� ���� ���������
		if (NumOfActivations > 0)
		{
			// �������� ���� ���������
			NumOfActivations--;

			// ��������� ����������
			CapsuleCollision->SetEnableGravity(false);
		}
	}
///____________///
//////////////////


/////////////////////
/// ������ ������ ///
///_______________///
/// 
	void APinusHolly::BeginPlay()
	{
		Super::BeginPlay();

		// ����������� ������� ������������ � ������� ������������
		CapsuleCollision->OnComponentHit.AddDynamic(this, &APinusHolly::HitDelo);
	}
///_______________///
/////////////////////


////////////////////
/// ������������ ///
///______________///
/// 
	void APinusHolly::HitDelo(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
	{
		// ���� ������ ������������ - ����
		ADelo* delo = Cast<ADelo>(OtherActor);
		if (delo)
		{
			// ������� ������ ������
			FVector direction =  delo->BoxCollision->GetComponentLocation() - CapsuleCollision->GetComponentLocation();
		
			// �����������
			direction.Normalize();

			// ������������ ������� �������� ���� � ����������� �����������
			delo->BoxCollision->AddImpulse(direction * PushPower);
		}
	}
///______________///
////////////////////

