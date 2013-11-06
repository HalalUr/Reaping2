#include "i_core.h"

TargetPlayerController::TargetPlayerController(Actor* player):Controller()
	,mCounter(2)
	,mHeadingModifier(0)
	,mPlayer(player)
{

}

void TargetPlayerController::SetActor(Actor* Obj)
{
	Controller::SetActor(Obj);
	if(!mActor)return;
	mActor->SetHeading(0);
	mActor->SetSpeed(0.1);
	Action const* Act=ActionHolder::Get().GetAction("move");
	if(Act) Act->Activate(*mActor);
}

void TargetPlayerController::Update( double Seconds )
{
	if(!mActor)return;
	if(!mPlayer)return;
	mCounter+=Seconds;
	mCounter=0;
	double Rot=atan2(mPlayer->GetY()-mActor->GetY(),mPlayer->GetX()-mActor->GetX());
	double Radians=Rot-mActor->GetHeading();
	static const double pi=boost::math::constants::pi<double>();
	while (Radians < -pi)
	{
		Radians += pi*2;
	}
	while (Radians > pi)
	{
		Radians -= pi*2;
	}
	double RotSpd=(Radians>0?1:-1)*0.01;
	mActor->SetHeading(mActor->GetHeading()+RotSpd);
	mActor->SetOrientation(mActor->GetHeading());
}
