// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoverBike.generated.h"

UCLASS()
class AHoverBike : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHoverBike();
	
	UFUNCTION()
	virtual FString GetName() const;

	UFUNCTION()
	virtual float GetTopSpeed() const;

	UFUNCTION()
	virtual float GetAcceleration() const;

	UFUNCTION()
	virtual float GetHandling() const;
	


protected:

	UPROPERTY()
	FString name;

	UPROPERTY()
	float topSpeed;

	UPROPERTY()
	float acceleration;

	UPROPERTY()
	float handling;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
