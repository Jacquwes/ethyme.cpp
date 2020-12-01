#include "include/ethyme.hpp"

#include <iostream>

int main()
{
	Ethyme::Client client("Bot token");

	client.addHandler(Ethyme::EventType::MessageCreate,
		[&](const Ethyme::Events::Event& event)
		{
			auto msgCreate = *(Ethyme::Events::MessageCreate*)&event;

			auto& message = msgCreate.Message();

			if (!message.Author().Bot())
				message.Channel().Send(message.Content());
		});

	try
	{
		client.Start();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}