

#include "PinusSpike.h"
#include "PinusBase.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// ����������� ///
///_____________///
/// 
/// ��� ��� ��� � ��������
/// 
	APinusSpike::APinusSpike() :
		APinusBase(),
		NumSpikes(8),
		SpikePower(15000.),
		SpikeSpawnRadius(50.)
	{
		// �����
	}
///_____________///
///////////////////


//////////////////
/// ���������� ///
///____________///
///
/// �������� � ������������� �������� ������ ����
///
	void APinusSpike::Activate()
	{
		// ���� ���� ���������
		if (NumOfActivations > 0)
		{
			// �������� ���� ���������
			NumOfActivations--;
			
			// ���������� ��� ������� ������������ �������
			for (int32 i = 0; i < NumSpikes; i++)
			{
				// ���� ��������
				double angle = 360 / NumSpikes * i;

				// ������� � ������������ � �����
				double xPosition = GetActorLocation().X + cos(angle) * SpikeSpawnRadius;
				double zPosition = GetActorLocation().Z + sin(angle) * SpikeSpawnRadius;
				
				// ��������
				APinusBase* pinus = GetWorld()->SpawnActor<APinusBase>(ClassSpikes, FVector(xPosition, 0., zPosition), FRotator(angle, 0., 0.));
				
				// ������ �������
				pinus->CapsuleCollision->AddImpulse( FVector(cos(angle)* SpikePower, 0., sin(angle)* SpikePower) );
			}
		}
	}
///____________///
//////////////////
