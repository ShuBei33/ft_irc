/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrassar <bbrassar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:34:18 by bbrassar          #+#    #+#             */
/*   Updated: 2022/11/25 10:48:12 by bbrassar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "ChannelMode.hpp"
# include "ChannelPrivilege.hpp"
# include "Client.hpp"
# include "Server.hpp"
# include "Recipient.hpp"

# include <map>
# include <string>
# include <set>
# include <vector>

class Client;
class Server;
class Recipient;

class Channel : public Recipient {

	private:
		struct ClientPrivilege
		{
			Client* client;
			ChannelPrivilege privilege;
		};

	public:
		Channel(Server& server);
		Channel(Server& server, std::string name = std::string(), std::string passwd = std::string());
		Channel(Channel const &src);
		~Channel();

		Channel						&operator=(Channel const &rhs);

		typedef std::vector< ClientPrivilege > ClientList;
		typedef std::set< std::string >	MaskList;

		ChannelMode			mode;
		std::string const	name;
		std::string			topic;
		std::string			passwd;
		unsigned int		userLimit;
		ClientList			allClients;
		MaskList			banMasks;
		MaskList			exceptionMasks;
		MaskList			invitationMasks;

		static ChannelMode const DEFAULT_MODE;

		bool	setName(std::string newName);						// must change cerr for the right stre
		bool	setChanModes(std::string modes);
		void	addClient(Client &newClient, ChannelPrivilege privilege);
		void	removeClient(Client &client);
		bool	hasClient(Client &client) const;

		std::string const& getIdentifier() const;
		void sendMessage(Client& sender, std::string const& message);

		/**
		 * Send a message from a client to all other clients in this channel
		 *
		 * @param sender the sender of the message
		 * @param msg the message to send
		 */
		void broadcast(Client &sender, std::string const msg);
};

#endif
