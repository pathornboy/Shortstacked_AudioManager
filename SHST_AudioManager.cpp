// Fill out your copyright notice in the Description page of Project Settings.


#include "SHST_AudioManager.h"

// Sets default values for this component's properties
USHST_AudioManager::USHST_AudioManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void USHST_AudioManager::BeginPlay()
{
	Super::BeginPlay();
	// ...

}


// Called every frame
void USHST_AudioManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForStoppedUAudio();
	// ...
}

void USHST_AudioManager::CheckForStoppedUAudio()
{
	if (m_ActiveAudio.Num() > 0) {
		//for (auto& Audio : m_ActiveAudio)
		//{
		//	if (!Audio->IsPlaying())
		//	{
		//		UAudioComponent* temp_Audio = Audio;
		//		m_ActiveAudio.RemoveSingle(Audio);
		//		temp_Audio->DestroyComponent();
		//		int cat = m_ActiveAudio.Num();
		//		UE_LOG(LogTemp, Warning, TEXT("Number of Active audio, %d"), cat);
		//	}

		//}
		for (int32 Index = m_ActiveAudio.Num() - 1; Index >= 0; --Index)
		{
			if (m_ActiveAudio[Index]->IsPlaying() == false)
			{
				UAudioComponent* temp_Audio = m_ActiveAudio[Index];
				const bool bAllowShrinking = false;
				m_ActiveAudio.RemoveAt(Index, 1, bAllowShrinking);
				temp_Audio->DestroyComponent();

			}
		}
	}


	if (m_ActiveMusic.Num() > 0) {
		for (int32 Index = m_ActiveMusic.Num() - 1; Index >= 0; --Index)
		{
			if (m_ActiveMusic[Index]->IsPlaying() == false)
			{
				UAudioComponent* temp_Audio = m_ActiveMusic[Index];
				const bool bAllowShrinking = false;
				m_ActiveMusic.RemoveAt(Index, 1, bAllowShrinking);
				temp_Audio->DestroyComponent();
			}
		}

	}
}


void USHST_AudioManager::PauseAllAudio()
{
	//UE_LOG(LogTemp, Warning, TEXT("PAUSED"));
	if (m_ActiveAudio.Num() > 0) {
		for (int32 Index = m_ActiveAudio.Num() - 1; Index >= 0; --Index)
		{
			m_ActiveAudio[Index]->SetPaused(true);
		}
	}
}

void USHST_AudioManager::ResumeAllAudio()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYED"));
	if (m_ActiveAudio.Num() > 0) {
		for (int32 Index = m_ActiveAudio.Num() - 1; Index >= 0; --Index)
		{
			m_ActiveAudio[Index]->SetPaused(false);
		}
	}
}

void USHST_AudioManager::StopAllAudio()
{
	if (m_ActiveAudio.Num() > 0) {
		for (int32 Index = m_ActiveAudio.Num() - 1; Index >= 0; --Index)
		{
			UAudioComponent* temp_Audio = m_ActiveAudio[Index];
			m_ActiveAudio[Index]->SetActive(false);
			const bool bAllowShrinking = false;
			m_ActiveAudio.RemoveAt(Index, 1, bAllowShrinking);
			temp_Audio->DestroyComponent();
		}
	}
}

void USHST_AudioManager::PauseMusic()
{
	//UE_LOG(LogTemp, Warning, TEXT("PAUSED"));
	if (m_ActiveMusic.Num() > 0) {
		for (int32 Index = m_ActiveMusic.Num() - 1; Index >= 0; --Index)
		{
			m_ActiveMusic[Index]->SetPaused(true);
		}
	}
}



void USHST_AudioManager::ResumeMusic()
{
	//UE_LOG(LogTemp, Warning, TEXT("PLAYED"));
	if (m_ActiveMusic.Num() > 0) {
		for (int32 Index = m_ActiveMusic.Num() - 1; Index >= 0; --Index)
		{
			m_ActiveMusic[Index]->SetPaused(false);
		}
	}
}



void USHST_AudioManager::PlayAudio(FString AudioName)
{
	FString FolderPath = TEXT("/Game/Sound/Sound_Effects/SFX/" + AudioName);
	const TCHAR* FilePath = *FolderPath;
	USoundBase* SoundCue = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, FilePath));
	if (SoundCue != nullptr)
	{
		UAudioComponent* NewAudio = NewObject <UAudioComponent>(this, UAudioComponent::StaticClass());
		NewAudio->SetSound(SoundCue);
		NewAudio->Play();
		m_ActiveAudio.Add(NewAudio);
	}
	else
	{
		FString Errorer = TEXT("Audio File '" + AudioName + "' Cannot be found");
		//const TCHAR* Errer = *Errorer;
		UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(Errorer));
	}
}



void USHST_AudioManager::PlayAudioAtLocation(FString AudioName, USoundAttenuation* Attenuationer, FVector Location)
{
	FString FolderPath = TEXT("/Game/Sound/Sound_Effects/SFX/" + AudioName);
	const TCHAR* FilePath = *FolderPath;
	USoundBase* SoundCue = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, FilePath));


	if (SoundCue != nullptr)
	{


		UAudioComponent* NewAudio = NewObject <UAudioComponent>(this, UAudioComponent::StaticClass());
		NewAudio->SetWorldLocation(Location);

		if (Attenuationer != nullptr)
		{
			NewAudio->AttenuationSettings = Attenuationer;
		}
		else
		{
			FString FolderPath2 = TEXT("/Game/Sound/Sound_Effects/Attenuation/DefaultAttenuation");
			const TCHAR* FilePath2 = *FolderPath2;
			USoundAttenuation* Attenuationer2 = Cast<USoundAttenuation>(StaticLoadObject(USoundAttenuation::StaticClass(), NULL, FilePath2));
			NewAudio->AttenuationSettings = Attenuationer2;
		}
		
		
		NewAudio->bAllowSpatialization = true;
		NewAudio->SetSound(SoundCue);
		NewAudio->Play();
		m_ActiveAudio.Add(NewAudio);
	}
	else
	{
		FString Errorer = TEXT("Audio File '" + AudioName + "' Cannot be found");
		//const TCHAR* Errer = *Errorer;
		UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(Errorer));
	}
}

void USHST_AudioManager::PlayMusic(FString AudioName)
{
	FString FolderPath = TEXT("/Game/Sound/Music/" + AudioName);
	const TCHAR* FilePath = *FolderPath;
	USoundBase* SoundCue = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, FilePath));
	if (SoundCue != nullptr)
	{
		UAudioComponent* NewAudio = NewObject <UAudioComponent>(this, UAudioComponent::StaticClass());
		NewAudio->SetSound(SoundCue);
		NewAudio->Play();
		m_ActiveMusic.Add(NewAudio);
	}
	else
	{
		FString Errorer = TEXT("Music File '" + AudioName + "' Cannot be found");
		//const TCHAR* Errer = *Errorer;
		UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(Errorer));
	}
}

void USHST_AudioManager::StopMusic()
{
	if (m_ActiveMusic.Num() > 0) {
		for (int32 Index = m_ActiveMusic.Num() - 1; Index >= 0; --Index)
		{
			UAudioComponent* temp_Audio = m_ActiveMusic[Index];
			m_ActiveMusic[Index]->SetPaused(true);
			const bool bAllowShrinking = false;
			m_ActiveMusic.RemoveAt(Index, 1, bAllowShrinking);
			temp_Audio->DestroyComponent();
		}
	}
}

void USHST_AudioManager::CrossfadeMusic(FString AudioName, float duration)
{




	FString FolderPath = TEXT("/Game/Sound/Music/" + AudioName);
	const TCHAR* FilePath = *FolderPath;
	USoundBase* SoundCue = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), NULL, FilePath));
	if (SoundCue != nullptr)
	{

		if (m_ActiveMusic.Num() > 0) {
			for (int32 Index = m_ActiveMusic.Num() - 1; Index >= 0; --Index)
			{
				m_ActiveMusic[Index]->FadeOut(duration, 0.0);
				const bool bAllowShrinking = false;
				m_ActiveMusic.RemoveAt(Index, 1, bAllowShrinking);
			}
		}



		UAudioComponent* NewAudio = NewObject <UAudioComponent>(this, UAudioComponent::StaticClass());
		NewAudio->SetSound(SoundCue);
		NewAudio->FadeIn(duration, 1.0f, 0.0);
		m_ActiveAudio.Add(NewAudio);
	}
	else
	{
		FString Errorer = TEXT("Audio File '" + AudioName + "' Cannot be found");
		//const TCHAR* Errer = *Errorer;
		UE_LOG(LogTemp, Warning, TEXT("This is the data: %s"), *FString(Errorer));
	}






}