// Fill out your copyright notice in the Description page of Project Settings.

#include "HoverBike.h"
// Sets default values
AHoverBike::AHoverBike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	name = "Bike";
	topSpeed = 1000.f;
    acceleration = 1000.f;
    handling = 1000.f;

}
FString AHoverBike::GetName() const
{
    // Implement default behavior here if needed
    return name; // Default top speed
}

float AHoverBike::GetTopSpeed() const
{
    // Implement default behavior here if needed
    return topSpeed; // Default top speed
}

float AHoverBike::GetAcceleration() const
{
    // Implement default behavior here if needed
    return acceleration; // Default top speed
}

float AHoverBike::GetHandling() const
{
    // Implement default behavior here if needed
    return handling; // Default top speed
}

// Called when the game starts or when spawned
void AHoverBike::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoverBike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
