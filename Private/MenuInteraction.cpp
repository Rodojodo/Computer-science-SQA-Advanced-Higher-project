// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuInteraction.h"
#include "MainMenuManager.h"
#include "DatabaseManager.h"
#include "Engine/World.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "NimbusRider.h"
#include "SkyRunner.h"
#include "AeroSwift.h"



void UMenuInteraction::NativeConstruct()
{
    Super::NativeConstruct();

    MainMenuManager = Cast<AMainMenuManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMainMenuManager::StaticClass()));

    // Widget assignments
    UsernameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ETBUsername")));
    PasswordTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ETBPassword")));
    ConfirmPasswordTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ETBConfirmPassword")));
    IncorrectPopUp = Cast<UTextBlock>(GetWidgetFromName(TEXT("TIncorrect")));
    TArrayContainer = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("BikeNameContainer")));
    ImageContainer = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("BikeImageContainer")));

    // Sorting handling if ImageContainer exists
    if (ImageContainer)
    {
        SortHandling();
    }

    // Set FinalUsername text
    FinalUsername = Cast<UTextBlock>(GetWidgetFromName(TEXT("TFinalUsername")));
    if (FinalUsername)
    {
        FinalUsername->SetText(FText::FromString(MainMenuManager->Username));
    }

    // Set FinalTrack image
    FinalTrack = Cast<UImage>(GetWidgetFromName(TEXT("IFinalTrack")));
    if (FinalTrack)
    {
        UTexture2D* Texture = MainMenuManager->ChosenTrack;
        if (Texture)
        {
            FSlateBrush Brush;
            Brush.SetResourceObject(Texture);
            Brush.ImageSize.X = 500.0f;
            Brush.ImageSize.Y = 500.0f;
            FinalTrack->SetBrush(Brush);
            FinalTrack->SetOpacity(1.0f);
            FinalTrack->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load texture in Final track loading"));
        }
    }

    // Set chosen bike button
    ChosenContainer = Cast<UHorizontalBox>(GetWidgetFromName(TEXT("ChosenContainer")));
    if (ChosenContainer)
    {
        UButton* BFinalBike = MainMenuManager->ChosenBike;
        ChosenContainer->AddChild(BFinalBike);
        UHorizontalBoxSlot* ButtonSlot = Cast<UHorizontalBoxSlot>(BFinalBike->Slot);
        if (ButtonSlot)
        {
            ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
            ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
            ButtonSlot->SetPadding(FMargin(0));
            ButtonSlot->SetSize(ESlateSizeRule::Fill);
        }
    }

    // Button event bindings
    if (UButton* BDB = Cast<UButton>(GetWidgetFromName(TEXT("BDB"))))
    {
        BDB->OnClicked.AddDynamic(this, &UMenuInteraction::QueryButtonHandler);
    }

    if (UButton* BChangeScreen = Cast<UButton>(GetWidgetFromName(TEXT("BChangeScreen"))))
    {
        BChangeScreen->OnClicked.AddDynamic(this, &UMenuInteraction::ChangeScreenDefault);
    }

    if (UButton* BSortSpeed = Cast<UButton>(GetWidgetFromName(TEXT("BSortSpeed"))))
    {
        BSortSpeed->OnClicked.AddDynamic(this, &UMenuInteraction::SortSpeed);
    }

    if (UButton* BSortAcceleration = Cast<UButton>(GetWidgetFromName(TEXT("BSortAcceleration"))))
    {
        BSortAcceleration->OnClicked.AddDynamic(this, &UMenuInteraction::SortAcceleration); 
    }

    if (UButton* BSortHandling = Cast<UButton>(GetWidgetFromName(TEXT("BSortHandling"))))
    {
        BSortHandling->OnClicked.AddDynamic(this, &UMenuInteraction::SortHandling);
    }

    if (UButton* BTrack1 = Cast<UButton>(GetWidgetFromName(TEXT("BTrack1"))))
    {
        BTrack1->OnClicked.AddDynamic(this, &UMenuInteraction::SelectTrack1);
    }

    if (UButton* BTrack2 = Cast<UButton>(GetWidgetFromName(TEXT("BTrack2"))))
    {
        BTrack2->OnClicked.AddDynamic(this, &UMenuInteraction::SelectTrack2);
    }

    if (UButton* BTrack3 = Cast<UButton>(GetWidgetFromName(TEXT("BTrack3"))))
    {
        BTrack3->OnClicked.AddDynamic(this, &UMenuInteraction::SelectTrack3);
    }
}



void UMenuInteraction::ChangeScreenAndSetUsername(int mode, FString Username)
{
    UE_LOG(LogTemp, Log, TEXT("ChangingScreen"));


    if (!MainMenuManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("AMainMenuManager not found in the world!"));
        return;
    }

    if (mode == 1)
    {
        MainMenuManager->Username = Username;
    }

    MainMenuManager->ChangeScreen(NextScreen);
}

void UMenuInteraction::ChangeScreenDefault(){ ChangeScreenAndSetUsername(); }



void UMenuInteraction::SelectTrack1()
{
    MainMenuManager->ChosenTrack = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track1.track1'")));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectTrack2()
{
    MainMenuManager->ChosenTrack = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track2.track2'")));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectTrack3()
{
    MainMenuManager->ChosenTrack = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track3.track3'")));
    ChangeScreenAndSetUsername();
}


void UMenuInteraction::SelectBike1()
{
    ChangeScreenAndSetUsername();
    MainMenuManager->ChosenBike = CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/IAeroSwift.IAeroSwift'");
}

void UMenuInteraction::SelectBike2()
{
    ChangeScreenAndSetUsername();
    MainMenuManager->ChosenBike = CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/INimbusRider.INimbusRider'");
}

void UMenuInteraction::SelectBike3()
{
    ChangeScreenAndSetUsername();
    MainMenuManager->ChosenBike = CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/ISkyRunner.ISkyRunner'");
}


void UMenuInteraction::SortSpeed() { SortBikeAndSetLooks(1); }

void UMenuInteraction::SortAcceleration() { SortBikeAndSetLooks(2); }

void UMenuInteraction::SortHandling() { SortBikeAndSetLooks(3); }



void UMenuInteraction::SortBikeAndSetLooks(int SortingCriteria)
{
    if (!ImageContainer || !TArrayContainer)
    {
        UE_LOG(LogTemp, Error, TEXT("ImageContainer or TArrayContainer not found"));
        return;
    }

    TArray<UButton*> ButtonArray;
    TArray<AHoverBike*> HoverBikeArray;

    // Create buttons and spawn hover bikes
    ButtonArray.Add(CreateButtonWithImage("/Game/Images/IAeroSwift.IAeroSwift", 1));
    ButtonArray.Add(CreateButtonWithImage("/Game/Images/INimbusRider.INimbusRider", 2));
    ButtonArray.Add(CreateButtonWithImage("/Game/Images/ISkyRunner.ISkyRunner", 3));

    HoverBikeArray.Add(Cast<AAeroSwift>(SpawnActor(AAeroSwift::StaticClass())));
    HoverBikeArray.Add(Cast<ANimbusRider>(SpawnActor(ANimbusRider::StaticClass())));
    HoverBikeArray.Add(Cast<ASkyRunner>(SpawnActor(ASkyRunner::StaticClass())));

    // Sort based on the sorting criterion
    int ArrayLen = HoverBikeArray.Num();
    bool Swapped = true;
    int StopIndex = ArrayLen;

    while (Swapped && StopIndex >= 0)
    {
        Swapped = false;
        for (int i = 0; i < (StopIndex - 1); i++)
        {
            float CurrentValue = 0.0f;
            float NextValue = 0.0f;

            switch (SortingCriteria)
            {
            case 1: // Sort by top speed
                CurrentValue = HoverBikeArray[i]->GetTopSpeed();
                NextValue = HoverBikeArray[i + 1]->GetTopSpeed();
                break;
            case 2: // Sort by acceleration
                CurrentValue = HoverBikeArray[i]->GetAcceleration();
                NextValue = HoverBikeArray[i + 1]->GetAcceleration();
                break;
            case 3: // Sort by handling
                CurrentValue = HoverBikeArray[i]->GetHandling();
                NextValue = HoverBikeArray[i + 1]->GetHandling();
                break;
            default: // Invalid criterion
                UE_LOG(LogTemp, Warning, TEXT("Invalid sorting criteria!"));
                return;
            }

            if (CurrentValue < NextValue)
            {
                Swap(HoverBikeArray[i], HoverBikeArray[i + 1]);
                Swap(ButtonArray[i], ButtonArray[i + 1]);
                Swapped = true;
            }
        }
        StopIndex -= 1;
    }
    TArrayContainer->ClearChildren();
    // Create text blocks and set their properties
    for (int i = 0; i < ArrayLen; ++i)
    {
        FString ResultString = HoverBikeArray[i]->GetName(); // Assuming GetName() returns the name
        UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
        if (TextBlock)
        {
            TextBlock->SetText(FText::FromString(ResultString));
            TextBlock->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor(0x2F, 0x3E, 0x46, 0xFF)));
            TextBlock->SetJustification(ETextJustify::Center);
            TArrayContainer->AddChild(TextBlock);
            UHorizontalBoxSlot* TextSlot = Cast<UHorizontalBoxSlot>(TextBlock->Slot);
            if (TextSlot)
            {
                TextSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
                TextSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
                TextSlot->SetPadding(FMargin(0));
                TextSlot->SetSize(ESlateSizeRule::Fill);
            }
        }
    }

    // Clear and populate the image container with sorted buttons
    ImageContainer->ClearChildren();
    for (UButton* Button : ButtonArray)
    {
        ImageContainer->AddChild(Button);
        UHorizontalBoxSlot* ButtonSlot = Cast<UHorizontalBoxSlot>(Button->Slot);
        if (ButtonSlot)
        {
            ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
            ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
            ButtonSlot->SetPadding(FMargin(0));
            ButtonSlot->SetSize(ESlateSizeRule::Fill);
        }
    }
}

void UMenuInteraction::QueryButtonHandler()
{
    UE_LOG(LogTemp, Log, TEXT("Button pressed!"));

    if (!UsernameTextBox || !PasswordTextBox)
    {
        UE_LOG(LogTemp, Error, TEXT("Text boxes not found"));
        return;
    }

    FString Username = UsernameTextBox->GetText().ToString();
    FString Password = PasswordTextBox->GetText().ToString();
    FString ConfirmPassword = ConfirmPasswordTextBox ? ConfirmPasswordTextBox->GetText().ToString() : FString();

    ADatabaseManager* DatabaseManager = Cast<ADatabaseManager>(SpawnActor(ADatabaseManager::StaticClass()));
    if (!DatabaseManager)
    {
        UE_LOG(LogTemp, Error, TEXT("ADatabaseManager not spawned successfully"));
        return;
    }

    FString QueryResult;
    if (ConfirmPassword.IsEmpty())
    {
        QueryResult = DatabaseManager->Login(*Username, *Password);
    }
    else
    {
        QueryResult = DatabaseManager->CreateUser(*Username, *Password, *ConfirmPassword);
    }

    if (QueryResult == "Success")
    {
        ChangeScreenAndSetUsername(1, *Username);
    }
    else
    {
        IncorrectPopUp->SetText(FText::FromString(QueryResult));
        IncorrectPopUp->SetVisibility(ESlateVisibility::Visible);

        if (IncorrectPopUp->GetVisibility() == ESlateVisibility::Visible)
        {
            IncorrectPopUp->SetVisibility(ESlateVisibility::Hidden);
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {IncorrectPopUp->SetVisibility(ESlateVisibility::Visible);}, 0.1f, false);
        }
    }

    DatabaseManager->Destroy();
}



AActor* UMenuInteraction::SpawnActor(TSubclassOf<AActor> ActorClass)
{
    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Error, TEXT("World could not be found when spawning actor"));
        return nullptr;
    }

    // Define the spawn parameters
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    // Spawn and return the actor
    return World->SpawnActor<AActor>(ActorClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
}

UButton* UMenuInteraction::CreateButtonWithImage(FString Path, int bike)
{
    UButton* NewButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass());

    if (NewButton)
    {

        // Set button background color
        NewButton->SetBackgroundColor(FLinearColor::Black);

        UImage* ButtonImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());

        if (ButtonImage)
        {
            UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path));

            if (Texture)
            {
                // Set brush image
                FSlateBrush Brush;
                Brush.SetResourceObject(Texture);
                Brush.ImageSize.X = 500.0f;
                Brush.ImageSize.Y = 500.0f;
                ButtonImage->SetBrush(Brush);
                ButtonImage->SetOpacity(1.0f);

                // Set button image visibility
                ButtonImage->SetVisibility(ESlateVisibility::Visible);
            }

            // Add image to button
            NewButton->AddChild(ButtonImage);

            // Set button slot properties
            UHorizontalBoxSlot* ButtonSlot = Cast<UHorizontalBoxSlot>(NewButton->Slot);
            if (ButtonSlot)
            {
                ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
                ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
                ButtonSlot->SetPadding(FMargin(0));
            }
        }
        if (bike == 1)
        {
            NewButton->OnClicked.AddDynamic(this, &UMenuInteraction::SelectBike1);
        }
        else if (bike == 2)
        {
            NewButton->OnClicked.AddDynamic(this, &UMenuInteraction::SelectBike2);
        }
        else if (bike == 3)
        {
            NewButton->OnClicked.AddDynamic(this, &UMenuInteraction::SelectBike3);
        }
        
        return NewButton;
    }
    else
    {
        return nullptr;
    }
}
