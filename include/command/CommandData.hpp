/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbouthai <mbouthai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:54:18 by mbouthai          #+#    #+#             */
/*   Updated: 2023/09/24 11:35:12 by mbouthai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

class User;

typedef struct s_data
{
    std::string prefix;
    std::string command;
    std::vector<std::string> arguments;
    std::string trail;
    std::string originalInput;
	bool valid;
    bool trailPresent;
} Data;