// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyRunner.h"

// Sets default values
ASkyRunner::ASkyRunner()
{
    // Set custom values for properties
	name = "SkyRunner";
	topSpeed = 1500.f;
    acceleration = 750.f;
    handling = 750.f;
}

// Called when the game starts or when spawned
void ASkyRunner::BeginPlay()
{
    Super::BeginPlay();
    // Add any custom initialization code here
}