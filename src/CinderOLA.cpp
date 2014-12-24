#include "CinderOla.h"



using namespace std;

namespace cinder {

/////////////////////////////////////////
///// OlaManager
/////////////////////////////////////////
OlaManager::OlaManager(){
    buffer = make_shared<ola::DmxBuffer>();
    pClient = new ola::client::StreamingClient(ola::client::StreamingClient::Options());
    ola::InitLogging(ola::OLA_LOG_DEBUG, ola::OLA_LOG_STDERR);
    
    if (!buffer->Blackout()){
        cerr << "Couldn\'t reset buffer to 0s" << endl;
    }
    if (!pClient->Setup()) {
        cerr << "OLA Setup Failed" << endl;
    }
    else {
        bOladSetup = true;
        cout << "Connected to OLAD" << endl;
    }
};

OlaManager::~OlaManager(){
    delete pClient;
};

static const vector<uint8_t> black(){
    vector<uint8_t> bgr {static_cast<uint8_t>(0), static_cast<uint8_t>(0), static_cast<uint8_t>(0)};
    return bgr;
};

static const std::vector<uint8_t> white(){
    vector<uint8_t> bgr {static_cast<uint8_t>(255), static_cast<uint8_t>(255), static_cast<uint8_t>(255)};
    return bgr;
};

void    OlaManager::setFixture(uint8_t fixtureId, std::vector<uint8_t> colorData){
    int offset = fixtureId * 3; //set fixture offset
    //std::cout << "the starting channel is: " + std::to_string(fixtureId) << std::endl;
    buffer->SetRange(offset, colorData.data(), 3);
    //std::cout << *buffer << std::endl;
};

void OlaManager::setFixturesTo(uint8_t start, uint8_t end, uint8_t colorData){
    buffer->SetRangeToValue(start, colorData, 512);
};

}//// namespace cinder