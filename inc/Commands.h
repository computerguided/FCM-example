#ifndef DOORS_CONTROLLING_SYSTEM_COMMANDS_H
#define DOORS_CONTROLLING_SYSTEM_COMMANDS_H

#include "FcmMessage.h"

FCM_SET_INTERFACE(Commands,
    FCM_DEFINE_MESSAGE(ConnectedInd);
    FCM_DEFINE_MESSAGE(LockDoorInd,
        uint doorId{};
    );
    FCM_DEFINE_MESSAGE(UnlockDoorInd,
        uint doorId{};
    );
    FCM_DEFINE_MESSAGE(AddTagInd,
        uint doorId{};
        uint tagId{};
    );
    FCM_DEFINE_MESSAGE(RemoveTagInd,
        uint doorId{};
        uint tagId{};
    );
    FCM_DEFINE_MESSAGE(KeepAliveInd);
);

#endif //DOORS_CONTROLLING_SYSTEM_COMMANDS_H
