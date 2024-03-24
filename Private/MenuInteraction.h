// Name: Geronimo Jones   SCN: 120763237

#pragma once

#include "CoreMinimal.h"
#include "MainMenuManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "MenuInteraction.generated.h"


/**
 * 
 */
UCLASS()
class PLEASEPLEASEPLEASE_API UMenuInteraction : public UUserWidget
{
    GENERATED_BODY()


public:
    UFUNCTION()
    AActor* SpawnActor(TSubclassOf<AActor> ActorClass);
    

private:
    virtual void NativeConstruct() override;



    UFUNCTION()
    void ChangeScreenAndSetUsername(int mode = 0, FString Username = "");
    
    UFUNCTION()
    void ChangeScreenDefault();



    UFUNCTION()
    void SelectTrack1();

    UFUNCTION()
    void SelectTrack2();

    UFUNCTION()
    void SelectTrack3();

    UFUNCTION()
    void SelectBike1();

    UFUNCTION()
    void SelectBike2();

    UFUNCTION()
    void SelectBike3();


    UFUNCTION()
    void SortSpeed();

    UFUNCTION()
    void SortAcceleration();

    UFUNCTION()
    void SortHandling();



    UFUNCTION()
    void SortBikeAndSetLooks(int SortingCriteria);

    UFUNCTION()
    void QueryButtonHandler();



    UFUNCTION()
	UButton* CreateButtonWithImage(FString Path, int bike = 0);



    UPROPERTY()
    AMainMenuManager* MainMenuManager;

    UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> NextScreen;
	UUserWidget* WidgetInstance;


    UPROPERTY()
    UEditableTextBox* UsernameTextBox;

    UPROPERTY()
    UEditableTextBox* PasswordTextBox;

    UPROPERTY()
    UEditableTextBox* ConfirmPasswordTextBox;

    UPROPERTY()
    UTextBlock* IncorrectPopUp;

    UPROPERTY()
    UTextBlock* FinalUsername;

    UPROPERTY()
    UHorizontalBox* TArrayContainer;

    UPROPERTY()
    UHorizontalBox* ImageContainer;

    UPROPERTY()
    UHorizontalBox* ChosenContainer;

    UPROPERTY()
    UImage* FinalTrack;
};
