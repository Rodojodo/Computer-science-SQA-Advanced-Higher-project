// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HoverBike.h"
#include "SkyRunner.generated.h"

/**
 * 
 */
UCLASS()
class ASkyRunner : public AHoverBike
{
	GENERATED_BODY()
	
public:
    // Sets default values for this hoverbike
    ASkyRunner();

    // // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
