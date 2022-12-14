/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/12/14 17:03:22 by lrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ChannelMode.hpp"
# include "ChannelPrivilege.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Recipient.hpp"
# include "Reply.hpp"

# include <map>
# include <string>
# include <set>
# include <vector>

class Client;
class Server;
class Recipient;

class Channel : public Recipient {

	public:
		Channel(Server* server);
		Channel(Server* server, std::string name = std::string(), std::string passwd = std::string());
		Channel(Channel const &src);
		~Channel();
		Channel				&operator=(Channel const &rhs);

		struct ClientPrivilege
		{
			Client* client;
			ChannelPrivilege privilege;
		};
		
		typedef std::vector< ClientPrivilege > ClientList;
		typedef std::set< std::string >	MaskList;

		std::string const	name;
		std::string			topic;
		std::string			passwd;
		ChannelMode			mode; // will comment later
		std::string			modes;
		bool				inviteMode;
		bool				keyMode;
		bool				usrLimitMode;
		unsigned int		userLimit;
		ClientList			allClients;
		MaskList			allChanOps;
		MaskList			invitationMasks;
		MaskList			banMasks; // not used yet
		MaskList			exceptionMasks; // not used

		static ChannelMode const DEFAULT_MODE;

		bool	setName(std::string newName);						// must change cerr for the right stream
		void	addChanModes(std::string newModes);
		void	removeChanModes(std::string byeModes);
		void	addChanOps(std::string nick);
		void	removeChanOps(std::string nick);
		void	addClient(Client &newClient, ChannelPrivilege privilege);
		void	removeClient(Client &client);
		bool	hasClient(Client &client) const;

		int		getClientPriv(Client &client);

		// Recipient overloads
		std::string const& getIdentifier() const;
		void sendMessage(Client& sender, std::string const& command, std::string const& message);
		//
};

#endif
