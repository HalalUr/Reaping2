#ifndef INCLUDED_CORE_BUFF_HOLDER_COMPONENT_H
#define INCLUDED_CORE_BUFF_HOLDER_COMPONENT_H

#include "i_buff_holder_component.h"
#include "core/property_loader.h"

class BuffHolderComponent : public IBuffHolderComponent
{
public:
    BuffHolderComponent();
    virtual BuffList_t& GetBuffList();
    virtual void AddBuff(std::auto_ptr<Buff> buff);
    ~BuffHolderComponent();
protected:
    friend class ComponentFactory;
    BuffHolder mBuffList;
private:
};

class SecsToEndModifier
{
public:
    SecsToEndModifier(double secsToEnd);
    void operator()(Opt<Buff> buff);

protected:
    double mSecsToEnd;
};

class BuffHolderComponentLoader : public ComponentLoader<BuffHolderComponent>
{
    virtual void BindValues();
protected:
    BuffHolderComponentLoader();
    friend class ComponentLoaderFactory;
};

#endif//INCLUDED_CORE_BUFF_HOLDER_COMPONENT_H

