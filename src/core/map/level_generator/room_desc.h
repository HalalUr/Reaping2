#ifndef INCLUDED_MAP_ROOM_DESC_H
#define INCLUDED_MAP_ROOM_DESC_H

#include "platform/i_platform.h"
#include "core/opt.h"
#include "entrance_type.h"
#include "room_property.h"

namespace map {

class IRoom;
// describes a room cell
struct Cell 
{
    typedef std::set<EntranceType::Type> Entrances_t;
    Entrances_t mPossibleEntrances; // possible entrances to this cell
    bool mFilled = false; // filled if the correspoinding RoomDesc places stg into this cell
    glm::vec2 mDescCoord = glm::vec2( -1, -1 ); // relative position inside the room
    void AddEntrance( EntranceType::Type const& entrance );
    void SetEntrances( Entrances_t const& entrances );
    bool HasEntrance( EntranceType::Type const& entrance) const;
    Entrances_t const& GetEntrances() const;
    void SetFilled( bool filled );
    bool IsFilled();
    void Load( Json::Value& setters );
};

// describes an n*n room.
// can contain empty cells that could be filled later
struct RoomDesc
{
    typedef std::vector<std::vector<Cell>> CellMatrix_t;
    typedef std::set<RoomProperty::Type> Properties_t;
    RoomDesc();
    void SetCellCount( int32_t cellCount );
    int32_t GetCellCount() const;
    void SetCellSize( int32_t cellSize );
    int32_t GetCellSize() const;
    Properties_t const& GetProperties() const;
    void SetProperties( Properties_t const& properties );
    bool HasProperty( RoomProperty::Type prop ) const;
    void ClearProperties();
    void AddProperty( RoomProperty::Type prop );
    Cell& GetCell( int32_t x, int32_t y );
    Cell& GetCell( glm::vec2 pos );
    Cell const& GetCell( int32_t x, int32_t y ) const;
    Cell const& GetCell( glm::vec2 pos ) const;
    bool IsFilled( int32_t x, int32_t y ) const;
    bool IsFilled( glm::vec2 pos ) const;
    void ClearCellEntrances();
    Opt<IRoom> GetRoom();
    void SetRoom( Opt<IRoom> room );

    typedef std::vector<int32_t> PlacedActorGUIDs_t;
    PlacedActorGUIDs_t mPlacedActorGUIDs; // for debug
    void Load( Json::Value& setters );
protected:
    int32_t mCellCount = 0;
    int32_t mCellSize = 500;
    Properties_t mPossibleProperties;
    CellMatrix_t mCells;
    Opt<IRoom> mRoom;
};

} // namespace map

#endif//INCLUDED_MAP_ROOM_DESC_H
