#ifndef _WORLD_OBJECT_H
#define _WORLD_OBJECT_H

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
using boost::assign::map_list_of;      // bring 'map_list_of()' into scope

#include <map>
using std::map;

#include "../math/vecposition.h"
#include <vector>
using std::vector;
#include "../math/Geometry.h"
#include "../parser/VisionObject.h"

enum WorldObjType {   // Types of objects
    WO_BALL,

    // Self and Teammates
    WO_TEAMMATE1,
    WO_TEAMMATE2,
    WO_TEAMMATE3,
    WO_TEAMMATE4,
    WO_TEAMMATE5,
    WO_TEAMMATE6,

    // Opponents
    WO_OPPONENT1,
    WO_OPPONENT2,
    WO_OPPONENT3,
    WO_OPPONENT4,
    WO_OPPONENT5,
    WO_OPPONENT6,

    // Heads
    WO_TEAMMATE_HEAD1,
    WO_TEAMMATE_HEAD2,
    WO_TEAMMATE_HEAD3,
    WO_TEAMMATE_HEAD4,
    WO_TEAMMATE_HEAD5,
    WO_TEAMMATE_HEAD6,

    WO_OPPONENT_HEAD1,
    WO_OPPONENT_HEAD2,
    WO_OPPONENT_HEAD3,
    WO_OPPONENT_HEAD4,
    WO_OPPONENT_HEAD5,
    WO_OPPONENT_HEAD6,

    // Left arms
    WO_TEAMMATE_ARM_L1,
    WO_TEAMMATE_ARM_L2,
    WO_TEAMMATE_ARM_L3,
    WO_TEAMMATE_ARM_L4,
    WO_TEAMMATE_ARM_L5,
    WO_TEAMMATE_ARM_L6,

    WO_OPPONENT_ARM_L1,
    WO_OPPONENT_ARM_L2,
    WO_OPPONENT_ARM_L3,
    WO_OPPONENT_ARM_L4,
    WO_OPPONENT_ARM_L5,
    WO_OPPONENT_ARM_L6,

    // Right arms
    WO_TEAMMATE_ARM_R1,
    WO_TEAMMATE_ARM_R2,
    WO_TEAMMATE_ARM_R3,
    WO_TEAMMATE_ARM_R4,
    WO_TEAMMATE_ARM_R5,
    WO_TEAMMATE_ARM_R6,

    WO_OPPONENT_ARM_R1,
    WO_OPPONENT_ARM_R2,
    WO_OPPONENT_ARM_R3,
    WO_OPPONENT_ARM_R4,
    WO_OPPONENT_ARM_R5,
    WO_OPPONENT_ARM_R6,

    // Left feet
    WO_TEAMMATE_FOOT_L1,
    WO_TEAMMATE_FOOT_L2,
    WO_TEAMMATE_FOOT_L3,
    WO_TEAMMATE_FOOT_L4,
    WO_TEAMMATE_FOOT_L5,
    WO_TEAMMATE_FOOT_L6,

    WO_OPPONENT_FOOT_L1,
    WO_OPPONENT_FOOT_L2,
    WO_OPPONENT_FOOT_L3,
    WO_OPPONENT_FOOT_L4,
    WO_OPPONENT_FOOT_L5,
    WO_OPPONENT_FOOT_L6,

    // Right feet
    WO_TEAMMATE_FOOT_R1,
    WO_TEAMMATE_FOOT_R2,
    WO_TEAMMATE_FOOT_R3,
    WO_TEAMMATE_FOOT_R4,
    WO_TEAMMATE_FOOT_R5,
    WO_TEAMMATE_FOOT_R6,

    WO_OPPONENT_FOOT_R1,
    WO_OPPONENT_FOOT_R2,
    WO_OPPONENT_FOOT_R3,
    WO_OPPONENT_FOOT_R4,
    WO_OPPONENT_FOOT_R5,
    WO_OPPONENT_FOOT_R6,

    FLAG_1_L,
    FLAG_1_R,
    FLAG_2_L,
    FLAG_2_R,

    //Goal Posts
    GOALPOST_1_L,
    GOALPOST_1_R,
    GOALPOST_2_L,
    GOALPOST_2_R,
    LINE,

    NUM_WORLD_OBJS,

};

static map<int,const char*> WorldObjType2Str = map_list_of
        ( WO_BALL,       "WO_BALL")
        ( WO_TEAMMATE1,  "WO_TEAMMATE1" )
        ( WO_TEAMMATE2,  "WO_TEAMMATE2" )
        ( WO_TEAMMATE3,  "WO_TEAMMATE3" )
        ( WO_TEAMMATE4,  "WO_TEAMMATE4" )
        ( WO_TEAMMATE5,  "WO_TEAMMATE5" )
        ( WO_TEAMMATE6,  "WO_TEAMMATE6" )

        ( WO_OPPONENT1,  "WO_OPPONENT1" )
        ( WO_OPPONENT2,  "WO_OPPONENT2" )
        ( WO_OPPONENT3,  "WO_OPPONENT3" )
        ( WO_OPPONENT4,  "WO_OPPONENT4" )
        ( WO_OPPONENT5,  "WO_OPPONENT5" )
        ( WO_OPPONENT6,  "WO_OPPONENT6" )

        ( WO_TEAMMATE_HEAD1,  "WO_TEAMMATE_HEAD1" )
        ( WO_TEAMMATE_HEAD2,  "WO_TEAMMATE_HEAD2" )
        ( WO_TEAMMATE_HEAD3,  "WO_TEAMMATE_HEAD3" )
        ( WO_TEAMMATE_HEAD4,  "WO_TEAMMATE_HEAD4" )
        ( WO_TEAMMATE_HEAD5,  "WO_TEAMMATE_HEAD5" )
        ( WO_TEAMMATE_HEAD6,  "WO_TEAMMATE_HEAD6" )

        ( WO_OPPONENT_HEAD1,  "WO_OPPONENT_HEAD1" )
        ( WO_OPPONENT_HEAD2,  "WO_OPPONENT_HEAD2" )
        ( WO_OPPONENT_HEAD3,  "WO_OPPONENT_HEAD3" )
        ( WO_OPPONENT_HEAD4,  "WO_OPPONENT_HEAD4" )
        ( WO_OPPONENT_HEAD5,  "WO_OPPONENT_HEAD5" )
        ( WO_OPPONENT_HEAD6,  "WO_OPPONENT_HEAD6" )

        ( WO_TEAMMATE_ARM_L1,  "WO_TEAMMATE_ARM_L1" )
        ( WO_TEAMMATE_ARM_L2,  "WO_TEAMMATE_ARM_L2" )
        ( WO_TEAMMATE_ARM_L3,  "WO_TEAMMATE_ARM_L3" )
        ( WO_TEAMMATE_ARM_L4,  "WO_TEAMMATE_ARM_L4" )
        ( WO_TEAMMATE_ARM_L5,  "WO_TEAMMATE_ARM_L5" )
        ( WO_TEAMMATE_ARM_L6,  "WO_TEAMMATE_ARM_L6" )

        ( WO_OPPONENT_ARM_L1,  "WO_OPPONENT_ARM_L1" )
        ( WO_OPPONENT_ARM_L2,  "WO_OPPONENT_ARM_L2" )
        ( WO_OPPONENT_ARM_L3,  "WO_OPPONENT_ARM_L3" )
        ( WO_OPPONENT_ARM_L4,  "WO_OPPONENT_ARM_L4" )
        ( WO_OPPONENT_ARM_L5,  "WO_OPPONENT_ARM_L5" )
        ( WO_OPPONENT_ARM_L6,  "WO_OPPONENT_ARM_L6" )

        ( WO_TEAMMATE_ARM_R1,  "WO_TEAMMATE_ARM_R1" )
        ( WO_TEAMMATE_ARM_R2,  "WO_TEAMMATE_ARM_R2" )
        ( WO_TEAMMATE_ARM_R3,  "WO_TEAMMATE_ARM_R3" )
        ( WO_TEAMMATE_ARM_R4,  "WO_TEAMMATE_ARM_R4" )
        ( WO_TEAMMATE_ARM_R5,  "WO_TEAMMATE_ARM_R5" )
        ( WO_TEAMMATE_ARM_R6,  "WO_TEAMMATE_ARM_R6" )

        ( WO_OPPONENT_ARM_R1,  "WO_OPPONENT_ARM_R1" )
        ( WO_OPPONENT_ARM_R2,  "WO_OPPONENT_ARM_R2" )
        ( WO_OPPONENT_ARM_R3,  "WO_OPPONENT_ARM_R3" )
        ( WO_OPPONENT_ARM_R4,  "WO_OPPONENT_ARM_R4" )
        ( WO_OPPONENT_ARM_R5,  "WO_OPPONENT_ARM_R5" )
        ( WO_OPPONENT_ARM_R6,  "WO_OPPONENT_ARM_R6" )

        ( WO_TEAMMATE_FOOT_L1,  "WO_TEAMMATE_FOOT_L1" )
        ( WO_TEAMMATE_FOOT_L2,  "WO_TEAMMATE_FOOT_L2" )
        ( WO_TEAMMATE_FOOT_L3,  "WO_TEAMMATE_FOOT_L3" )
        ( WO_TEAMMATE_FOOT_L4,  "WO_TEAMMATE_FOOT_L4" )
        ( WO_TEAMMATE_FOOT_L5,  "WO_TEAMMATE_FOOT_L5" )
        ( WO_TEAMMATE_FOOT_L6,  "WO_TEAMMATE_FOOT_L6" )

        ( WO_OPPONENT_FOOT_L1,  "WO_OPPONENT_FOOT_L1" )
        ( WO_OPPONENT_FOOT_L2,  "WO_OPPONENT_FOOT_L2" )
        ( WO_OPPONENT_FOOT_L3,  "WO_OPPONENT_FOOT_L3" )
        ( WO_OPPONENT_FOOT_L4,  "WO_OPPONENT_FOOT_L4" )
        ( WO_OPPONENT_FOOT_L5,  "WO_OPPONENT_FOOT_L5" )
        ( WO_OPPONENT_FOOT_L6,  "WO_OPPONENT_FOOT_L6" )

        ( WO_TEAMMATE_FOOT_R1,  "WO_TEAMMATE_FOOT_R1" )
        ( WO_TEAMMATE_FOOT_R2,  "WO_TEAMMATE_FOOT_R2" )
        ( WO_TEAMMATE_FOOT_R3,  "WO_TEAMMATE_FOOT_R3" )
        ( WO_TEAMMATE_FOOT_R4,  "WO_TEAMMATE_FOOT_R4" )
        ( WO_TEAMMATE_FOOT_R5,  "WO_TEAMMATE_FOOT_R5" )
        ( WO_TEAMMATE_FOOT_R6,  "WO_TEAMMATE_FOOT_R6" )

        ( WO_OPPONENT_FOOT_R1,  "WO_OPPONENT_FOOT_R1" )
        ( WO_OPPONENT_FOOT_R2,  "WO_OPPONENT_FOOT_R2" )
        ( WO_OPPONENT_FOOT_R3,  "WO_OPPONENT_FOOT_R3" )
        ( WO_OPPONENT_FOOT_R4,  "WO_OPPONENT_FOOT_R4" )
        ( WO_OPPONENT_FOOT_R5,  "WO_OPPONENT_FOOT_R5" )
        ( WO_OPPONENT_FOOT_R6,  "WO_OPPONENT_FOOT_R6" )

        ( FLAG_1_L,      "FLAG_1_L" )
        ( FLAG_1_R,      "FLAG_1_R" )
        ( FLAG_2_L,      "FLAG_2_L" )
        ( FLAG_2_R,      "FLAG_2_R" )
        ( GOALPOST_1_L,  "GOALPOST_1_L" )
        ( GOALPOST_1_R,  "GOALPOST_1_R" )
        ( GOALPOST_2_L,  "GOALPOST_2_L" )
        ( GOALPOST_2_R,  "GOALPOST_2_R" )
        ( LINE,  "LINE" )
        ;

struct WorldObject {

    WorldObject() {
        pos.setVecPosition( 0, 0, 0 );
        orien = 0;
        absVel.setX(0); // currently only used for ball and opponent velocities
        absVel.setY(0); // currently only used for ball and opponent velocities
        id = -1;
        currentlySeen = false;
        cycleLastSeen = -1;
        timeLastSeen = -1;
        currentlySeenOrien = false;
        cycleOrienLastSeen = -1;
        timeOrienLastSeen = -1;
        validPosition = false;
        sighting.setVecPosition(0,0,0);
        sightingOrien = 0;
        haveSighting = false;
        sightingTime = -1;
        sightingUNum = 0;
    }

    VecPosition pos; // Global coordinate system position of object
    SIM::AngDeg orien; // Global coordinate system orientation of object

    // Absolute (global coordinate system) velocity
    SIM::Point2D absVel; // currently only used for ball and opponent velocities

    int id; // unique id for all objects that can ever be seen
    bool currentlySeen; // if we currently see an object
    bool currentlySeenOrien; // if we can currently determine object's oreintation
    int cycleLastSeen; // Cycle we last saw object
    double timeLastSeen; // Time we last saw object
    int cycleOrienLastSeen; // Cycle we last determined orientation of object
    double timeOrienLastSeen; // Time we last determined orientation of object
    bool validPosition; // if we believe the objects's position is valid (we looked at where the object should be and don't see it there)
    VisionObject vision;
    VecPosition sighting; // Position of object as reported by teammate
    SIM::AngDeg sightingOrien; // Orientation of object as reported by teammate
    bool haveSighting; // If a teammate has reported seeing object
    double sightingTime; // Time of sighting of object by teammate
    int sightingUNum; // Uniform number of teammate who reported sighting

    vector<VisionObject> lines; // Used for field line observations
};

#endif
