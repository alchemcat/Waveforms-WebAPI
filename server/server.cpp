
/*
	___  __      __  ___
   |   \ \ \    / / | __|
   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI server
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
#include <csignal>
#include <regex>

#define CPPHTTPLIB_OPENSSL_SUPPORT

#include "cpp-httplib/httplib.h"
#include "nlohmann/json.hpp"
#include "cxxopts/cxxopts.hpp"
#include "dwf-webapi-server.hpp"

//using namespace std;
using json = nlohmann::json;


#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
	httplib::SSLServer svr("./server.crt.pem", "./server.key.pem");

	//(generate private key) $ openssl genrsa - out server.key.pem
	//        (generate CSR) $ openssl req - new - sha256 - key server.key.pem - out server.csr.pem
	//        (generate CRT) $ openssl x509 - req - in server.csr.pem - signkey server.key.pem - out server.crt.pem - days 7300 - extensions server
	//   (check CRT content) $ openssl x509 - inform PEM - text - noout - in server.crt.pem

#else
	httplib::Server svr;
#endif
Dwf::WebAPI::Server apiserver;

void signal_handler(int signal)
{
	// only async-signal-safe functions should be called here!

	svr.stop();
	apiserver.CloseAllDevices();
}

void change_key(json &object, const std::string& old_key, const std::string& new_key)
{
	// usage : change_key(jreq, it.key(), sanitized_key);

	if (old_key != new_key)
	{
		// get iterator to old key; TODO: error handling if key is not present
		json::iterator it = object.find(old_key);
		// create null value for new key and swap value from old key
		std::swap(object[new_key], it.value());
		// delete value at old key (cheap, because the value is null after swap)
		object.erase(it);
	}
}

int main(int argc, char* argv[])
{
	if (signal(SIGINT, signal_handler) == SIG_ERR)
	{
		std::cout << "SIG_ERR: Failure to capture signals." << std::endl;
		return 1;
	}

	int port;
	std::string hostname;

	try
	{
		cxxopts::Options options(argv[0], " - a Waveforms-WebAPI server");

		options.add_options()
			("n,hostname", "Hostname, e.g., 127.0.0.1.", cxxopts::value<std::string>()->default_value("0.0.0.0"))
			("p,port", "Port number listened", cxxopts::value<int>()->default_value("8000"))
			("h,help", "Print usage")
			;

		auto result = options.parse(argc, argv);

		if (result.count("help"))
		{
			std::cout << options.help() << std::endl;
			return 0;
		}

		port = result["port"].as<int>();
		hostname = result["hostname"].as<std::string>();
	}
	catch (const cxxopts::OptionException& e)
	{
		std::cout << "error parsing options: " << e.what() << std::endl;
		return 1;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Digilent Waveforms-WebAPI server starts on " << hostname << ":" << port << std::endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////


	svr.Post("/", [](const httplib::Request& req, httplib::Response& res) // [&apiserver] captures a local variable.
	{
		// Basic Authorization
		std::cout << "authorization: " << std::endl;
		std::string hash_tested = req.get_header_value("Authorization");
		std::cout << hash_tested << std::endl;
		std::string username = "dwf-webapi";
		std::string password = "123456789";
		std::string hash_calced = "Basic " + httplib::detail::base64_encode(username + ":" + password);
		if (hash_tested != hash_calced) { res.status = 400; return; }
		std::cout << "request: " << req.body << std::endl;

		// For XSS vulnerability
		std::string sanitized_body = std::regex_replace(req.body, std::regex("[<>!@#$%^&/\\\\]"), "");

		// For CSRF vulnerability
		// check X-From = Origin (of client). Origin is added by XMLHttpRequest (XHR) in a typical web-browser when CROS access
		// check Host = (address of this server) which is added by a client.
		std::string header_from = req.get_header_value("X-From");
		std::string header_origin = req.get_header_value("Origin");
		std::string header_host = req.get_header_value("Host");
		if (header_from != header_origin){ res.status = 400; return; }
		if (header_host != "localhost:8000") { res.status = 400; return; }

		try
		{
			auto jreq = json::parse(sanitized_body);

			std::string api_name;

			for (json::iterator it = jreq.begin(); it != jreq.end(); ++it)
			{
				//std::cout << "checking: " << it.key() << " : " << it.value() << std::endl;
				apiserver.InvokeAPICall(it.key(), it);

				//break;
			}

			std::cout << "response: " << jreq.dump() << std::endl;

			res.set_content(jreq.dump(), "application/json");
		}
		catch (json::exception& e)
		{
			// output exception information
			std::cout << "message: " << e.what() << '\n'
				      << "exception id: " << e.id << std::endl;

			json jres;
			res.set_content(jres.dump(), "application/json");
		}
	});

	svr.Post("/stop", [&](const httplib::Request& req, httplib::Response& res) {
		svr.stop();
		apiserver.CloseAllDevices();
		std::cout << "web-server stopped by POST /stop." << std::endl;
	});

	//svr.Options("/", [](const httplib::Request& req, httplib::Response& res) {
	//	 Do nothing for CSRF vulnerability (i.e., ignore a preflight request from a web-browser)
	//});

	svr.listen(hostname.c_str(), port);

	std::cout << "bye." << std::endl;
	return 0;
}

