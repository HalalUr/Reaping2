#include "core/program_state.h"
#include "platform/model_value.h"
namespace core {

    ProgramState::ProgramState()
        : mMode(ProgramState::Local)
        , mClientConnected(false)
        , mControlledActorGUID(-1)
        , mProgramStateModel( "programstate", &platform::RootModel::Get() )
        , mIsClientModel( RefTo( mIsClient ), "isclient", &mProgramStateModel )
        , mIsClient(0)
    {
    }

    void ProgramState::SetMode(ProgramState::Mode mode)
    {
        mMode=mode;
        mIsClient=mMode==ProgramState::Client;
    }

    Opt<ClientData> ProgramState::FindClientDataByClientId(int32_t clientId)
    {
        for (ClientDatas_t::iterator i=mClientDatas.begin(), e=mClientDatas.end();i!=e;++i)
        {
            if (i->mClientId==clientId)
            {
                return Opt<ClientData>(&*i);
            }
        }
        return Opt<ClientData>();
    }

    Opt<ClientData> ProgramState::FindClientDataByActorGUID(int32_t actorGUID)
    {
        for (ClientDatas_t::iterator i=mClientDatas.begin(), e=mClientDatas.end();i!=e;++i)
        {
            if (i->mClientActorGUID==actorGUID)
            {
                return Opt<ClientData>(&*i);
            }
        }
        return Opt<ClientData>();
    }

    Opt<ClientData> ProgramState::FindClientDataByClientName(std::string clientName)
    {
        for (ClientDatas_t::iterator i=mClientDatas.begin(), e=mClientDatas.end();i!=e;++i)
        {
            if (i->mClientName==clientName)
            {
                return Opt<ClientData>(&*i);
            }
        }
        return Opt<ClientData>();
    }


    ClientData::ClientData() 
        :mClientId(0)
        ,mClientActorGUID(-1)
        ,mKill(0)
        ,mDeath(0)
        ,mAssist(0)
        ,mScore(0)
        ,mReady(false)
        ,mConnected(true)
    {

    }

    ClientData::ClientData(int32_t clientId, std::string const& clientName)
        :mClientId(clientId)
        ,mClientName(clientName)
        ,mClientActorGUID(-1)
        ,mKill(0)
        ,mDeath(0)
        ,mAssist(0)
        ,mScore(0)
        ,mReady(false)
        ,mConnected(true)
    {

    }

} // namespace core
