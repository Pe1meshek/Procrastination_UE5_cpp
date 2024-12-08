
#include "PlaneForCursor.h"


///////////////////
/// ����������� ///
///_____________///
/// 
	APlaneForCursor::APlaneForCursor()
	{
		MashComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootPlane"));
		SetRootComponent(MashComponent);
	
		// ������ ������ ���� ���������, �������
		MashComponent->SetVisibility(false);

		// ��������� ��������
		MashComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	}
///_____________///
///////////////////
