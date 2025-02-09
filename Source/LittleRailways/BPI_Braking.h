// Copyright Stevens Studios, all rights reserved
// Written by Thomas Stevens

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPI_Braking.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPI_Braking : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LITTLERAILWAYS_API IBPI_Braking
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControls")
	void Brake(int passedForce);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControls")
	void Regulator(int passedTorque);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LocoControls")
	void SetReverser(int passedDetent);
};