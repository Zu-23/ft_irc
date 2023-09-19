/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <mbouthai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:55:04 by mbouthai          #+#    #+#             */
/*   Updated: 2023/09/19 02:02:02 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrivMsgCommand.hpp"
#include "Utilities.hpp"

//ERR_NORECIPIENT D                 ERR_NOTEXTTOSEND D
//           ERR_CANNOTSENDTOCHAN D           ERR_NOTOPLEVEL
//           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS D
//           ERR_NOSUCHNICK D
//           RPL_AWAY D

PrivMsg::PrivMsg() : Command("PRIVMSG", true, false)
{}

PrivMsg::~PrivMsg()
{}

PrivMsg::PrivMsg(const PrivMsg& instance) : Command(instance)
{}

PrivMsg& PrivMsg::operator=(const PrivMsg& instance)
{
    if (this != &instance)
        Command::operator=(instance);
    return *this;
}

void PrivMsg::executeCommand(User *user, Data &data)
{   
    if (data.arguments.empty())
    {
        user->sendMessage(ERR_NORECIPIENT(data.command));
        return ;
    }

    if (data.arguments.size() == 1 && data.trail.empty())
    {
        user->sendMessage(ERR_NOTEXTTOSEND);
        return ;
    }

    std::vector<std::string> recipients = split(data.arguments[0], ',');

    if (recipients.size() > 3)
    {
        user->sendMessage(ERR_TOOMANYTARGETS(data.arguments[0],
            "ERR_TOOMANYTARGETS",
            "Bruv, are u okay?, reduce them targets and try again"));
        return ;
    }

    std::string message = ":" + user->getNickname() + "!" 
        + user->getUsername() + "@" 
        + user->getHostname() + " " 
        + data.command + " " + data.arguments[0] + " :";
    
    message += data.arguments.size() == 1 ? data.trail : data.arguments[1];
    
    for (std::vector<std::string>::const_iterator it = recipients.begin();
        it != recipients.end();
        it++)
    {
        const User *userTarget = Server::getInstance()->getAuthenticatedUser(*it);

        if (userTarget)
        {
            if (userTarget->getNickname() == user->getNickname())
                continue ;
                
            userTarget->sendMessage(message);
            
            if (userTarget->isAway())
                user->sendMessage(RPL_AWAY(userTarget->getNickname(), userTarget->getAwayMessage()));
        }
        else
        {
            const Channel *channelTarget = Server::getInstance()->getChannel(*it);

            if (!channelTarget)
            {
                user->sendMessage(ERR_NOSUCHNICK(*it));
                continue;
            }

            const std::pair<User *, Modes>& channelUser = channelTarget->getUser(user->getNickname());

            if ((!channelUser.first && channelTarget->isExternalMessagesEnabled())
                || (channelTarget->isUserBanned(user->getNickname()))
                || (!channelUser.second.channelOperator 
                    && !channelUser.second.voice 
                    && channelTarget->isModerated()))
            {
                user->sendMessage(ERR_CANNOT_SEND_TO_CHAN(user->getNickname(),
                    channelTarget->getName()));
                continue;
            }
            
            channelTarget->broadcast(user->getNickname(), message);
        }
        
    }
}