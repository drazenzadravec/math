// MathWolfram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#include "stdafx.h"

/// <summary>
/// Input loop and evaluator
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	// if arguments exist.
	if (argc > 1)
	{
		// open confg file
		std::string line;
		std::ifstream appConfig("app.config");
		if (appConfig.is_open())
		{
			// get first line
			std::getline(appConfig, line);
			appConfig.close();
		}
		else
		{
			std::cout << "Unable to open file";
			return 1;
		}

		// create the command
		std::string commandLine = "-linkmode launch -linkname \"" + line + "\"";

		WSENV env;
		WSLINK link;
		int error;

		// WSTP Initialise
		env = WSInitialize((WSEnvironmentParameter)0);
		if (env == (WSENV)0)
		{
			std::cout << "Unable to initialize";
			return 1;
		}

		// WSTP Open a connection to the wolfram kernel
		link = WSOpenString(env, commandLine.c_str(), &error);
		if (link == (WSLINK)0 || error != WSEOK)
		{
			std::cout << "Unable to create link";
			return 1;
		}

		// WSTP Activate link
		if (!WSActivate(link))
		{
			std::cout << "Link not activated!";
			return 1;
		}

		// the expression
		LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8> expression(link);

		// until result.
		while (true)
		{
			// get input name
			std::string inputNameString;
			LLU::WS::Function inputPacketFunction;
			expression >> inputPacketFunction;

			// get current header name
			std::string head = inputPacketFunction.getHead();
			int argCount = inputPacketFunction.getArgc();

			// new line
			std::cout << std::endl;

			// if return the exit
			if (head == "ReturnTextPacket")
			{
				// new line
				std::cout << std::endl;
			}

			if (argCount < 10)
			{
				// for each arg count
				for (int i = 0; i < argCount; i++)
				{
					// write the name string.
					expression >> inputNameString;
					std::cout << inputNameString;
				}
			}

			// if output
			if (head == "OutputNamePacket"){}

			// if return then exit
			if (head == "ReturnTextPacket")
			{
				// exit loop
				break;
			}

			// if input add the argument
			if (head == "InputNamePacket")
			{
				LLU::WS::Function enterTextFunction("EnterTextPacket", 1);
				expression << enterTextFunction << argv[1];
			}

			// if error
			if (head == "MessagePacket")
			{
				// exit loop
				break;
			}
		}

		// close.
		WSClose(link);
		WSDeinitialize(env);
	}
	else
	{
		// must have arguments
		std::cout << "Add arguments";
	}
	return 0;
}
