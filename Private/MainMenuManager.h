// Name: Geronimo Jones   SCN: 120763237

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MainMenuManager.generated.h"

UCLASS()
class AMainMenuManager : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AMainMenuManager();


	UFUNCTION()
	void ChangeScreen(TSubclassOf<UUserWidget> WidgetClass);


	UFUNCTION()
	FString GetUsername();

	UFUNCTION()
	void SetUsername(FString NewUsername);

	UFUNCTION()
	UButton* GetChosenBike();

	UFUNCTION()
	void SetChosenBike(UButton* NewChosenBike);

	UFUNCTION()
	UTexture2D* GetChosenTrack();

	UFUNCTION()
	void SetChosenTrack(UTexture2D* NewChosenTrack);


private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> NextScreen;
	UUserWidget* WidgetInstance;

	UPROPERTY()
	FString Username;

	UPROPERTY()
	UButton* ChosenBike;

	UPROPERTY()
	UTexture2D* ChosenTrack;
};
