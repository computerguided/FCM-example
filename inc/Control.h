#ifndef DOORS_CONTROLLING_SYSTEM_CONTROL_H
#define DOORS_CONTROLLING_SYSTEM_CONTROL_H

#include "FcmMessage.h"

FCM_SET_INTERFACE(Control,
    FCM_DEFINE_MESSAGE(DoorDetectedInd,
        uint doorId{};
    );
    FCM_DEFINE_MESSAGE(ReleaseDoorInd);
    FCM_DEFINE_MESSAGE(SetLockInd,
        bool locked{};
    );
    FCM_DEFINE_MESSAGE(DoorStateChangedInd,
        uint doorId{};
        bool open{};
    );
    FCM_DEFINE_MESSAGE(DoorLockChangedInd,
        uint doorId{};
        bool locked{};
    );
    FCM_DEFINE_MESSAGE(AddTagInd,
        uint tagId{};
    );
    FCM_DEFINE_MESSAGE(RemoveTagInd,
        uint tagId{};
    );
    FCM_DEFINE_MESSAGE(ErrorInd,
        uint doorId{};
        std::string error{};
    );
    FCM_DEFINE_MESSAGE(AlarmInd,
        uint doorId{};
        std::string alarm{};
    );
);

#endif //DOORS_CONTROLLING_SYSTEM_CONTROL_H
