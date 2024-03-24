// Name: Geronimo Jones   SCN: 120763237

#include "SkyRunner.h"

// Sets default values
ASkyRunner::ASkyRunner()
{
    // Set custom values for properties
	name = "SkyRunner";
	topSpeed = 1500.f;
    acceleration = 750.f;
    handling = 750.f;
    // UE_LOG(LogTemp, Log, TEXT("%s created, parameters: %f, %f, %f"), *name, topSpeed, acceleration, handling);
}

// Called when the game starts or when spawned
void ASkyRunner::BeginPlay()
{
    Super::BeginPlay();
    // Add any custom initialization code here
}