#ifndef DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
#define DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H

#include "FcmFunctionalComponent.h"
#include "ConfigurationDatabase.h"

// Create an Administrator class as subclass of FcmFunctionalComponent
class Administrator : public FcmFunctionalComponent
{
public:
    explicit Administrator(const std::string& nameParam,
                           const FcmSettings& settingsParam = {})
        : FcmFunctionalComponent(nameParam, settingsParam) { /* TODO */ };

    void setConfigurationDatabase(std::shared_ptr<ConfigurationDatabase>& handler)
    {
        configurationDatabase = handler;
    }

    void initialize() override;

protected:
    // References
    std::shared_ptr<ConfigurationDatabase> configurationDatabase;

    // State variables
    std::vector<std::string> pendingEvents;

    void setTransitions() override;
    void setChoicePoints() override;
    void setStates() override;
};

#endif //DOORS_CONTROLLING_SYSTEM_ADMINISTRATOR_H
