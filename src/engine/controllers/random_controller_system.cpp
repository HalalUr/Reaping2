#include "platform/i_platform.h"
#include "engine/controllers/random_controller_system.h"
#include "engine/engine.h"
#include "platform/auto_id.h"
#include "core/random_controller_component.h"
#include "core/i_move_component.h"
#include "core/i_position_component.h"

namespace engine {

RandomControllerSystem::RandomControllerSystem()
    : mScene( Scene::Get() )
{

}

void RandomControllerSystem::Init()
{


}

void RandomControllerSystem::Update(double DeltaTime)
{
    for( ActorList_t::iterator it = mScene.GetActors().begin(), e = mScene.GetActors().end(); it != e; ++it )
    {
        Actor& actor = **it;
        Opt<RandomControllerComponent> randomCC = actor.Get<RandomControllerComponent>();
        if (!randomCC.IsValid()||!randomCC->IsEnabled())
        {
            continue;
        }
        if (actor.Get<IMoveComponent>()->GetHeading()==0.0&&actor.Get<IMoveComponent>()->GetSpeed()==0)
        {
            actor.AddAction( AutoId( "move" ) ); //TODO: there will be no actions, this one wont be needed
        }
        randomCC->SetCounter(randomCC->GetCounter()+DeltaTime);
        if ( randomCC->GetCounter() > 2 )
        {
            randomCC->SetCounter(0);
            randomCC->SetHeadingModifier(( rand() % 10 - 5 ) * .33);

            actor.Get<IMoveComponent>()->SetSpeed( ( rand() % 10 )*.03 );
        }
        actor.Get<IMoveComponent>()->SetHeading( actor.Get<IMoveComponent>()->GetHeading() + DeltaTime * randomCC->GetHeadingModifier() );
        actor.Get<IPositionComponent>()->SetOrientation( actor.Get<IMoveComponent>()->GetHeading() );

    }
}

} // namespace engine

