

#include "PinusSpike.h"
#include "PinusBase.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
/// Тут все как у родителя
/// 
	APinusSpike::APinusSpike() :
		APinusBase(),
		NumSpikes(8),
		SpikePower(15000.),
		SpikeSpawnRadius(50.)
	{
		// пусто
	}
///_____________///
///////////////////


//////////////////
/// Акстивация ///
///____________///
///
/// Создание и разбрасывание снарядов вокруг себя
///
	void APinusSpike::Activate()
	{
		// Если есть активации
		if (NumOfActivations > 0)
		{
			// Вычитаем одну активацию
			NumOfActivations--;
			
			// Повтооряем для каждого создаваемого снаярда
			for (int32 i = 0; i < NumSpikes; i++)
			{
				// Угол создания
				double angle = 360 / NumSpikes * i;

				// Позиция в соответствии с углом
				double xPosition = GetActorLocation().X + cos(angle) * SpikeSpawnRadius;
				double zPosition = GetActorLocation().Z + sin(angle) * SpikeSpawnRadius;
				
				// Создание
				APinusBase* pinus = GetWorld()->SpawnActor<APinusBase>(ClassSpikes, FVector(xPosition, 0., zPosition), FRotator(angle, 0., 0.));
				
				// Задаем импульс
				pinus->CapsuleCollision->AddImpulse( FVector(cos(angle)* SpikePower, 0., sin(angle)* SpikePower) );
			}
		}
	}
///____________///
//////////////////
