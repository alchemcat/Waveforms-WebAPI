
/*
    ___  __      __  ___
   |   \ \ \    / / | __|
   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI-client wrapper
   |___/   \_/\_/___|_|_    version 0.1.0 for Waveforms API 3.13.8
  |"""""| |"""""""""""""|   https://github.com/alchemcat/Waveforms-WebAPI
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

#include <iostream>

#include "nlohmann/json.hpp"
#include "cpp-httplib/httplib.h"
#include "digilent/waveforms/dwf.h"

//#include <stdio.h>
//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>
//#include <unistd.h>


namespace Dwf
{
	namespace WebAPI
	{
		namespace Client
		{
			using namespace std;
			using json = nlohmann::json;

			namespace {
				string _hostname = "localhost";
				string _origin = "";
				string _username = "";
				string _password = "";
				int _port = 8000;

				std::string GetLocalhostIP()
				{
					//char *hostnamet = (char*)"localhost";
					//struct addrinfo hints, *res;
					//struct in_addr addr;
					//int err;

					//memset(&hints, 0, sizeof(hints));
					//hints.ai_socktype = SOCK_STREAM;
					//hints.ai_family = AF_INET;

					//if ((err = getaddrinfo(hostnamet, NULL, &hints, &res)) != 0) {
					//	printf("error %d\n", err);
					//	return 1;
					//}

					//addr.s_addr = ((struct sockaddr_in *)(res->ai_addr))->sin_addr.s_addr;

					//char string_buf[128];
					//printf("ip address : %s\n", inet_ntop(AF_INET, &addr, string_buf, 128));

					//freeaddrinfo(res);


					std::string dest;
					int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
					if (s < 0) return dest;

					// a dummy IP address to which a connection is tried to established
					struct in_addr dummy;
					inet_pton(AF_INET, "192.0.2.4", &dummy);

					struct sockaddr_in exaddr = { 0 };
					std::memset(&exaddr, 0, sizeof(exaddr));
					exaddr.sin_family = AF_INET;
					std::memcpy((char*)&exaddr.sin_addr, &dummy, sizeof(dummy));

					if (connect(s, (struct sockaddr*)&exaddr, sizeof(exaddr)) < 0) {
#ifdef WIN32
						closesocket(s);
#else
						close(s);
#endif
						return dest;
					}

					struct sockaddr_in addr = { 0 };
					socklen_t len = sizeof(addr);
					int status = getsockname(s, (struct sockaddr*)&addr, &len);

					char string_buf[128];
					if (status >= 0) inet_ntop(AF_INET, &(addr.sin_addr), string_buf, 128);

#ifdef WIN32
					closesocket(s);
#else
					close(s);
#endif

					return std::string(string_buf);
				}
			}

			void SetServer (string hostname, int port, string username, string password)
			{
				_hostname = hostname;
				_port = port;
				_username = username;
				_password = password;
				_origin = GetLocalhostIP(); cout << "Origin: " << _origin << endl;
			}

			json DispatchAPICall (json jreq)
			{

				string sjson = jreq.dump();
				cout << "Request:" << sjson << endl;

#ifdef CPPHTTPLIB_OPENSSL_SUPPORT
				httplib::SSLClient cli(_hostname, _port);
				cli.set_ca_cert_path("./cacert.pem"); // download from https://curl.haxx.se/docs/caextract.html
				cli.enable_server_certificate_verification(false); // set false if using a private CA, or ...
#else
				httplib::Client cli(_hostname, _port);
#endif
				httplib::Headers headers = { {"X-From", _origin}, {"Origin", _origin}, {"Host", ("localhost:" + std::to_string(8000))} };
				cli.set_basic_auth(_username.c_str(), _password.c_str());

				auto res = cli.Post("/", headers, sjson, "application/json");

				json jres;

				if (res && res->status == 200) {
					cout << "Response: ";
					jres = json::parse(res->body);
					for (json::iterator it = jres.begin(); it != jres.end(); ++it) {
						cout << it.key() << " : " << it.value() << endl;
					}
					cout << endl;
				}
				else
				{
					cout << "failed!: " << res << endl;
				}

				return jres;
			}
		}
	}
}



/*
FDwfGetLastError DWFERC *pdwferc
DWFERC *
pdwferc
*/
//  (match no. 1)

	int FDwfGetLastError(DWFERC *pdwferc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfGetLastError",
				{
					{{"(return)", 0}},
					{{"DWFERC", (*pdwferc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfGetLastError") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					DWFERC p1 = it0[1].begin().value().get<DWFERC>();

					(*pdwferc) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfGetLastErrorMsg char szError[512]
char
szError[512]
*/
// 2 (match no. 2)

	int FDwfGetLastErrorMsg(char szError[512])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfGetLastErrorMsg",
				{
					{{"(return)", 0}},
					{{"char", (std::vector<char>(&szError[0], &szError[512])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfGetLastErrorMsg") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					vector<char> p1 = it0[1].begin().value().get<vector<char>>();

					std::memmove(szError, p1.data(), 512 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfGetVersion char szVersion[32]
char
szVersion[32]
*/
// 2 (match no. 3)

	int FDwfGetVersion(char szVersion[32])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfGetVersion",
				{
					{{"(return)", 0}},
					{{"char", (std::vector<char>(&szVersion[0], &szVersion[32])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfGetVersion") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					vector<char> p1 = it0[1].begin().value().get<vector<char>>();

					std::memmove(szVersion, p1.data(), 32 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfParamSet DwfParam param, int value
DwfParam
param
int
value
*/
// 2 (match no. 4)

	int FDwfParamSet(DwfParam param, int value)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfParamSet",
				{
					{{"(return)", 0}},
					{{"DwfParam", param }},
					{{"int", value }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfParamSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					DwfParam p1 = it0[1].begin().value().get<DwfParam>();
					int p2 = it0[2].begin().value().get<int>();

					(param) = p1;
					(value) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfParamGet DwfParam param, int *pvalue
DwfParam
param
int *
pvalue
*/
// 3 (match no. 5)

	int FDwfParamGet(DwfParam param, int *pvalue)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfParamGet",
				{
					{{"(return)", 0}},
					{{"DwfParam", param }},
					{{"int", (*pvalue) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfParamGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					DwfParam p1 = it0[1].begin().value().get<DwfParam>();
					int p2 = it0[2].begin().value().get<int>();

					(param) = p1;
					(*pvalue) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnum ENUMFILTER enumfilter, int *pcDevice
ENUMFILTER
enumfilter
int *
pcDevice
*/
// 3 (match no. 6)

	int FDwfEnum(ENUMFILTER enumfilter, int *pcDevice)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnum",
				{
					{{"(return)", 0}},
					{{"ENUMFILTER", enumfilter }},
					{{"int", (*pcDevice) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnum") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					ENUMFILTER p1 = it0[1].begin().value().get<ENUMFILTER>();
					int p2 = it0[2].begin().value().get<int>();

					(enumfilter) = p1;
					(*pcDevice) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumDeviceType int idxDevice, DEVID *pDeviceId, DEVVER *pDeviceRevision
int
idxDevice
DEVID *
pDeviceId
DEVVER *
pDeviceRevision
*/
// 3 (match no. 7)

	int FDwfEnumDeviceType(int idxDevice, DEVID *pDeviceId, DEVVER *pDeviceRevision)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumDeviceType",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"DEVID", (*pDeviceId) }},
					{{"DEVVER", (*pDeviceRevision) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumDeviceType") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					DEVID p2 = it0[2].begin().value().get<DEVID>();
					DEVVER p3 = it0[3].begin().value().get<DEVVER>();

					(idxDevice) = p1;
					(*pDeviceId) = p2;
					(*pDeviceRevision) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumDeviceIsOpened int idxDevice, int *pfIsUsed
int
idxDevice
int *
pfIsUsed
*/
// 4 (match no. 8)

	int FDwfEnumDeviceIsOpened(int idxDevice, int *pfIsUsed)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumDeviceIsOpened",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"int", (*pfIsUsed) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumDeviceIsOpened") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();

					(idxDevice) = p1;
					(*pfIsUsed) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumUserName int idxDevice, char szUserName[32]
int
idxDevice
char
szUserName[32]
*/
// 3 (match no. 9)

	int FDwfEnumUserName(int idxDevice, char szUserName[32])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumUserName",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"char", (std::vector<char>(&szUserName[0], &szUserName[32])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumUserName") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();

					(idxDevice) = p1;
					std::memmove(szUserName, p2.data(), 32 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumDeviceName int idxDevice, char szDeviceName[32]
int
idxDevice
char
szDeviceName[32]
*/
// 3 (match no. 10)

	int FDwfEnumDeviceName(int idxDevice, char szDeviceName[32])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumDeviceName",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"char", (std::vector<char>(&szDeviceName[0], &szDeviceName[32])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumDeviceName") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();

					(idxDevice) = p1;
					std::memmove(szDeviceName, p2.data(), 32 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumSN int idxDevice, char szSN[32]
int
idxDevice
char
szSN[32]
*/
// 3 (match no. 11)

	int FDwfEnumSN(int idxDevice, char szSN[32])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumSN",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"char", (std::vector<char>(&szSN[0], &szSN[32])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumSN") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();

					(idxDevice) = p1;
					std::memmove(szSN, p2.data(), 32 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumConfig int idxDevice, int *pcConfig
int
idxDevice
int *
pcConfig
*/
// 3 (match no. 12)

	int FDwfEnumConfig(int idxDevice, int *pcConfig)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumConfig",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"int", (*pcConfig) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumConfig") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();

					(idxDevice) = p1;
					(*pcConfig) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumConfigInfo int idxConfig, DwfEnumConfigInfo info, int *pv
int
idxConfig
DwfEnumConfigInfo
info
int *
pv
*/
// 3 (match no. 13)

	int FDwfEnumConfigInfo(int idxConfig, DwfEnumConfigInfo info, int *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumConfigInfo",
				{
					{{"(return)", 0}},
					{{"int", idxConfig }},
					{{"DwfEnumConfigInfo", info }},
					{{"int", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumConfigInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					DwfEnumConfigInfo p2 = it0[2].begin().value().get<DwfEnumConfigInfo>();
					int p3 = it0[3].begin().value().get<int>();

					(idxConfig) = p1;
					(info) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceOpen int idxDevice, HDWF *phdwf
int
idxDevice
HDWF *
phdwf
*/
// 4 (match no. 14)

	int FDwfDeviceOpen(int idxDevice, HDWF *phdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceOpen",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"HDWF", (*phdwf) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceOpen") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					HDWF p2 = it0[2].begin().value().get<HDWF>();

					(idxDevice) = p1;
					(*phdwf) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceConfigOpen int idxDev, int idxCfg, HDWF *phdwf
int
idxDev
int
idxCfg
HDWF *
phdwf
*/
// 3 (match no. 15)

	int FDwfDeviceConfigOpen(int idxDev, int idxCfg, HDWF *phdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceConfigOpen",
				{
					{{"(return)", 0}},
					{{"int", idxDev }},
					{{"int", idxCfg }},
					{{"HDWF", (*phdwf) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceConfigOpen") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();
					HDWF p3 = it0[3].begin().value().get<HDWF>();

					(idxDev) = p1;
					(idxCfg) = p2;
					(*phdwf) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceClose HDWF hdwf
HDWF
hdwf
*/
// 4 (match no. 16)

	int FDwfDeviceClose(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceClose",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceClose") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceCloseAll

*/
// 2 (match no. 17)

	int FDwfDeviceCloseAll()
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceCloseAll",
				{
					{{"(return)", 0}},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceCloseAll") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 1)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();

				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceAutoConfigureSet HDWF hdwf, int fAutoConfigure
HDWF
hdwf
int
fAutoConfigure
*/
// 1 (match no. 18)

	int FDwfDeviceAutoConfigureSet(HDWF hdwf, int fAutoConfigure)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceAutoConfigureSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fAutoConfigure }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceAutoConfigureSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fAutoConfigure) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceAutoConfigureGet HDWF hdwf, int *pfAutoConfigure
HDWF
hdwf
int *
pfAutoConfigure
*/
// 3 (match no. 19)

	int FDwfDeviceAutoConfigureGet(HDWF hdwf, int *pfAutoConfigure)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceAutoConfigureGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfAutoConfigure) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceAutoConfigureGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfAutoConfigure) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceReset HDWF hdwf
HDWF
hdwf
*/
// 3 (match no. 20)

	int FDwfDeviceReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceEnableSet HDWF hdwf, int fEnable
HDWF
hdwf
int
fEnable
*/
// 2 (match no. 21)

	int FDwfDeviceEnableSet(HDWF hdwf, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceTriggerInfo HDWF hdwf, int *pfstrigsrc
HDWF
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 22)

	int FDwfDeviceTriggerInfo(HDWF hdwf, int *pfstrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceTriggerInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceTriggerInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceTriggerSet HDWF hdwf, int idxPin, TRIGSRC trigsrc
HDWF
hdwf
int
idxPin
TRIGSRC
trigsrc
*/
// 3 (match no. 23)

	int FDwfDeviceTriggerSet(HDWF hdwf, int idxPin, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceTriggerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxPin }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceTriggerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(idxPin) = p2;
					(trigsrc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceTriggerGet HDWF hdwf, int idxPin, TRIGSRC *ptrigsrc
HDWF
hdwf
int
idxPin
TRIGSRC *
ptrigsrc
*/
// 4 (match no. 24)

	int FDwfDeviceTriggerGet(HDWF hdwf, int idxPin, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceTriggerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxPin }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceTriggerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(idxPin) = p2;
					(*ptrigsrc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceTriggerPC HDWF hdwf
HDWF
hdwf
*/
// 4 (match no. 25)

	int FDwfDeviceTriggerPC(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceTriggerPC",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceTriggerPC") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceTriggerSlopeInfo HDWF hdwf, int *pfsslope
HDWF
hdwf
int *
pfsslope
*/
// 2 (match no. 26)

	int FDwfDeviceTriggerSlopeInfo(HDWF hdwf, int *pfsslope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceTriggerSlopeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsslope) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceTriggerSlopeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsslope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceParamSet HDWF hdwf, DwfParam param, int value
HDWF
hdwf
DwfParam
param
int
value
*/
// 3 (match no. 27)

	int FDwfDeviceParamSet(HDWF hdwf, DwfParam param, int value)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceParamSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfParam", param }},
					{{"int", value }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceParamSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfParam p2 = it0[2].begin().value().get<DwfParam>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(param) = p2;
					(value) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDeviceParamGet HDWF hdwf, DwfParam param, int *pvalue
HDWF
hdwf
DwfParam
param
int *
pvalue
*/
// 4 (match no. 28)

	int FDwfDeviceParamGet(HDWF hdwf, DwfParam param, int *pvalue)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDeviceParamGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfParam", param }},
					{{"int", (*pvalue) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDeviceParamGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfParam p2 = it0[2].begin().value().get<DwfParam>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(param) = p2;
					(*pvalue) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInReset HDWF hdwf
HDWF
hdwf
*/
// 4 (match no. 29)

	int FDwfAnalogInReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInConfigure HDWF hdwf, int fReconfigure, int fStart
HDWF
hdwf
int
fReconfigure
int
fStart
*/
// 2 (match no. 30)

	int FDwfAnalogInConfigure(HDWF hdwf, int fReconfigure, int fStart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fReconfigure }},
					{{"int", fStart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(fReconfigure) = p2;
					(fStart) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerForce HDWF hdwf
HDWF
hdwf
*/
// 4 (match no. 31)

	int FDwfAnalogInTriggerForce(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerForce",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerForce") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatus HDWF hdwf, int fReadData, DwfState *psts
HDWF
hdwf
int
fReadData
DwfState *
psts
*/
// 2 (match no. 32)

	int FDwfAnalogInStatus(HDWF hdwf, int fReadData, DwfState *psts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fReadData }},
					{{"DwfState", (*psts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfState p3 = it0[3].begin().value().get<DwfState>();

					(hdwf) = p1;
					(fReadData) = p2;
					(*psts) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusSamplesLeft HDWF hdwf, int *pcSamplesLeft
HDWF
hdwf
int *
pcSamplesLeft
*/
// 4 (match no. 33)

	int FDwfAnalogInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusSamplesLeft",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcSamplesLeft) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusSamplesLeft") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcSamplesLeft) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusSamplesValid HDWF hdwf, int *pcSamplesValid
HDWF
hdwf
int *
pcSamplesValid
*/
// 3 (match no. 34)

	int FDwfAnalogInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusSamplesValid",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcSamplesValid) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusSamplesValid") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcSamplesValid) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusIndexWrite HDWF hdwf, int *pidxWrite
HDWF
hdwf
int *
pidxWrite
*/
// 3 (match no. 35)

	int FDwfAnalogInStatusIndexWrite(HDWF hdwf, int *pidxWrite)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusIndexWrite",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pidxWrite) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusIndexWrite") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pidxWrite) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusAutoTriggered HDWF hdwf, int *pfAuto
HDWF
hdwf
int *
pfAuto
*/
// 3 (match no. 36)

	int FDwfAnalogInStatusAutoTriggered(HDWF hdwf, int *pfAuto)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusAutoTriggered",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfAuto) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusAutoTriggered") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfAuto) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusData HDWF hdwf, int idxChannel, double *rgdVoltData, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdVoltData
int
cdData
*/
// 3 (match no. 37)

	int FDwfAnalogInStatusData(HDWF hdwf, int idxChannel, double *rgdVoltData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusData",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdVoltData[0], &rgdVoltData[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusData") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdVoltData, p3.data(), 0 * sizeof(double));
					(cdData) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusData2 HDWF hdwf, int idxChannel, double *rgdVoltData, int idxData, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdVoltData
int
idxData
int
cdData
*/
// 5 (match no. 38)

	int FDwfAnalogInStatusData2(HDWF hdwf, int idxChannel, double *rgdVoltData, int idxData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusData2",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdVoltData[0], &rgdVoltData[cdData])) }},
					{{"int", idxData }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusData2") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdVoltData, p3.data(), 0 * sizeof(double));
					(idxData) = p4;
					(cdData) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusData16 HDWF hdwf, int idxChannel, short *rgu16Data, int idxData, int cdData
HDWF
hdwf
int
idxChannel
short *
rgu16Data
int
idxData
int
cdData
*/
// 6 (match no. 39)

	int FDwfAnalogInStatusData16(HDWF hdwf, int idxChannel, short *rgu16Data, int idxData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusData16",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"short", (std::vector<short>(&rgu16Data[0], &rgu16Data[cdData])) }},
					{{"int", idxData }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusData16") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<short> p3 = it0[3].begin().value().get<vector<short>>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgu16Data, p3.data(), 0 * sizeof(short));
					(idxData) = p4;
					(cdData) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusNoise HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdMin
double *
rgdMax
int
cdData
*/
// 6 (match no. 40)

	int FDwfAnalogInStatusNoise(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusNoise",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdMin[0], &rgdMin[cdData])) }},
					{{"double", (std::vector<double>(&rgdMax[0], &rgdMax[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusNoise") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					vector<double> p4 = it0[4].begin().value().get<vector<double>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdMin, p3.data(), 0 * sizeof(double));
					std::memmove(rgdMax, p4.data(), 0 * sizeof(double));
					(cdData) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusNoise2 HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int idxData, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdMin
double *
rgdMax
int
idxData
int
cdData
*/
// 6 (match no. 41)

	int FDwfAnalogInStatusNoise2(HDWF hdwf, int idxChannel, double *rgdMin, double *rgdMax, int idxData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusNoise2",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdMin[0], &rgdMin[cdData])) }},
					{{"double", (std::vector<double>(&rgdMax[0], &rgdMax[cdData])) }},
					{{"int", idxData }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusNoise2") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 7)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					vector<double> p4 = it0[4].begin().value().get<vector<double>>();
					int p5 = it0[5].begin().value().get<int>();
					int p6 = it0[6].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdMin, p3.data(), 0 * sizeof(double));
					std::memmove(rgdMax, p4.data(), 0 * sizeof(double));
					(idxData) = p5;
					(cdData) = p6;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusSample HDWF hdwf, int idxChannel, double *pdVoltSample
HDWF
hdwf
int
idxChannel
double *
pdVoltSample
*/
// 7 (match no. 42)

	int FDwfAnalogInStatusSample(HDWF hdwf, int idxChannel, double *pdVoltSample)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusSample",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pdVoltSample) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusSample") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pdVoltSample) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInStatusRecord HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt
HDWF
hdwf
int *
pcdDataAvailable
int *
pcdDataLost
int *
pcdDataCorrupt
*/
// 4 (match no. 43)

	int FDwfAnalogInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInStatusRecord",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcdDataAvailable) }},
					{{"int", (*pcdDataLost) }},
					{{"int", (*pcdDataCorrupt) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInStatusRecord") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(*pcdDataAvailable) = p2;
					(*pcdDataLost) = p3;
					(*pcdDataCorrupt) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInRecordLengthSet HDWF hdwf, double sLength
HDWF
hdwf
double
sLength
*/
// 5 (match no. 44)

	int FDwfAnalogInRecordLengthSet(HDWF hdwf, double sLength)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInRecordLengthSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", sLength }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInRecordLengthSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(sLength) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInRecordLengthGet HDWF hdwf, double *psLength
HDWF
hdwf
double *
psLength
*/
// 3 (match no. 45)

	int FDwfAnalogInRecordLengthGet(HDWF hdwf, double *psLength)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInRecordLengthGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psLength) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInRecordLengthGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psLength) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInFrequencyInfo HDWF hdwf, double *phzMin, double *phzMax
HDWF
hdwf
double *
phzMin
double *
phzMax
*/
// 3 (match no. 46)

	int FDwfAnalogInFrequencyInfo(HDWF hdwf, double *phzMin, double *phzMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInFrequencyInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*phzMin) }},
					{{"double", (*phzMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInFrequencyInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(*phzMin) = p2;
					(*phzMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInFrequencySet HDWF hdwf, double hzFrequency
HDWF
hdwf
double
hzFrequency
*/
// 4 (match no. 47)

	int FDwfAnalogInFrequencySet(HDWF hdwf, double hzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInFrequencySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hzFrequency }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInFrequencySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hzFrequency) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInFrequencyGet HDWF hdwf, double *phzFrequency
HDWF
hdwf
double *
phzFrequency
*/
// 3 (match no. 48)

	int FDwfAnalogInFrequencyGet(HDWF hdwf, double *phzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInFrequencyGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*phzFrequency) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInFrequencyGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*phzFrequency) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInBitsInfo HDWF hdwf, int *pnBits
HDWF
hdwf
int *
pnBits
*/
// 3 (match no. 49)

	int FDwfAnalogInBitsInfo(HDWF hdwf, int *pnBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInBitsInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnBits) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInBitsInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInBufferSizeInfo HDWF hdwf, int *pnSizeMin, int *pnSizeMax
HDWF
hdwf
int *
pnSizeMin
int *
pnSizeMax
*/
// 3 (match no. 50)

	int FDwfAnalogInBufferSizeInfo(HDWF hdwf, int *pnSizeMin, int *pnSizeMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInBufferSizeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSizeMin) }},
					{{"int", (*pnSizeMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInBufferSizeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSizeMin) = p2;
					(*pnSizeMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInBufferSizeSet HDWF hdwf, int nSize
HDWF
hdwf
int
nSize
*/
// 4 (match no. 51)

	int FDwfAnalogInBufferSizeSet(HDWF hdwf, int nSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInBufferSizeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", nSize }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInBufferSizeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(nSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInBufferSizeGet HDWF hdwf, int *pnSize
HDWF
hdwf
int *
pnSize
*/
// 3 (match no. 52)

	int FDwfAnalogInBufferSizeGet(HDWF hdwf, int *pnSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInBufferSizeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSize) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInBufferSizeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInNoiseSizeInfo HDWF hdwf, int *pnSizeMax
HDWF
hdwf
int *
pnSizeMax
*/
// 3 (match no. 53)

	int FDwfAnalogInNoiseSizeInfo(HDWF hdwf, int *pnSizeMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInNoiseSizeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSizeMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInNoiseSizeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSizeMax) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInNoiseSizeSet HDWF hdwf, int nSize
HDWF
hdwf
int
nSize
*/
// 3 (match no. 54)

	int FDwfAnalogInNoiseSizeSet(HDWF hdwf, int nSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInNoiseSizeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", nSize }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInNoiseSizeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(nSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInNoiseSizeGet HDWF hdwf, int *pnSize
HDWF
hdwf
int *
pnSize
*/
// 3 (match no. 55)

	int FDwfAnalogInNoiseSizeGet(HDWF hdwf, int *pnSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInNoiseSizeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSize) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInNoiseSizeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInAcquisitionModeInfo HDWF hdwf, int *pfsacqmode
HDWF
hdwf
int *
pfsacqmode
*/
// 3 (match no. 56)

	int FDwfAnalogInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInAcquisitionModeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsacqmode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInAcquisitionModeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsacqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInAcquisitionModeSet HDWF hdwf, ACQMODE acqmode
HDWF
hdwf
ACQMODE
acqmode
*/
// 3 (match no. 57)

	int FDwfAnalogInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInAcquisitionModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"ACQMODE", acqmode }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInAcquisitionModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

					(hdwf) = p1;
					(acqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInAcquisitionModeGet HDWF hdwf, ACQMODE *pacqmode
HDWF
hdwf
ACQMODE *
pacqmode
*/
// 3 (match no. 58)

	int FDwfAnalogInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInAcquisitionModeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"ACQMODE", (*pacqmode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInAcquisitionModeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

					(hdwf) = p1;
					(*pacqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelCount HDWF hdwf, int *pcChannel
HDWF
hdwf
int *
pcChannel
*/
// 3 (match no. 59)

	int FDwfAnalogInChannelCount(HDWF hdwf, int *pcChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelCount",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcChannel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelCount") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelEnableSet HDWF hdwf, int idxChannel, int fEnable
HDWF
hdwf
int
idxChannel
int
fEnable
*/
// 3 (match no. 60)

	int FDwfAnalogInChannelEnableSet(HDWF hdwf, int idxChannel, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelEnableGet HDWF hdwf, int idxChannel, int *pfEnable
HDWF
hdwf
int
idxChannel
int *
pfEnable
*/
// 4 (match no. 61)

	int FDwfAnalogInChannelEnableGet(HDWF hdwf, int idxChannel, int *pfEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelFilterInfo HDWF hdwf, int *pfsfilter
HDWF
hdwf
int *
pfsfilter
*/
// 4 (match no. 62)

	int FDwfAnalogInChannelFilterInfo(HDWF hdwf, int *pfsfilter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelFilterInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsfilter) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelFilterInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsfilter) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelFilterSet HDWF hdwf, int idxChannel, FILTER filter
HDWF
hdwf
int
idxChannel
FILTER
filter
*/
// 3 (match no. 63)

	int FDwfAnalogInChannelFilterSet(HDWF hdwf, int idxChannel, FILTER filter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelFilterSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"FILTER", filter }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelFilterSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					FILTER p3 = it0[3].begin().value().get<FILTER>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(filter) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelFilterGet HDWF hdwf, int idxChannel, FILTER *pfilter
HDWF
hdwf
int
idxChannel
FILTER *
pfilter
*/
// 4 (match no. 64)

	int FDwfAnalogInChannelFilterGet(HDWF hdwf, int idxChannel, FILTER *pfilter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelFilterGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"FILTER", (*pfilter) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelFilterGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					FILTER p3 = it0[3].begin().value().get<FILTER>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfilter) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelRangeInfo HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps
HDWF
hdwf
double *
pvoltsMin
double *
pvoltsMax
double *
pnSteps
*/
// 4 (match no. 65)

	int FDwfAnalogInChannelRangeInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelRangeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelRangeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsMin) = p2;
					(*pvoltsMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelRangeSteps HDWF hdwf, double rgVoltsStep[32], int *pnSteps
HDWF
hdwf
double
rgVoltsStep[32]
int *
pnSteps
*/
// 5 (match no. 66)

	int FDwfAnalogInChannelRangeSteps(HDWF hdwf, double rgVoltsStep[32], int *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelRangeSteps",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (std::vector<double>(&rgVoltsStep[0], &rgVoltsStep[32])) }},
					{{"int", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelRangeSteps") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					vector<double> p2 = it0[2].begin().value().get<vector<double>>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					std::memmove(rgVoltsStep, p2.data(), 32 * sizeof(double));
					(*pnSteps) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelRangeSet HDWF hdwf, int idxChannel, double voltsRange
HDWF
hdwf
int
idxChannel
double
voltsRange
*/
// 4 (match no. 67)

	int FDwfAnalogInChannelRangeSet(HDWF hdwf, int idxChannel, double voltsRange)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelRangeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", voltsRange }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelRangeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(voltsRange) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelRangeGet HDWF hdwf, int idxChannel, double *pvoltsRange
HDWF
hdwf
int
idxChannel
double *
pvoltsRange
*/
// 4 (match no. 68)

	int FDwfAnalogInChannelRangeGet(HDWF hdwf, int idxChannel, double *pvoltsRange)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelRangeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltsRange) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelRangeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltsRange) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelOffsetInfo HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps
HDWF
hdwf
double *
pvoltsMin
double *
pvoltsMax
double *
pnSteps
*/
// 4 (match no. 69)

	int FDwfAnalogInChannelOffsetInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelOffsetInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelOffsetInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsMin) = p2;
					(*pvoltsMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelOffsetSet HDWF hdwf, int idxChannel, double voltOffset
HDWF
hdwf
int
idxChannel
double
voltOffset
*/
// 5 (match no. 70)

	int FDwfAnalogInChannelOffsetSet(HDWF hdwf, int idxChannel, double voltOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelOffsetSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", voltOffset }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelOffsetSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(voltOffset) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelOffsetGet HDWF hdwf, int idxChannel, double *pvoltOffset
HDWF
hdwf
int
idxChannel
double *
pvoltOffset
*/
// 4 (match no. 71)

	int FDwfAnalogInChannelOffsetGet(HDWF hdwf, int idxChannel, double *pvoltOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelOffsetGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltOffset) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelOffsetGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltOffset) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelAttenuationSet HDWF hdwf, int idxChannel, double xAttenuation
HDWF
hdwf
int
idxChannel
double
xAttenuation
*/
// 4 (match no. 72)

	int FDwfAnalogInChannelAttenuationSet(HDWF hdwf, int idxChannel, double xAttenuation)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelAttenuationSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", xAttenuation }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelAttenuationSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(xAttenuation) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInChannelAttenuationGet HDWF hdwf, int idxChannel, double *pxAttenuation
HDWF
hdwf
int
idxChannel
double *
pxAttenuation
*/
// 4 (match no. 73)

	int FDwfAnalogInChannelAttenuationGet(HDWF hdwf, int idxChannel, double *pxAttenuation)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInChannelAttenuationGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pxAttenuation) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInChannelAttenuationGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pxAttenuation) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF
hdwf
TRIGSRC
trigsrc
*/
// 4 (match no. 74)

	int FDwfAnalogInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(trigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 75)

	int FDwfAnalogInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(*ptrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerPositionInfo HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps
HDWF
hdwf
double *
psecMin
double *
psecMax
double *
pnSteps
*/
// 3 (match no. 76)

	int FDwfAnalogInTriggerPositionInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerPositionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerPositionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerPositionSet HDWF hdwf, double secPosition
HDWF
hdwf
double
secPosition
*/
// 5 (match no. 77)

	int FDwfAnalogInTriggerPositionSet(HDWF hdwf, double secPosition)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerPositionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secPosition }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerPositionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secPosition) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerPositionGet HDWF hdwf, double *psecPosition
HDWF
hdwf
double *
psecPosition
*/
// 3 (match no. 78)

	int FDwfAnalogInTriggerPositionGet(HDWF hdwf, double *psecPosition)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerPositionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecPosition) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerPositionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecPosition) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerPositionStatus HDWF hdwf, double *psecPosition
HDWF
hdwf
double *
psecPosition
*/
// 3 (match no. 79)

	int FDwfAnalogInTriggerPositionStatus(HDWF hdwf, double *psecPosition)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerPositionStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecPosition) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerPositionStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecPosition) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerAutoTimeoutInfo HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps
HDWF
hdwf
double *
psecMin
double *
psecMax
double *
pnSteps
*/
// 3 (match no. 80)

	int FDwfAnalogInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerAutoTimeoutInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerAutoTimeoutInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerAutoTimeoutSet HDWF hdwf, double secTimeout
HDWF
hdwf
double
secTimeout
*/
// 5 (match no. 81)

	int FDwfAnalogInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerAutoTimeoutSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secTimeout }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerAutoTimeoutSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secTimeout) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerAutoTimeoutGet HDWF hdwf, double *psecTimeout
HDWF
hdwf
double *
psecTimeout
*/
// 3 (match no. 82)

	int FDwfAnalogInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerAutoTimeoutGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecTimeout) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerAutoTimeoutGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecTimeout) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHoldOffInfo HDWF hdwf, double *psecMin, double *psecMax, double *pnStep
HDWF
hdwf
double *
psecMin
double *
psecMax
double *
pnStep
*/
// 3 (match no. 83)

	int FDwfAnalogInTriggerHoldOffInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnStep)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHoldOffInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
					{{"double", (*pnStep) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHoldOffInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
					(*pnStep) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHoldOffSet HDWF hdwf, double secHoldOff
HDWF
hdwf
double
secHoldOff
*/
// 5 (match no. 84)

	int FDwfAnalogInTriggerHoldOffSet(HDWF hdwf, double secHoldOff)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHoldOffSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secHoldOff }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHoldOffSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secHoldOff) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHoldOffGet HDWF hdwf, double *psecHoldOff
HDWF
hdwf
double *
psecHoldOff
*/
// 3 (match no. 85)

	int FDwfAnalogInTriggerHoldOffGet(HDWF hdwf, double *psecHoldOff)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHoldOffGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecHoldOff) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHoldOffGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecHoldOff) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerTypeInfo HDWF hdwf, int *pfstrigtype
HDWF
hdwf
int *
pfstrigtype
*/
// 3 (match no. 86)

	int FDwfAnalogInTriggerTypeInfo(HDWF hdwf, int *pfstrigtype)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerTypeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigtype) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerTypeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigtype) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerTypeSet HDWF hdwf, TRIGTYPE trigtype
HDWF
hdwf
TRIGTYPE
trigtype
*/
// 3 (match no. 87)

	int FDwfAnalogInTriggerTypeSet(HDWF hdwf, TRIGTYPE trigtype)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerTypeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGTYPE", trigtype }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerTypeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGTYPE p2 = it0[2].begin().value().get<TRIGTYPE>();

					(hdwf) = p1;
					(trigtype) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerTypeGet HDWF hdwf, TRIGTYPE *ptrigtype
HDWF
hdwf
TRIGTYPE *
ptrigtype
*/
// 3 (match no. 88)

	int FDwfAnalogInTriggerTypeGet(HDWF hdwf, TRIGTYPE *ptrigtype)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerTypeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGTYPE", (*ptrigtype) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerTypeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGTYPE p2 = it0[2].begin().value().get<TRIGTYPE>();

					(hdwf) = p1;
					(*ptrigtype) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerChannelInfo HDWF hdwf, int *pidxMin, int *pidxMax
HDWF
hdwf
int *
pidxMin
int *
pidxMax
*/
// 3 (match no. 89)

	int FDwfAnalogInTriggerChannelInfo(HDWF hdwf, int *pidxMin, int *pidxMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerChannelInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pidxMin) }},
					{{"int", (*pidxMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerChannelInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(*pidxMin) = p2;
					(*pidxMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerChannelSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 4 (match no. 90)

	int FDwfAnalogInTriggerChannelSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerChannelSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerChannelSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerChannelGet HDWF hdwf, int *pidxChannel
HDWF
hdwf
int *
pidxChannel
*/
// 3 (match no. 91)

	int FDwfAnalogInTriggerChannelGet(HDWF hdwf, int *pidxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerChannelGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pidxChannel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerChannelGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pidxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerFilterInfo HDWF hdwf, int *pfsfilter
HDWF
hdwf
int *
pfsfilter
*/
// 3 (match no. 92)

	int FDwfAnalogInTriggerFilterInfo(HDWF hdwf, int *pfsfilter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerFilterInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsfilter) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerFilterInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsfilter) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerFilterSet HDWF hdwf, FILTER filter
HDWF
hdwf
FILTER
filter
*/
// 3 (match no. 93)

	int FDwfAnalogInTriggerFilterSet(HDWF hdwf, FILTER filter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerFilterSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"FILTER", filter }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerFilterSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					FILTER p2 = it0[2].begin().value().get<FILTER>();

					(hdwf) = p1;
					(filter) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerFilterGet HDWF hdwf, FILTER *pfilter
HDWF
hdwf
FILTER *
pfilter
*/
// 3 (match no. 94)

	int FDwfAnalogInTriggerFilterGet(HDWF hdwf, FILTER *pfilter)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerFilterGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"FILTER", (*pfilter) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerFilterGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					FILTER p2 = it0[2].begin().value().get<FILTER>();

					(hdwf) = p1;
					(*pfilter) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLevelInfo HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps
HDWF
hdwf
double *
pvoltsMin
double *
pvoltsMax
double *
pnSteps
*/
// 3 (match no. 95)

	int FDwfAnalogInTriggerLevelInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLevelInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLevelInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsMin) = p2;
					(*pvoltsMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLevelSet HDWF hdwf, double voltsLevel
HDWF
hdwf
double
voltsLevel
*/
// 5 (match no. 96)

	int FDwfAnalogInTriggerLevelSet(HDWF hdwf, double voltsLevel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLevelSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", voltsLevel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLevelSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(voltsLevel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLevelGet HDWF hdwf, double *pvoltsLevel
HDWF
hdwf
double *
pvoltsLevel
*/
// 3 (match no. 97)

	int FDwfAnalogInTriggerLevelGet(HDWF hdwf, double *pvoltsLevel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLevelGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsLevel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLevelGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsLevel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHysteresisInfo HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps
HDWF
hdwf
double *
pvoltsMin
double *
pvoltsMax
double *
pnSteps
*/
// 3 (match no. 98)

	int FDwfAnalogInTriggerHysteresisInfo(HDWF hdwf, double *pvoltsMin, double *pvoltsMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHysteresisInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHysteresisInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsMin) = p2;
					(*pvoltsMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHysteresisSet HDWF hdwf, double voltsLevel
HDWF
hdwf
double
voltsLevel
*/
// 5 (match no. 99)

	int FDwfAnalogInTriggerHysteresisSet(HDWF hdwf, double voltsLevel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHysteresisSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", voltsLevel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHysteresisSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(voltsLevel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerHysteresisGet HDWF hdwf, double *pvoltsHysteresis
HDWF
hdwf
double *
pvoltsHysteresis
*/
// 3 (match no. 100)

	int FDwfAnalogInTriggerHysteresisGet(HDWF hdwf, double *pvoltsHysteresis)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerHysteresisGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvoltsHysteresis) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerHysteresisGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*pvoltsHysteresis) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerConditionInfo HDWF hdwf, int *pfstrigcond
HDWF
hdwf
int *
pfstrigcond
*/
// 3 (match no. 101)

	int FDwfAnalogInTriggerConditionInfo(HDWF hdwf, int *pfstrigcond)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerConditionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigcond) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerConditionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigcond) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerConditionSet HDWF hdwf, DwfTriggerSlope trigcond
HDWF
hdwf
DwfTriggerSlope
trigcond
*/
// 3 (match no. 102)

	int FDwfAnalogInTriggerConditionSet(HDWF hdwf, DwfTriggerSlope trigcond)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerConditionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", trigcond }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerConditionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(trigcond) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerConditionGet HDWF hdwf, DwfTriggerSlope *ptrigcond
HDWF
hdwf
DwfTriggerSlope *
ptrigcond
*/
// 3 (match no. 103)

	int FDwfAnalogInTriggerConditionGet(HDWF hdwf, DwfTriggerSlope *ptrigcond)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerConditionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", (*ptrigcond) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerConditionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(*ptrigcond) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthInfo HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps
HDWF
hdwf
double *
psecMin
double *
psecMax
double *
pnSteps
*/
// 3 (match no. 104)

	int FDwfAnalogInTriggerLengthInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthSet HDWF hdwf, double secLength
HDWF
hdwf
double
secLength
*/
// 5 (match no. 105)

	int FDwfAnalogInTriggerLengthSet(HDWF hdwf, double secLength)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secLength }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secLength) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthGet HDWF hdwf, double *psecLength
HDWF
hdwf
double *
psecLength
*/
// 3 (match no. 106)

	int FDwfAnalogInTriggerLengthGet(HDWF hdwf, double *psecLength)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecLength) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecLength) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthConditionInfo HDWF hdwf, int *pfstriglen
HDWF
hdwf
int *
pfstriglen
*/
// 3 (match no. 107)

	int FDwfAnalogInTriggerLengthConditionInfo(HDWF hdwf, int *pfstriglen)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthConditionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstriglen) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthConditionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstriglen) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthConditionSet HDWF hdwf, TRIGLEN triglen
HDWF
hdwf
TRIGLEN
triglen
*/
// 3 (match no. 108)

	int FDwfAnalogInTriggerLengthConditionSet(HDWF hdwf, TRIGLEN triglen)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthConditionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGLEN", triglen }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthConditionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGLEN p2 = it0[2].begin().value().get<TRIGLEN>();

					(hdwf) = p1;
					(triglen) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerLengthConditionGet HDWF hdwf, TRIGLEN *ptriglen
HDWF
hdwf
TRIGLEN *
ptriglen
*/
// 3 (match no. 109)

	int FDwfAnalogInTriggerLengthConditionGet(HDWF hdwf, TRIGLEN *ptriglen)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerLengthConditionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGLEN", (*ptriglen) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerLengthConditionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGLEN p2 = it0[2].begin().value().get<TRIGLEN>();

					(hdwf) = p1;
					(*ptriglen) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF
hdwf
TRIGSRC
trigsrc
*/
// 3 (match no. 110)

	int FDwfAnalogInSamplingSourceSet(HDWF hdwf, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(trigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 111)

	int FDwfAnalogInSamplingSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(*ptrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF
hdwf
DwfTriggerSlope
slope
*/
// 3 (match no. 112)

	int FDwfAnalogInSamplingSlopeSet(HDWF hdwf, DwfTriggerSlope slope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingSlopeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", slope }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingSlopeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(slope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 113)

	int FDwfAnalogInSamplingSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingSlopeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", (*pslope) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingSlopeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(*pslope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingDelaySet HDWF hdwf, double sec
HDWF
hdwf
double
sec
*/
// 3 (match no. 114)

	int FDwfAnalogInSamplingDelaySet(HDWF hdwf, double sec)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingDelaySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", sec }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingDelaySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(sec) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInSamplingDelayGet HDWF hdwf, double *psec
HDWF
hdwf
double *
psec
*/
// 3 (match no. 115)

	int FDwfAnalogInSamplingDelayGet(HDWF hdwf, double *psec)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInSamplingDelayGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psec) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInSamplingDelayGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psec) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutCount HDWF hdwf, int *pcChannel
HDWF
hdwf
int *
pcChannel
*/
// 3 (match no. 116)

	int FDwfAnalogOutCount(HDWF hdwf, int *pcChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutCount",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcChannel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutCount") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutMasterSet HDWF hdwf, int idxChannel, int idxMaster
HDWF
hdwf
int
idxChannel
int
idxMaster
*/
// 3 (match no. 117)

	int FDwfAnalogOutMasterSet(HDWF hdwf, int idxChannel, int idxMaster)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutMasterSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxMaster }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutMasterSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxMaster) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutMasterGet HDWF hdwf, int idxChannel, int *pidxMaster
HDWF
hdwf
int
idxChannel
int *
pidxMaster
*/
// 4 (match no. 118)

	int FDwfAnalogOutMasterGet(HDWF hdwf, int idxChannel, int *pidxMaster)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutMasterGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pidxMaster) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutMasterGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pidxMaster) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutTriggerSourceSet HDWF hdwf, int idxChannel, TRIGSRC trigsrc
HDWF
hdwf
int
idxChannel
TRIGSRC
trigsrc
*/
// 4 (match no. 119)

	int FDwfAnalogOutTriggerSourceSet(HDWF hdwf, int idxChannel, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutTriggerSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutTriggerSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(trigsrc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutTriggerSourceGet HDWF hdwf, int idxChannel, TRIGSRC *ptrigsrc
HDWF
hdwf
int
idxChannel
TRIGSRC *
ptrigsrc
*/
// 4 (match no. 120)

	int FDwfAnalogOutTriggerSourceGet(HDWF hdwf, int idxChannel, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutTriggerSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutTriggerSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*ptrigsrc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutTriggerSlopeSet HDWF hdwf, int idxChannel, DwfTriggerSlope slope
HDWF
hdwf
int
idxChannel
DwfTriggerSlope
slope
*/
// 4 (match no. 121)

	int FDwfAnalogOutTriggerSlopeSet(HDWF hdwf, int idxChannel, DwfTriggerSlope slope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutTriggerSlopeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfTriggerSlope", slope }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutTriggerSlopeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfTriggerSlope p3 = it0[3].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(slope) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutTriggerSlopeGet HDWF hdwf, int idxChannel, DwfTriggerSlope *pslope
HDWF
hdwf
int
idxChannel
DwfTriggerSlope *
pslope
*/
// 4 (match no. 122)

	int FDwfAnalogOutTriggerSlopeGet(HDWF hdwf, int idxChannel, DwfTriggerSlope *pslope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutTriggerSlopeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfTriggerSlope", (*pslope) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutTriggerSlopeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfTriggerSlope p3 = it0[3].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pslope) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRunInfo HDWF hdwf, int idxChannel, double *psecMin, double *psecMax
HDWF
hdwf
int
idxChannel
double *
psecMin
double *
psecMax
*/
// 4 (match no. 123)

	int FDwfAnalogOutRunInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRunInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRunInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psecMin) = p3;
					(*psecMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRunSet HDWF hdwf, int idxChannel, double secRun
HDWF
hdwf
int
idxChannel
double
secRun
*/
// 5 (match no. 124)

	int FDwfAnalogOutRunSet(HDWF hdwf, int idxChannel, double secRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRunSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", secRun }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRunSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(secRun) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRunGet HDWF hdwf, int idxChannel, double *psecRun
HDWF
hdwf
int
idxChannel
double *
psecRun
*/
// 4 (match no. 125)

	int FDwfAnalogOutRunGet(HDWF hdwf, int idxChannel, double *psecRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRunGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*psecRun) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRunGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psecRun) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRunStatus HDWF hdwf, int idxChannel, double *psecRun
HDWF
hdwf
int
idxChannel
double *
psecRun
*/
// 4 (match no. 126)

	int FDwfAnalogOutRunStatus(HDWF hdwf, int idxChannel, double *psecRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRunStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*psecRun) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRunStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psecRun) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutWaitInfo HDWF hdwf, int idxChannel, double *psecMin, double *psecMax
HDWF
hdwf
int
idxChannel
double *
psecMin
double *
psecMax
*/
// 4 (match no. 127)

	int FDwfAnalogOutWaitInfo(HDWF hdwf, int idxChannel, double *psecMin, double *psecMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutWaitInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutWaitInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psecMin) = p3;
					(*psecMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutWaitSet HDWF hdwf, int idxChannel, double secWait
HDWF
hdwf
int
idxChannel
double
secWait
*/
// 5 (match no. 128)

	int FDwfAnalogOutWaitSet(HDWF hdwf, int idxChannel, double secWait)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutWaitSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", secWait }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutWaitSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(secWait) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutWaitGet HDWF hdwf, int idxChannel, double *psecWait
HDWF
hdwf
int
idxChannel
double *
psecWait
*/
// 4 (match no. 129)

	int FDwfAnalogOutWaitGet(HDWF hdwf, int idxChannel, double *psecWait)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutWaitGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*psecWait) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutWaitGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psecWait) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatInfo HDWF hdwf, int idxChannel, int *pnMin, int *pnMax
HDWF
hdwf
int
idxChannel
int *
pnMin
int *
pnMax
*/
// 4 (match no. 130)

	int FDwfAnalogOutRepeatInfo(HDWF hdwf, int idxChannel, int *pnMin, int *pnMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pnMin) }},
					{{"int", (*pnMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pnMin) = p3;
					(*pnMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatSet HDWF hdwf, int idxChannel, int cRepeat
HDWF
hdwf
int
idxChannel
int
cRepeat
*/
// 5 (match no. 131)

	int FDwfAnalogOutRepeatSet(HDWF hdwf, int idxChannel, int cRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", cRepeat }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(cRepeat) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatGet HDWF hdwf, int idxChannel, int *pcRepeat
HDWF
hdwf
int
idxChannel
int *
pcRepeat
*/
// 4 (match no. 132)

	int FDwfAnalogOutRepeatGet(HDWF hdwf, int idxChannel, int *pcRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pcRepeat) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pcRepeat) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatStatus HDWF hdwf, int idxChannel, int *pcRepeat
HDWF
hdwf
int
idxChannel
int *
pcRepeat
*/
// 4 (match no. 133)

	int FDwfAnalogOutRepeatStatus(HDWF hdwf, int idxChannel, int *pcRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pcRepeat) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pcRepeat) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatTriggerSet HDWF hdwf, int idxChannel, int fRepeatTrigger
HDWF
hdwf
int
idxChannel
int
fRepeatTrigger
*/
// 4 (match no. 134)

	int FDwfAnalogOutRepeatTriggerSet(HDWF hdwf, int idxChannel, int fRepeatTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatTriggerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fRepeatTrigger }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatTriggerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fRepeatTrigger) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutRepeatTriggerGet HDWF hdwf, int idxChannel, int *pfRepeatTrigger
HDWF
hdwf
int
idxChannel
int *
pfRepeatTrigger
*/
// 4 (match no. 135)

	int FDwfAnalogOutRepeatTriggerGet(HDWF hdwf, int idxChannel, int *pfRepeatTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutRepeatTriggerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfRepeatTrigger) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutRepeatTriggerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfRepeatTrigger) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutLimitationInfo HDWF hdwf, int idxChannel, double *pMin, double *pMax
HDWF
hdwf
int
idxChannel
double *
pMin
double *
pMax
*/
// 4 (match no. 136)

	int FDwfAnalogOutLimitationInfo(HDWF hdwf, int idxChannel, double *pMin, double *pMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutLimitationInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pMin) }},
					{{"double", (*pMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutLimitationInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pMin) = p3;
					(*pMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutLimitationSet HDWF hdwf, int idxChannel, double limit
HDWF
hdwf
int
idxChannel
double
limit
*/
// 5 (match no. 137)

	int FDwfAnalogOutLimitationSet(HDWF hdwf, int idxChannel, double limit)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutLimitationSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", limit }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutLimitationSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(limit) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutLimitationGet HDWF hdwf, int idxChannel, double *plimit
HDWF
hdwf
int
idxChannel
double *
plimit
*/
// 4 (match no. 138)

	int FDwfAnalogOutLimitationGet(HDWF hdwf, int idxChannel, double *plimit)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutLimitationGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*plimit) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutLimitationGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*plimit) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutModeSet HDWF hdwf, int idxChannel, DwfAnalogOutMode mode
HDWF
hdwf
int
idxChannel
DwfAnalogOutMode
mode
*/
// 4 (match no. 139)

	int FDwfAnalogOutModeSet(HDWF hdwf, int idxChannel, DwfAnalogOutMode mode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfAnalogOutMode", mode }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfAnalogOutMode p3 = it0[3].begin().value().get<DwfAnalogOutMode>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(mode) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutModeGet HDWF hdwf, int idxChannel, DwfAnalogOutMode *pmode
HDWF
hdwf
int
idxChannel
DwfAnalogOutMode *
pmode
*/
// 4 (match no. 140)

	int FDwfAnalogOutModeGet(HDWF hdwf, int idxChannel, DwfAnalogOutMode *pmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutModeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfAnalogOutMode", (*pmode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutModeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfAnalogOutMode p3 = it0[3].begin().value().get<DwfAnalogOutMode>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pmode) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutIdleInfo HDWF hdwf, int idxChannel, int *pfsidle
HDWF
hdwf
int
idxChannel
int *
pfsidle
*/
// 4 (match no. 141)

	int FDwfAnalogOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsidle)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutIdleInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsidle) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutIdleInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsidle) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutIdleSet HDWF hdwf, int idxChannel, DwfAnalogOutIdle idle
HDWF
hdwf
int
idxChannel
DwfAnalogOutIdle
idle
*/
// 4 (match no. 142)

	int FDwfAnalogOutIdleSet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle idle)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutIdleSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfAnalogOutIdle", idle }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutIdleSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfAnalogOutIdle p3 = it0[3].begin().value().get<DwfAnalogOutIdle>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idle) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutIdleGet HDWF hdwf, int idxChannel, DwfAnalogOutIdle *pidle
HDWF
hdwf
int
idxChannel
DwfAnalogOutIdle *
pidle
*/
// 4 (match no. 143)

	int FDwfAnalogOutIdleGet(HDWF hdwf, int idxChannel, DwfAnalogOutIdle *pidle)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutIdleGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfAnalogOutIdle", (*pidle) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutIdleGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfAnalogOutIdle p3 = it0[3].begin().value().get<DwfAnalogOutIdle>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pidle) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeInfo HDWF hdwf, int idxChannel, int *pfsnode
HDWF
hdwf
int
idxChannel
int *
pfsnode
*/
// 4 (match no. 144)

	int FDwfAnalogOutNodeInfo(HDWF hdwf, int idxChannel, int *pfsnode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsnode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsnode) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeEnableSet HDWF hdwf, int idxChannel, AnalogOutNode node, int fEnable
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
int
fEnable
*/
// 4 (match no. 145)

	int FDwfAnalogOutNodeEnableSet(HDWF hdwf, int idxChannel, AnalogOutNode node, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(fEnable) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeEnableGet HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfEnable
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
int *
pfEnable
*/
// 5 (match no. 146)

	int FDwfAnalogOutNodeEnableGet(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"int", (*pfEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pfEnable) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFunctionInfo HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfsfunc
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
int *
pfsfunc
*/
// 5 (match no. 147)

	int FDwfAnalogOutNodeFunctionInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pfsfunc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFunctionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"int", (*pfsfunc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFunctionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pfsfunc) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFunctionSet HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC func
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
FUNC
func
*/
// 5 (match no. 148)

	int FDwfAnalogOutNodeFunctionSet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC func)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFunctionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"FUNC", func }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFunctionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					FUNC p4 = it0[4].begin().value().get<FUNC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(func) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFunctionGet HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC *pfunc
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
FUNC *
pfunc
*/
// 5 (match no. 149)

	int FDwfAnalogOutNodeFunctionGet(HDWF hdwf, int idxChannel, AnalogOutNode node, FUNC *pfunc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFunctionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"FUNC", (*pfunc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFunctionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					FUNC p4 = it0[4].begin().value().get<FUNC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pfunc) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFrequencyInfo HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzMin, double *phzMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
phzMin
double *
phzMax
*/
// 5 (match no. 150)

	int FDwfAnalogOutNodeFrequencyInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzMin, double *phzMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFrequencyInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*phzMin) }},
					{{"double", (*phzMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFrequencyInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*phzMin) = p4;
					(*phzMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFrequencySet HDWF hdwf, int idxChannel, AnalogOutNode node, double hzFrequency
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double
hzFrequency
*/
// 6 (match no. 151)

	int FDwfAnalogOutNodeFrequencySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double hzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFrequencySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", hzFrequency }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFrequencySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(hzFrequency) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeFrequencyGet HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzFrequency
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
phzFrequency
*/
// 5 (match no. 152)

	int FDwfAnalogOutNodeFrequencyGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *phzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeFrequencyGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*phzFrequency) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeFrequencyGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*phzFrequency) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeAmplitudeInfo HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pMin
double *
pMax
*/
// 5 (match no. 153)

	int FDwfAnalogOutNodeAmplitudeInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeAmplitudeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pMin) }},
					{{"double", (*pMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeAmplitudeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pMin) = p4;
					(*pMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeAmplitudeSet HDWF hdwf, int idxChannel, AnalogOutNode node, double vAmplitude
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double
vAmplitude
*/
// 6 (match no. 154)

	int FDwfAnalogOutNodeAmplitudeSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vAmplitude)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeAmplitudeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", vAmplitude }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeAmplitudeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(vAmplitude) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeAmplitudeGet HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvAmplitude
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pvAmplitude
*/
// 5 (match no. 155)

	int FDwfAnalogOutNodeAmplitudeGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvAmplitude)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeAmplitudeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pvAmplitude) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeAmplitudeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pvAmplitude) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeOffsetInfo HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pMin
double *
pMax
*/
// 5 (match no. 156)

	int FDwfAnalogOutNodeOffsetInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pMin, double *pMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeOffsetInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pMin) }},
					{{"double", (*pMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeOffsetInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pMin) = p4;
					(*pMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeOffsetSet HDWF hdwf, int idxChannel, AnalogOutNode node, double vOffset
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double
vOffset
*/
// 6 (match no. 157)

	int FDwfAnalogOutNodeOffsetSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double vOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeOffsetSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", vOffset }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeOffsetSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(vOffset) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeOffsetGet HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvOffset
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pvOffset
*/
// 5 (match no. 158)

	int FDwfAnalogOutNodeOffsetGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pvOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeOffsetGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pvOffset) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeOffsetGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pvOffset) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeSymmetryInfo HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageMin, double *ppercentageMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
ppercentageMin
double *
ppercentageMax
*/
// 5 (match no. 159)

	int FDwfAnalogOutNodeSymmetryInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageMin, double *ppercentageMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeSymmetryInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*ppercentageMin) }},
					{{"double", (*ppercentageMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeSymmetryInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*ppercentageMin) = p4;
					(*ppercentageMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeSymmetrySet HDWF hdwf, int idxChannel, AnalogOutNode node, double percentageSymmetry
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double
percentageSymmetry
*/
// 6 (match no. 160)

	int FDwfAnalogOutNodeSymmetrySet(HDWF hdwf, int idxChannel, AnalogOutNode node, double percentageSymmetry)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeSymmetrySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", percentageSymmetry }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeSymmetrySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(percentageSymmetry) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeSymmetryGet HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageSymmetry
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
ppercentageSymmetry
*/
// 5 (match no. 161)

	int FDwfAnalogOutNodeSymmetryGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *ppercentageSymmetry)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeSymmetryGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*ppercentageSymmetry) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeSymmetryGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*ppercentageSymmetry) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodePhaseInfo HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreeMin, double *pdegreeMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pdegreeMin
double *
pdegreeMax
*/
// 5 (match no. 162)

	int FDwfAnalogOutNodePhaseInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreeMin, double *pdegreeMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodePhaseInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pdegreeMin) }},
					{{"double", (*pdegreeMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodePhaseInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pdegreeMin) = p4;
					(*pdegreeMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodePhaseSet HDWF hdwf, int idxChannel, AnalogOutNode node, double degreePhase
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double
degreePhase
*/
// 6 (match no. 163)

	int FDwfAnalogOutNodePhaseSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double degreePhase)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodePhaseSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", degreePhase }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodePhaseSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(degreePhase) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodePhaseGet HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreePhase
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
pdegreePhase
*/
// 5 (match no. 164)

	int FDwfAnalogOutNodePhaseGet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *pdegreePhase)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodePhaseGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (*pdegreePhase) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodePhaseGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pdegreePhase) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeDataInfo HDWF hdwf, int idxChannel, AnalogOutNode node, int *pnSamplesMin, int *pnSamplesMax
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
int *
pnSamplesMin
int *
pnSamplesMax
*/
// 5 (match no. 165)

	int FDwfAnalogOutNodeDataInfo(HDWF hdwf, int idxChannel, AnalogOutNode node, int *pnSamplesMin, int *pnSamplesMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeDataInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"int", (*pnSamplesMin) }},
					{{"int", (*pnSamplesMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeDataInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*pnSamplesMin) = p4;
					(*pnSamplesMax) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodeDataSet HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
rgdData
int
cdData
*/
// 6 (match no. 166)

	int FDwfAnalogOutNodeDataSet(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodeDataSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (std::vector<double>(&rgdData[0], &rgdData[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodeDataSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					vector<double> p4 = it0[4].begin().value().get<vector<double>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					std::memmove(rgdData, p4.data(), 0 * sizeof(double));
					(cdData) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutCustomAMFMEnableSet HDWF hdwf, int idxChannel, int fEnable
HDWF
hdwf
int
idxChannel
int
fEnable
*/
// 6 (match no. 167)

	int FDwfAnalogOutCustomAMFMEnableSet(HDWF hdwf, int idxChannel, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutCustomAMFMEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutCustomAMFMEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutCustomAMFMEnableGet HDWF hdwf, int idxChannel, int *pfEnable
HDWF
hdwf
int
idxChannel
int *
pfEnable
*/
// 4 (match no. 168)

	int FDwfAnalogOutCustomAMFMEnableGet(HDWF hdwf, int idxChannel, int *pfEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutCustomAMFMEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutCustomAMFMEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutReset HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 4 (match no. 169)

	int FDwfAnalogOutReset(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutConfigure HDWF hdwf, int idxChannel, int fStart
HDWF
hdwf
int
idxChannel
int
fStart
*/
// 3 (match no. 170)

	int FDwfAnalogOutConfigure(HDWF hdwf, int idxChannel, int fStart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fStart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fStart) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutStatus HDWF hdwf, int idxChannel, DwfState *psts
HDWF
hdwf
int
idxChannel
DwfState *
psts
*/
// 4 (match no. 171)

	int FDwfAnalogOutStatus(HDWF hdwf, int idxChannel, DwfState *psts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfState", (*psts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfState p3 = it0[3].begin().value().get<DwfState>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*psts) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodePlayStatus HDWF hdwf, int idxChannel, AnalogOutNode node, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
int *
cdDataFree
int *
cdDataLost
int *
cdDataCorrupted
*/
// 4 (match no. 172)

	int FDwfAnalogOutNodePlayStatus(HDWF hdwf, int idxChannel, AnalogOutNode node, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodePlayStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"int", (*cdDataFree) }},
					{{"int", (*cdDataLost) }},
					{{"int", (*cdDataCorrupted) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodePlayStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 7)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();
					int p6 = it0[6].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					(*cdDataFree) = p4;
					(*cdDataLost) = p5;
					(*cdDataCorrupted) = p6;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutNodePlayData HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData
HDWF
hdwf
int
idxChannel
AnalogOutNode
node
double *
rgdData
int
cdData
*/
// 7 (match no. 173)

	int FDwfAnalogOutNodePlayData(HDWF hdwf, int idxChannel, AnalogOutNode node, double *rgdData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutNodePlayData",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"AnalogOutNode", node }},
					{{"double", (std::vector<double>(&rgdData[0], &rgdData[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutNodePlayData") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
					vector<double> p4 = it0[4].begin().value().get<vector<double>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(node) = p3;
					std::memmove(rgdData, p4.data(), 0 * sizeof(double));
					(cdData) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOReset HDWF hdwf
HDWF
hdwf
*/
// 6 (match no. 174)

	int FDwfAnalogIOReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOConfigure HDWF hdwf
HDWF
hdwf
*/
// 2 (match no. 175)

	int FDwfAnalogIOConfigure(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOStatus HDWF hdwf
HDWF
hdwf
*/
// 2 (match no. 176)

	int FDwfAnalogIOStatus(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOEnableInfo HDWF hdwf, int *pfSet, int *pfStatus
HDWF
hdwf
int *
pfSet
int *
pfStatus
*/
// 2 (match no. 177)

	int FDwfAnalogIOEnableInfo(HDWF hdwf, int *pfSet, int *pfStatus)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOEnableInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfSet) }},
					{{"int", (*pfStatus) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOEnableInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(*pfSet) = p2;
					(*pfStatus) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOEnableSet HDWF hdwf, int fMasterEnable
HDWF
hdwf
int
fMasterEnable
*/
// 4 (match no. 178)

	int FDwfAnalogIOEnableSet(HDWF hdwf, int fMasterEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fMasterEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fMasterEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOEnableGet HDWF hdwf, int *pfMasterEnable
HDWF
hdwf
int *
pfMasterEnable
*/
// 3 (match no. 179)

	int FDwfAnalogIOEnableGet(HDWF hdwf, int *pfMasterEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfMasterEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfMasterEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOEnableStatus HDWF hdwf, int *pfMasterEnable
HDWF
hdwf
int *
pfMasterEnable
*/
// 3 (match no. 180)

	int FDwfAnalogIOEnableStatus(HDWF hdwf, int *pfMasterEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOEnableStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfMasterEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOEnableStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfMasterEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelCount HDWF hdwf, int *pnChannel
HDWF
hdwf
int *
pnChannel
*/
// 3 (match no. 181)

	int FDwfAnalogIOChannelCount(HDWF hdwf, int *pnChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelCount",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnChannel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelCount") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelName HDWF hdwf, int idxChannel, char szName[32], char szLabel[16]
HDWF
hdwf
int
idxChannel
char
szName[32]
char
szLabel[16]
*/
// 3 (match no. 182)

	int FDwfAnalogIOChannelName(HDWF hdwf, int idxChannel, char szName[32], char szLabel[16])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelName",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"char", (std::vector<char>(&szName[0], &szName[32])) }},
					{{"char", (std::vector<char>(&szLabel[0], &szLabel[16])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelName") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<char> p3 = it0[3].begin().value().get<vector<char>>();
					vector<char> p4 = it0[4].begin().value().get<vector<char>>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(szName, p3.data(), 32 * sizeof(char));
					std::memmove(szLabel, p4.data(), 16 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelInfo HDWF hdwf, int idxChannel, int *pnNodes
HDWF
hdwf
int
idxChannel
int *
pnNodes
*/
// 5 (match no. 183)

	int FDwfAnalogIOChannelInfo(HDWF hdwf, int idxChannel, int *pnNodes)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pnNodes) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pnNodes) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeName HDWF hdwf, int idxChannel, int idxNode, char szNodeName[32], char szNodeUnits[16]
HDWF
hdwf
int
idxChannel
int
idxNode
char
szNodeName[32]
char
szNodeUnits[16]
*/
// 4 (match no. 184)

	int FDwfAnalogIOChannelNodeName(HDWF hdwf, int idxChannel, int idxNode, char szNodeName[32], char szNodeUnits[16])
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeName",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"char", (std::vector<char>(&szNodeName[0], &szNodeName[32])) }},
					{{"char", (std::vector<char>(&szNodeUnits[0], &szNodeUnits[16])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeName") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<char> p4 = it0[4].begin().value().get<vector<char>>();
					vector<char> p5 = it0[5].begin().value().get<vector<char>>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					std::memmove(szNodeName, p4.data(), 32 * sizeof(char));
					std::memmove(szNodeUnits, p5.data(), 16 * sizeof(char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeInfo HDWF hdwf, int idxChannel, int idxNode, ANALOGIO *panalogio
HDWF
hdwf
int
idxChannel
int
idxNode
ANALOGIO *
panalogio
*/
// 6 (match no. 185)

	int FDwfAnalogIOChannelNodeInfo(HDWF hdwf, int idxChannel, int idxNode, ANALOGIO *panalogio)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"ANALOGIO", (*panalogio) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					ANALOGIO p4 = it0[4].begin().value().get<ANALOGIO>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(*panalogio) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeSetInfo HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps
HDWF
hdwf
int
idxChannel
int
idxNode
double *
pmin
double *
pmax
int *
pnSteps
*/
// 5 (match no. 186)

	int FDwfAnalogIOChannelNodeSetInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeSetInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"double", (*pmin) }},
					{{"double", (*pmax) }},
					{{"int", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeSetInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 7)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();
					int p6 = it0[6].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(*pmin) = p4;
					(*pmax) = p5;
					(*pnSteps) = p6;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeSet HDWF hdwf, int idxChannel, int idxNode, double value
HDWF
hdwf
int
idxChannel
int
idxNode
double
value
*/
// 7 (match no. 187)

	int FDwfAnalogIOChannelNodeSet(HDWF hdwf, int idxChannel, int idxNode, double value)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"double", value }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(value) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeGet HDWF hdwf, int idxChannel, int idxNode, double *pvalue
HDWF
hdwf
int
idxChannel
int
idxNode
double *
pvalue
*/
// 5 (match no. 188)

	int FDwfAnalogIOChannelNodeGet(HDWF hdwf, int idxChannel, int idxNode, double *pvalue)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"double", (*pvalue) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(*pvalue) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeStatusInfo HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps
HDWF
hdwf
int
idxChannel
int
idxNode
double *
pmin
double *
pmax
int *
pnSteps
*/
// 5 (match no. 189)

	int FDwfAnalogIOChannelNodeStatusInfo(HDWF hdwf, int idxChannel, int idxNode, double *pmin, double *pmax, int *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeStatusInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"double", (*pmin) }},
					{{"double", (*pmax) }},
					{{"int", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeStatusInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 7)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();
					int p6 = it0[6].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(*pmin) = p4;
					(*pmax) = p5;
					(*pnSteps) = p6;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogIOChannelNodeStatus HDWF hdwf, int idxChannel, int idxNode, double *pvalue
HDWF
hdwf
int
idxChannel
int
idxNode
double *
pvalue
*/
// 7 (match no. 190)

	int FDwfAnalogIOChannelNodeStatus(HDWF hdwf, int idxChannel, int idxNode, double *pvalue)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogIOChannelNodeStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", idxNode }},
					{{"double", (*pvalue) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogIOChannelNodeStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(idxNode) = p3;
					(*pvalue) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOReset HDWF hdwf
HDWF
hdwf
*/
// 5 (match no. 191)

	int FDwfDigitalIOReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOConfigure HDWF hdwf
HDWF
hdwf
*/
// 2 (match no. 192)

	int FDwfDigitalIOConfigure(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOStatus HDWF hdwf
HDWF
hdwf
*/
// 2 (match no. 193)

	int FDwfDigitalIOStatus(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableInfo HDWF hdwf, unsigned int *pfsOutputEnableMask
HDWF
hdwf
unsigned int *
pfsOutputEnableMask
*/
// 2 (match no. 194)

	int FDwfDigitalIOOutputEnableInfo(HDWF hdwf, unsigned int *pfsOutputEnableMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsOutputEnableMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsOutputEnableMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableSet HDWF hdwf, unsigned int fsOutputEnable
HDWF
hdwf
unsigned int
fsOutputEnable
*/
// 3 (match no. 195)

	int FDwfDigitalIOOutputEnableSet(HDWF hdwf, unsigned int fsOutputEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", fsOutputEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(fsOutputEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableGet HDWF hdwf, unsigned int *pfsOutputEnable
HDWF
hdwf
unsigned int *
pfsOutputEnable
*/
// 3 (match no. 196)

	int FDwfDigitalIOOutputEnableGet(HDWF hdwf, unsigned int *pfsOutputEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsOutputEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsOutputEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputInfo HDWF hdwf, unsigned int *pfsOutputMask
HDWF
hdwf
unsigned int *
pfsOutputMask
*/
// 3 (match no. 197)

	int FDwfDigitalIOOutputInfo(HDWF hdwf, unsigned int *pfsOutputMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsOutputMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsOutputMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputSet HDWF hdwf, unsigned int fsOutput
HDWF
hdwf
unsigned int
fsOutput
*/
// 3 (match no. 198)

	int FDwfDigitalIOOutputSet(HDWF hdwf, unsigned int fsOutput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", fsOutput }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(fsOutput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputGet HDWF hdwf, unsigned int *pfsOutput
HDWF
hdwf
unsigned int *
pfsOutput
*/
// 3 (match no. 199)

	int FDwfDigitalIOOutputGet(HDWF hdwf, unsigned int *pfsOutput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsOutput) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsOutput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOInputInfo HDWF hdwf, unsigned int *pfsInputMask
HDWF
hdwf
unsigned int *
pfsInputMask
*/
// 3 (match no. 200)

	int FDwfDigitalIOInputInfo(HDWF hdwf, unsigned int *pfsInputMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOInputInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsInputMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOInputInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsInputMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOInputStatus HDWF hdwf, unsigned int *pfsInput
HDWF
hdwf
unsigned int *
pfsInput
*/
// 3 (match no. 201)

	int FDwfDigitalIOInputStatus(HDWF hdwf, unsigned int *pfsInput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOInputStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsInput) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOInputStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsInput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableInfo64 HDWF hdwf, unsigned long long *pfsOutputEnableMask
HDWF
hdwf
unsigned long long *
pfsOutputEnableMask
*/
// 3 (match no. 202)

	int FDwfDigitalIOOutputEnableInfo64(HDWF hdwf, unsigned long long *pfsOutputEnableMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableInfo64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsOutputEnableMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableInfo64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsOutputEnableMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableSet64 HDWF hdwf, unsigned long long fsOutputEnable
HDWF
hdwf
unsigned long long
fsOutputEnable
*/
// 3 (match no. 203)

	int FDwfDigitalIOOutputEnableSet64(HDWF hdwf, unsigned long long fsOutputEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableSet64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", fsOutputEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableSet64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(fsOutputEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputEnableGet64 HDWF hdwf, unsigned long long *pfsOutputEnable
HDWF
hdwf
unsigned long long *
pfsOutputEnable
*/
// 3 (match no. 204)

	int FDwfDigitalIOOutputEnableGet64(HDWF hdwf, unsigned long long *pfsOutputEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputEnableGet64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsOutputEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputEnableGet64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsOutputEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputInfo64 HDWF hdwf, unsigned long long *pfsOutputMask
HDWF
hdwf
unsigned long long *
pfsOutputMask
*/
// 3 (match no. 205)

	int FDwfDigitalIOOutputInfo64(HDWF hdwf, unsigned long long *pfsOutputMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputInfo64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsOutputMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputInfo64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsOutputMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputSet64 HDWF hdwf, unsigned long long fsOutput
HDWF
hdwf
unsigned long long
fsOutput
*/
// 3 (match no. 206)

	int FDwfDigitalIOOutputSet64(HDWF hdwf, unsigned long long fsOutput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputSet64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", fsOutput }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputSet64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(fsOutput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOOutputGet64 HDWF hdwf, unsigned long long *pfsOutput
HDWF
hdwf
unsigned long long *
pfsOutput
*/
// 3 (match no. 207)

	int FDwfDigitalIOOutputGet64(HDWF hdwf, unsigned long long *pfsOutput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOOutputGet64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsOutput) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOOutputGet64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsOutput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOInputInfo64 HDWF hdwf, unsigned long long *pfsInputMask
HDWF
hdwf
unsigned long long *
pfsInputMask
*/
// 3 (match no. 208)

	int FDwfDigitalIOInputInfo64(HDWF hdwf, unsigned long long *pfsInputMask)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOInputInfo64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsInputMask) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOInputInfo64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsInputMask) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalIOInputStatus64 HDWF hdwf, unsigned long long *pfsInput
HDWF
hdwf
unsigned long long *
pfsInput
*/
// 3 (match no. 209)

	int FDwfDigitalIOInputStatus64(HDWF hdwf, unsigned long long *pfsInput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalIOInputStatus64",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned long long", (*pfsInput) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalIOInputStatus64") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

					(hdwf) = p1;
					(*pfsInput) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInReset HDWF hdwf
HDWF
hdwf
*/
// 3 (match no. 210)

	int FDwfDigitalInReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInConfigure HDWF hdwf, int fReconfigure, int fStart
HDWF
hdwf
int
fReconfigure
int
fStart
*/
// 2 (match no. 211)

	int FDwfDigitalInConfigure(HDWF hdwf, int fReconfigure, int fStart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fReconfigure }},
					{{"int", fStart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(fReconfigure) = p2;
					(fStart) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatus HDWF hdwf, int fReadData, DwfState *psts
HDWF
hdwf
int
fReadData
DwfState *
psts
*/
// 4 (match no. 212)

	int FDwfDigitalInStatus(HDWF hdwf, int fReadData, DwfState *psts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fReadData }},
					{{"DwfState", (*psts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfState p3 = it0[3].begin().value().get<DwfState>();

					(hdwf) = p1;
					(fReadData) = p2;
					(*psts) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusSamplesLeft HDWF hdwf, int *pcSamplesLeft
HDWF
hdwf
int *
pcSamplesLeft
*/
// 4 (match no. 213)

	int FDwfDigitalInStatusSamplesLeft(HDWF hdwf, int *pcSamplesLeft)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusSamplesLeft",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcSamplesLeft) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusSamplesLeft") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcSamplesLeft) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusSamplesValid HDWF hdwf, int *pcSamplesValid
HDWF
hdwf
int *
pcSamplesValid
*/
// 3 (match no. 214)

	int FDwfDigitalInStatusSamplesValid(HDWF hdwf, int *pcSamplesValid)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusSamplesValid",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcSamplesValid) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusSamplesValid") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcSamplesValid) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusIndexWrite HDWF hdwf, int *pidxWrite
HDWF
hdwf
int *
pidxWrite
*/
// 3 (match no. 215)

	int FDwfDigitalInStatusIndexWrite(HDWF hdwf, int *pidxWrite)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusIndexWrite",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pidxWrite) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusIndexWrite") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pidxWrite) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusAutoTriggered HDWF hdwf, int *pfAuto
HDWF
hdwf
int *
pfAuto
*/
// 3 (match no. 216)

	int FDwfDigitalInStatusAutoTriggered(HDWF hdwf, int *pfAuto)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusAutoTriggered",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfAuto) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusAutoTriggered") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfAuto) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusData HDWF hdwf, void *rgData, int countOfDataBytes
HDWF
hdwf
void *
rgData
int
countOfDataBytes
*/
// 3 (match no. 217)

	int FDwfDigitalInStatusData(HDWF hdwf, void *rgData, int countOfDataBytes)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusData",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"char", (std::vector<char>(&((char*)rgData)[0], &((char*)rgData)[countOfDataBytes])) }},
					{{"int", countOfDataBytes }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusData") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					std::memmove(rgData, p2.data(), 0 * sizeof(char));
					(countOfDataBytes) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusData2 HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes
HDWF
hdwf
void *
rgData
int
idxSample
int
countOfDataBytes
*/
// 4 (match no. 218)

	int FDwfDigitalInStatusData2(HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusData2",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"char", (std::vector<char>(&((char*)rgData)[0], &((char*)rgData)[countOfDataBytes])) }},
					{{"int", idxSample }},
					{{"int", countOfDataBytes }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusData2") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					std::memmove(rgData, p2.data(), 0 * sizeof(char));
					(idxSample) = p3;
					(countOfDataBytes) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusNoise2 HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes
HDWF
hdwf
void *
rgData
int
idxSample
int
countOfDataBytes
*/
// 5 (match no. 219)

	int FDwfDigitalInStatusNoise2(HDWF hdwf, void *rgData, int idxSample, int countOfDataBytes)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusNoise2",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"char", (std::vector<char>(&((char*)rgData)[0], &((char*)rgData)[countOfDataBytes])) }},
					{{"int", idxSample }},
					{{"int", countOfDataBytes }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusNoise2") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					vector<char> p2 = it0[2].begin().value().get<vector<char>>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					std::memmove(rgData, p2.data(), 0 * sizeof(char));
					(idxSample) = p3;
					(countOfDataBytes) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInStatusRecord HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt
HDWF
hdwf
int *
pcdDataAvailable
int *
pcdDataLost
int *
pcdDataCorrupt
*/
// 5 (match no. 220)

	int FDwfDigitalInStatusRecord(HDWF hdwf, int *pcdDataAvailable, int *pcdDataLost, int *pcdDataCorrupt)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInStatusRecord",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcdDataAvailable) }},
					{{"int", (*pcdDataLost) }},
					{{"int", (*pcdDataCorrupt) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInStatusRecord") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(*pcdDataAvailable) = p2;
					(*pcdDataLost) = p3;
					(*pcdDataCorrupt) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInInternalClockInfo HDWF hdwf, double *phzFreq
HDWF
hdwf
double *
phzFreq
*/
// 5 (match no. 221)

	int FDwfDigitalInInternalClockInfo(HDWF hdwf, double *phzFreq)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInInternalClockInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*phzFreq) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInInternalClockInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*phzFreq) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInClockSourceInfo HDWF hdwf, int *pfsDwfDigitalInClockSource
HDWF
hdwf
int *
pfsDwfDigitalInClockSource
*/
// 3 (match no. 222)

	int FDwfDigitalInClockSourceInfo(HDWF hdwf, int *pfsDwfDigitalInClockSource)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInClockSourceInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsDwfDigitalInClockSource) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInClockSourceInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsDwfDigitalInClockSource) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInClockSourceSet HDWF hdwf, DwfDigitalInClockSource v
HDWF
hdwf
DwfDigitalInClockSource
v
*/
// 3 (match no. 223)

	int FDwfDigitalInClockSourceSet(HDWF hdwf, DwfDigitalInClockSource v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInClockSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfDigitalInClockSource", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInClockSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfDigitalInClockSource p2 = it0[2].begin().value().get<DwfDigitalInClockSource>();

					(hdwf) = p1;
					(v) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInClockSourceGet HDWF hdwf, DwfDigitalInClockSource *pv
HDWF
hdwf
DwfDigitalInClockSource *
pv
*/
// 3 (match no. 224)

	int FDwfDigitalInClockSourceGet(HDWF hdwf, DwfDigitalInClockSource *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInClockSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfDigitalInClockSource", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInClockSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfDigitalInClockSource p2 = it0[2].begin().value().get<DwfDigitalInClockSource>();

					(hdwf) = p1;
					(*pv) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInDividerInfo HDWF hdwf, unsigned int *pdivMax
HDWF
hdwf
unsigned int *
pdivMax
*/
// 3 (match no. 225)

	int FDwfDigitalInDividerInfo(HDWF hdwf, unsigned int *pdivMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInDividerInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pdivMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInDividerInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pdivMax) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInDividerSet HDWF hdwf, unsigned int div
HDWF
hdwf
unsigned int
div
*/
// 3 (match no. 226)

	int FDwfDigitalInDividerSet(HDWF hdwf, unsigned int div)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInDividerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", div }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInDividerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(div) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInDividerGet HDWF hdwf, unsigned int *pdiv
HDWF
hdwf
unsigned int *
pdiv
*/
// 3 (match no. 227)

	int FDwfDigitalInDividerGet(HDWF hdwf, unsigned int *pdiv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInDividerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pdiv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInDividerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pdiv) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInBitsInfo HDWF hdwf, int *pnBits
HDWF
hdwf
int *
pnBits
*/
// 3 (match no. 228)

	int FDwfDigitalInBitsInfo(HDWF hdwf, int *pnBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInBitsInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnBits) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInBitsInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleFormatSet HDWF hdwf, int nBits
HDWF
hdwf
int
nBits
*/
// 3 (match no. 229)

	int FDwfDigitalInSampleFormatSet(HDWF hdwf, int nBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleFormatSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", nBits }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleFormatSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(nBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleFormatGet HDWF hdwf, int *pnBits
HDWF
hdwf
int *
pnBits
*/
// 3 (match no. 230)

	int FDwfDigitalInSampleFormatGet(HDWF hdwf, int *pnBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleFormatGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnBits) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleFormatGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInInputOrderSet HDWF hdwf, bool fDioFirst
HDWF
hdwf
bool
fDioFirst
*/
// 3 (match no. 231)

	int FDwfDigitalInInputOrderSet(HDWF hdwf, bool fDioFirst)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInInputOrderSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"bool", fDioFirst }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInInputOrderSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					bool p2 = it0[2].begin().value().get<bool>();

					(hdwf) = p1;
					(fDioFirst) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInBufferSizeInfo HDWF hdwf, int *pnSizeMax
HDWF
hdwf
int *
pnSizeMax
*/
// 3 (match no. 232)

	int FDwfDigitalInBufferSizeInfo(HDWF hdwf, int *pnSizeMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInBufferSizeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSizeMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInBufferSizeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSizeMax) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInBufferSizeSet HDWF hdwf, int nSize
HDWF
hdwf
int
nSize
*/
// 3 (match no. 233)

	int FDwfDigitalInBufferSizeSet(HDWF hdwf, int nSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInBufferSizeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", nSize }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInBufferSizeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(nSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInBufferSizeGet HDWF hdwf, int *pnSize
HDWF
hdwf
int *
pnSize
*/
// 3 (match no. 234)

	int FDwfDigitalInBufferSizeGet(HDWF hdwf, int *pnSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInBufferSizeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pnSize) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInBufferSizeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pnSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleModeInfo HDWF hdwf, int *pfsDwfDigitalInSampleMode
HDWF
hdwf
int *
pfsDwfDigitalInSampleMode
*/
// 3 (match no. 235)

	int FDwfDigitalInSampleModeInfo(HDWF hdwf, int *pfsDwfDigitalInSampleMode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleModeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsDwfDigitalInSampleMode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleModeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsDwfDigitalInSampleMode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleModeSet HDWF hdwf, DwfDigitalInSampleMode v
HDWF
hdwf
DwfDigitalInSampleMode
v
*/
// 3 (match no. 236)

	int FDwfDigitalInSampleModeSet(HDWF hdwf, DwfDigitalInSampleMode v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfDigitalInSampleMode", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfDigitalInSampleMode p2 = it0[2].begin().value().get<DwfDigitalInSampleMode>();

					(hdwf) = p1;
					(v) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleModeGet HDWF hdwf, DwfDigitalInSampleMode *pv
HDWF
hdwf
DwfDigitalInSampleMode *
pv
*/
// 3 (match no. 237)

	int FDwfDigitalInSampleModeGet(HDWF hdwf, DwfDigitalInSampleMode *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleModeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfDigitalInSampleMode", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleModeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfDigitalInSampleMode p2 = it0[2].begin().value().get<DwfDigitalInSampleMode>();

					(hdwf) = p1;
					(*pv) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleSensibleSet HDWF hdwf, unsigned int fs
HDWF
hdwf
unsigned int
fs
*/
// 3 (match no. 238)

	int FDwfDigitalInSampleSensibleSet(HDWF hdwf, unsigned int fs)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleSensibleSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", fs }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleSensibleSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(fs) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInSampleSensibleGet HDWF hdwf, unsigned int *pfs
HDWF
hdwf
unsigned int *
pfs
*/
// 3 (match no. 239)

	int FDwfDigitalInSampleSensibleGet(HDWF hdwf, unsigned int *pfs)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInSampleSensibleGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfs) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInSampleSensibleGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfs) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInAcquisitionModeInfo HDWF hdwf, int *pfsacqmode
HDWF
hdwf
int *
pfsacqmode
*/
// 3 (match no. 240)

	int FDwfDigitalInAcquisitionModeInfo(HDWF hdwf, int *pfsacqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInAcquisitionModeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfsacqmode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInAcquisitionModeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfsacqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInAcquisitionModeSet HDWF hdwf, ACQMODE acqmode
HDWF
hdwf
ACQMODE
acqmode
*/
// 3 (match no. 241)

	int FDwfDigitalInAcquisitionModeSet(HDWF hdwf, ACQMODE acqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInAcquisitionModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"ACQMODE", acqmode }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInAcquisitionModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

					(hdwf) = p1;
					(acqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInAcquisitionModeGet HDWF hdwf, ACQMODE *pacqmode
HDWF
hdwf
ACQMODE *
pacqmode
*/
// 3 (match no. 242)

	int FDwfDigitalInAcquisitionModeGet(HDWF hdwf, ACQMODE *pacqmode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInAcquisitionModeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"ACQMODE", (*pacqmode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInAcquisitionModeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

					(hdwf) = p1;
					(*pacqmode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF
hdwf
TRIGSRC
trigsrc
*/
// 3 (match no. 243)

	int FDwfDigitalInTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(trigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 244)

	int FDwfDigitalInTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(*ptrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF
hdwf
DwfTriggerSlope
slope
*/
// 3 (match no. 245)

	int FDwfDigitalInTriggerSlopeSet(HDWF hdwf, DwfTriggerSlope slope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSlopeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", slope }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSlopeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(slope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 246)

	int FDwfDigitalInTriggerSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSlopeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", (*pslope) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSlopeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(*pslope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerPositionInfo HDWF hdwf, unsigned int *pnSamplesAfterTriggerMax
HDWF
hdwf
unsigned int *
pnSamplesAfterTriggerMax
*/
// 3 (match no. 247)

	int FDwfDigitalInTriggerPositionInfo(HDWF hdwf, unsigned int *pnSamplesAfterTriggerMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerPositionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pnSamplesAfterTriggerMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerPositionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pnSamplesAfterTriggerMax) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerPositionSet HDWF hdwf, unsigned int cSamplesAfterTrigger
HDWF
hdwf
unsigned int
cSamplesAfterTrigger
*/
// 3 (match no. 248)

	int FDwfDigitalInTriggerPositionSet(HDWF hdwf, unsigned int cSamplesAfterTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerPositionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", cSamplesAfterTrigger }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerPositionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(cSamplesAfterTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerPositionGet HDWF hdwf, unsigned int *pcSamplesAfterTrigger
HDWF
hdwf
unsigned int *
pcSamplesAfterTrigger
*/
// 3 (match no. 249)

	int FDwfDigitalInTriggerPositionGet(HDWF hdwf, unsigned int *pcSamplesAfterTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerPositionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pcSamplesAfterTrigger) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerPositionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pcSamplesAfterTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerPrefillSet HDWF hdwf, unsigned int cSamplesBeforeTrigger
HDWF
hdwf
unsigned int
cSamplesBeforeTrigger
*/
// 3 (match no. 250)

	int FDwfDigitalInTriggerPrefillSet(HDWF hdwf, unsigned int cSamplesBeforeTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerPrefillSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", cSamplesBeforeTrigger }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerPrefillSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(cSamplesBeforeTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerPrefillGet HDWF hdwf, unsigned int *pcSamplesBeforeTrigger
HDWF
hdwf
unsigned int *
pcSamplesBeforeTrigger
*/
// 3 (match no. 251)

	int FDwfDigitalInTriggerPrefillGet(HDWF hdwf, unsigned int *pcSamplesBeforeTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerPrefillGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pcSamplesBeforeTrigger) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerPrefillGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pcSamplesBeforeTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerAutoTimeoutInfo HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps
HDWF
hdwf
double *
psecMin
double *
psecMax
double *
pnSteps
*/
// 3 (match no. 252)

	int FDwfDigitalInTriggerAutoTimeoutInfo(HDWF hdwf, double *psecMin, double *psecMax, double *pnSteps)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerAutoTimeoutInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
					{{"double", (*pnSteps) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerAutoTimeoutInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
					(*pnSteps) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerAutoTimeoutSet HDWF hdwf, double secTimeout
HDWF
hdwf
double
secTimeout
*/
// 5 (match no. 253)

	int FDwfDigitalInTriggerAutoTimeoutSet(HDWF hdwf, double secTimeout)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerAutoTimeoutSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secTimeout }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerAutoTimeoutSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secTimeout) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerAutoTimeoutGet HDWF hdwf, double *psecTimeout
HDWF
hdwf
double *
psecTimeout
*/
// 3 (match no. 254)

	int FDwfDigitalInTriggerAutoTimeoutGet(HDWF hdwf, double *psecTimeout)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerAutoTimeoutGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecTimeout) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerAutoTimeoutGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecTimeout) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerInfo HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall
HDWF
hdwf
unsigned int *
pfsLevelLow
unsigned int *
pfsLevelHigh
unsigned int *
pfsEdgeRise
unsigned int *
pfsEdgeFall
*/
// 3 (match no. 255)

	int FDwfDigitalInTriggerInfo(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsLevelLow) }},
					{{"unsigned int", (*pfsLevelHigh) }},
					{{"unsigned int", (*pfsEdgeRise) }},
					{{"unsigned int", (*pfsEdgeFall) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();
					unsigned int p5 = it0[5].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsLevelLow) = p2;
					(*pfsLevelHigh) = p3;
					(*pfsEdgeRise) = p4;
					(*pfsEdgeFall) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSet HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall
HDWF
hdwf
unsigned int
fsLevelLow
unsigned int
fsLevelHigh
unsigned int
fsEdgeRise
unsigned int
fsEdgeFall
*/
// 6 (match no. 256)

	int FDwfDigitalInTriggerSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", fsLevelLow }},
					{{"unsigned int", fsLevelHigh }},
					{{"unsigned int", fsEdgeRise }},
					{{"unsigned int", fsEdgeFall }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();
					unsigned int p5 = it0[5].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(fsLevelLow) = p2;
					(fsLevelHigh) = p3;
					(fsEdgeRise) = p4;
					(fsEdgeFall) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerGet HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall
HDWF
hdwf
unsigned int *
pfsLevelLow
unsigned int *
pfsLevelHigh
unsigned int *
pfsEdgeRise
unsigned int *
pfsEdgeFall
*/
// 6 (match no. 257)

	int FDwfDigitalInTriggerGet(HDWF hdwf, unsigned int *pfsLevelLow, unsigned int *pfsLevelHigh, unsigned int *pfsEdgeRise, unsigned int *pfsEdgeFall)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pfsLevelLow) }},
					{{"unsigned int", (*pfsLevelHigh) }},
					{{"unsigned int", (*pfsEdgeRise) }},
					{{"unsigned int", (*pfsEdgeFall) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();
					unsigned int p5 = it0[5].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pfsLevelLow) = p2;
					(*pfsLevelHigh) = p3;
					(*pfsEdgeRise) = p4;
					(*pfsEdgeFall) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerResetSet HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall
HDWF
hdwf
unsigned int
fsLevelLow
unsigned int
fsLevelHigh
unsigned int
fsEdgeRise
unsigned int
fsEdgeFall
*/
// 6 (match no. 258)

	int FDwfDigitalInTriggerResetSet(HDWF hdwf, unsigned int fsLevelLow, unsigned int fsLevelHigh, unsigned int fsEdgeRise, unsigned int fsEdgeFall)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerResetSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", fsLevelLow }},
					{{"unsigned int", fsLevelHigh }},
					{{"unsigned int", fsEdgeRise }},
					{{"unsigned int", fsEdgeFall }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerResetSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();
					unsigned int p5 = it0[5].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(fsLevelLow) = p2;
					(fsLevelHigh) = p3;
					(fsEdgeRise) = p4;
					(fsEdgeFall) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerCountSet HDWF hdwf, int cCount, int fRestart
HDWF
hdwf
int
cCount
int
fRestart
*/
// 6 (match no. 259)

	int FDwfDigitalInTriggerCountSet(HDWF hdwf, int cCount, int fRestart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerCountSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cCount }},
					{{"int", fRestart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerCountSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(cCount) = p2;
					(fRestart) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerLengthSet HDWF hdwf, double secMin, double secMax, int idxSync
HDWF
hdwf
double
secMin
double
secMax
int
idxSync
*/
// 4 (match no. 260)

	int FDwfDigitalInTriggerLengthSet(HDWF hdwf, double secMin, double secMax, int idxSync)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerLengthSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secMin }},
					{{"double", secMax }},
					{{"int", idxSync }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerLengthSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(secMin) = p2;
					(secMax) = p3;
					(idxSync) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerMatchSet HDWF hdwf, int iPin, unsigned int fsMask, unsigned int fsValue, int cBitStuffing
HDWF
hdwf
int
iPin
unsigned int
fsMask
unsigned int
fsValue
int
cBitStuffing
*/
// 5 (match no. 261)

	int FDwfDigitalInTriggerMatchSet(HDWF hdwf, int iPin, unsigned int fsMask, unsigned int fsValue, int cBitStuffing)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerMatchSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", iPin }},
					{{"unsigned int", fsMask }},
					{{"unsigned int", fsValue }},
					{{"int", cBitStuffing }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerMatchSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(iPin) = p2;
					(fsMask) = p3;
					(fsValue) = p4;
					(cBitStuffing) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutReset HDWF hdwf
HDWF
hdwf
*/
// 6 (match no. 262)

	int FDwfDigitalOutReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutConfigure HDWF hdwf, int fStart
HDWF
hdwf
int
fStart
*/
// 2 (match no. 263)

	int FDwfDigitalOutConfigure(HDWF hdwf, int fStart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fStart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fStart) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutStatus HDWF hdwf, DwfState *psts
HDWF
hdwf
DwfState *
psts
*/
// 3 (match no. 264)

	int FDwfDigitalOutStatus(HDWF hdwf, DwfState *psts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfState", (*psts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfState p2 = it0[2].begin().value().get<DwfState>();

					(hdwf) = p1;
					(*psts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutInternalClockInfo HDWF hdwf, double *phzFreq
HDWF
hdwf
double *
phzFreq
*/
// 3 (match no. 265)

	int FDwfDigitalOutInternalClockInfo(HDWF hdwf, double *phzFreq)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutInternalClockInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*phzFreq) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutInternalClockInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*phzFreq) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF
hdwf
TRIGSRC
trigsrc
*/
// 3 (match no. 266)

	int FDwfDigitalOutTriggerSourceSet(HDWF hdwf, TRIGSRC trigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTriggerSourceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", trigsrc }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTriggerSourceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(trigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 267)

	int FDwfDigitalOutTriggerSourceGet(HDWF hdwf, TRIGSRC *ptrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTriggerSourceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"TRIGSRC", (*ptrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTriggerSourceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

					(hdwf) = p1;
					(*ptrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRunInfo HDWF hdwf, double *psecMin, double *psecMax
HDWF
hdwf
double *
psecMin
double *
psecMax
*/
// 3 (match no. 268)

	int FDwfDigitalOutRunInfo(HDWF hdwf, double *psecMin, double *psecMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRunInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRunInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRunSet HDWF hdwf, double secRun
HDWF
hdwf
double
secRun
*/
// 4 (match no. 269)

	int FDwfDigitalOutRunSet(HDWF hdwf, double secRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRunSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secRun }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRunSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secRun) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRunGet HDWF hdwf, double *psecRun
HDWF
hdwf
double *
psecRun
*/
// 3 (match no. 270)

	int FDwfDigitalOutRunGet(HDWF hdwf, double *psecRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRunGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecRun) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRunGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecRun) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRunStatus HDWF hdwf, double *psecRun
HDWF
hdwf
double *
psecRun
*/
// 3 (match no. 271)

	int FDwfDigitalOutRunStatus(HDWF hdwf, double *psecRun)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRunStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecRun) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRunStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecRun) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutWaitInfo HDWF hdwf, double *psecMin, double *psecMax
HDWF
hdwf
double *
psecMin
double *
psecMax
*/
// 3 (match no. 272)

	int FDwfDigitalOutWaitInfo(HDWF hdwf, double *psecMin, double *psecMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutWaitInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecMin) }},
					{{"double", (*psecMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutWaitInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(*psecMin) = p2;
					(*psecMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutWaitSet HDWF hdwf, double secWait
HDWF
hdwf
double
secWait
*/
// 4 (match no. 273)

	int FDwfDigitalOutWaitSet(HDWF hdwf, double secWait)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutWaitSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", secWait }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutWaitSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(secWait) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutWaitGet HDWF hdwf, double *psecWait
HDWF
hdwf
double *
psecWait
*/
// 3 (match no. 274)

	int FDwfDigitalOutWaitGet(HDWF hdwf, double *psecWait)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutWaitGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*psecWait) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutWaitGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*psecWait) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatInfo HDWF hdwf, unsigned int *pnMin, unsigned int *pnMax
HDWF
hdwf
unsigned int *
pnMin
unsigned int *
pnMax
*/
// 3 (match no. 275)

	int FDwfDigitalOutRepeatInfo(HDWF hdwf, unsigned int *pnMin, unsigned int *pnMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pnMin) }},
					{{"unsigned int", (*pnMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pnMin) = p2;
					(*pnMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatSet HDWF hdwf, unsigned int cRepeat
HDWF
hdwf
unsigned int
cRepeat
*/
// 4 (match no. 276)

	int FDwfDigitalOutRepeatSet(HDWF hdwf, unsigned int cRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", cRepeat }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(cRepeat) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatGet HDWF hdwf, unsigned int *pcRepeat
HDWF
hdwf
unsigned int *
pcRepeat
*/
// 3 (match no. 277)

	int FDwfDigitalOutRepeatGet(HDWF hdwf, unsigned int *pcRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pcRepeat) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pcRepeat) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatStatus HDWF hdwf, unsigned int *pcRepeat
HDWF
hdwf
unsigned int *
pcRepeat
*/
// 3 (match no. 278)

	int FDwfDigitalOutRepeatStatus(HDWF hdwf, unsigned int *pcRepeat)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned int", (*pcRepeat) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned int p2 = it0[2].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(*pcRepeat) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTriggerSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF
hdwf
DwfTriggerSlope
slope
*/
// 3 (match no. 279)

	int FDwfDigitalOutTriggerSlopeSet(HDWF hdwf, DwfTriggerSlope slope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTriggerSlopeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", slope }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTriggerSlopeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(slope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTriggerSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 280)

	int FDwfDigitalOutTriggerSlopeGet(HDWF hdwf, DwfTriggerSlope *pslope)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTriggerSlopeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfTriggerSlope", (*pslope) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTriggerSlopeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

					(hdwf) = p1;
					(*pslope) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatTriggerSet HDWF hdwf, int fRepeatTrigger
HDWF
hdwf
int
fRepeatTrigger
*/
// 3 (match no. 281)

	int FDwfDigitalOutRepeatTriggerSet(HDWF hdwf, int fRepeatTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatTriggerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fRepeatTrigger }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatTriggerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fRepeatTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutRepeatTriggerGet HDWF hdwf, int *pfRepeatTrigger
HDWF
hdwf
int *
pfRepeatTrigger
*/
// 3 (match no. 282)

	int FDwfDigitalOutRepeatTriggerGet(HDWF hdwf, int *pfRepeatTrigger)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutRepeatTriggerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfRepeatTrigger) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutRepeatTriggerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfRepeatTrigger) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCount HDWF hdwf, int *pcChannel
HDWF
hdwf
int *
pcChannel
*/
// 3 (match no. 283)

	int FDwfDigitalOutCount(HDWF hdwf, int *pcChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCount",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pcChannel) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCount") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pcChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutEnableSet HDWF hdwf, int idxChannel, int fEnable
HDWF
hdwf
int
idxChannel
int
fEnable
*/
// 3 (match no. 284)

	int FDwfDigitalOutEnableSet(HDWF hdwf, int idxChannel, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutEnableGet HDWF hdwf, int idxChannel, int *pfEnable
HDWF
hdwf
int
idxChannel
int *
pfEnable
*/
// 4 (match no. 285)

	int FDwfDigitalOutEnableGet(HDWF hdwf, int idxChannel, int *pfEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutOutputInfo HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutOutput
HDWF
hdwf
int
idxChannel
int *
pfsDwfDigitalOutOutput
*/
// 4 (match no. 286)

	int FDwfDigitalOutOutputInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutOutput)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutOutputInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsDwfDigitalOutOutput) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutOutputInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsDwfDigitalOutOutput) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutOutputSet HDWF hdwf, int idxChannel, DwfDigitalOutOutput v
HDWF
hdwf
int
idxChannel
DwfDigitalOutOutput
v
*/
// 4 (match no. 287)

	int FDwfDigitalOutOutputSet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutOutputSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutOutput", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutOutputSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutOutput p3 = it0[3].begin().value().get<DwfDigitalOutOutput>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(v) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutOutputGet HDWF hdwf, int idxChannel, DwfDigitalOutOutput *pv
HDWF
hdwf
int
idxChannel
DwfDigitalOutOutput *
pv
*/
// 4 (match no. 288)

	int FDwfDigitalOutOutputGet(HDWF hdwf, int idxChannel, DwfDigitalOutOutput *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutOutputGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutOutput", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutOutputGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutOutput p3 = it0[3].begin().value().get<DwfDigitalOutOutput>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTypeInfo HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutType
HDWF
hdwf
int
idxChannel
int *
pfsDwfDigitalOutType
*/
// 4 (match no. 289)

	int FDwfDigitalOutTypeInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutType)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTypeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsDwfDigitalOutType) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTypeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsDwfDigitalOutType) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTypeSet HDWF hdwf, int idxChannel, DwfDigitalOutType v
HDWF
hdwf
int
idxChannel
DwfDigitalOutType
v
*/
// 4 (match no. 290)

	int FDwfDigitalOutTypeSet(HDWF hdwf, int idxChannel, DwfDigitalOutType v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTypeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutType", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTypeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutType p3 = it0[3].begin().value().get<DwfDigitalOutType>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(v) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTypeGet HDWF hdwf, int idxChannel, DwfDigitalOutType *pv
HDWF
hdwf
int
idxChannel
DwfDigitalOutType *
pv
*/
// 4 (match no. 291)

	int FDwfDigitalOutTypeGet(HDWF hdwf, int idxChannel, DwfDigitalOutType *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTypeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutType", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTypeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutType p3 = it0[3].begin().value().get<DwfDigitalOutType>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutIdleInfo HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutIdle
HDWF
hdwf
int
idxChannel
int *
pfsDwfDigitalOutIdle
*/
// 4 (match no. 292)

	int FDwfDigitalOutIdleInfo(HDWF hdwf, int idxChannel, int *pfsDwfDigitalOutIdle)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutIdleInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsDwfDigitalOutIdle) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutIdleInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsDwfDigitalOutIdle) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutIdleSet HDWF hdwf, int idxChannel, DwfDigitalOutIdle v
HDWF
hdwf
int
idxChannel
DwfDigitalOutIdle
v
*/
// 4 (match no. 293)

	int FDwfDigitalOutIdleSet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutIdleSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutIdle", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutIdleSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutIdle p3 = it0[3].begin().value().get<DwfDigitalOutIdle>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(v) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutIdleGet HDWF hdwf, int idxChannel, DwfDigitalOutIdle *pv
HDWF
hdwf
int
idxChannel
DwfDigitalOutIdle *
pv
*/
// 4 (match no. 294)

	int FDwfDigitalOutIdleGet(HDWF hdwf, int idxChannel, DwfDigitalOutIdle *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutIdleGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"DwfDigitalOutIdle", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutIdleGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					DwfDigitalOutIdle p3 = it0[3].begin().value().get<DwfDigitalOutIdle>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDividerInfo HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax
HDWF
hdwf
int
idxChannel
unsigned int *
vMin
unsigned int *
vMax
*/
// 4 (match no. 295)

	int FDwfDigitalOutDividerInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDividerInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*vMin) }},
					{{"unsigned int", (*vMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDividerInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*vMin) = p3;
					(*vMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDividerInitSet HDWF hdwf, int idxChannel, unsigned int v
HDWF
hdwf
int
idxChannel
unsigned int
v
*/
// 5 (match no. 296)

	int FDwfDigitalOutDividerInitSet(HDWF hdwf, int idxChannel, unsigned int v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDividerInitSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDividerInitSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(v) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDividerInitGet HDWF hdwf, int idxChannel, unsigned int *pv
HDWF
hdwf
int
idxChannel
unsigned int *
pv
*/
// 4 (match no. 297)

	int FDwfDigitalOutDividerInitGet(HDWF hdwf, int idxChannel, unsigned int *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDividerInitGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDividerInitGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDividerSet HDWF hdwf, int idxChannel, unsigned int v
HDWF
hdwf
int
idxChannel
unsigned int
v
*/
// 4 (match no. 298)

	int FDwfDigitalOutDividerSet(HDWF hdwf, int idxChannel, unsigned int v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDividerSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDividerSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(v) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDividerGet HDWF hdwf, int idxChannel, unsigned int *pv
HDWF
hdwf
int
idxChannel
unsigned int *
pv
*/
// 4 (match no. 299)

	int FDwfDigitalOutDividerGet(HDWF hdwf, int idxChannel, unsigned int *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDividerGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDividerGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pv) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCounterInfo HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax
HDWF
hdwf
int
idxChannel
unsigned int *
vMin
unsigned int *
vMax
*/
// 4 (match no. 300)

	int FDwfDigitalOutCounterInfo(HDWF hdwf, int idxChannel, unsigned int *vMin, unsigned int *vMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCounterInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*vMin) }},
					{{"unsigned int", (*vMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCounterInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*vMin) = p3;
					(*vMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCounterInitSet HDWF hdwf, int idxChannel, int fHigh, unsigned int v
HDWF
hdwf
int
idxChannel
int
fHigh
unsigned int
v
*/
// 5 (match no. 301)

	int FDwfDigitalOutCounterInitSet(HDWF hdwf, int idxChannel, int fHigh, unsigned int v)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCounterInitSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fHigh }},
					{{"unsigned int", v }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCounterInitSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fHigh) = p3;
					(v) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCounterInitGet HDWF hdwf, int idxChannel, int *pfHigh, unsigned int *pv
HDWF
hdwf
int
idxChannel
int *
pfHigh
unsigned int *
pv
*/
// 5 (match no. 302)

	int FDwfDigitalOutCounterInitGet(HDWF hdwf, int idxChannel, int *pfHigh, unsigned int *pv)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCounterInitGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfHigh) }},
					{{"unsigned int", (*pv) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCounterInitGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfHigh) = p3;
					(*pv) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCounterSet HDWF hdwf, int idxChannel, unsigned int vLow, unsigned int vHigh
HDWF
hdwf
int
idxChannel
unsigned int
vLow
unsigned int
vHigh
*/
// 5 (match no. 303)

	int FDwfDigitalOutCounterSet(HDWF hdwf, int idxChannel, unsigned int vLow, unsigned int vHigh)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCounterSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", vLow }},
					{{"unsigned int", vHigh }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCounterSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(vLow) = p3;
					(vHigh) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutCounterGet HDWF hdwf, int idxChannel, unsigned int *pvLow, unsigned int *pvHigh
HDWF
hdwf
int
idxChannel
unsigned int *
pvLow
unsigned int *
pvHigh
*/
// 5 (match no. 304)

	int FDwfDigitalOutCounterGet(HDWF hdwf, int idxChannel, unsigned int *pvLow, unsigned int *pvHigh)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutCounterGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*pvLow) }},
					{{"unsigned int", (*pvHigh) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutCounterGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvLow) = p3;
					(*pvHigh) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDataInfo HDWF hdwf, int idxChannel, unsigned int *pcountOfBitsMax
HDWF
hdwf
int
idxChannel
unsigned int *
pcountOfBitsMax
*/
// 5 (match no. 305)

	int FDwfDigitalOutDataInfo(HDWF hdwf, int idxChannel, unsigned int *pcountOfBitsMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDataInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"unsigned int", (*pcountOfBitsMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDataInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					unsigned int p3 = it0[3].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pcountOfBitsMax) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutDataSet HDWF hdwf, int idxChannel, void *rgBits, unsigned int countOfBits
HDWF
hdwf
int
idxChannel
void *
rgBits
unsigned int
countOfBits
*/
// 4 (match no. 306)

	int FDwfDigitalOutDataSet(HDWF hdwf, int idxChannel, void *rgBits, unsigned int countOfBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutDataSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"char", (std::vector<char>(&((char*)rgBits)[0], &((char*)rgBits)[countOfBits])) }},
					{{"unsigned int", countOfBits }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutDataSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<char> p3 = it0[3].begin().value().get<vector<char>>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgBits, p3.data(), 0 * sizeof(char));
					(countOfBits) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartReset HDWF hdwf
HDWF
hdwf
*/
// 5 (match no. 307)

	int FDwfDigitalUartReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartRateSet HDWF hdwf, double hz
HDWF
hdwf
double
hz
*/
// 2 (match no. 308)

	int FDwfDigitalUartRateSet(HDWF hdwf, double hz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartRateSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hz }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartRateSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartBitsSet HDWF hdwf, int cBits
HDWF
hdwf
int
cBits
*/
// 3 (match no. 309)

	int FDwfDigitalUartBitsSet(HDWF hdwf, int cBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartBitsSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cBits }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartBitsSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(cBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartParitySet HDWF hdwf, int parity
HDWF
hdwf
int
parity
*/
// 3 (match no. 310)

	int FDwfDigitalUartParitySet(HDWF hdwf, int parity)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartParitySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", parity }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartParitySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(parity) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartStopSet HDWF hdwf, double cBit
HDWF
hdwf
double
cBit
*/
// 3 (match no. 311)

	int FDwfDigitalUartStopSet(HDWF hdwf, double cBit)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartStopSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", cBit }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartStopSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(cBit) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartTxSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 312)

	int FDwfDigitalUartTxSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartTxSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartTxSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartRxSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 313)

	int FDwfDigitalUartRxSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartRxSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartRxSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartTx HDWF hdwf, char *szTx, int cTx
HDWF
hdwf
char *
szTx
int
cTx
*/
// 3 (match no. 314)

	int FDwfDigitalUartTx(HDWF hdwf, char *szTx, int cTx)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartTx",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"char", (*szTx) }},
					{{"int", cTx }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartTx") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					char p2 = it0[2].begin().value().get<char>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(*szTx) = p2;
					(cTx) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalUartRx HDWF hdwf, char *szRx, int cRx, int *pcRx, int *pParity
HDWF
hdwf
char *
szRx
int
cRx
int *
pcRx
int *
pParity
*/
// 4 (match no. 315)

	int FDwfDigitalUartRx(HDWF hdwf, char *szRx, int cRx, int *pcRx, int *pParity)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalUartRx",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"char", (*szRx) }},
					{{"int", cRx }},
					{{"int", (*pcRx) }},
					{{"int", (*pParity) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalUartRx") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					char p2 = it0[2].begin().value().get<char>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(*szRx) = p2;
					(cRx) = p3;
					(*pcRx) = p4;
					(*pParity) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiReset HDWF hdwf
HDWF
hdwf
*/
// 6 (match no. 316)

	int FDwfDigitalSpiReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiFrequencySet HDWF hdwf, double hz
HDWF
hdwf
double
hz
*/
// 2 (match no. 317)

	int FDwfDigitalSpiFrequencySet(HDWF hdwf, double hz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiFrequencySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hz }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiFrequencySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiClockSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 318)

	int FDwfDigitalSpiClockSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiClockSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiClockSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiDataSet HDWF hdwf, int idxDQ, int idxChannel
HDWF
hdwf
int
idxDQ
int
idxChannel
*/
// 3 (match no. 319)

	int FDwfDigitalSpiDataSet(HDWF hdwf, int idxDQ, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiDataSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxDQ }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiDataSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxDQ) = p2;
					(idxChannel) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiModeSet HDWF hdwf, int iMode
HDWF
hdwf
int
iMode
*/
// 4 (match no. 320)

	int FDwfDigitalSpiModeSet(HDWF hdwf, int iMode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", iMode }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(iMode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiOrderSet HDWF hdwf, int fMSBFirst
HDWF
hdwf
int
fMSBFirst
*/
// 3 (match no. 321)

	int FDwfDigitalSpiOrderSet(HDWF hdwf, int fMSBFirst)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiOrderSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fMSBFirst }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiOrderSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fMSBFirst) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiSelect HDWF hdwf, int idxChannel, int level
HDWF
hdwf
int
idxChannel
int
level
*/
// 3 (match no. 322)

	int FDwfDigitalSpiSelect(HDWF hdwf, int idxChannel, int level)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiSelect",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", level }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiSelect") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(level) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWriteRead HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX, unsigned char *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned char *
rgTX
int
cTX
unsigned char *
rgRX
int
cRX
*/
// 4 (match no. 323)

	int FDwfDigitalSpiWriteRead(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX, unsigned char *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWriteRead",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned char", (std::vector<unsigned char>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
					{{"unsigned char", (std::vector<unsigned char>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWriteRead") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 8)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
					int p5 = it0[5].begin().value().get<int>();
					vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();
					int p7 = it0[7].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned char));
					(cTX) = p5;
					std::memmove(rgRX, p6.data(), 0 * sizeof(unsigned char));
					(cRX) = p7;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWriteRead16 HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX, unsigned short *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned short *
rgTX
int
cTX
unsigned short *
rgRX
int
cRX
*/
// 8 (match no. 324)

	int FDwfDigitalSpiWriteRead16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX, unsigned short *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWriteRead16",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned short", (std::vector<unsigned short>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
					{{"unsigned short", (std::vector<unsigned short>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWriteRead16") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 8)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
					int p5 = it0[5].begin().value().get<int>();
					vector<unsigned short> p6 = it0[6].begin().value().get<vector<unsigned short>>();
					int p7 = it0[7].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned short));
					(cTX) = p5;
					std::memmove(rgRX, p6.data(), 0 * sizeof(unsigned short));
					(cRX) = p7;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWriteRead32 HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX, unsigned int *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned int *
rgTX
int
cTX
unsigned int *
rgRX
int
cRX
*/
// 8 (match no. 325)

	int FDwfDigitalSpiWriteRead32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX, unsigned int *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWriteRead32",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned int", (std::vector<unsigned int>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
					{{"unsigned int", (std::vector<unsigned int>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWriteRead32") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 8)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
					int p5 = it0[5].begin().value().get<int>();
					vector<unsigned int> p6 = it0[6].begin().value().get<vector<unsigned int>>();
					int p7 = it0[7].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned int));
					(cTX) = p5;
					std::memmove(rgRX, p6.data(), 0 * sizeof(unsigned int));
					(cRX) = p7;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiRead HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned char *
rgRX
int
cRX
*/
// 8 (match no. 326)

	int FDwfDigitalSpiRead(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiRead",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned char", (std::vector<unsigned char>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiRead") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgRX, p4.data(), 0 * sizeof(unsigned char));
					(cRX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiReadOne HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *pRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned int *
pRX
*/
// 6 (match no. 327)

	int FDwfDigitalSpiReadOne(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *pRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiReadOne",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned int", (*pRX) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiReadOne") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					(*pRX) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiRead16 HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned short *
rgRX
int
cRX
*/
// 5 (match no. 328)

	int FDwfDigitalSpiRead16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiRead16",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned short", (std::vector<unsigned short>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiRead16") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgRX, p4.data(), 0 * sizeof(unsigned short));
					(cRX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiRead32 HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgRX, int cRX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned int *
rgRX
int
cRX
*/
// 6 (match no. 329)

	int FDwfDigitalSpiRead32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgRX, int cRX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiRead32",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned int", (std::vector<unsigned int>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiRead32") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgRX, p4.data(), 0 * sizeof(unsigned int));
					(cRX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWrite HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned char *
rgTX
int
cTX
*/
// 6 (match no. 330)

	int FDwfDigitalSpiWrite(HDWF hdwf, int cDQ, int cBitPerWord, unsigned char *rgTX, int cTX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWrite",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned char", (std::vector<unsigned char>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWrite") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned char));
					(cTX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWriteOne HDWF hdwf, int cDQ, int cBits, unsigned int vTX
HDWF
hdwf
int
cDQ
int
cBits
unsigned int
vTX
*/
// 6 (match no. 331)

	int FDwfDigitalSpiWriteOne(HDWF hdwf, int cDQ, int cBits, unsigned int vTX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWriteOne",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBits }},
					{{"unsigned int", vTX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWriteOne") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					unsigned int p4 = it0[4].begin().value().get<unsigned int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBits) = p3;
					(vTX) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWrite16 HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned short *
rgTX
int
cTX
*/
// 5 (match no. 332)

	int FDwfDigitalSpiWrite16(HDWF hdwf, int cDQ, int cBitPerWord, unsigned short *rgTX, int cTX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWrite16",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned short", (std::vector<unsigned short>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWrite16") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned short));
					(cTX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalSpiWrite32 HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX
HDWF
hdwf
int
cDQ
int
cBitPerWord
unsigned int *
rgTX
int
cTX
*/
// 6 (match no. 333)

	int FDwfDigitalSpiWrite32(HDWF hdwf, int cDQ, int cBitPerWord, unsigned int *rgTX, int cTX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalSpiWrite32",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cDQ }},
					{{"int", cBitPerWord }},
					{{"unsigned int", (std::vector<unsigned int>(&rgTX[0], &rgTX[cTX])) }},
					{{"int", cTX }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalSpiWrite32") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(cDQ) = p2;
					(cBitPerWord) = p3;
					std::memmove(rgTX, p4.data(), 0 * sizeof(unsigned int));
					(cTX) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cReset HDWF hdwf
HDWF
hdwf
*/
// 6 (match no. 334)

	int FDwfDigitalI2cReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cClear HDWF hdwf, int *pfFree
HDWF
hdwf
int *
pfFree
*/
// 2 (match no. 335)

	int FDwfDigitalI2cClear(HDWF hdwf, int *pfFree)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cClear",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfFree) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cClear") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfFree) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cStretchSet HDWF hdwf, int fEnable
HDWF
hdwf
int
fEnable
*/
// 3 (match no. 336)

	int FDwfDigitalI2cStretchSet(HDWF hdwf, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cStretchSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cStretchSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cRateSet HDWF hdwf, double hz
HDWF
hdwf
double
hz
*/
// 3 (match no. 337)

	int FDwfDigitalI2cRateSet(HDWF hdwf, double hz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cRateSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hz }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cRateSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cReadNakSet HDWF hdwf, int fNakLastReadByte
HDWF
hdwf
int
fNakLastReadByte
*/
// 3 (match no. 338)

	int FDwfDigitalI2cReadNakSet(HDWF hdwf, int fNakLastReadByte)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cReadNakSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fNakLastReadByte }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cReadNakSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fNakLastReadByte) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cSclSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 339)

	int FDwfDigitalI2cSclSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cSclSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cSclSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cSdaSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 340)

	int FDwfDigitalI2cSdaSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cSdaSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cSdaSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cWriteRead HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, unsigned char *rgRx, int cRx, int *pNak
HDWF
hdwf
unsigned char
adr8bits
unsigned char *
rgbTx
int
cTx
unsigned char *
rgRx
int
cRx
int *
pNak
*/
// 3 (match no. 341)

	int FDwfDigitalI2cWriteRead(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, unsigned char *rgRx, int cRx, int *pNak)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cWriteRead",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned char", adr8bits }},
					{{"unsigned char", (std::vector<unsigned char>(&rgbTx[0], &rgbTx[cTx])) }},
					{{"int", cTx }},
					{{"unsigned char", (std::vector<unsigned char>(&rgRx[0], &rgRx[cRx])) }},
					{{"int", cRx }},
					{{"int", (*pNak) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cWriteRead") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 8)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned char p2 = it0[2].begin().value().get<unsigned char>();
					vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
					int p4 = it0[4].begin().value().get<int>();
					vector<unsigned char> p5 = it0[5].begin().value().get<vector<unsigned char>>();
					int p6 = it0[6].begin().value().get<int>();
					int p7 = it0[7].begin().value().get<int>();

					(hdwf) = p1;
					(adr8bits) = p2;
					std::memmove(rgbTx, p3.data(), 0 * sizeof(unsigned char));
					(cTx) = p4;
					std::memmove(rgRx, p5.data(), 0 * sizeof(unsigned char));
					(cRx) = p6;
					(*pNak) = p7;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cRead HDWF hdwf, unsigned char adr8bits, unsigned char *rgbRx, int cRx, int *pNak
HDWF
hdwf
unsigned char
adr8bits
unsigned char *
rgbRx
int
cRx
int *
pNak
*/
// 8 (match no. 342)

	int FDwfDigitalI2cRead(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbRx, int cRx, int *pNak)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cRead",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned char", adr8bits }},
					{{"unsigned char", (std::vector<unsigned char>(&rgbRx[0], &rgbRx[cRx])) }},
					{{"int", cRx }},
					{{"int", (*pNak) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cRead") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned char p2 = it0[2].begin().value().get<unsigned char>();
					vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(adr8bits) = p2;
					std::memmove(rgbRx, p3.data(), 0 * sizeof(unsigned char));
					(cRx) = p4;
					(*pNak) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cWrite HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, int *pNak
HDWF
hdwf
unsigned char
adr8bits
unsigned char *
rgbTx
int
cTx
int *
pNak
*/
// 6 (match no. 343)

	int FDwfDigitalI2cWrite(HDWF hdwf, unsigned char adr8bits, unsigned char *rgbTx, int cTx, int *pNak)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cWrite",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned char", adr8bits }},
					{{"unsigned char", (std::vector<unsigned char>(&rgbTx[0], &rgbTx[cTx])) }},
					{{"int", cTx }},
					{{"int", (*pNak) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cWrite") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned char p2 = it0[2].begin().value().get<unsigned char>();
					vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(adr8bits) = p2;
					std::memmove(rgbTx, p3.data(), 0 * sizeof(unsigned char));
					(cTx) = p4;
					(*pNak) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalI2cWriteOne HDWF hdwf, unsigned char adr8bits, unsigned char bTx, int *pNak
HDWF
hdwf
unsigned char
adr8bits
unsigned char
bTx
int *
pNak
*/
// 6 (match no. 344)

	int FDwfDigitalI2cWriteOne(HDWF hdwf, unsigned char adr8bits, unsigned char bTx, int *pNak)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalI2cWriteOne",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"unsigned char", adr8bits }},
					{{"unsigned char", bTx }},
					{{"int", (*pNak) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalI2cWriteOne") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					unsigned char p2 = it0[2].begin().value().get<unsigned char>();
					unsigned char p3 = it0[3].begin().value().get<unsigned char>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(adr8bits) = p2;
					(bTx) = p3;
					(*pNak) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanReset HDWF hdwf
HDWF
hdwf
*/
// 5 (match no. 345)

	int FDwfDigitalCanReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanRateSet HDWF hdwf, double hz
HDWF
hdwf
double
hz
*/
// 2 (match no. 346)

	int FDwfDigitalCanRateSet(HDWF hdwf, double hz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanRateSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hz }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanRateSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanPolaritySet HDWF hdwf, int fHigh
HDWF
hdwf
int
fHigh
*/
// 3 (match no. 347)

	int FDwfDigitalCanPolaritySet(HDWF hdwf, int fHigh)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanPolaritySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fHigh }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanPolaritySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fHigh) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanTxSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 348)

	int FDwfDigitalCanTxSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanTxSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanTxSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanRxSet HDWF hdwf, int idxChannel
HDWF
hdwf
int
idxChannel
*/
// 3 (match no. 349)

	int FDwfDigitalCanRxSet(HDWF hdwf, int idxChannel)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanRxSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanRxSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanTx HDWF hdwf, int vID, int fExtended, int fRemote, int cDLC, unsigned char *rgTX
HDWF
hdwf
int
vID
int
fExtended
int
fRemote
int
cDLC
unsigned char *
rgTX
*/
// 3 (match no. 350)

	int FDwfDigitalCanTx(HDWF hdwf, int vID, int fExtended, int fRemote, int cDLC, unsigned char *rgTX)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanTx",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", vID }},
					{{"int", fExtended }},
					{{"int", fRemote }},
					{{"int", cDLC }},
					{{"unsigned char", (std::vector<unsigned char>(&rgTX[0], &rgTX[cDLC])) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanTx") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 7)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();
					vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();

					(hdwf) = p1;
					(vID) = p2;
					(fExtended) = p3;
					(fRemote) = p4;
					(cDLC) = p5;
					std::memmove(rgTX, p6.data(), 0 * sizeof(unsigned char));
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalCanRx HDWF hdwf, int *pvID, int *pfExtended, int *pfRemote, int *pcDLC, unsigned char *rgRX, int cRX, int *pvStatus
HDWF
hdwf
int *
pvID
int *
pfExtended
int *
pfRemote
int *
pcDLC
unsigned char *
rgRX
int
cRX
int *
pvStatus
*/
// 7 (match no. 351)

	int FDwfDigitalCanRx(HDWF hdwf, int *pvID, int *pfExtended, int *pfRemote, int *pcDLC, unsigned char *rgRX, int cRX, int *pvStatus)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalCanRx",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pvID) }},
					{{"int", (*pfExtended) }},
					{{"int", (*pfRemote) }},
					{{"int", (*pcDLC) }},
					{{"unsigned char", (std::vector<unsigned char>(&rgRX[0], &rgRX[cRX])) }},
					{{"int", cRX }},
					{{"int", (*pvStatus) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalCanRx") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 9)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();
					vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();
					int p7 = it0[7].begin().value().get<int>();
					int p8 = it0[8].begin().value().get<int>();

					(hdwf) = p1;
					(*pvID) = p2;
					(*pfExtended) = p3;
					(*pfRemote) = p4;
					(*pcDLC) = p5;
					std::memmove(rgRX, p6.data(), 0 * sizeof(unsigned char));
					(cRX) = p7;
					(*pvStatus) = p8;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceReset HDWF hdwf
HDWF
hdwf
*/
// 9 (match no. 352)

	int FDwfAnalogImpedanceReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceModeSet HDWF hdwf, int mode
HDWF
hdwf
int
mode
*/
// 2 (match no. 353)

	int FDwfAnalogImpedanceModeSet(HDWF hdwf, int mode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceModeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", mode }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceModeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(mode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceModeGet HDWF hdwf, int *mode
HDWF
hdwf
int *
mode
*/
// 3 (match no. 354)

	int FDwfAnalogImpedanceModeGet(HDWF hdwf, int *mode)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceModeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*mode) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceModeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*mode) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceReferenceSet HDWF hdwf, double ohms
HDWF
hdwf
double
ohms
*/
// 3 (match no. 355)

	int FDwfAnalogImpedanceReferenceSet(HDWF hdwf, double ohms)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceReferenceSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", ohms }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceReferenceSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(ohms) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceReferenceGet HDWF hdwf, double *pohms
HDWF
hdwf
double *
pohms
*/
// 3 (match no. 356)

	int FDwfAnalogImpedanceReferenceGet(HDWF hdwf, double *pohms)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceReferenceGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pohms) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceReferenceGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*pohms) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceFrequencySet HDWF hdwf, double hz
HDWF
hdwf
double
hz
*/
// 3 (match no. 357)

	int FDwfAnalogImpedanceFrequencySet(HDWF hdwf, double hz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceFrequencySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", hz }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceFrequencySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(hz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceFrequencyGet HDWF hdwf, double *phz
HDWF
hdwf
double *
phz
*/
// 3 (match no. 358)

	int FDwfAnalogImpedanceFrequencyGet(HDWF hdwf, double *phz)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceFrequencyGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*phz) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceFrequencyGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*phz) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceAmplitudeSet HDWF hdwf, double volts
HDWF
hdwf
double
volts
*/
// 3 (match no. 359)

	int FDwfAnalogImpedanceAmplitudeSet(HDWF hdwf, double volts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceAmplitudeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", volts }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceAmplitudeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(volts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceAmplitudeGet HDWF hdwf, double *pvolts
HDWF
hdwf
double *
pvolts
*/
// 3 (match no. 360)

	int FDwfAnalogImpedanceAmplitudeGet(HDWF hdwf, double *pvolts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceAmplitudeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvolts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceAmplitudeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*pvolts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceOffsetSet HDWF hdwf, double volts
HDWF
hdwf
double
volts
*/
// 3 (match no. 361)

	int FDwfAnalogImpedanceOffsetSet(HDWF hdwf, double volts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceOffsetSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", volts }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceOffsetSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(volts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceOffsetGet HDWF hdwf, double *pvolts
HDWF
hdwf
double *
pvolts
*/
// 3 (match no. 362)

	int FDwfAnalogImpedanceOffsetGet(HDWF hdwf, double *pvolts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceOffsetGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pvolts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceOffsetGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();

					(hdwf) = p1;
					(*pvolts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceProbeSet HDWF hdwf, double ohmRes, double faradCap
HDWF
hdwf
double
ohmRes
double
faradCap
*/
// 3 (match no. 363)

	int FDwfAnalogImpedanceProbeSet(HDWF hdwf, double ohmRes, double faradCap)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceProbeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", ohmRes }},
					{{"double", faradCap }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceProbeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(ohmRes) = p2;
					(faradCap) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceProbeGet HDWF hdwf, double *pohmRes, double *pfaradCap
HDWF
hdwf
double *
pohmRes
double *
pfaradCap
*/
// 4 (match no. 364)

	int FDwfAnalogImpedanceProbeGet(HDWF hdwf, double *pohmRes, double *pfaradCap)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceProbeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pohmRes) }},
					{{"double", (*pfaradCap) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceProbeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(*pohmRes) = p2;
					(*pfaradCap) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedancePeriodSet HDWF hdwf, int cMinPeriods
HDWF
hdwf
int
cMinPeriods
*/
// 4 (match no. 365)

	int FDwfAnalogImpedancePeriodSet(HDWF hdwf, int cMinPeriods)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedancePeriodSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", cMinPeriods }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedancePeriodSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(cMinPeriods) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedancePeriodGet HDWF hdwf, int *cMinPeriods
HDWF
hdwf
int *
cMinPeriods
*/
// 3 (match no. 366)

	int FDwfAnalogImpedancePeriodGet(HDWF hdwf, int *cMinPeriods)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedancePeriodGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*cMinPeriods) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedancePeriodGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*cMinPeriods) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceCompReset HDWF hdwf
HDWF
hdwf
*/
// 3 (match no. 367)

	int FDwfAnalogImpedanceCompReset(HDWF hdwf)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceCompReset",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceCompReset") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 2)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();

					(hdwf) = p1;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceCompSet HDWF hdwf, double ohmOpenResistance, double ohmOpenReactance, double ohmShortResistance, double ohmShortReactance
HDWF
hdwf
double
ohmOpenResistance
double
ohmOpenReactance
double
ohmShortResistance
double
ohmShortReactance
*/
// 2 (match no. 368)

	int FDwfAnalogImpedanceCompSet(HDWF hdwf, double ohmOpenResistance, double ohmOpenReactance, double ohmShortResistance, double ohmShortReactance)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceCompSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", ohmOpenResistance }},
					{{"double", ohmOpenReactance }},
					{{"double", ohmShortResistance }},
					{{"double", ohmShortReactance }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceCompSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(ohmOpenResistance) = p2;
					(ohmOpenReactance) = p3;
					(ohmShortResistance) = p4;
					(ohmShortReactance) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceCompGet HDWF hdwf, double *pohmOpenResistance, double *pohmOpenReactance, double *pohmShortResistance, double *pohmShortReactance
HDWF
hdwf
double *
pohmOpenResistance
double *
pohmOpenReactance
double *
pohmShortResistance
double *
pohmShortReactance
*/
// 6 (match no. 369)

	int FDwfAnalogImpedanceCompGet(HDWF hdwf, double *pohmOpenResistance, double *pohmOpenReactance, double *pohmShortResistance, double *pohmShortReactance)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceCompGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"double", (*pohmOpenResistance) }},
					{{"double", (*pohmOpenReactance) }},
					{{"double", (*pohmShortResistance) }},
					{{"double", (*pohmShortReactance) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceCompGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					double p2 = it0[2].begin().value().get<double>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();
					double p5 = it0[5].begin().value().get<double>();

					(hdwf) = p1;
					(*pohmOpenResistance) = p2;
					(*pohmOpenReactance) = p3;
					(*pohmShortResistance) = p4;
					(*pohmShortReactance) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceConfigure HDWF hdwf, int fStart
HDWF
hdwf
int
fStart
*/
// 6 (match no. 370)

	int FDwfAnalogImpedanceConfigure(HDWF hdwf, int fStart)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceConfigure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fStart }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceConfigure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fStart) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceStatus HDWF hdwf, DwfState *psts
HDWF
hdwf
DwfState *
psts
*/
// 3 (match no. 371)

	int FDwfAnalogImpedanceStatus(HDWF hdwf, DwfState *psts)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfState", (*psts) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfState p2 = it0[2].begin().value().get<DwfState>();

					(hdwf) = p1;
					(*psts) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceStatusInput HDWF hdwf, int idxChannel, double *pgain, double *pradian
HDWF
hdwf
int
idxChannel
double *
pgain
double *
pradian
*/
// 3 (match no. 372)

	int FDwfAnalogImpedanceStatusInput(HDWF hdwf, int idxChannel, double *pgain, double *pradian)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceStatusInput",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pgain) }},
					{{"double", (*pradian) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceStatusInput") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pgain) = p3;
					(*pradian) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogImpedanceStatusMeasure HDWF hdwf, DwfAnalogImpedance measure, double *pvalue
HDWF
hdwf
DwfAnalogImpedance
measure
double *
pvalue
*/
// 5 (match no. 373)

	int FDwfAnalogImpedanceStatusMeasure(HDWF hdwf, DwfAnalogImpedance measure, double *pvalue)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogImpedanceStatusMeasure",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"DwfAnalogImpedance", measure }},
					{{"double", (*pvalue) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogImpedanceStatusMeasure") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					DwfAnalogImpedance p2 = it0[2].begin().value().get<DwfAnalogImpedance>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(measure) = p2;
					(*pvalue) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInMixedSet HDWF hdwf, int fEnable
HDWF
hdwf
int
fEnable
*/
// 4 (match no. 374)

	int FDwfDigitalInMixedSet(HDWF hdwf, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInMixedSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInMixedSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(fEnable) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogInTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 375)

	int FDwfAnalogInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogInTriggerSourceInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogInTriggerSourceInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutTriggerSourceInfo HDWF hdwf, int idxChannel, int *pfstrigsrc
HDWF
hdwf
int
idxChannel
int *
pfstrigsrc
*/
// 3 (match no. 376)

	int FDwfAnalogOutTriggerSourceInfo(HDWF hdwf, int idxChannel, int *pfstrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutTriggerSourceInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfstrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutTriggerSourceInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfstrigsrc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalInTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF
hdwf
int *
pfstrigsrc
*/
// 4 (match no. 377)

	int FDwfDigitalInTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalInTriggerSourceInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalInTriggerSourceInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfDigitalOutTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 378)

	int FDwfDigitalOutTriggerSourceInfo(HDWF hdwf, int *pfstrigsrc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfDigitalOutTriggerSourceInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", (*pfstrigsrc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfDigitalOutTriggerSourceInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();

					(hdwf) = p1;
					(*pfstrigsrc) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutEnableSet HDWF hdwf, int idxChannel, int fEnable
HDWF
hdwf
int
idxChannel
int
fEnable
*/
// 3 (match no. 379)

	int FDwfAnalogOutEnableSet(HDWF hdwf, int idxChannel, int fEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutEnableSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", fEnable }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutEnableSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(fEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutEnableGet HDWF hdwf, int idxChannel, int *pfEnable
HDWF
hdwf
int
idxChannel
int *
pfEnable
*/
// 4 (match no. 380)

	int FDwfAnalogOutEnableGet(HDWF hdwf, int idxChannel, int *pfEnable)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutEnableGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfEnable) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutEnableGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfEnable) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFunctionInfo HDWF hdwf, int idxChannel, int *pfsfunc
HDWF
hdwf
int
idxChannel
int *
pfsfunc
*/
// 4 (match no. 381)

	int FDwfAnalogOutFunctionInfo(HDWF hdwf, int idxChannel, int *pfsfunc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFunctionInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pfsfunc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFunctionInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfsfunc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFunctionSet HDWF hdwf, int idxChannel, FUNC func
HDWF
hdwf
int
idxChannel
FUNC
func
*/
// 4 (match no. 382)

	int FDwfAnalogOutFunctionSet(HDWF hdwf, int idxChannel, FUNC func)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFunctionSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"FUNC", func }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFunctionSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					FUNC p3 = it0[3].begin().value().get<FUNC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(func) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFunctionGet HDWF hdwf, int idxChannel, FUNC *pfunc
HDWF
hdwf
int
idxChannel
FUNC *
pfunc
*/
// 4 (match no. 383)

	int FDwfAnalogOutFunctionGet(HDWF hdwf, int idxChannel, FUNC *pfunc)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFunctionGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"FUNC", (*pfunc) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFunctionGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					FUNC p3 = it0[3].begin().value().get<FUNC>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pfunc) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFrequencyInfo HDWF hdwf, int idxChannel, double *phzMin, double *phzMax
HDWF
hdwf
int
idxChannel
double *
phzMin
double *
phzMax
*/
// 4 (match no. 384)

	int FDwfAnalogOutFrequencyInfo(HDWF hdwf, int idxChannel, double *phzMin, double *phzMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFrequencyInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*phzMin) }},
					{{"double", (*phzMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFrequencyInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*phzMin) = p3;
					(*phzMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFrequencySet HDWF hdwf, int idxChannel, double hzFrequency
HDWF
hdwf
int
idxChannel
double
hzFrequency
*/
// 5 (match no. 385)

	int FDwfAnalogOutFrequencySet(HDWF hdwf, int idxChannel, double hzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFrequencySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", hzFrequency }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFrequencySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(hzFrequency) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutFrequencyGet HDWF hdwf, int idxChannel, double *phzFrequency
HDWF
hdwf
int
idxChannel
double *
phzFrequency
*/
// 4 (match no. 386)

	int FDwfAnalogOutFrequencyGet(HDWF hdwf, int idxChannel, double *phzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutFrequencyGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*phzFrequency) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutFrequencyGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*phzFrequency) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutAmplitudeInfo HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax
HDWF
hdwf
int
idxChannel
double *
pvoltsMin
double *
pvoltsMax
*/
// 4 (match no. 387)

	int FDwfAnalogOutAmplitudeInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutAmplitudeInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutAmplitudeInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltsMin) = p3;
					(*pvoltsMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutAmplitudeSet HDWF hdwf, int idxChannel, double voltsAmplitude
HDWF
hdwf
int
idxChannel
double
voltsAmplitude
*/
// 5 (match no. 388)

	int FDwfAnalogOutAmplitudeSet(HDWF hdwf, int idxChannel, double voltsAmplitude)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutAmplitudeSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", voltsAmplitude }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutAmplitudeSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(voltsAmplitude) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutAmplitudeGet HDWF hdwf, int idxChannel, double *pvoltsAmplitude
HDWF
hdwf
int
idxChannel
double *
pvoltsAmplitude
*/
// 4 (match no. 389)

	int FDwfAnalogOutAmplitudeGet(HDWF hdwf, int idxChannel, double *pvoltsAmplitude)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutAmplitudeGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltsAmplitude) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutAmplitudeGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltsAmplitude) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutOffsetInfo HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax
HDWF
hdwf
int
idxChannel
double *
pvoltsMin
double *
pvoltsMax
*/
// 4 (match no. 390)

	int FDwfAnalogOutOffsetInfo(HDWF hdwf, int idxChannel, double *pvoltsMin, double *pvoltsMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutOffsetInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltsMin) }},
					{{"double", (*pvoltsMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutOffsetInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltsMin) = p3;
					(*pvoltsMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutOffsetSet HDWF hdwf, int idxChannel, double voltsOffset
HDWF
hdwf
int
idxChannel
double
voltsOffset
*/
// 5 (match no. 391)

	int FDwfAnalogOutOffsetSet(HDWF hdwf, int idxChannel, double voltsOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutOffsetSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", voltsOffset }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutOffsetSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(voltsOffset) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutOffsetGet HDWF hdwf, int idxChannel, double *pvoltsOffset
HDWF
hdwf
int
idxChannel
double *
pvoltsOffset
*/
// 4 (match no. 392)

	int FDwfAnalogOutOffsetGet(HDWF hdwf, int idxChannel, double *pvoltsOffset)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutOffsetGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pvoltsOffset) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutOffsetGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pvoltsOffset) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutSymmetryInfo HDWF hdwf, int idxChannel, double *ppercentageMin, double *ppercentageMax
HDWF
hdwf
int
idxChannel
double *
ppercentageMin
double *
ppercentageMax
*/
// 4 (match no. 393)

	int FDwfAnalogOutSymmetryInfo(HDWF hdwf, int idxChannel, double *ppercentageMin, double *ppercentageMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutSymmetryInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*ppercentageMin) }},
					{{"double", (*ppercentageMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutSymmetryInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*ppercentageMin) = p3;
					(*ppercentageMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutSymmetrySet HDWF hdwf, int idxChannel, double percentageSymmetry
HDWF
hdwf
int
idxChannel
double
percentageSymmetry
*/
// 5 (match no. 394)

	int FDwfAnalogOutSymmetrySet(HDWF hdwf, int idxChannel, double percentageSymmetry)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutSymmetrySet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", percentageSymmetry }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutSymmetrySet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(percentageSymmetry) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutSymmetryGet HDWF hdwf, int idxChannel, double *ppercentageSymmetry
HDWF
hdwf
int
idxChannel
double *
ppercentageSymmetry
*/
// 4 (match no. 395)

	int FDwfAnalogOutSymmetryGet(HDWF hdwf, int idxChannel, double *ppercentageSymmetry)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutSymmetryGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*ppercentageSymmetry) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutSymmetryGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*ppercentageSymmetry) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutPhaseInfo HDWF hdwf, int idxChannel, double *pdegreeMin, double *pdegreeMax
HDWF
hdwf
int
idxChannel
double *
pdegreeMin
double *
pdegreeMax
*/
// 4 (match no. 396)

	int FDwfAnalogOutPhaseInfo(HDWF hdwf, int idxChannel, double *pdegreeMin, double *pdegreeMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutPhaseInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pdegreeMin) }},
					{{"double", (*pdegreeMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutPhaseInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();
					double p4 = it0[4].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pdegreeMin) = p3;
					(*pdegreeMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutPhaseSet HDWF hdwf, int idxChannel, double degreePhase
HDWF
hdwf
int
idxChannel
double
degreePhase
*/
// 5 (match no. 397)

	int FDwfAnalogOutPhaseSet(HDWF hdwf, int idxChannel, double degreePhase)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutPhaseSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", degreePhase }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutPhaseSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(degreePhase) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutPhaseGet HDWF hdwf, int idxChannel, double *pdegreePhase
HDWF
hdwf
int
idxChannel
double *
pdegreePhase
*/
// 4 (match no. 398)

	int FDwfAnalogOutPhaseGet(HDWF hdwf, int idxChannel, double *pdegreePhase)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutPhaseGet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (*pdegreePhase) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutPhaseGet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 4)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					double p3 = it0[3].begin().value().get<double>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pdegreePhase) = p3;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutDataInfo HDWF hdwf, int idxChannel, int *pnSamplesMin, int *pnSamplesMax
HDWF
hdwf
int
idxChannel
int *
pnSamplesMin
int *
pnSamplesMax
*/
// 4 (match no. 399)

	int FDwfAnalogOutDataInfo(HDWF hdwf, int idxChannel, int *pnSamplesMin, int *pnSamplesMax)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutDataInfo",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*pnSamplesMin) }},
					{{"int", (*pnSamplesMax) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutDataInfo") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*pnSamplesMin) = p3;
					(*pnSamplesMax) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutDataSet HDWF hdwf, int idxChannel, double *rgdData, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdData
int
cdData
*/
// 5 (match no. 400)

	int FDwfAnalogOutDataSet(HDWF hdwf, int idxChannel, double *rgdData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutDataSet",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdData[0], &rgdData[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutDataSet") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdData, p3.data(), 0 * sizeof(double));
					(cdData) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutPlayStatus HDWF hdwf, int idxChannel, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted
HDWF
hdwf
int
idxChannel
int *
cdDataFree
int *
cdDataLost
int *
cdDataCorrupted
*/
// 5 (match no. 401)

	int FDwfAnalogOutPlayStatus(HDWF hdwf, int idxChannel, int *cdDataFree, int *cdDataLost, int *cdDataCorrupted)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutPlayStatus",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"int", (*cdDataFree) }},
					{{"int", (*cdDataLost) }},
					{{"int", (*cdDataCorrupted) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutPlayStatus") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 6)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					int p3 = it0[3].begin().value().get<int>();
					int p4 = it0[4].begin().value().get<int>();
					int p5 = it0[5].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					(*cdDataFree) = p3;
					(*cdDataLost) = p4;
					(*cdDataCorrupted) = p5;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfAnalogOutPlayData HDWF hdwf, int idxChannel, double *rgdData, int cdData
HDWF
hdwf
int
idxChannel
double *
rgdData
int
cdData
*/
// 6 (match no. 402)

	int FDwfAnalogOutPlayData(HDWF hdwf, int idxChannel, double *rgdData, int cdData)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfAnalogOutPlayData",
				{
					{{"(return)", 0}},
					{{"HDWF", hdwf }},
					{{"int", idxChannel }},
					{{"double", (std::vector<double>(&rgdData[0], &rgdData[cdData])) }},
					{{"int", cdData }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfAnalogOutPlayData") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 5)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					HDWF p1 = it0[1].begin().value().get<HDWF>();
					int p2 = it0[2].begin().value().get<int>();
					vector<double> p3 = it0[3].begin().value().get<vector<double>>();
					int p4 = it0[4].begin().value().get<int>();

					(hdwf) = p1;
					(idxChannel) = p2;
					std::memmove(rgdData, p3.data(), 0 * sizeof(double));
					(cdData) = p4;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumAnalogInChannels int idxDevice, int *pnChannels
int
idxDevice
int *
pnChannels
*/
// 5 (match no. 403)

	int FDwfEnumAnalogInChannels(int idxDevice, int *pnChannels)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumAnalogInChannels",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"int", (*pnChannels) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumAnalogInChannels") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();

					(idxDevice) = p1;
					(*pnChannels) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumAnalogInBufferSize int idxDevice, int *pnBufferSize
int
idxDevice
int *
pnBufferSize
*/
// 3 (match no. 404)

	int FDwfEnumAnalogInBufferSize(int idxDevice, int *pnBufferSize)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumAnalogInBufferSize",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"int", (*pnBufferSize) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumAnalogInBufferSize") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();

					(idxDevice) = p1;
					(*pnBufferSize) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumAnalogInBits int idxDevice, int *pnBits
int
idxDevice
int *
pnBits
*/
// 3 (match no. 405)

	int FDwfEnumAnalogInBits(int idxDevice, int *pnBits)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumAnalogInBits",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"int", (*pnBits) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumAnalogInBits") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					int p2 = it0[2].begin().value().get<int>();

					(idxDevice) = p1;
					(*pnBits) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}


/*
FDwfEnumAnalogInFrequency int idxDevice, double *phzFrequency
int
idxDevice
double *
phzFrequency
*/
// 3 (match no. 406)

	int FDwfEnumAnalogInFrequency(int idxDevice, double *phzFrequency)
	{
		using namespace std;
		using json = nlohmann::json;

		int p0 = 0;

		json jreq = {
			{
				"FDwfEnumAnalogInFrequency",
				{
					{{"(return)", 0}},
					{{"int", idxDevice }},
					{{"double", (*phzFrequency) }},
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "FDwfEnumAnalogInFrequency") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == 3)
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
					int p1 = it0[1].begin().value().get<int>();
					double p2 = it0[2].begin().value().get<double>();

					(idxDevice) = p1;
					(*phzFrequency) = p2;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}

