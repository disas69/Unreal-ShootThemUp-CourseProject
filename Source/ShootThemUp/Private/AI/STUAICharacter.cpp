// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/STUAIWeaponComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;

    UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement();
    if (CharacterMovementComponent != nullptr)
    {
        CharacterMovementComponent->bUseControllerDesiredRotation = true;
        CharacterMovementComponent->RotationRate = FRotator(0.0f, 250.0f, 0.0f);
    }
}

void ASTUAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASTUAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ASTUAICharacter::OnDeath()
{
    Super::OnDeath();

    const AAIController* AIController = Cast<AAIController>(GetController());
    if (AIController != nullptr && AIController->BrainComponent != nullptr)
    {
        AIController->BrainComponent->Cleanup();
    }
}