// Fill out your copyright notice in the Description page of Project Settings.

#include "SuperConejo.h"
#include "ConejoMultiplayerController.h"
#include "UnrealNetwork.h"

AConejoMultiplayerController::AConejoMultiplayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	/* Initialize The Values */
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("Class'/Script/SuperConejo.Conejo'"));
    if (PlayerPawnBPClass.Class != NULL) {
        PawnToUseA = PlayerPawnBPClass.Class;
    }
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass2(TEXT("BlueprintGeneratedClass'/Game/SuperConejo/Blueprints/Conejo/Conejo_BP.Conejo_BP_C'"));
    if (PlayerPawnBPClass2.Class != NULL) {
        PawnToUseB = PlayerPawnBPClass2.Class;
    }
 
	/* Make sure the PawnClass is Replicated */
	bReplicates = true;
}
 
void AConejoMultiplayerController::BeginPlay()
{
	Super::BeginPlay();
 
	DeterminePawnClass();
}
 
// Pawn Class
void AConejoMultiplayerController::DeterminePawnClass_Implementation()
{
	if (Role < ROLE_Authority) {//somos clientes
        ServerSetPawn(PawnToUseB);
	}
    else {
        ServerSetPawn(PawnToUseA);
    }
}
 
bool AConejoMultiplayerController::ServerSetPawn_Validate(TSubclassOf<APawn> InPawnClass)
{
	return true;
}
 
void AConejoMultiplayerController::ServerSetPawn_Implementation(TSubclassOf<APawn> InPawnClass)
{
	MyPawnClass = InPawnClass;
 
	/* Just in case we didn't get the PawnClass on the Server in time... */
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}
 
// Replication
void AConejoMultiplayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(AConejoMultiplayerController, MyPawnClass);
}


