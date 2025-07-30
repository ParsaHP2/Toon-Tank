// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

ATank::ATank(){
SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
SpringArm->SetupAttachment(RootComponent);

Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
Camera->SetupAttachment(SpringArm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComp){

    Super::SetupPlayerInputComponent(PlayerInputComp);

    PlayerInputComp->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComp->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    
    
    PlayerInputComp->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
    PlayerInputComp->BindAction(TEXT("Dash"), IE_Pressed, this, &ATank::Dash);
    PlayerInputComp->BindAction(TEXT("Parry"), IE_Pressed, this, &ATank::Parry);
}

void ATank::Tick(float DeltaTime){

    Super::Tick(DeltaTime);

    if (isDashing) {
        DashTimer -= DeltaTime;
        if (DashTimer <= 0.f) {
            isDashing = false;
            TankSpeed = NormalSpeed;
            UE_LOG(LogTemp, Warning, TEXT("Dash ended!"));
        }
    } else if(isParrying){
        ParryTimer -= DeltaTime;
        TurretMesh->SetMaterial(1, ParryMaterial);
        if (ParryTimer <= 0.f) {
            isParrying = false;
            TurretMesh->SetMaterial(1, DefaultMaterial);
            UE_LOG(LogTemp, Warning, TEXT("Parry ended and is equal to: %d"),ParryCounter);
        }

    }

    if (TankPlayerController){
        FHitResult hitRes;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
            false, hitRes);
        RotateTurret(hitRes.ImpactPoint);

    }

}

void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    bAlive = false;
}

void ATank::BeginPlay(){
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::Move(float Value){
    FVector DeltaLocation = FVector::ZeroVector;
    

    DeltaLocation.X = Value * TankSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value){
    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(DeltaRotation, true);

}

void ATank::Dash(){
    float CurrentTime = GetWorld()->GetTimeSeconds();

    if (isDashing || (CurrentTime - LastDashTime < DashCooldown)) {
        return; // Still dashing or on cooldown
    }

    if(!isParrying){ // Make sure the player can't Parry AND Dash
        isDashing = true;
        TankSpeed = DashSpeed;
        DashTimer = DashDuration;
        LastDashTime = CurrentTime;
    }

    UE_LOG(LogTemp, Warning, TEXT("Dash started!"));
}

void ATank::Parry(){
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (isParrying || (CurrentTime - LastParryTime < ParryCooldown)) {
        return; // Still dashing or on cooldown
    }

    if(!isDashing){ // Make sure the player can't Dash AND Parry
        isParrying = true;
        ParryTimer = ParryDuration;
        LastParryTime = CurrentTime;
    }

    UE_LOG(LogTemp, Warning, TEXT("Parry started!"));

}
