// Name: Geronimo Jones   SCN: 120763237

#include "MainMenuManager.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "MenuInteraction.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AMainMenuManager::AMainMenuManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AMainMenuManager::BeginPlay()
{
	Super::BeginPlay();
	ChangeScreen(NextScreen);
}

void AMainMenuManager::ChangeScreen(TSubclassOf<UUserWidget> WidgetClass)
{
    APlayerController* PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerControllerRef->SetShowMouseCursor(true);
    // Make sure WidgetClass is set
    if (WidgetClass)
    {
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

FString AMainMenuManager::GetUsername(){return Username;}

void AMainMenuManager::SetUsername(FString NewUsername){Username = NewUsername;}

UButton* AMainMenuManager::GetChosenBike(){return ChosenBike;}

void AMainMenuManager::SetChosenBike(UButton* NewChosenBike){ChosenBike = NewChosenBike;}

UTexture2D* AMainMenuManager::GetChosenTrack(){return ChosenTrack;}

void AMainMenuManager::SetChosenTrack(UTexture2D* NewChosenTrack){ChosenTrack = NewChosenTrack;}