#include "core/shot_collision_component.h"
#include "core/i_position_component.h"
#include "core/i_move_component.h"
#include "core/i_health_component.h"
#include "core/component_factory.h"
#include "core/i_collision_component.h"
#include "core/scene.h"
#include "platform/i_platform.h"
#include <portable_iarchive.hpp>
#include <portable_oarchive.hpp>

ShotCollisionComponent::ShotCollisionComponent()
    : CollisionComponent()
    , mDamage( 0 )
    , mParentGUID( -1 )
    , mHitClosest( true )
    , mDamageOnce( true )
    , mHitCountToKill( 1 )
    , mDoDamage( true )
{

}

void ShotCollisionComponent::SetDamage( int32_t Damage )
{
    mDamage = Damage;
}

int32_t ShotCollisionComponent::GetDamage() const
{
    return mDamage;
}

void ShotCollisionComponent::SetParentGUID( int32_t parentGUID )
{
    mParentGUID = parentGUID;
}

int32_t ShotCollisionComponent::GetParentGuid() const
{
    return mParentGUID;
}

bool ShotCollisionComponent::CanPassThrough( CollisionClass::Type CollType ) const
{
    return std::find( mPassThroughTypes.begin(), mPassThroughTypes.end(), CollType ) != mPassThroughTypes.end();
}

void ShotCollisionComponent::SetPassThrough( std::vector<CollisionClass::Type> const& CollTypes )
{
    mPassThroughTypes = CollTypes;
}

bool ShotCollisionComponent::IsHitClosest()
{
    return mHitClosest;
}

void ShotCollisionComponent::SetHitClosest( bool hitClosest )
{
    mHitClosest = hitClosest;
}

bool ShotCollisionComponent::IsDamageOnce()
{
    return mDamageOnce;
}

void ShotCollisionComponent::SetDamageOnce( bool damageOnce )
{
    mDamageOnce = damageOnce;
}

void ShotCollisionComponent::SetHitCountToKill(int32_t hitCountToKill)
{
    mHitCountToKill = hitCountToKill;
}

int32_t ShotCollisionComponent::GetHitCountToKill()const
{
    return mHitCountToKill;
}

ShotCollisionComponent::ActorsCollided_t& ShotCollisionComponent::GetActorsCollided()
{
    return mActorsCollided;
}

void ShotCollisionComponent::AddDamagedActorId( int32_t damagedActorId )
{
    mDamagedActorIds.insert( damagedActorId );
}

ShotCollisionComponent::Damaged_Actor_Ids_t const& ShotCollisionComponent::GetDamagedActorIds() const
{
    return mDamagedActorIds;
}

void ShotCollisionComponent::ResetDamagedActorIds()
{
    mDamagedActorIds.clear();
}

void ShotCollisionComponent::SetDoDamage( bool doDamage )
{
    mDoDamage = doDamage;
}

bool ShotCollisionComponent::IsDoDamage()const
{
    return mDoDamage;
}

void ShotCollisionComponentLoader::BindValues()
{
    Bind( "damage", func_int32_t( &ShotCollisionComponent::SetDamage ) );
    std::vector<CollisionClass::Type> PassThroughTypes;
    Json::Value const& json = ( *mSetters )["passthrough"];
    if( json.isArray() )
    {
        for (Json::Value::iterator i = json.begin(), e = json.end(); i != e; ++i)
        {
            Json::Value& part = *i;
            CollisionClass::Type typ = CollisionClass::Get()(AutoId( part.asString() ));
            PassThroughTypes.push_back( typ );
        }
    }
    Bind<std::vector<CollisionClass::Type> >( &ShotCollisionComponent::SetPassThrough, PassThroughTypes );
    Bind( "damage_once", func_bool( &ShotCollisionComponent::SetDamageOnce ) );
    Bind( "hit_closest", func_bool( &ShotCollisionComponent::SetHitClosest ) );
    Bind( "hit_count_to_kill", func_int32_t(&ShotCollisionComponent::SetHitCountToKill ) );
}

ShotCollisionComponentLoader::ShotCollisionComponentLoader()
{
    SetBase<CollisionComponentLoader>();
}

REAPING2_CLASS_EXPORT_IMPLEMENT( ShotCollisionComponent, ShotCollisionComponent );
