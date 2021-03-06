#include "platform/i_platform.h"
#include "engine/fade_out_system.h"
#include "core/i_health_component.h"
#include "core/i_fade_out_component.h"

namespace engine {

FadeOutSystem::FadeOutSystem()
    : mScene( Scene::Get() )
{

}

void FadeOutSystem::Init()
{
    mScene.AddValidator( GetType_static(), []( Actor const& actor )->bool {
        return actor.Get<IFadeOutComponent>().IsValid(); } );
}

void FadeOutSystem::Update( double DeltaTime )
{
    for (auto actor : mScene.GetActorsFromMap( GetType_static() ))
    {
        Opt<IFadeOutComponent> fadeOutC = actor->Get<IFadeOutComponent>();
        if ( !fadeOutC.IsValid() )
        {
            continue;
        }
        double currSecsToEnd = fadeOutC->GetSecsToEnd();
        double newSecsToEnd = currSecsToEnd - DeltaTime;
        if ( currSecsToEnd > 0 && newSecsToEnd <= 0 )
        {
            newSecsToEnd = 0;
            Opt<IHealthComponent> healthC = actor->Get<IHealthComponent>();
            if ( healthC.IsValid() )
            {
                healthC->SetHP( 0 );
            }
        }
        fadeOutC->SetSecsToEnd( newSecsToEnd );
    }

}

} // namespace engine

