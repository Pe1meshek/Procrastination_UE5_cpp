/*
������ ������

��������� - ������������� � ��������
*/
#pragma once

#include "CoreMinimal.h"
#include "PinusBase.h"
#include "PinusHell.generated.h"


UCLASS()
class DBCPPTRY17042_API APinusHell : public APinusBase
{
	GENERATED_BODY()
	
public:
	APinusHell();

	// ��������� (���������������)
	void Activate() override;
};
