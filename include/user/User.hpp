/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <mbouthai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:52:44 by mbouthai          #+#    #+#             */
/*   Updated: 2023/09/24 11:27:52 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>

class User
{
    private:
        const int             _socket;

        std::string     _nickname;
        std::string     _username;
        std::string     _fullname;
        std::string     _hostname;
	    std::string	    _partialMessage;
        std::string     _awayMessage;
        
        bool            _authenticated;
        bool            _away;

        bool             _usedPassword;
        int              _joinedChannelsCount;

    protected:
    
        User();
        
    public:

        ~User();
        User(const User& instance);
        User& operator=(const User& instance);

        User(int socket);

        int          getSocket() const;

        const std::string&    getNickname() const;
        const std::string&    getUsername() const;
        const std::string&    getFullname() const;
        const std::string&    getHostname() const;
        
        const std::string&    getPartialMessage() const;
        const std::string&    getAwayMessage() const;
        
        bool            isAuthenticated() const;
        bool            isAway() const;

        bool      hasUsedPassword() const;

        int         getJoinedChannelsCount() const;

        void    setNickname(const std::string& nickname);
        void    setUsername(const std::string& username);
        void    setFullname(const std::string& fullname);
        void    setHostname(const std::string& hostname);

        void    setPartialMessage(const std::string& msgpartial);
        void    setAwayMessage(const std::string& message);

        void    setAuthenticated(bool authenticated);
        void    setAway(bool boolean);

        void    setUsedPassword(bool b);

        void    setJoinedChannelsCount(int count);

        bool    sendMessage(const std::string &message) const;

};

std::ostream&	operator<<(std::ostream& outputStream, const User& user);
