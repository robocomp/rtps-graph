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

#include <thread>
#include <chrono>

#include "cadenaPublisher.h"

//using namespace eprosima::fastrtps;
//using namespace eprosima::fastrtps::rtps;

cadenaPublisher::cadenaPublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

cadenaPublisher::~cadenaPublisher() { eprosima::fastrtps::Domain::removeParticipant(mp_participant);}

bool cadenaPublisher::init()
{
    // Create RTPSParticipant

    eprosima::fastrtps::rtps::Locator_t locator;
    eprosima::fastrtps::rtps::IPLocator::setIPv4(locator, 239, 255, 0 , 1);
    locator.port = 22222;
    
    eprosima::fastrtps::ParticipantAttributes PParam;
    PParam.rtps.defaultMulticastLocatorList.push_back(locator);

    PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
    mp_participant = eprosima::fastrtps::Domain::createParticipant(PParam);
    if(mp_participant == nullptr)
    {
        return false;
    }

    //Register the type

    eprosima::fastrtps::Domain::registerType(mp_participant, static_cast<eprosima::fastrtps::TopicDataType*>(&myType));

    // Create Publisher

    eprosima::fastrtps::PublisherAttributes Wparam;
    Wparam.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    Wparam.topic.topicDataType = myType.getName();  //This type MUST be registered
    Wparam.topic.topicName = "cadenaPubSubTopic";
    Wparam.qos.m_reliability.kind = eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;

    mp_publisher = eprosima::fastrtps::Domain::createPublisher(mp_participant,Wparam,static_cast<eprosima::fastrtps::PublisherListener*>(&m_listener));

    if(mp_publisher == nullptr)
    {
        return false;
    }

    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

void cadenaPublisher::PubListener::onPublicationMatched(eprosima::fastrtps::Publisher* pub, 
                                                        eprosima::fastrtps::rtps::MatchingInfo& info)
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

void cadenaPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }

    // Publication code

    HelloWorld st;

    /* Initialize your structure here */

    int msgsent = 0;
    char ch = 'y';
    do
    {
        mp_publisher->write(&st);  ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << std::endl;
         std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep 250 ms
    } while(true);

    // do
    // {
    //     if(ch == 'y')
    //     {
    //         mp_publisher->write(&st);  ++msgsent;
    //         std::cout << "Sending sample, count=" << msgsent << ", send another sample?(y-yes,n-stop): ";
    //     }
    //     else if(ch == 'n')
    //     {
    //         std::cout << "Stopping execution " << std::endl;
    //         break;
    //     }
    //     else
    //     {
    //         std::cout << "Command " << ch << " not recognized, please enter \"y/n\":";
    //     }
    // } while(std::cin >> ch);
}
