#ifndef INCLUDED_CORE_HEAT_SOURCE_COMPONENT_H
#define INCLUDED_CORE_HEAT_SOURCE_COMPONENT_H

#include "i_heat_source_component.h"
#include "core/property_loader.h"
#include "platform/export.h"

class HeatSourceComponent : public IHeatSourceComponent
{
public:
    HeatSourceComponent();
protected:
    friend class ComponentFactory;
private:
public:
    friend class ::boost::serialization::access;
    template<class Archive>
    void serialize( Archive& ar, const unsigned int version );
};

template<class Archive>
void HeatSourceComponent::serialize( Archive& ar, const unsigned int version )
{
    //NOTE: generated archive for this class
    ar& boost::serialization::base_object<IHeatSourceComponent>( *this );
}

class HeatSourceComponentLoader : public ComponentLoader<HeatSourceComponent>
{
public:
    DEFINE_COMPONENT_LOADER_BASE( HeatSourceComponentLoader )
private:
    virtual void BindValues();
protected:
    HeatSourceComponentLoader();
    friend class ComponentLoaderFactory;
};


REAPING2_CLASS_EXPORT_KEY2( HeatSourceComponent, HeatSourceComponent, "heat_source_component" );
#endif//INCLUDED_CORE_HEAT_SOURCE_COMPONENT_H

//command:  "classgenerator.exe" -g "component" -c "heat_source_component"
