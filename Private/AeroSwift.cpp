// Name: Geronimo Jones   SCN: 120763237


#include "AeroSwift.h"


// Sets default values
AAeroSwift::AAeroSwift()
{
    // Set custom values for properties
	name = "AeroSwift";
	topSpeed = 750.f;
    acceleration = 1000.f;
    handling = 1250.f;
    // UE_LOG(LogTemp, Log, TEXT("%s created, parameters: %f, %f, %f"), *name, topSpeed, acceleration, handling);
}

// Called when the game starts or when spawned
void AAeroSwift::BeginPlay()
{
    Super::BeginPlay();
    // Add any custom initialization code here
}