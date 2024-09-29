#ifndef DOORS_CONTROLLING_SYSTEM_ADMIN_H
#define DOORS_CONTROLLING_SYSTEM_ADMIN_H

#include <sys/types.h>

#include "FcmMessage.h"

FCM_SET_INTERFACE( Admin,
    FCM_DEFINE_MESSAGE(BackendUrlReq);
    FCM_DEFINE_MESSAGE(BackendUrlRsp,
        std::string url{};
    );
    FCM_DEFINE_MESSAGE(DoorStateChangedInd,
        uint doorId{};
        bool open{};
    );
    FCM_DEFINE_MESSAGE(DoorLockChangedInd,
        uint doorId{};
        bool locked{};
    );
);

#endif //DOORS_CONTROLLING_SYSTEM_ADMIN_H
