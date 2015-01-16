/**
 * Cinder-OLA block
 * by Kevin Siwoff, @kevindefinit
 * Work in progress. See licenses in readme for details.
 * @TODOs: implement boost signals for event binding/handling
 **/

#pragma once
//uncomment this line for full
//ola debug log
//#define CI_OLA_LOG_DEBUG

#include "cinder/Cinder.h"
#include "cinder/Function.h"

#include "ola/Logging.h"
#include "ola/DmxBuffer.h"
#include "ola/client/OlaClient.h"
#include "ola/client/StreamingClient.h"
#include "ola/Constants.h"

//#include <boost/signals2.hpp>


namespace cinder {
class OlaManager {
public:
    OlaManager();
    ~OlaManager();
    
    void                        setup(uint8_t universe);
    void                        setFixture(uint8_t fixtureId, std::vector<uint8_t> colorData);
    void                        setFixturesTo(uint8_t start, uint8_t end, uint8_t colorData);
    void                        sendDmx();
    
//    typedef boost::signals2::signal<void( OlaManager* )> OlaSignal;
//    OlaSignal* getSignal() { return &_signal; }; // Notice we return a pointer to the signal
    
    static const std::vector<uint8_t> black();
    static const std::vector<uint8_t> white();
    
    std::shared_ptr<ola::DmxBuffer> buffer;
    bool                        isSetup = false;
    const uint8_t               getStartUniverse();

private:
    std::shared_ptr<ola::client::StreamingClient> pClient;
protected:
    //    OlaSignal                       _signal;
    uint8_t                         mStartUniverse;
};
}//// namespace cinder