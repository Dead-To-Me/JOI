// Fill out your copyright notice in the Description page of Project Settings.


#include "JOIMusicManager.h"

#include "Components/AudioComponent.h"

// Sets default values
AJOIMusicManager::AJOIMusicManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Music"));
    SetRootComponent(AudioComponent);

    Scale = 1;
    Exponent = 0.5;

}

// Called when the game starts or when spawned
void AJOIMusicManager::BeginPlay()
{
    Super::BeginPlay();

}


void AJOIMusicManager::ConvertSpectrumToBars(const TArray<float>& MagnitudeSpectrum, UPARAM(Ref) TArray<float>& Out)
{
    int32 SourceSize = MagnitudeSpectrum.Num();
    int32 GroupSize = FMath::CeilToInt(static_cast<float>(SourceSize) / static_cast<float>(Out.Num()));

    for (int32 BarIndex = 0; BarIndex < Out.Num(); BarIndex++)
    {
        int32 Start = BarIndex * GroupSize;
        int32 End = FMath::Min(Start + GroupSize, SourceSize);

        float Sum = 0.0f;
        for (int32 i = Start; i < End; i++)
        {
            Sum += MagnitudeSpectrum[i];
        }
        if (Out.IsValidIndex(BarIndex))
        {
            Out[BarIndex] = Sum / (End - Start);
        }
    }
}


void AJOIMusicManager::NormalizeMusicBars(UPARAM(Ref) TArray<float>& MusicBars)
{
    for (int32 i = 0; i < MusicBars.Num(); i++)
    {
        float NewValue = FMath::Pow(MusicBars[i], Exponent);
        NewValue = FMath::LogX(10.0f, NewValue * Scale + 1.0f);
        MusicBars[i] = NewValue;
        //MusicBars[i] = MusicBars[i] * 0.9f + NewValue * 0.1f;
    }
}
