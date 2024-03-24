// Name: Geronimo Jones   SCN: 120763237

#include "HoverBike.h"
// Sets default values
AHoverBike::AHoverBike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}
FString AHoverBike::GetName() const
{
    return name; // Default top speed
}

float AHoverBike::GetTopSpeed() const
{
    return topSpeed; // Default top speed
}

float AHoverBike::GetAcceleration() const
{
    return acceleration; // Default top speed
}

float AHoverBike::GetHandling() const
{
    return handling; // Default top speed
}