

#include "PinusHell.h"
#include "Components/CapsuleComponent.h"


///////////////////
/// ����������� ///
///_____________///
/// 
/// ��� ��� ��� � ��������
/// 
	APinusHell::APinusHell() : APinusBase()
	{
	}
///_____________///
///////////////////


//////////////////
/// ���������� ///
///____________///
///
/// ���������� � ��������
/// 
	void APinusHell::Activate()
	{
		// ���� ���� ���������
		if(NumOfActivations > 0)
		{
			// �������� ���� ���������
			NumOfActivations--;

			// ����������� �� 100% �� ��������� (�� 1000%)
			CapsuleCollision->SetWorldScale3D(CapsuleCollision->GetComponentScale() + FVector(1., 0., 1.));
		}
	}
///____________///
//////////////////

 