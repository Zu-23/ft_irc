/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <mbouthai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:55:04 by mbouthai          #+#    #+#             */
/*   Updated: 2023/09/24 12:59:07 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteCommand.hpp"
#include "Server.hpp"

//ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
//           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
//           ERR_CHANOPRIVSNEEDED
//           RPL_INVITING                    RPL_AWAY

InviteCommand::InviteCommand()
    : Command("INVITE", true, false)
{}

InviteCommand::~InviteCommand()
{}

InviteCommand::InviteCommand(const InviteCommand& instance) : Command(instance)
{}

InviteCommand& InviteCommand::operator=(const InviteCommand& instance)
{
    if (this != &instance)
        Command::operator=(instance);
    return *this;
}


void InviteCommand::executeCommand(User *user, Data &data)
{   
    if (data.arguments.empty())
    {
        user->sendMessage(ERR_NEEDMOREPARAMS(user->getNickname(), data.command));
        return ;
    }

    const User *userTarget = Server::getInstance()->getUser(data.arguments[0]);
    
    if (!userTarget)
    {
        user->sendMessage(ERR_NOSUCHNICK(data.arguments[0]));
        return ;
    }
    
    Channel *channelTarget = Server::getInstance()->getChannel(data.arguments[1]);

    if (!channelTarget)
        return ;
    
    if (!channelTarget->containsUser(user->getNickname()))
    {
        user->sendMessage(ERR_NOTONCHANNEL(user->getNickname(), data.arguments[1]));
        return ;
    }

    if (channelTarget->containsUser(data.arguments[0]))
    {
        user->sendMessage(ERR_USERONCHANNEL(data.arguments[0], data.arguments[1]));
        return ;
    }

    if (channelTarget->isInviteOnly() 
        && !channelTarget->getUser(user->getNickname()).second.channelOperator)
    {
        user->sendMessage(ERR_CHANOPRIVSNEEDED(user->getNickname(), data.arguments[0]));
        return ;
    }

    channelTarget->inviteUser(data.arguments[0]);

    std::string message = ":" + user->getNickname() + "!" 
        + user->getUsername() + "@" 
        + user->getHostname() + " " 
        + data.command + " " + data.arguments[0] + " " + data.arguments[1];

    if (!userTarget->sendMessage(message))
        return ;

    if (userTarget->isAway())
        user->sendMessage(RPL_AWAY(userTarget->getNickname(), userTarget->getAwayMessage()));
    
    user->sendMessage(RPL_INVITING(data.arguments[1],
        userTarget->getNickname(),
        channelTarget->getName()));

    // :atw.hu.eu.dal.net NOTICE @#new :mouad invited nguy into channel #new
    

}