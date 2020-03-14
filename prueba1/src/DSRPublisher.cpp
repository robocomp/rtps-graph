// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file cadenaPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/Domain.h>
#include <fastrtps/transport/UDPv4TransportDescriptor.h>

#include <thread>
#include <chrono>
#include "DSRPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

DSRPublisher::DSRPublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

DSRPublisher::~DSRPublisher() 
{ 
    eprosima::fastrtps::Domain::removeParticipant(mp_participant);
}

bool DSRPublisher::init()
{
    // Create RTPSParticipant     
    eprosima::fastrtps::ParticipantAttributes PParam;
    PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
    
    //Create a descriptor for the new transport.
    auto custom_transport = std::make_shared<UDPv4TransportDescriptor>();
    custom_transport->sendBufferSize = 65000;
    custom_transport->receiveBufferSize = 65000;
    custom_transport->maxMessageSize = 65000;
    custom_transport->interfaceWhiteList.emplace_back("127.0.0.1");
    //custom_transport->interfaceWhiteList.emplace_back("192.168.1.253");
    

    //Disable the built-in Transport Layer.
    PParam.rtps.useBuiltinTransports = false;

    //Link the Transport Layer to the Participant.
    PParam.rtps.userTransports.push_back(custom_transport);

    mp_participant = eprosima::fastrtps::Domain::createParticipant(PParam);

    if(mp_participant == nullptr)
    {
        return false;
    }

    //Register the type
    eprosima::fastrtps::Domain::registerType(mp_participant, static_cast<eprosima::fastrtps::TopicDataType*>(&dsrdeltaType));

    // Create Publisher
    eprosima::fastrtps::PublisherAttributes Wparam;
    Wparam.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    Wparam.topic.topicDataType = dsrdeltaType.getName();  //This type MUST be registered
    Wparam.topic.topicName = "DSRDeltaPubSubTopic";
    eprosima::fastrtps::rtps::Locator_t locator;
    eprosima::fastrtps::rtps::IPLocator::setIPv4(locator, 239, 255, 0 , 1);
    locator.port = 7900;
    Wparam.multicastLocatorList.push_back(locator);
    Wparam.qos.m_reliability.kind = eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;
    Wparam.qos.m_publishMode.kind = eprosima::fastrtps::ASYNCHRONOUS_PUBLISH_MODE;
    Wparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    mp_publisher = eprosima::fastrtps::Domain::createPublisher(mp_participant,Wparam,static_cast<eprosima::fastrtps::PublisherListener*>(&m_listener));

    //Wparam.times.heartbeatPeriod.nanosec = 500000000; //500 ms
    if(mp_publisher == nullptr)
    {
        return false;
    }
    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

eprosima::fastrtps::rtps::GUID_t DSRPublisher::getParticipantID() const
{   
    return mp_participant->getGuid();
}

void DSRPublisher::PubListener::onPublicationMatched(eprosima::fastrtps::Publisher* pub, eprosima::fastrtps::rtps::MatchingInfo& info)
{
    (void)pub;
    if (info.status == eprosima::fastrtps::rtps::MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Publisher matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Publisher unmatched" << std::endl;
    }
}

void DSRPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }
    std::cout << __FUNCTION__ << " HOLA" << std::endl;
    
    // Publication code
    DSRDelta st;
    std::vector<int32_t> caca(10000, 0);
    int j=0;
    for(auto &i : caca)
        i = j++;
    st.load(caca);
    
    /* Initialize your structure here */

    int msgsent = 0;
  
    do
    {
        mp_publisher->write(&st);  
        ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << " " << st.load().size() * 4 << std::endl;
        std::this_thread::sleep_for(std::chrono::microseconds(1000000)); // Sleep 250 ms
    } while(true);
}
