// MathWolfram.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "stdafx.h"
#include "stdafx.cpp"

/// <summary>
/// input loop and evaluator
/// </summary>
/// <param name="argc">length</param>
/// <param name="argv">arguments</param>
/// <returns>0 if ok; else 1</returns>
int main(int argc, char* argv[])
{
	// if arguments exist.
	if (argc > 1)
	{
		// open confg file
		std::string line;
		std::string appConfigFile = "./app.config";
		int loopMax = 2000;
		int loopCount = 0;

		// if app config path
		if (argc > 2) {
			std::string path(argv[2]);
			appConfigFile = path + "app.config";
		}

		// open the file
		std::ifstream appConfig(appConfigFile);
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

		// check if math link file exits
		std::ifstream mathlinkFile(line.c_str());

		// If file exists.
		if (!mathlinkFile.good())
		{
			std::cout << "Unable to open math link file";
			return 1;
		}
		else
		{
			// Close the file stream.
			mathlinkFile.close();
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
			std::cout << "Link not activated";
			return 1;
		}

		// the expression
		LLU::WSStream<LLU::WS::Encoding::UTF8, LLU::WS::Encoding::UTF8> expression(link);
		std::stringstream resultStream;

		// until result.
		while (loopCount <= loopMax)
		{
			// count loop
			loopCount = loopCount + 1;
			
			// get input name
			std::string inputNameString;
			LLU::WS::Function inputPacketFunction;
			expression >> inputPacketFunction;

			// get current header name
			std::string head = inputPacketFunction.getHead();
			int argCount = inputPacketFunction.getArgc();

			// new line
			resultStream << "placeholder" << std::endl;

			// if return then exit
			if (head == "ReturnTextPacket")
			{
				// new line
				resultStream << "placeholder" << std::endl;
			}

			if (argCount < 10)
			{
				// for each arg count
				for (int i = 0; i < argCount; i++)
				{
					// write the name string.
					expression >> inputNameString;
					resultStream << inputNameString;
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

		// exit wolfram
		WSPutFunction(link, "Exit", 0);
		if (WSError(link)) 
		{
			// write the error
			std::cout << WSErrorMessage(link) << std::endl;
		}
		else
		{
			// too many loops some error
			if (loopCount >= loopMax)
			{
				std::cout << "$Failed with loop error" << std::endl;
			}
			else
			{
				// temp store
				std::string resultString = resultStream.str();
				bool replacedString = false;

				// remove the place holder
				replacedString = replace_string(resultString, "placeholder\nIn[1]:= placeholder\n", "");
				replacedString = replace_string(resultString, "Out[1]= placeholder\nplaceholder\n", "");

				// new string
				std::cout << resultString << std::endl;
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
