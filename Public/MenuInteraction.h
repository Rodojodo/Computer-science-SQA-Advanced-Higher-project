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

protected:
    virtual void NativeConstruct() override;


public:

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
    

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> NextScreen;
	UUserWidget* WidgetInstance;

    UFUNCTION()
    AActor* SpawnActor(TSubclassOf<AActor> ActorClass);

    UFUNCTION()
	UButton* CreateButtonWithImage(FString Path, int bike = 0);

protected:
    UFUNCTION()
    void SortBikeAndSetLooks(int SortingCriteria);

    UFUNCTION()
    void SortSpeed();

    UFUNCTION()
    void SortAcceleration();

    UFUNCTION()
    void SortHandling();

    UFUNCTION()
    void ChangeScreenDefault();

    UFUNCTION()
    void SelectBike1();

    UFUNCTION()
    void SelectBike2();

    UFUNCTION()
    void SelectBike3();

    UFUNCTION()
    void SelectTrack1();

    UFUNCTION()
    void SelectTrack2();

    UFUNCTION()
    void SelectTrack3();

    UFUNCTION()
    void ChangeScreenAndSetUsername(int mode = 0, FString Username = "");
    
    UFUNCTION()
    void QueryButtonHandler();

private:
    UPROPERTY()
    AMainMenuManager* MainMenuManager;
};
