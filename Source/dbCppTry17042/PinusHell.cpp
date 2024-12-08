

#include "PinusHell.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// Конструктор ///
///_____________///
/// 
/// Тут все как у родителя
/// 
	APinusHell::APinusHell() : APinusBase()
	{
	}
///_____________///
///////////////////


//////////////////
/// Акстивация ///
///____________///
///
/// Увеличение в размерах
/// 
	void APinusHell::Activate()
	{
		// Если есть активации
		if(NumOfActivations > 0)
		{
			// Вычитаем одну активацию
			NumOfActivations--;

			// Увеличиваем на 100% от оригинала (на 1000%)
			CapsuleCollision->SetWorldScale3D(CapsuleCollision->GetComponentScale() + FVector(1., 0., 1.));
		}
	}
///____________///
//////////////////

 