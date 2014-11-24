#ifndef INCLUDED_CORE_I_POSITION_COMPONENT_H
#define INCLUDED_CORE_I_POSITION_COMPONENT_H
#include "component.h"

class IPositionComponent : public Component
{
public:
    DEFINE_COMPONENT_BASE(IPositionComponent)
	virtual double const& GetX() const =0; //TODO: component style, its not a really good idea for models, if components are changed
	virtual double const& GetY() const =0;
	virtual double const& GetOrientation() const=0;
	virtual void SetX( double X )=0;
	virtual void SetY( double Y )=0;
	virtual void SetOrientation( double Orientation )=0;
protected:
	friend class ComponentFactory;
};

#endif//INCLUDED_CORE_I_POSITION_COMPONENT_H