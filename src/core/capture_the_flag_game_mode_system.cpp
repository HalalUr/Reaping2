#include "platform/i_platform.h"
#include "capture_the_flag_game_mode_system.h"
#include "ui/ui.h"
#include "core/ctf_program_state.h"
#include "network/ctf_client_datas_message.h"
#include "network/messsage_holder.h"

namespace core {

CaptureTheFlagGameModeSystem::CaptureTheFlagGameModeSystem()
    : mScene( Scene::Get() )
    , mProgramState(core::ProgramState::Get())
{
}


void CaptureTheFlagGameModeSystem::Init()
{
    mOnStartGameMode=EventServer<core::StartGameModeEvent>::Get().Subscribe( boost::bind( &CaptureTheFlagGameModeSystem::OnStartGameMode, this, _1 ) );
}


void CaptureTheFlagGameModeSystem::Update(double DeltaTime)
{

}

void CaptureTheFlagGameModeSystem::OnStartGameMode(core::StartGameModeEvent const& Evt)
{
    if (Evt.mMode!="ctf")
    {
        return;
    }
    if (mProgramState.mMode==core::ProgramState::Server)
    {
        ctf::ProgramState& ctfProgramState=ctf::ProgramState::Get();
        ctfProgramState.mClientDatas.clear();
        bool isBlueTeam=true;
        for (core::ProgramState::ClientDatas_t::iterator i=mProgramState.mClientDatas.begin(), e=mProgramState.mClientDatas.end();i!=e;++i)
        {
            ctfProgramState.mClientDatas.push_back(ctf::ClientData((*i).mClientId,
                isBlueTeam?(ctf::ClientData::Blue):(ctf::ClientData::Red)));
            isBlueTeam=!isBlueTeam;
        }
        std::auto_ptr<network::ctf::ClientDatasMessage> clientDatasMsg(new network::ctf::ClientDatasMessage);
        clientDatasMsg->mClientDatas=ctfProgramState.mClientDatas;
        network::MessageHolder::Get().AddOutgoingMessage(clientDatasMsg);
    }
    mScene.Load("level2");
    Ui::Get().Load("hud");
}


} // namespace core

