
/*
	___  __      __  ___
   |   \ \ \    / / | __|
   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI client
   |___/   \_/\_/___|_|_    version 0.1.0
  |"""""| |"""""""""""""|   https://github.com/
 _|     |_|   Web API   |
 "`-0-0-'"`-0-0-----0-0-'

 Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 SPDX-License-Identifier: MIT
 Copyright (c) 2020 Yasuo Matsubara

 Permission is hereby  granted, free of charge, to any  person obtaining a copy
 of this software and associated  documentation files (the "Software"), to deal
 in the Software  without restriction, including without  limitation the rights
 to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
 copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
 IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
 FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
 AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
 LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*/

#include "pch.h"

#include <iostream>
#include <array>
#include <regex>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "cxxopts/cxxopts.hpp"
#include "dwf-webapi-client.hpp"

//using namespace std;
using json = nlohmann::json;


int main(int argc, char* argv[])
{
	std::string hostname;
	int port;

	try
	{
		cxxopts::Options options(argv[0], " - a Waveforms-WebAPI client");

		options.add_options()
			("n,hostname", "Hostname, e.g., 127.0.0.1", cxxopts::value<std::string>()->default_value("localhost"))
			("f,hostnamefile", "Hostname file from which a hostname is taken", cxxopts::value<std::string>()->default_value("./hostname.txt"))
			("p,port", "Port number", cxxopts::value<int>()->default_value("8000"))
			("h,help", "Print usage")
			;

		auto result = options.parse(argc, argv);

		if (result.count("help"))
		{
			std::cout << options.help() << std::endl;
			return 0;
		}

		if (result.count("hostname"))
		{
			hostname = result["hostname"].as<std::string>();
		}
		else
		{
			std::string fn = result["hostnamefile"].as<std::string>();
			std::ifstream ifs(fn, std::ios::in);

			if (ifs.fail()) {
				std::cerr << "Failed to hostname file." << std::endl;
				hostname = "localhost";
			}
			else
			{
				ifs >> hostname;
				//std::string str;
				//while (getline(ifs, str)) {
				//	std::cout << "#" << str << std::endl;
				//}
				if (!hostname.length())
				{
					hostname = "localhost";
				}
			}
		}

		port = result["port"].as<int>();
	}
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		return 1;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Digilent Waveforms-WebAPI client starts on " << hostname << ":" << port << std::endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////


	Dwf::WebAPI::Client::SetServer(hostname, port, "dwf-webapi", "123456789");

	int device = -1;
	HDWF hdwf = -1;
	char szError[512] = { 0 };
	char szVersion[32] = { 0 };

	int status = FDwfDeviceOpen(device, &hdwf);
	if (hdwf == 0 || hdwf == -1)
	{
		FDwfGetLastErrorMsg(szError);
		std::cout << "Cannot open device - status code: " << szError << std::endl;

		return 1;
	}

	FDwfGetVersion(szVersion);
	std::cout << "Connected to AnalogDiscovery." << szVersion << std::endl;

	FDwfDeviceClose(hdwf);


	return 0;
}

