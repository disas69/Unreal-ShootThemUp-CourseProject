// Shoot Them Up demo game project. Evgenii Esaulenko, 2024

#include "UI/STUGameEndWidget.h"
#include "FSTUTextUtils.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/STUPlayerState.h"
#include "UI/STUPlayerStatsWidget.h"

bool USTUGameEndWidget::Initialize()
{
    const bool bInit = Super::Initialize();
    if (RestartLevelButton != nullptr)
    {
        RestartLevelButton->OnClicked.AddDynamic(this, &USTUGameEndWidget::RestartLevel);
    }

    ASTUGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASTUGameModeBase>();
    if (GameMode)
    {
        GameMode->GameStateChanged.AddUObject(this, &USTUGameEndWidget::OnGameStateChange);
    }
    
    return bInit;
}

void USTUGameEndWidget::OnGameStateChange(EGameState NewState)
{
    if (NewState == EGameState::Finished)
    {
        DisplayPlayersStats();
    }
}

void USTUGameEndWidget::DisplayPlayersStats()
{
    PlayerStatsBox->ClearChildren();

    for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const AController* Controller = It->Get();
        if (Controller != nullptr)
        {
            const ASTUPlayerState* PlayerState = Controller->GetPlayerState<ASTUPlayerState>();
            if (PlayerState != nullptr)
            {
                USTUPlayerStatsWidget* UserWidget = CreateWidget<USTUPlayerStatsWidget>(GetWorld(), PlayerStatsWidgetClass);
                if (UserWidget != nullptr)
                {
                    UserWidget->SetPlayerName(FSTUTextUtils::TextFromString(PlayerState->GetPlayerName()));
                    UserWidget->SetKills(FSTUTextUtils::TextFromInt(PlayerState->GetKillsNum()));
                    UserWidget->SetDeaths(FSTUTextUtils::TextFromInt(PlayerState->GetDeathsNum()));
                    UserWidget->SetTeam(FSTUTextUtils::TextFromInt(PlayerState->GetTeamID()));
                    UserWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
                    PlayerStatsBox->AddChild(UserWidget);
                }
            }
        }
    }
}

void USTUGameEndWidget::RestartLevel()
{
    const FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevel));
}