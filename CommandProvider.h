
#ifndef INTERNALMONITORING_COMMANDPROVIDER_HPP_
#define INTERNALMONITORING_COMMANDPROVIDER_HPP_
#include "Version.h"
#include "Manufacturer.h"
#include <array>
#include <QMainWindow>
#include <Array_mapping.h>

namespace InternalMonitoring {

class CommandProvider {
public:
    virtual uint8_t getPeriodicCommand() = 0;
    virtual void onPollRoundEnd() = 0;
};

}

#endif /* INTERNALMONITORING_COMMANDPROVIDER_HPP_ */
