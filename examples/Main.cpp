/**
 * @file    Main.cpp
 * @brief   Example program for the simple LoggerC++ system
 *
 * Copyright (c) 2013 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
*/
#include "../src/LoggerCpp.h"


/**
 * @brief Simple test class
 */
class Tester {
public:
    Tester() :
        mLogger("Tester")
    {
    }

    void constTest (void) const {
        mLogger.debug() << "log within a const method";
    }

private:
    Log::Logger mLogger; //!< A named logger to produce log
};



/**
 * @brief Simple example program
 */
int main (void)
{
    Log::Logger logger("TestLog");

    logger.debug() << "NO logs before configure";
    // Configure the Log Manager (create the Output objects)
    Log::Manager::configure();

    Tester tester;
    tester.constTest();

    logger.debug()  << "Debug.";
    logger.info()   << "Info.";
    logger.notice() << "Notice.";
    logger.warning()<< "Warning.";

    logger.setLevel(Log::Log::eWarning);

    logger.debug()  << "Debug.";
    logger.info()   << "Info.";
    logger.notice() << "Notice.";
    logger.warning()<< "Warning.";
    logger.error()  << "Error.";
    logger.critic() << "Critic.";

    logger.setLevel(Log::Log::eDebug);
    logger.debug() << "Variable = " << std::hex << 0x75af0 << " test";
    logger.debug() << "Variable = " << std::right << std::setfill('0') << std::setw(8) << 76035 << " test";

    Log::Logger logger2("TestLog");
    Log::Logger logger3("OtherChannel");
    logger.debug() << "First logger to the Channel";
    logger2.debug() << "Second logger to the Channel";
    logger3.debug() << "Third logger, other Channel";
    logger.setLevel(Log::Log::eInfo);
    logger.debug() << "first logger inhibited";
    logger2.debug() << "second logger also disabled";
    logger3.debug() << "third logger still active";
    logger.setLevel(Log::Log::eDebug);
    logger.debug() << "first logger re-activated";
    logger2.debug() << "second logger also re-activated";
    logger3.debug() << "third logger always active";

    // Terminate the Log Manager (destroy the Output objects)
    Log::Manager::terminate();
    logger.debug() << "NO more logs here";

    return 0;
}
