#ifndef INCLUDED_CORE_ION_GUN_H
#define INCLUDED_CORE_ION_GUN_H
#include "core/weapon.h"

class IonGun : public Weapon
{
public:
    IonGun( int32_t Id );
    IonGun();
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version);
};

template<class Archive>
void IonGun::serialize(Archive& ar, const unsigned int version)
{
    ar & boost::serialization::base_object<Weapon>(*this);
}

class IonGunLoader: public ItemLoader<IonGun>
{
public:
    virtual void BindValues();
    IonGunLoader();
    friend class ItemLoaderFactory;
};

#endif//INCLUDED_CORE_ION_GUN_H
