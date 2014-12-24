#pragma once

#include "cinder/Cinder.h"
#include "cinder/Function.h"

#include "ola/Logging.h"
#include "ola/DmxBuffer.h"
#include "ola/client/OlaClient.h"
#include "ola/client/StreamingClient.h"
#include "ola/Constants.h"

namespace cinder {
class OlaManager {
public:
    bool                        bOladSetup = false;
    OlaManager();
    ~OlaManager();
    static const std::vector<uint8_t> black();
    static const std::vector<uint8_t> white();
    
    void                        setFixture(uint8_t fixtureId, std::vector<uint8_t> colorData);
    void                        setFixturesTo(uint8_t start, uint8_t end, uint8_t colorData);

    std::shared_ptr<ola::DmxBuffer> buffer;
    
private:
    ola::client::StreamingClient *pClient;
};
}//// namespace cinder