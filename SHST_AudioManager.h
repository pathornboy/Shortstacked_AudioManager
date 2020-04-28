// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"
//#include "FMODEvent.h"
//#include "FMODBlueprintStatics.h"
#include "SHST_AudioManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class SHORTSTACKED_API USHST_AudioManager : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USHST_AudioManager();
	UFUNCTION(BlueprintCallable)
		void LoadAudio(FString AudioName); //Load Audio into map for optimization
	UFUNCTION(BlueprintCallable)
		void LoadMusic(FString AudioName,float duration=0.0f); //Load Audio into map for optimization
	UFUNCTION(BlueprintCallable)
		void LoadAttenuation(FString AudioName); //Load Audio into map for optimization
	UFUNCTION(BlueprintCallable)
		void PlayAudio(FString AudioName); //Play 2D Audio, fire and forget
	UFUNCTION(BlueprintCallable)
		void PlayAudioAtLocation(FString AudioName, FString AttenuationName, FVector Location); //Play 3D Audio at the specified location, fire and forget
	UFUNCTION(BlueprintCallable)
		void PauseAllAudio(); // Pause all audio
	UFUNCTION(BlueprintCallable)
		void ResumeAllAudio(); //Resume all audio
	UFUNCTION(BlueprintCallable)
		void StopAllAudio(); //Stop all audio
	UFUNCTION(BlueprintCallable)
		void PlayMusic(FString AudioName,float starttime = 0.0f); //Play Music, Stop any music currently playing
	UFUNCTION(BlueprintCallable)
		void StopMusic(); //Stop Music
	UFUNCTION(BlueprintCallable)
		void PauseMusic(); // Pause the Music
	UFUNCTION(BlueprintCallable)
		void ResumeMusic(); //Resume the Music
	UFUNCTION(BlueprintCallable)
		void FadeInMusic(FString AudioName, float duration, float starttime=0.0f); //Fade In the music
	UFUNCTION(BlueprintCallable)
		void FadeOutMusic(float duration); //Fade Out the music
	UFUNCTION(BlueprintCallable)
		void CrossfadeMusic(FString AudioName,float duration,bool random = false); //Change Music by crossfading
	UFUNCTION(BlueprintCallable)
		UAudioComponent* AddStem(FString AudioName, FString StemName,float starttime =0.0f,bool random=false); //Add new Stem
	UFUNCTION(BlueprintCallable)
		UAudioComponent* GetStem(FString StemName); //Get A Particular Stem
	UFUNCTION(BlueprintCallable)
		void RemoveStem(FString StemName); //Remove Stem from runtime
	UFUNCTION(BlueprintCallable)
		UAudioComponent* GetCurrentMusic(); //Get Currently Playing Music
	//UFUNCTION(BlueprintCallable)
	//	void PlayFMODEvent(UFMODEvent* FMODEvent, UObject* WorldContextObj, FTransform transform, bool AutoPlay); //Change Music by crossfading


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> m_audioToLoadAtStart;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> m_musicToLoadAtStart;

	// Called when the game starts
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString, USoundBase*> m_AudioBank;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString, USoundBase*> m_MusicBank;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString, float> m_MusicDurationBank;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString, USoundAttenuation*> m_AttenuationBank;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UAudioComponent*> m_ActiveAudio;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UAudioComponent*> m_ActiveMusic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<FString, UAudioComponent*> m_ActiveStem;
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//	TArray< TSubclassOf<USoundClass> > m_SoundClips;
	UFUNCTION()
		void CheckForStoppedUAudio(); //Check if there is Stopped UAudio and delete it from the list


	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
