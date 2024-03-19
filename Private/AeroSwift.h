// Name: Geronimo Jones   SCN: 120763237

#pragma once

#include "CoreMinimal.h"
#include "HoverBike.h"
#include "AeroSwift.generated.h"

/**
 * 
 */
UCLASS()
class AAeroSwift : public AHoverBike
{
	GENERATED_BODY()
	
public:
    // Sets default values for this hoverbike
    AAeroSwift();

    // // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
