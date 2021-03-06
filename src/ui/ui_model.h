#pragma once
#ifndef INCLUDED_UI_MODEL_H
#define INCLUDED_UI_MODEL_H

#include "platform/model_value.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "platform/singleton.h"

namespace ui {

class UiModel : public platform::Singleton<UiModel>, public platform::ModelValue
{
    friend class platform::Singleton<UiModel>;
    UiModel();

    struct Val
    {
        Val();
        int32_t base;
    };
    std::map<std::string, Val> mValues;
    boost::ptr_vector<platform::ModelValue> mOwnedModels;
    boost::ptr_vector<platform::ModelValue> mOwnedCallModels;
    int32_t Value( std::string const& name );
    void Add( std::string const& name, int32_t val );
    virtual ModelValue* FindSubModel( std::string const& name ) const;
    ModelValue* CreateModel( std::string const& name );
public:
    ~UiModel();
};

}

#endif // INCLUDED_UI_MODEL_H

