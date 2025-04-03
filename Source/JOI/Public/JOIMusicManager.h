// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JOIMusicManager.generated.h"

UCLASS()
class JOI_API AJOIMusicManager : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    float Scale;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    float Exponent;

public:
    // Sets default values for this actor's properties
    AJOIMusicManager();

    UFUNCTION(BlueprintCallable)
    void ConvertSpectrumToBars(const TArray<float>& MagnitudeSpectrum, UPARAM(Ref) TArray<float>& Out);

    UFUNCTION(BlueprintCallable)
    void NormalizeMusicBars(UPARAM(Ref) TArray<float>& MusicBars);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
};
