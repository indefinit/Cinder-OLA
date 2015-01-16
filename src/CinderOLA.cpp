#include "CinderOla.h"



using namespace std;

namespace cinder {

/////////////////////////////////////////
///// OlaManager
/////////////////////////////////////////
OlaManager::OlaManager()
{    
};

OlaManager::~OlaManager()
{
};

void OlaManager::setup(uint8_t universe)
{
    buffer = make_shared<ola::DmxBuffer>();
//    pClient = new ola::client::StreamingClient(ola::client::StreamingClient::Options());
    
    pClient = make_shared<ola::client::StreamingClient>(ola::client::StreamingClient::Options());
#ifdef CI_OLA_LOG_DEBUG
    ola::InitLogging(ola::OLA_LOG_DEBUG, ola::OLA_LOG_STDERR);
#else
    ola::InitLogging(ola::OLA_LOG_WARN, ola::OLA_LOG_STDERR);
#endif
    
    if (!buffer->Blackout()){
        cerr << "Couldn\'t reset buffer to 0s" << endl;
    }
    if (!pClient->Setup()) {
        cerr << "OLA Setup Failed" << endl;
    }
    else {
        isSetup = true;
        mStartUniverse = universe;
        cout << "Connected to OLAD" << endl;
    }
}
    
const uint8_t OlaManager::getStartUniverse()
{
    return mStartUniverse;
}
    
static const vector<uint8_t> black(){
    vector<uint8_t> bgr {static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0)};
    return bgr;
};

static const std::vector<uint8_t> white(){
    vector<uint8_t> bgr {static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255)};
    return bgr;
};

void    OlaManager::setFixture(uint8_t fixtureId, const std::vector<uint8_t> colorData){
    int offset = fixtureId * 3; //set fixture offset
    //std::cout << "the starting channel is: " + std::to_string(fixtureId) << std::endl;
    buffer->SetRange(offset, colorData.data(), 3);
    //std::cout << *buffer << std::endl;

};

void OlaManager::setFixturesTo(uint8_t start, uint8_t end, uint8_t colorData){
    buffer->SetRangeToValue(start, colorData, 512);
};

void OlaManager::sendDmx(){
    if (!pClient->SendDmx(getStartUniverse(), *buffer)){
        std::cerr << "error sending dmx" << std::endl;
    }
    if(!buffer->Blackout()){
        std::cerr << "couldnt blackout buffer" << std::endl;
    }
//    _signal( this ); //dispatch event to listeners
};

}//// namespace cinder