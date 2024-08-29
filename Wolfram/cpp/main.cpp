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
		bool isError = false;

		// if app config path
		if (argc > 2) {
			std::string path(argv[2]);
			appConfigFile = path + "app.config";
		}
		else
		{
			// get the executing path
			char result[PATH_MAX];
			ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
			if (count >= 0)
				result[count] = '\0';

			// get path and exe name
			std::string pathExe(result);
			std::string exeName(argv[0]);

			// replace exe name with empty in path.
			replace_string(exeName, "./", "");
			replace_string(exeName, ".\\", "");
			replace_string(pathExe, exeName, "");

			// config path
			appConfigFile = pathExe + "app.config";
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

		// create the command
		std::string commandLine = line;

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
			if (head == "OutputNamePacket") {}

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

			// if error
			if (WSError(link))
			{
				// exit loop
				isError = true;
				break;
			}
		}

		// if error
		if (isError)
		{
			// write the error
			std::cout << WSErrorMessage(link) << std::endl;
		}

		// exit wolfram
		WSPutFunction(link, "Exit", 0);
		if (WSError(link))
		{
			// write the error
			isError = true;
			std::cout << WSErrorMessage(link) << std::endl;
		}

		// if no error
		if (!isError)
		{
			// too many loops some error
			if (loopCount >= loopMax)
			{
				std::cout << "$Failed with loop error" << std::endl;
			}
			else
			{
				// remove the line with the word 'placeholder'
				std::stringstream resultStreamExclude_placeholder = if_line_in_stream_contains_exclude(resultStream, "placeholder");
				std::stringstream resultStreamExclude_syntax = if_line_in_stream_contains_exclude(resultStreamExclude_placeholder, "Syntax:");
				std::stringstream result_stream = if_line_in_stream_contains_exclude(resultStreamExclude_syntax, "syntax:");

				// attempt to find an error
				if (find_error_in_stream(result_stream))
				{
					// new string
					std::cout << "$Failed syntax error or other" << std::endl;
				}
				else
				{
					// temp store
					std::string resultString = result_stream.str();
					std::cout << resultString << std::endl;
				}
			}
		}
		else
		{
			std::cout << "$Failed internal wolfram error" << std::endl;
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