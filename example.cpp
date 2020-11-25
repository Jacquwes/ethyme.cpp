#include "include/ethyme.hpp"

#include <iostream>

int main()
{
	Ethyme::Client client("Bot token");

	client.addHandler(Ethyme::EventType::MessageCreate,
		[&](std::shared_ptr<const Ethyme::Events::Event> event)
		{
			auto msgCreate = std::dynamic_pointer_cast<const Ethyme::Events::MessageCreate>(event);

			auto message = msgCreate->Message();

			std::cout << /*message->Author()->Username() << " sent a message : " <<*/ message->Content() << std::endl;
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