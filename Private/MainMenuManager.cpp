// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MenuInteraction.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMainMenuManager::AMainMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();
	ChangeScreen(NextScreen);
}

// Called every frame
void AMainMenuManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}




// In a function where you want to add the widget to the viewport
void AMainMenuManager::ChangeScreen(TSubclassOf<UUserWidget> WidgetClass)
{
    UE_LOG(LogTemp, Log, TEXT("Changing Screen Phase:1"));
    APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerControllerRef->SetShowMouseCursor(true);
    // Make sure WidgetClass is set
    if (WidgetClass)
    {
        UE_LOG(LogTemp, Log, TEXT("Changing Screen Phase:2"));
        // Get the first player controller from the world
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

        // Create an instance of the widget
        WidgetInstance = UWidgetBlueprintLibrary::Create(this, WidgetClass, PlayerController);

        // Check if the instance is valid
        if (WidgetInstance)
        {
            // Add the widget to the viewport
            WidgetInstance->AddToViewport();
        }
    }
    else{UE_LOG(LogTemp, Error, TEXT("Widget class not true"))}
}