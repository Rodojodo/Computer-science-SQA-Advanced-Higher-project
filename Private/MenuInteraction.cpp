// Name: Geronimo Jones   SCN: 120763237

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
#include "AeroSwift.h"
#include "NimbusRider.h"
#include "SkyRunner.h"




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
        FinalUsername->SetText(FText::FromString(MainMenuManager->GetUsername()));
    }

    // Set FinalTrack image
    FinalTrack = Cast<UImage>(GetWidgetFromName(TEXT("IFinalTrack")));
    if (FinalTrack)
    {
        UTexture2D* Texture = MainMenuManager->GetChosenTrack();
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
        UButton* BFinalBike = MainMenuManager->GetChosenBike();
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
    // Check if MainMenuManager is valid
    if (!MainMenuManager)
    {
        // Log a warning if MainMenuManager is not found
        UE_LOG(LogTemp, Warning, TEXT("AMainMenuManager not found in the world!"));
        return; // Return early to prevent potential crashes
    }

    // Check the mode to determine if we need to set the username
    if (mode == 1)
    {
        // Set the provided username to MainMenuManager->Username
        MainMenuManager->SetUsername(Username);
    }

    // Change the screen using MainMenuManager
    MainMenuManager->ChangeScreen(NextScreen);
}

void UMenuInteraction::ChangeScreenDefault(){ ChangeScreenAndSetUsername(); }



void UMenuInteraction::SelectTrack1()
{
    MainMenuManager->SetChosenTrack(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track1.track1'"))));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectTrack2()
{
    MainMenuManager->SetChosenTrack(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track2.track2'"))));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectTrack3()
{
    MainMenuManager->SetChosenTrack(Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr, TEXT("/Script/Engine.Texture2D'/Game/Images/track3.track3'"))));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectBike1()
{
    MainMenuManager->SetChosenBike(CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/IAeroSwift.IAeroSwift'"));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectBike2()
{
    MainMenuManager->SetChosenBike(CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/INimbusRider.INimbusRider'"));
    ChangeScreenAndSetUsername();
}

void UMenuInteraction::SelectBike3()
{
    MainMenuManager->SetChosenBike(CreateButtonWithImage("/Script/Engine.Texture2D'/Game/Images/ISkyRunner.ISkyRunner'"));
    ChangeScreenAndSetUsername();
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
    // Create text blocks for each element in the HoverBikeArray and set their properties
    for (int i = 0; i < ArrayLen; ++i)
    {
        FString ResultString = HoverBikeArray[i]->GetName(); // Get the name of the current HoverBike
        HoverBikeArray[i]->Destroy();
        UTextBlock* TextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass()); // Construct a new TextBlock widget
        if (TextBlock)
        {
            // Set the text of the TextBlock to the name of the HoverBike
            TextBlock->SetText(FText::FromString(ResultString));
            
            // Set the color of the text
            TextBlock->SetColorAndOpacity(FLinearColor::FromSRGBColor(FColor(0x2F, 0x3E, 0x46, 0xFF)));
            
            // Set text justification to center
            TextBlock->SetJustification(ETextJustify::Center);
            
            // Add the TextBlock as a child to the TArrayContainer
            TArrayContainer->AddChild(TextBlock);
            
            // Set properties of the TextBlock's slot (positioning and sizing)
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

    // Clear and repopulate the image container with sorted buttons
    ImageContainer->ClearChildren(); // Clear any existing children of the ImageContainer
    for (UButton* Button : ButtonArray)
    {
        ImageContainer->AddChild(Button); // Add each button from ButtonArray to the ImageContainer
        UHorizontalBoxSlot* ButtonSlot = Cast<UHorizontalBoxSlot>(Button->Slot);
        if (ButtonSlot)
        {
            // Set properties of the Button's slot (positioning and sizing)
            ButtonSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
            ButtonSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
            ButtonSlot->SetPadding(FMargin(0));
            ButtonSlot->SetSize(ESlateSizeRule::Fill);
        }
    }
}

void UMenuInteraction::QueryButtonHandler()
{
    // Check if the required text boxes are valid
    if (!UsernameTextBox || !PasswordTextBox)
    {
        // Log an error if text boxes are not found and return early
        UE_LOG(LogTemp, Error, TEXT("Text boxes not found"));
        return;
    }

    // Retrieve text input from the text boxes
    FString Username = UsernameTextBox->GetText().ToString();
    FString Password = PasswordTextBox->GetText().ToString();
    FString ConfirmPassword = ConfirmPasswordTextBox ? ConfirmPasswordTextBox->GetText().ToString() : FString();

    // Attempt to spawn an instance of ADatabaseManager
    ADatabaseManager* DatabaseManager = Cast<ADatabaseManager>(SpawnActor(ADatabaseManager::StaticClass()));
    if (!DatabaseManager)
    {
        // Log an error if ADatabaseManager fails to spawn and return early
        UE_LOG(LogTemp, Error, TEXT("ADatabaseManager not spawned successfully"));
        return;
    }

    FString QueryResult;
    // Perform login or user creation query based on the presence of ConfirmPassword
    if (ConfirmPassword.IsEmpty())
    {
        QueryResult = DatabaseManager->Login(*Username, *Password);
    }
    else
    {
        QueryResult = DatabaseManager->CreateUser(*Username, *Password, *ConfirmPassword);
    }

    // Check the query result
    if (QueryResult == "Success")
    {
        // If the query was successful, change the screen and set the username
        ChangeScreenAndSetUsername(1, *Username);
    }
    else
    {
        // If the query failed, display an error message
        IncorrectPopUp->SetText(FText::FromString(QueryResult));
        IncorrectPopUp->SetVisibility(ESlateVisibility::Visible);

        // Hide and then show the error message again after a short delay
        if (IncorrectPopUp->GetVisibility() == ESlateVisibility::Visible)
        {
            IncorrectPopUp->SetVisibility(ESlateVisibility::Hidden);
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {IncorrectPopUp->SetVisibility(ESlateVisibility::Visible);}, 0.1f, false);
        }
    }

    // Clean up by destroying the DatabaseManager instance
    DatabaseManager->Destroy();
}



AActor* UMenuInteraction::SpawnActor(TSubclassOf<AActor> ActorClass)
{
    // Get the current world
    UWorld* World = GetWorld();
    if (!World)
    {
        // Log an error if the world could not be found and return nullptr
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

