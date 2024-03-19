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


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> NextScreen;
	UUserWidget* WidgetInstance;

	UFUNCTION()
	void ChangeScreen(TSubclassOf<UUserWidget> WidgetClass);


	UPROPERTY()
	FString Username;

	UPROPERTY()
	UButton* ChosenBike;

	UPROPERTY()
	UTexture2D* ChosenTrack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
