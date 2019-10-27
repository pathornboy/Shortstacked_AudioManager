// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"
#include "SHST_AudioManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class SHORTSTACKED_API USHST_AudioManager : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USHST_AudioManager();
	UFUNCTION(BlueprintCallable)
		void PlayAudio(FString AudioName); //Play 2D Audio, fire and forget
	UFUNCTION(BlueprintCallable)
		void PlayAudioAtLocation(FString AudioName, USoundAttenuation* Attenuationer, FVector Location); //Play 3D Audio at the specified location, fire and forget
	UFUNCTION(BlueprintCallable)
		void PauseAllAudio(); // Pause all audio
	UFUNCTION(BlueprintCallable)
		void ResumeAllAudio(); //Resume all audio
	UFUNCTION(BlueprintCallable)
		void StopAllAudio(); //Stop all audio
	UFUNCTION(BlueprintCallable)
		void PlayMusic(FString AudioName); //Play Music
	UFUNCTION(BlueprintCallable)
		void StopMusic(); //Play Music
	UFUNCTION(BlueprintCallable)
		void PauseMusic(); // Stop the Music
	UFUNCTION(BlueprintCallable)
		void ResumeMusic(); //Resume the Music
	UFUNCTION(BlueprintCallable)
		void CrossfadeMusic(FString AudioName,float duration); //Change Music by crossfading

protected:
	// Called when the game starts

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UAudioComponent*> m_ActiveAudio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UAudioComponent*> m_ActiveMusic;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	TArray< TSubclassOf<USoundClass> > m_SoundClips;
	UFUNCTION()
		void CheckForStoppedUAudio(); //Check if there is Stopped UAudio and delete it from the list


	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
