#ifndef DOORS_CONTROLLING_SYSTEM_CONFIG_H
#define DOORS_CONTROLLING_SYSTEM_CONFIG_H

#include "FcmMessage.h"

FCM_SET_INTERFACE( Config,
    FCM_DEFINE_MESSAGE( InitializedInd );
    FCM_DEFINE_MESSAGE( BackendUrlInd,
        std::string url{};
    );
    FCM_DEFINE_MESSAGE( EventStoredInd );
);

#endif //DOORS_CONTROLLING_SYSTEM_CONFIG_H
