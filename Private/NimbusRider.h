// Name: Geronimo Jones   SCN: 120763237

#pragma once

#include "CoreMinimal.h"
#include "HoverBike.h"
#include "NimbusRider.generated.h"

/**
 * 
 */
UCLASS()
class ANimbusRider : public AHoverBike
{
	GENERATED_BODY()
	
public:
    // Sets default values for this hoverbike
    ANimbusRider();

    // // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
