// Name: Geronimo Jones   SCN: 120763237

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DatabaseManager.generated.h"

/**
 * 
 */
UCLASS()
class ADatabaseManager : public AActor
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	ADatabaseManager();


	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "SQL Queries")
	FString CreateUser(FString username, FString password, FString confirmedPass);


	UFUNCTION(BlueprintCallable, Category = "SQL Queries")
	FString Login(FString username, FString password);




protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




private:
// 	UFUNCTION()
// 	FString HashPassword(FString password);
};