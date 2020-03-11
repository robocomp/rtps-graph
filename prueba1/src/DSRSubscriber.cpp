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
 * @file cadenaSubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/transport/UDPv4TransportDescriptor.h>
#include <fastrtps/Domain.h>

#include "DSRSubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

DSRSubscriber::DSRSubscriber() : mp_participant(nullptr), mp_subscriber(nullptr) {}

DSRSubscriber::~DSRSubscriber() {	Domain::removeParticipant(mp_participant);}

bool DSRSubscriber::init()
{

    // Create RTPSParticipant

    ParticipantAttributes PParam;
    PParam.rtps.setName("Participant_subscriber"); //You can put the name you want
    //PParam.rtps.builtin.domainId = 80;
    
    //Create a descriptor for the new transport.
    auto custom_transport = std::make_shared<eprosima::fastrtps::rtps::UDPv4TransportDescriptor>();
    custom_transport->sendBufferSize = 65000;
    custom_transport->receiveBufferSize = 65000;
    custom_transport->maxMessageSize = 65000;
    custom_transport->interfaceWhiteList.emplace_back("192.168.1.253");

    //Disable the built-in Transport Layer.
    PParam.rtps.useBuiltinTransports = false;

    //Link the Transport Layer to the Participant.
    PParam.rtps.userTransports.push_back(custom_transport);
    
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant == nullptr)
    {
        return false;
    }

    //Register the type
    Domain::registerType(mp_participant, static_cast<TopicDataType*>(&dsrdeltaType));

    // Create Subscriber
    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = dsrdeltaType.getName(); //Must be registered before the creation of the subscriber
    Rparam.topic.topicName = "DSRDeltaPubSubTopic";
    eprosima::fastrtps::rtps::Locator_t locator;
    IPLocator::setIPv4(locator, 239, 255, 0 , 1);
    locator.port = 7900;
    Rparam.multicastLocatorList.push_back(locator);
    Rparam.qos.m_reliability.kind = eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;
    Rparam.historyMemoryPolicy = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    mp_subscriber = Domain::createSubscriber(mp_participant, Rparam, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    return true;
}

void DSRSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub, MatchingInfo& info)
{
    (void)sub;
    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched" << std::endl;
    }
}

void DSRSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    // Take data
    DSRDelta st;
    //std::cout << "Sample received" << std::endl;
    if(sub->takeNextData(&st, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            // Print your structure data here.
            ++n_msg;
            std::cout << "Sample received, count=" << n_msg << " " << st.load().size() * 4 << std::endl;
            //int j= 0;
            // for(auto i: st.load())
            //     if( i != j++)
            //     {
            //         std::cout << "SHIT" << std::endl;
            //         exit(-1);
            //     }
        }
    }
    //fps.print(1000, st.load().size() * 4 * 8);
    //std::cout << "Sample received, count=" << n_msg << " " << st.load().size() * 4 *f << " bps" << std::endl;
}

void DSRSubscriber::run()
{
    std::cout << "Waiting for Data, press Enter to stop the Subscriber. "<<std::endl;
    std::cin.ignore();
    std::cout << "Shutting down the Subscriber." << std::endl;
}
