#ifndef DOORS_CONTROLLING_SYSTEM_SENSING_H
#define DOORS_CONTROLLING_SYSTEM_SENSING_H

#include "FcmMessage.h"

FCM_SET_INTERFACE(Sensing,
    FCM_DEFINE_MESSAGE(DoorDetectedInd,
        uint doorId{};
    );
    FCM_DEFINE_MESSAGE(LockSensorInd,
        bool locked{};
    );
    FCM_DEFINE_MESSAGE(DoorSensorInd,
        bool open{};
    );
    FCM_DEFINE_MESSAGE(LockFailInd);
    FCM_DEFINE_MESSAGE(UnlockFailInd);
);

#endif //DOORS_CONTROLLING_SYSTEM_SENSING_H
