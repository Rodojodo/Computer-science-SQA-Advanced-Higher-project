// Name: Geronimo Jones   SCN: 120763237

#include "NimbusRider.h"

// Sets default values
ANimbusRider::ANimbusRider()
{
    // Set custom values for properties
	name = "NimbusRider";
	topSpeed = 1100.f;
    acceleration = 1100.f;
    handling = 800.f;
    // UE_LOG(LogTemp, Log, TEXT("%s created, parameters: %f, %f, %f"), *name, topSpeed, acceleration, handling);
}

// Called when the game starts or when spawned
void ANimbusRider::BeginPlay()
{
    Super::BeginPlay();
    // Add any custom initialization code here
}