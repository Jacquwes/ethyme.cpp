#include "include/ethyme.hpp"

#include <iostream>

int main()
{
	auto client = new Ethyme::Client("Bot token");

	client->addHandler(Ethyme::EventType::MessageCreate,
		[&](std::shared_ptr<const Ethyme::Events::Event> event)
		{
			auto msgCreate = std::dynamic_pointer_cast<const Ethyme::Events::MessageCreate>(event);

			auto message = msgCreate->Message();

			if (!message->Author()->Bot())
				message->Channel()->Send(message->Content());
			return;
		});

	try
	{
		client->Start();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
}