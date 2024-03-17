// Fill out your copyright notice in the Description page of Project Settings.


#include "NimbusRider.h"

// Sets default values
ANimbusRider::ANimbusRider()
{
    // Set custom values for properties
	name = "NimbusRider";
	topSpeed = 1100.f;
    acceleration = 1100.f;
    handling = 800.f;
}

// Called when the game starts or when spawned
void ANimbusRider::BeginPlay()
{
    Super::BeginPlay();
    // Add any custom initialization code here
}