#include "platform/i_platform.h"
#include "brush_repo.h"
#include "normal_brush.h"

using platform::AutoId;

namespace map {

DefaultBrush const BrushRepo::mDefault = DefaultBrush();

BrushRepo::BrushRepo()
    : Repository<IBrush>(mDefault)
{
    int32_t id=AutoId("normal");
    mElements.insert(id, new NormalBrush(AutoId("normal")));
}


void DefaultBrush::Update(double DeltaTime)
{

}

DefaultBrush::DefaultBrush()
    :IBrush(-1)
{

}

} // namespace map

