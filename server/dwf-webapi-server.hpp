
/*
    ___  __      __  ___  
   |   \ \ \    / / | __| 
   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI-server wrapper
   |___/   \_/\_/___|_|_    version 0.1.0 for Waveforms API 3.13.8
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

#include <iostream>

#include "nlohmann/json.hpp"
#include "digilent/waveforms/dwf.h"


namespace Dwf
{
	namespace WebAPI
	{
		using namespace std;
		using json = nlohmann::json;

		class Server
		{
		private:

			typedef int (*FARPROCm)(json::iterator);


/*
FDwfGetLastError DWFERC *pdwferc
DWFERC *
pdwferc
*/
//  (match no. 1)
			static int _FDwfGetLastError(json::iterator it)
			{
				cout << "	FDwfGetLastError called." << endl;
				
				if (it.key() != "FDwfGetLastError") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							DWFERC p1 = it0[1].begin().value().get<DWFERC>();

							int p0 = FDwfGetLastError(&p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfGetLastErrorMsg char szError[512]
char 
szError[512]
*/
// 2 (match no. 2)
			static int _FDwfGetLastErrorMsg(json::iterator it)
			{
				cout << "	FDwfGetLastErrorMsg called." << endl;
				
				if (it.key() != "FDwfGetLastErrorMsg") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							vector<char> p1 = it0[1].begin().value().get<vector<char>>();

							int p0 = FDwfGetLastErrorMsg(p1.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfGetVersion char szVersion[32]
char 
szVersion[32]
*/
// 2 (match no. 3)
			static int _FDwfGetVersion(json::iterator it)
			{
				cout << "	FDwfGetVersion called." << endl;
				
				if (it.key() != "FDwfGetVersion") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							vector<char> p1 = it0[1].begin().value().get<vector<char>>();

							int p0 = FDwfGetVersion(p1.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfParamSet DwfParam param, int value
DwfParam 
param
int 
value
*/
// 2 (match no. 4)
			static int _FDwfParamSet(json::iterator it)
			{
				cout << "	FDwfParamSet called." << endl;
				
				if (it.key() != "FDwfParamSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							DwfParam p1 = it0[1].begin().value().get<DwfParam>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfParamSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfParamGet DwfParam param, int *pvalue
DwfParam 
param
int *
pvalue
*/
// 3 (match no. 5)
			static int _FDwfParamGet(json::iterator it)
			{
				cout << "	FDwfParamGet called." << endl;
				
				if (it.key() != "FDwfParamGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							DwfParam p1 = it0[1].begin().value().get<DwfParam>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfParamGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnum ENUMFILTER enumfilter, int *pcDevice
ENUMFILTER 
enumfilter
int *
pcDevice
*/
// 3 (match no. 6)
			static int _FDwfEnum(json::iterator it)
			{
				cout << "	FDwfEnum called." << endl;
				
				if (it.key() != "FDwfEnum") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							ENUMFILTER p1 = it0[1].begin().value().get<ENUMFILTER>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnum(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfEnumDeviceType(json::iterator it)
			{
				cout << "	FDwfEnumDeviceType called." << endl;
				
				if (it.key() != "FDwfEnumDeviceType") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							DEVID p2 = it0[2].begin().value().get<DEVID>();
							DEVVER p3 = it0[3].begin().value().get<DEVVER>();

							int p0 = FDwfEnumDeviceType(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumDeviceIsOpened int idxDevice, int *pfIsUsed
int 
idxDevice
int *
pfIsUsed
*/
// 4 (match no. 8)
			static int _FDwfEnumDeviceIsOpened(json::iterator it)
			{
				cout << "	FDwfEnumDeviceIsOpened called." << endl;
				
				if (it.key() != "FDwfEnumDeviceIsOpened") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnumDeviceIsOpened(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumUserName int idxDevice, char szUserName[32]
int 
idxDevice
char 
szUserName[32]
*/
// 3 (match no. 9)
			static int _FDwfEnumUserName(json::iterator it)
			{
				cout << "	FDwfEnumUserName called." << endl;
				
				if (it.key() != "FDwfEnumUserName") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();

							int p0 = FDwfEnumUserName(p1,p2.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumDeviceName int idxDevice, char szDeviceName[32]
int 
idxDevice
char 
szDeviceName[32]
*/
// 3 (match no. 10)
			static int _FDwfEnumDeviceName(json::iterator it)
			{
				cout << "	FDwfEnumDeviceName called." << endl;
				
				if (it.key() != "FDwfEnumDeviceName") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();

							int p0 = FDwfEnumDeviceName(p1,p2.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumSN int idxDevice, char szSN[32]
int 
idxDevice
char 
szSN[32]
*/
// 3 (match no. 11)
			static int _FDwfEnumSN(json::iterator it)
			{
				cout << "	FDwfEnumSN called." << endl;
				
				if (it.key() != "FDwfEnumSN") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();

							int p0 = FDwfEnumSN(p1,p2.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumConfig int idxDevice, int *pcConfig
int 
idxDevice
int *
pcConfig
*/
// 3 (match no. 12)
			static int _FDwfEnumConfig(json::iterator it)
			{
				cout << "	FDwfEnumConfig called." << endl;
				
				if (it.key() != "FDwfEnumConfig") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnumConfig(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfEnumConfigInfo(json::iterator it)
			{
				cout << "	FDwfEnumConfigInfo called." << endl;
				
				if (it.key() != "FDwfEnumConfigInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							DwfEnumConfigInfo p2 = it0[2].begin().value().get<DwfEnumConfigInfo>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfEnumConfigInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceOpen int idxDevice, HDWF *phdwf
int 
idxDevice
HDWF *
phdwf
*/
// 4 (match no. 14)
			static int _FDwfDeviceOpen(json::iterator it)
			{
				cout << "	FDwfDeviceOpen called." << endl;
				
				if (it.key() != "FDwfDeviceOpen") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							HDWF p2 = it0[2].begin().value().get<HDWF>();

							int p0 = FDwfDeviceOpen(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDeviceConfigOpen(json::iterator it)
			{
				cout << "	FDwfDeviceConfigOpen called." << endl;
				
				if (it.key() != "FDwfDeviceConfigOpen") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();
							HDWF p3 = it0[3].begin().value().get<HDWF>();

							int p0 = FDwfDeviceConfigOpen(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceClose HDWF hdwf
HDWF 
hdwf
*/
// 4 (match no. 16)
			static int _FDwfDeviceClose(json::iterator it)
			{
				cout << "	FDwfDeviceClose called." << endl;
				
				if (it.key() != "FDwfDeviceClose") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDeviceClose(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceCloseAll 

*/
// 2 (match no. 17)
			static int _FDwfDeviceCloseAll(json::iterator it)
			{
				cout << "	FDwfDeviceCloseAll called." << endl;
				
				if (it.key() != "FDwfDeviceCloseAll") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 1)
					{
						try
						{
							json::iterator it0 = params->begin();

							int p0 = FDwfDeviceCloseAll();

							it0 = params->begin();
							it0[0].begin().value() = p0;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceAutoConfigureSet HDWF hdwf, int fAutoConfigure
HDWF 
hdwf
int 
fAutoConfigure
*/
// 1 (match no. 18)
			static int _FDwfDeviceAutoConfigureSet(json::iterator it)
			{
				cout << "	FDwfDeviceAutoConfigureSet called." << endl;
				
				if (it.key() != "FDwfDeviceAutoConfigureSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDeviceAutoConfigureSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceAutoConfigureGet HDWF hdwf, int *pfAutoConfigure
HDWF 
hdwf
int *
pfAutoConfigure
*/
// 3 (match no. 19)
			static int _FDwfDeviceAutoConfigureGet(json::iterator it)
			{
				cout << "	FDwfDeviceAutoConfigureGet called." << endl;
				
				if (it.key() != "FDwfDeviceAutoConfigureGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDeviceAutoConfigureGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceReset HDWF hdwf
HDWF 
hdwf
*/
// 3 (match no. 20)
			static int _FDwfDeviceReset(json::iterator it)
			{
				cout << "	FDwfDeviceReset called." << endl;
				
				if (it.key() != "FDwfDeviceReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDeviceReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceEnableSet HDWF hdwf, int fEnable
HDWF 
hdwf
int 
fEnable
*/
// 2 (match no. 21)
			static int _FDwfDeviceEnableSet(json::iterator it)
			{
				cout << "	FDwfDeviceEnableSet called." << endl;
				
				if (it.key() != "FDwfDeviceEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDeviceEnableSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceTriggerInfo HDWF hdwf, int *pfstrigsrc
HDWF 
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 22)
			static int _FDwfDeviceTriggerInfo(json::iterator it)
			{
				cout << "	FDwfDeviceTriggerInfo called." << endl;
				
				if (it.key() != "FDwfDeviceTriggerInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDeviceTriggerInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDeviceTriggerSet(json::iterator it)
			{
				cout << "	FDwfDeviceTriggerSet called." << endl;
				
				if (it.key() != "FDwfDeviceTriggerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

							int p0 = FDwfDeviceTriggerSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDeviceTriggerGet(json::iterator it)
			{
				cout << "	FDwfDeviceTriggerGet called." << endl;
				
				if (it.key() != "FDwfDeviceTriggerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

							int p0 = FDwfDeviceTriggerGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceTriggerPC HDWF hdwf
HDWF 
hdwf
*/
// 4 (match no. 25)
			static int _FDwfDeviceTriggerPC(json::iterator it)
			{
				cout << "	FDwfDeviceTriggerPC called." << endl;
				
				if (it.key() != "FDwfDeviceTriggerPC") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDeviceTriggerPC(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDeviceTriggerSlopeInfo HDWF hdwf, int *pfsslope
HDWF 
hdwf
int *
pfsslope
*/
// 2 (match no. 26)
			static int _FDwfDeviceTriggerSlopeInfo(json::iterator it)
			{
				cout << "	FDwfDeviceTriggerSlopeInfo called." << endl;
				
				if (it.key() != "FDwfDeviceTriggerSlopeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDeviceTriggerSlopeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDeviceParamSet(json::iterator it)
			{
				cout << "	FDwfDeviceParamSet called." << endl;
				
				if (it.key() != "FDwfDeviceParamSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfParam p2 = it0[2].begin().value().get<DwfParam>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDeviceParamSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDeviceParamGet(json::iterator it)
			{
				cout << "	FDwfDeviceParamGet called." << endl;
				
				if (it.key() != "FDwfDeviceParamGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfParam p2 = it0[2].begin().value().get<DwfParam>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDeviceParamGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInReset HDWF hdwf
HDWF 
hdwf
*/
// 4 (match no. 29)
			static int _FDwfAnalogInReset(json::iterator it)
			{
				cout << "	FDwfAnalogInReset called." << endl;
				
				if (it.key() != "FDwfAnalogInReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogInReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInConfigure(json::iterator it)
			{
				cout << "	FDwfAnalogInConfigure called." << endl;
				
				if (it.key() != "FDwfAnalogInConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInConfigure(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerForce HDWF hdwf
HDWF 
hdwf
*/
// 4 (match no. 31)
			static int _FDwfAnalogInTriggerForce(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerForce called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerForce") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogInTriggerForce(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatus(json::iterator it)
			{
				cout << "	FDwfAnalogInStatus called." << endl;
				
				if (it.key() != "FDwfAnalogInStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfState p3 = it0[3].begin().value().get<DwfState>();

							int p0 = FDwfAnalogInStatus(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInStatusSamplesLeft HDWF hdwf, int *pcSamplesLeft
HDWF 
hdwf
int *
pcSamplesLeft
*/
// 4 (match no. 33)
			static int _FDwfAnalogInStatusSamplesLeft(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusSamplesLeft called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusSamplesLeft") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusSamplesLeft(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInStatusSamplesValid HDWF hdwf, int *pcSamplesValid
HDWF 
hdwf
int *
pcSamplesValid
*/
// 3 (match no. 34)
			static int _FDwfAnalogInStatusSamplesValid(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusSamplesValid called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusSamplesValid") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusSamplesValid(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInStatusIndexWrite HDWF hdwf, int *pidxWrite
HDWF 
hdwf
int *
pidxWrite
*/
// 3 (match no. 35)
			static int _FDwfAnalogInStatusIndexWrite(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusIndexWrite called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusIndexWrite") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusIndexWrite(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInStatusAutoTriggered HDWF hdwf, int *pfAuto
HDWF 
hdwf
int *
pfAuto
*/
// 3 (match no. 36)
			static int _FDwfAnalogInStatusAutoTriggered(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusAutoTriggered called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusAutoTriggered") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusAutoTriggered(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusData(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusData called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusData") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusData(p1,p2,p3.data(),p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusData2(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusData2 called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusData2") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusData2(p1,p2,p3.data(),p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusData16(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusData16 called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusData16") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<short> p3 = it0[3].begin().value().get<vector<short>>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusData16(p1,p2,p3.data(),p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusNoise(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusNoise called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusNoise") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							vector<double> p4 = it0[4].begin().value().get<vector<double>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusNoise(p1,p2,p3.data(),p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusNoise2(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusNoise2 called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusNoise2") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 7)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							vector<double> p4 = it0[4].begin().value().get<vector<double>>();
							int p5 = it0[5].begin().value().get<int>();
							int p6 = it0[6].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusNoise2(p1,p2,p3.data(),p4.data(),p5,p6);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusSample(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusSample called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusSample") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInStatusSample(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInStatusRecord(json::iterator it)
			{
				cout << "	FDwfAnalogInStatusRecord called." << endl;
				
				if (it.key() != "FDwfAnalogInStatusRecord") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogInStatusRecord(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInRecordLengthSet HDWF hdwf, double sLength
HDWF 
hdwf
double 
sLength
*/
// 5 (match no. 44)
			static int _FDwfAnalogInRecordLengthSet(json::iterator it)
			{
				cout << "	FDwfAnalogInRecordLengthSet called." << endl;
				
				if (it.key() != "FDwfAnalogInRecordLengthSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInRecordLengthSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInRecordLengthGet HDWF hdwf, double *psLength
HDWF 
hdwf
double *
psLength
*/
// 3 (match no. 45)
			static int _FDwfAnalogInRecordLengthGet(json::iterator it)
			{
				cout << "	FDwfAnalogInRecordLengthGet called." << endl;
				
				if (it.key() != "FDwfAnalogInRecordLengthGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInRecordLengthGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInFrequencyInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInFrequencyInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInFrequencyInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInFrequencyInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInFrequencySet HDWF hdwf, double hzFrequency
HDWF 
hdwf
double 
hzFrequency
*/
// 4 (match no. 47)
			static int _FDwfAnalogInFrequencySet(json::iterator it)
			{
				cout << "	FDwfAnalogInFrequencySet called." << endl;
				
				if (it.key() != "FDwfAnalogInFrequencySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInFrequencySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInFrequencyGet HDWF hdwf, double *phzFrequency
HDWF 
hdwf
double *
phzFrequency
*/
// 3 (match no. 48)
			static int _FDwfAnalogInFrequencyGet(json::iterator it)
			{
				cout << "	FDwfAnalogInFrequencyGet called." << endl;
				
				if (it.key() != "FDwfAnalogInFrequencyGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInFrequencyGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInBitsInfo HDWF hdwf, int *pnBits
HDWF 
hdwf
int *
pnBits
*/
// 3 (match no. 49)
			static int _FDwfAnalogInBitsInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInBitsInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInBitsInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInBitsInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInBufferSizeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInBufferSizeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInBufferSizeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInBufferSizeInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInBufferSizeSet HDWF hdwf, int nSize
HDWF 
hdwf
int 
nSize
*/
// 4 (match no. 51)
			static int _FDwfAnalogInBufferSizeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInBufferSizeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInBufferSizeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInBufferSizeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInBufferSizeGet HDWF hdwf, int *pnSize
HDWF 
hdwf
int *
pnSize
*/
// 3 (match no. 52)
			static int _FDwfAnalogInBufferSizeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInBufferSizeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInBufferSizeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInBufferSizeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInNoiseSizeInfo HDWF hdwf, int *pnSizeMax
HDWF 
hdwf
int *
pnSizeMax
*/
// 3 (match no. 53)
			static int _FDwfAnalogInNoiseSizeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInNoiseSizeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInNoiseSizeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInNoiseSizeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInNoiseSizeSet HDWF hdwf, int nSize
HDWF 
hdwf
int 
nSize
*/
// 3 (match no. 54)
			static int _FDwfAnalogInNoiseSizeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInNoiseSizeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInNoiseSizeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInNoiseSizeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInNoiseSizeGet HDWF hdwf, int *pnSize
HDWF 
hdwf
int *
pnSize
*/
// 3 (match no. 55)
			static int _FDwfAnalogInNoiseSizeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInNoiseSizeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInNoiseSizeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInNoiseSizeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInAcquisitionModeInfo HDWF hdwf, int *pfsacqmode
HDWF 
hdwf
int *
pfsacqmode
*/
// 3 (match no. 56)
			static int _FDwfAnalogInAcquisitionModeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInAcquisitionModeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInAcquisitionModeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInAcquisitionModeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInAcquisitionModeSet HDWF hdwf, ACQMODE acqmode
HDWF 
hdwf
ACQMODE 
acqmode
*/
// 3 (match no. 57)
			static int _FDwfAnalogInAcquisitionModeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInAcquisitionModeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInAcquisitionModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

							int p0 = FDwfAnalogInAcquisitionModeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInAcquisitionModeGet HDWF hdwf, ACQMODE *pacqmode
HDWF 
hdwf
ACQMODE *
pacqmode
*/
// 3 (match no. 58)
			static int _FDwfAnalogInAcquisitionModeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInAcquisitionModeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInAcquisitionModeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

							int p0 = FDwfAnalogInAcquisitionModeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInChannelCount HDWF hdwf, int *pcChannel
HDWF 
hdwf
int *
pcChannel
*/
// 3 (match no. 59)
			static int _FDwfAnalogInChannelCount(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelCount called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelCount") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInChannelCount(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelEnableSet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelEnableSet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInChannelEnableSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelEnableGet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelEnableGet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInChannelEnableGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInChannelFilterInfo HDWF hdwf, int *pfsfilter
HDWF 
hdwf
int *
pfsfilter
*/
// 4 (match no. 62)
			static int _FDwfAnalogInChannelFilterInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelFilterInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelFilterInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInChannelFilterInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelFilterSet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelFilterSet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelFilterSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							FILTER p3 = it0[3].begin().value().get<FILTER>();

							int p0 = FDwfAnalogInChannelFilterSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelFilterGet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelFilterGet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelFilterGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							FILTER p3 = it0[3].begin().value().get<FILTER>();

							int p0 = FDwfAnalogInChannelFilterGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelRangeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelRangeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelRangeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelRangeInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelRangeSteps(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelRangeSteps called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelRangeSteps") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							vector<double> p2 = it0[2].begin().value().get<vector<double>>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInChannelRangeSteps(p1,p2.data(),&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelRangeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelRangeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelRangeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelRangeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelRangeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelRangeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelRangeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelRangeGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelOffsetInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelOffsetInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelOffsetInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelOffsetInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelOffsetSet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelOffsetSet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelOffsetSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelOffsetSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelOffsetGet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelOffsetGet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelOffsetGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelOffsetGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelAttenuationSet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelAttenuationSet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelAttenuationSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelAttenuationSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInChannelAttenuationGet(json::iterator it)
			{
				cout << "	FDwfAnalogInChannelAttenuationGet called." << endl;
				
				if (it.key() != "FDwfAnalogInChannelAttenuationGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogInChannelAttenuationGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF 
hdwf
TRIGSRC 
trigsrc
*/
// 4 (match no. 74)
			static int _FDwfAnalogInTriggerSourceSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerSourceSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogInTriggerSourceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF 
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 75)
			static int _FDwfAnalogInTriggerSourceGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerSourceGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogInTriggerSourceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerPositionInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerPositionInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerPositionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerPositionInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerPositionSet HDWF hdwf, double secPosition
HDWF 
hdwf
double 
secPosition
*/
// 5 (match no. 77)
			static int _FDwfAnalogInTriggerPositionSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerPositionSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerPositionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerPositionSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerPositionGet HDWF hdwf, double *psecPosition
HDWF 
hdwf
double *
psecPosition
*/
// 3 (match no. 78)
			static int _FDwfAnalogInTriggerPositionGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerPositionGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerPositionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerPositionGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerPositionStatus HDWF hdwf, double *psecPosition
HDWF 
hdwf
double *
psecPosition
*/
// 3 (match no. 79)
			static int _FDwfAnalogInTriggerPositionStatus(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerPositionStatus called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerPositionStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerPositionStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerAutoTimeoutInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerAutoTimeoutInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerAutoTimeoutInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerAutoTimeoutInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerAutoTimeoutSet HDWF hdwf, double secTimeout
HDWF 
hdwf
double 
secTimeout
*/
// 5 (match no. 81)
			static int _FDwfAnalogInTriggerAutoTimeoutSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerAutoTimeoutSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerAutoTimeoutSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerAutoTimeoutSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerAutoTimeoutGet HDWF hdwf, double *psecTimeout
HDWF 
hdwf
double *
psecTimeout
*/
// 3 (match no. 82)
			static int _FDwfAnalogInTriggerAutoTimeoutGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerAutoTimeoutGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerAutoTimeoutGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerAutoTimeoutGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerHoldOffInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHoldOffInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHoldOffInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHoldOffInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerHoldOffSet HDWF hdwf, double secHoldOff
HDWF 
hdwf
double 
secHoldOff
*/
// 5 (match no. 84)
			static int _FDwfAnalogInTriggerHoldOffSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHoldOffSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHoldOffSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHoldOffSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerHoldOffGet HDWF hdwf, double *psecHoldOff
HDWF 
hdwf
double *
psecHoldOff
*/
// 3 (match no. 85)
			static int _FDwfAnalogInTriggerHoldOffGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHoldOffGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHoldOffGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHoldOffGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerTypeInfo HDWF hdwf, int *pfstrigtype
HDWF 
hdwf
int *
pfstrigtype
*/
// 3 (match no. 86)
			static int _FDwfAnalogInTriggerTypeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerTypeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerTypeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerTypeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerTypeSet HDWF hdwf, TRIGTYPE trigtype
HDWF 
hdwf
TRIGTYPE 
trigtype
*/
// 3 (match no. 87)
			static int _FDwfAnalogInTriggerTypeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerTypeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerTypeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGTYPE p2 = it0[2].begin().value().get<TRIGTYPE>();

							int p0 = FDwfAnalogInTriggerTypeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerTypeGet HDWF hdwf, TRIGTYPE *ptrigtype
HDWF 
hdwf
TRIGTYPE *
ptrigtype
*/
// 3 (match no. 88)
			static int _FDwfAnalogInTriggerTypeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerTypeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerTypeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGTYPE p2 = it0[2].begin().value().get<TRIGTYPE>();

							int p0 = FDwfAnalogInTriggerTypeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerChannelInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerChannelInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerChannelInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerChannelInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerChannelSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 4 (match no. 90)
			static int _FDwfAnalogInTriggerChannelSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerChannelSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerChannelSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerChannelSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerChannelGet HDWF hdwf, int *pidxChannel
HDWF 
hdwf
int *
pidxChannel
*/
// 3 (match no. 91)
			static int _FDwfAnalogInTriggerChannelGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerChannelGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerChannelGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerChannelGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerFilterInfo HDWF hdwf, int *pfsfilter
HDWF 
hdwf
int *
pfsfilter
*/
// 3 (match no. 92)
			static int _FDwfAnalogInTriggerFilterInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerFilterInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerFilterInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerFilterInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerFilterSet HDWF hdwf, FILTER filter
HDWF 
hdwf
FILTER 
filter
*/
// 3 (match no. 93)
			static int _FDwfAnalogInTriggerFilterSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerFilterSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerFilterSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							FILTER p2 = it0[2].begin().value().get<FILTER>();

							int p0 = FDwfAnalogInTriggerFilterSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerFilterGet HDWF hdwf, FILTER *pfilter
HDWF 
hdwf
FILTER *
pfilter
*/
// 3 (match no. 94)
			static int _FDwfAnalogInTriggerFilterGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerFilterGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerFilterGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							FILTER p2 = it0[2].begin().value().get<FILTER>();

							int p0 = FDwfAnalogInTriggerFilterGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerLevelInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLevelInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLevelInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLevelInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLevelSet HDWF hdwf, double voltsLevel
HDWF 
hdwf
double 
voltsLevel
*/
// 5 (match no. 96)
			static int _FDwfAnalogInTriggerLevelSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLevelSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLevelSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLevelSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLevelGet HDWF hdwf, double *pvoltsLevel
HDWF 
hdwf
double *
pvoltsLevel
*/
// 3 (match no. 97)
			static int _FDwfAnalogInTriggerLevelGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLevelGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLevelGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLevelGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerHysteresisInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHysteresisInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHysteresisInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHysteresisInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerHysteresisSet HDWF hdwf, double voltsLevel
HDWF 
hdwf
double 
voltsLevel
*/
// 5 (match no. 99)
			static int _FDwfAnalogInTriggerHysteresisSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHysteresisSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHysteresisSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHysteresisSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerHysteresisGet HDWF hdwf, double *pvoltsHysteresis
HDWF 
hdwf
double *
pvoltsHysteresis
*/
// 3 (match no. 100)
			static int _FDwfAnalogInTriggerHysteresisGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerHysteresisGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerHysteresisGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerHysteresisGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerConditionInfo HDWF hdwf, int *pfstrigcond
HDWF 
hdwf
int *
pfstrigcond
*/
// 3 (match no. 101)
			static int _FDwfAnalogInTriggerConditionInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerConditionInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerConditionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerConditionInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerConditionSet HDWF hdwf, DwfTriggerSlope trigcond
HDWF 
hdwf
DwfTriggerSlope 
trigcond
*/
// 3 (match no. 102)
			static int _FDwfAnalogInTriggerConditionSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerConditionSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerConditionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogInTriggerConditionSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerConditionGet HDWF hdwf, DwfTriggerSlope *ptrigcond
HDWF 
hdwf
DwfTriggerSlope *
ptrigcond
*/
// 3 (match no. 103)
			static int _FDwfAnalogInTriggerConditionGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerConditionGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerConditionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogInTriggerConditionGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogInTriggerLengthInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLengthInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLengthSet HDWF hdwf, double secLength
HDWF 
hdwf
double 
secLength
*/
// 5 (match no. 105)
			static int _FDwfAnalogInTriggerLengthSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLengthSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLengthGet HDWF hdwf, double *psecLength
HDWF 
hdwf
double *
psecLength
*/
// 3 (match no. 106)
			static int _FDwfAnalogInTriggerLengthGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInTriggerLengthGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLengthConditionInfo HDWF hdwf, int *pfstriglen
HDWF 
hdwf
int *
pfstriglen
*/
// 3 (match no. 107)
			static int _FDwfAnalogInTriggerLengthConditionInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthConditionInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthConditionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerLengthConditionInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLengthConditionSet HDWF hdwf, TRIGLEN triglen
HDWF 
hdwf
TRIGLEN 
triglen
*/
// 3 (match no. 108)
			static int _FDwfAnalogInTriggerLengthConditionSet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthConditionSet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthConditionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGLEN p2 = it0[2].begin().value().get<TRIGLEN>();

							int p0 = FDwfAnalogInTriggerLengthConditionSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerLengthConditionGet HDWF hdwf, TRIGLEN *ptriglen
HDWF 
hdwf
TRIGLEN *
ptriglen
*/
// 3 (match no. 109)
			static int _FDwfAnalogInTriggerLengthConditionGet(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerLengthConditionGet called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerLengthConditionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGLEN p2 = it0[2].begin().value().get<TRIGLEN>();

							int p0 = FDwfAnalogInTriggerLengthConditionGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF 
hdwf
TRIGSRC 
trigsrc
*/
// 3 (match no. 110)
			static int _FDwfAnalogInSamplingSourceSet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingSourceSet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogInSamplingSourceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF 
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 111)
			static int _FDwfAnalogInSamplingSourceGet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingSourceGet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogInSamplingSourceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF 
hdwf
DwfTriggerSlope 
slope
*/
// 3 (match no. 112)
			static int _FDwfAnalogInSamplingSlopeSet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingSlopeSet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingSlopeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogInSamplingSlopeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF 
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 113)
			static int _FDwfAnalogInSamplingSlopeGet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingSlopeGet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingSlopeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogInSamplingSlopeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingDelaySet HDWF hdwf, double sec
HDWF 
hdwf
double 
sec
*/
// 3 (match no. 114)
			static int _FDwfAnalogInSamplingDelaySet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingDelaySet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingDelaySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInSamplingDelaySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInSamplingDelayGet HDWF hdwf, double *psec
HDWF 
hdwf
double *
psec
*/
// 3 (match no. 115)
			static int _FDwfAnalogInSamplingDelayGet(json::iterator it)
			{
				cout << "	FDwfAnalogInSamplingDelayGet called." << endl;
				
				if (it.key() != "FDwfAnalogInSamplingDelayGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogInSamplingDelayGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogOutCount HDWF hdwf, int *pcChannel
HDWF 
hdwf
int *
pcChannel
*/
// 3 (match no. 116)
			static int _FDwfAnalogOutCount(json::iterator it)
			{
				cout << "	FDwfAnalogOutCount called." << endl;
				
				if (it.key() != "FDwfAnalogOutCount") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogOutCount(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutMasterSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutMasterSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutMasterSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutMasterSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutMasterGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutMasterGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutMasterGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutMasterGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutTriggerSourceSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutTriggerSourceSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutTriggerSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogOutTriggerSourceSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutTriggerSourceGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutTriggerSourceGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutTriggerSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							TRIGSRC p3 = it0[3].begin().value().get<TRIGSRC>();

							int p0 = FDwfAnalogOutTriggerSourceGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutTriggerSlopeSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutTriggerSlopeSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutTriggerSlopeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfTriggerSlope p3 = it0[3].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogOutTriggerSlopeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutTriggerSlopeGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutTriggerSlopeGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutTriggerSlopeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfTriggerSlope p3 = it0[3].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfAnalogOutTriggerSlopeGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRunInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutRunInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutRunInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutRunInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRunSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRunSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRunSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutRunSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRunGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRunGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRunGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutRunGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRunStatus(json::iterator it)
			{
				cout << "	FDwfAnalogOutRunStatus called." << endl;
				
				if (it.key() != "FDwfAnalogOutRunStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutRunStatus(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutWaitInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutWaitInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutWaitInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutWaitInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutWaitSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutWaitSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutWaitSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutWaitSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutWaitGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutWaitGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutWaitGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutWaitGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatStatus(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatStatus called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatStatus(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatTriggerSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatTriggerSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatTriggerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatTriggerSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutRepeatTriggerGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutRepeatTriggerGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutRepeatTriggerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutRepeatTriggerGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutLimitationInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutLimitationInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutLimitationInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutLimitationInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutLimitationSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutLimitationSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutLimitationSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutLimitationSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutLimitationGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutLimitationGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutLimitationGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutLimitationGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutModeSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutModeSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfAnalogOutMode p3 = it0[3].begin().value().get<DwfAnalogOutMode>();

							int p0 = FDwfAnalogOutModeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutModeGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutModeGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutModeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfAnalogOutMode p3 = it0[3].begin().value().get<DwfAnalogOutMode>();

							int p0 = FDwfAnalogOutModeGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutIdleInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutIdleInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutIdleInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutIdleInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutIdleSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutIdleSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutIdleSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfAnalogOutIdle p3 = it0[3].begin().value().get<DwfAnalogOutIdle>();

							int p0 = FDwfAnalogOutIdleSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutIdleGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutIdleGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutIdleGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfAnalogOutIdle p3 = it0[3].begin().value().get<DwfAnalogOutIdle>();

							int p0 = FDwfAnalogOutIdleGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeEnableSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeEnableSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeEnableSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeEnableGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeEnableGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeEnableGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFunctionInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFunctionInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFunctionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeFunctionInfo(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFunctionSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFunctionSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFunctionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							FUNC p4 = it0[4].begin().value().get<FUNC>();

							int p0 = FDwfAnalogOutNodeFunctionSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFunctionGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFunctionGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFunctionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							FUNC p4 = it0[4].begin().value().get<FUNC>();

							int p0 = FDwfAnalogOutNodeFunctionGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFrequencyInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFrequencyInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFrequencyInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeFrequencyInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFrequencySet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFrequencySet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFrequencySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeFrequencySet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeFrequencyGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeFrequencyGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeFrequencyGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeFrequencyGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeAmplitudeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeAmplitudeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeAmplitudeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeAmplitudeInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeAmplitudeSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeAmplitudeSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeAmplitudeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeAmplitudeSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeAmplitudeGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeAmplitudeGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeAmplitudeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeAmplitudeGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeOffsetInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeOffsetInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeOffsetInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeOffsetInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeOffsetSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeOffsetSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeOffsetSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeOffsetSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeOffsetGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeOffsetGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeOffsetGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeOffsetGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeSymmetryInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeSymmetryInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeSymmetryInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeSymmetryInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeSymmetrySet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeSymmetrySet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeSymmetrySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeSymmetrySet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeSymmetryGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeSymmetryGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeSymmetryGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodeSymmetryGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodePhaseInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodePhaseInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodePhaseInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodePhaseInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodePhaseSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodePhaseSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodePhaseSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodePhaseSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodePhaseGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodePhaseGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodePhaseGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutNodePhaseGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeDataInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeDataInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeDataInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeDataInfo(p1,p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodeDataSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodeDataSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodeDataSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							vector<double> p4 = it0[4].begin().value().get<vector<double>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodeDataSet(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutCustomAMFMEnableSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutCustomAMFMEnableSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutCustomAMFMEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutCustomAMFMEnableSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutCustomAMFMEnableGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutCustomAMFMEnableGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutCustomAMFMEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutCustomAMFMEnableGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogOutReset HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 4 (match no. 169)
			static int _FDwfAnalogOutReset(json::iterator it)
			{
				cout << "	FDwfAnalogOutReset called." << endl;
				
				if (it.key() != "FDwfAnalogOutReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogOutReset(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutConfigure(json::iterator it)
			{
				cout << "	FDwfAnalogOutConfigure called." << endl;
				
				if (it.key() != "FDwfAnalogOutConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutConfigure(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutStatus(json::iterator it)
			{
				cout << "	FDwfAnalogOutStatus called." << endl;
				
				if (it.key() != "FDwfAnalogOutStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfState p3 = it0[3].begin().value().get<DwfState>();

							int p0 = FDwfAnalogOutStatus(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodePlayStatus(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodePlayStatus called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodePlayStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 7)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();
							int p6 = it0[6].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodePlayStatus(p1,p2,p3,&p4,&p5,&p6);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutNodePlayData(json::iterator it)
			{
				cout << "	FDwfAnalogOutNodePlayData called." << endl;
				
				if (it.key() != "FDwfAnalogOutNodePlayData") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							AnalogOutNode p3 = it0[3].begin().value().get<AnalogOutNode>();
							vector<double> p4 = it0[4].begin().value().get<vector<double>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogOutNodePlayData(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOReset HDWF hdwf
HDWF 
hdwf
*/
// 6 (match no. 174)
			static int _FDwfAnalogIOReset(json::iterator it)
			{
				cout << "	FDwfAnalogIOReset called." << endl;
				
				if (it.key() != "FDwfAnalogIOReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogIOReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOConfigure HDWF hdwf
HDWF 
hdwf
*/
// 2 (match no. 175)
			static int _FDwfAnalogIOConfigure(json::iterator it)
			{
				cout << "	FDwfAnalogIOConfigure called." << endl;
				
				if (it.key() != "FDwfAnalogIOConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogIOConfigure(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOStatus HDWF hdwf
HDWF 
hdwf
*/
// 2 (match no. 176)
			static int _FDwfAnalogIOStatus(json::iterator it)
			{
				cout << "	FDwfAnalogIOStatus called." << endl;
				
				if (it.key() != "FDwfAnalogIOStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogIOStatus(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOEnableInfo(json::iterator it)
			{
				cout << "	FDwfAnalogIOEnableInfo called." << endl;
				
				if (it.key() != "FDwfAnalogIOEnableInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogIOEnableInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOEnableSet HDWF hdwf, int fMasterEnable
HDWF 
hdwf
int 
fMasterEnable
*/
// 4 (match no. 178)
			static int _FDwfAnalogIOEnableSet(json::iterator it)
			{
				cout << "	FDwfAnalogIOEnableSet called." << endl;
				
				if (it.key() != "FDwfAnalogIOEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogIOEnableSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOEnableGet HDWF hdwf, int *pfMasterEnable
HDWF 
hdwf
int *
pfMasterEnable
*/
// 3 (match no. 179)
			static int _FDwfAnalogIOEnableGet(json::iterator it)
			{
				cout << "	FDwfAnalogIOEnableGet called." << endl;
				
				if (it.key() != "FDwfAnalogIOEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogIOEnableGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOEnableStatus HDWF hdwf, int *pfMasterEnable
HDWF 
hdwf
int *
pfMasterEnable
*/
// 3 (match no. 180)
			static int _FDwfAnalogIOEnableStatus(json::iterator it)
			{
				cout << "	FDwfAnalogIOEnableStatus called." << endl;
				
				if (it.key() != "FDwfAnalogIOEnableStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogIOEnableStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogIOChannelCount HDWF hdwf, int *pnChannel
HDWF 
hdwf
int *
pnChannel
*/
// 3 (match no. 181)
			static int _FDwfAnalogIOChannelCount(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelCount called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelCount") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogIOChannelCount(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelName(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelName called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelName") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<char> p3 = it0[3].begin().value().get<vector<char>>();
							vector<char> p4 = it0[4].begin().value().get<vector<char>>();

							int p0 = FDwfAnalogIOChannelName(p1,p2,p3.data(),p4.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelInfo(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelInfo called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogIOChannelInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeName(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeName called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeName") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<char> p4 = it0[4].begin().value().get<vector<char>>();
							vector<char> p5 = it0[5].begin().value().get<vector<char>>();

							int p0 = FDwfAnalogIOChannelNodeName(p1,p2,p3,p4.data(),p5.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							ANALOGIO p4 = it0[4].begin().value().get<ANALOGIO>();

							int p0 = FDwfAnalogIOChannelNodeInfo(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeSetInfo(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeSetInfo called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeSetInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 7)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();
							int p6 = it0[6].begin().value().get<int>();

							int p0 = FDwfAnalogIOChannelNodeSetInfo(p1,p2,p3,&p4,&p5,&p6);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeSet(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeSet called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogIOChannelNodeSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeGet(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeGet called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogIOChannelNodeGet(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeStatusInfo(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeStatusInfo called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeStatusInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 7)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();
							int p6 = it0[6].begin().value().get<int>();

							int p0 = FDwfAnalogIOChannelNodeStatusInfo(p1,p2,p3,&p4,&p5,&p6);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogIOChannelNodeStatus(json::iterator it)
			{
				cout << "	FDwfAnalogIOChannelNodeStatus called." << endl;
				
				if (it.key() != "FDwfAnalogIOChannelNodeStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogIOChannelNodeStatus(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOReset HDWF hdwf
HDWF 
hdwf
*/
// 5 (match no. 191)
			static int _FDwfDigitalIOReset(json::iterator it)
			{
				cout << "	FDwfDigitalIOReset called." << endl;
				
				if (it.key() != "FDwfDigitalIOReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalIOReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOConfigure HDWF hdwf
HDWF 
hdwf
*/
// 2 (match no. 192)
			static int _FDwfDigitalIOConfigure(json::iterator it)
			{
				cout << "	FDwfDigitalIOConfigure called." << endl;
				
				if (it.key() != "FDwfDigitalIOConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalIOConfigure(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOStatus HDWF hdwf
HDWF 
hdwf
*/
// 2 (match no. 193)
			static int _FDwfDigitalIOStatus(json::iterator it)
			{
				cout << "	FDwfDigitalIOStatus called." << endl;
				
				if (it.key() != "FDwfDigitalIOStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalIOStatus(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableInfo HDWF hdwf, unsigned int *pfsOutputEnableMask
HDWF 
hdwf
unsigned int *
pfsOutputEnableMask
*/
// 2 (match no. 194)
			static int _FDwfDigitalIOOutputEnableInfo(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableInfo called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputEnableInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableSet HDWF hdwf, unsigned int fsOutputEnable
HDWF 
hdwf
unsigned int 
fsOutputEnable
*/
// 3 (match no. 195)
			static int _FDwfDigitalIOOutputEnableSet(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableSet called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputEnableSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableGet HDWF hdwf, unsigned int *pfsOutputEnable
HDWF 
hdwf
unsigned int *
pfsOutputEnable
*/
// 3 (match no. 196)
			static int _FDwfDigitalIOOutputEnableGet(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableGet called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputEnableGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputInfo HDWF hdwf, unsigned int *pfsOutputMask
HDWF 
hdwf
unsigned int *
pfsOutputMask
*/
// 3 (match no. 197)
			static int _FDwfDigitalIOOutputInfo(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputInfo called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputSet HDWF hdwf, unsigned int fsOutput
HDWF 
hdwf
unsigned int 
fsOutput
*/
// 3 (match no. 198)
			static int _FDwfDigitalIOOutputSet(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputSet called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputGet HDWF hdwf, unsigned int *pfsOutput
HDWF 
hdwf
unsigned int *
pfsOutput
*/
// 3 (match no. 199)
			static int _FDwfDigitalIOOutputGet(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputGet called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOOutputGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOInputInfo HDWF hdwf, unsigned int *pfsInputMask
HDWF 
hdwf
unsigned int *
pfsInputMask
*/
// 3 (match no. 200)
			static int _FDwfDigitalIOInputInfo(json::iterator it)
			{
				cout << "	FDwfDigitalIOInputInfo called." << endl;
				
				if (it.key() != "FDwfDigitalIOInputInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOInputInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOInputStatus HDWF hdwf, unsigned int *pfsInput
HDWF 
hdwf
unsigned int *
pfsInput
*/
// 3 (match no. 201)
			static int _FDwfDigitalIOInputStatus(json::iterator it)
			{
				cout << "	FDwfDigitalIOInputStatus called." << endl;
				
				if (it.key() != "FDwfDigitalIOInputStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalIOInputStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableInfo64 HDWF hdwf, unsigned long long *pfsOutputEnableMask
HDWF 
hdwf
unsigned long long *
pfsOutputEnableMask
*/
// 3 (match no. 202)
			static int _FDwfDigitalIOOutputEnableInfo64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableInfo64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableInfo64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputEnableInfo64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableSet64 HDWF hdwf, unsigned long long fsOutputEnable
HDWF 
hdwf
unsigned long long 
fsOutputEnable
*/
// 3 (match no. 203)
			static int _FDwfDigitalIOOutputEnableSet64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableSet64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableSet64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputEnableSet64(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputEnableGet64 HDWF hdwf, unsigned long long *pfsOutputEnable
HDWF 
hdwf
unsigned long long *
pfsOutputEnable
*/
// 3 (match no. 204)
			static int _FDwfDigitalIOOutputEnableGet64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputEnableGet64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputEnableGet64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputEnableGet64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputInfo64 HDWF hdwf, unsigned long long *pfsOutputMask
HDWF 
hdwf
unsigned long long *
pfsOutputMask
*/
// 3 (match no. 205)
			static int _FDwfDigitalIOOutputInfo64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputInfo64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputInfo64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputInfo64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputSet64 HDWF hdwf, unsigned long long fsOutput
HDWF 
hdwf
unsigned long long 
fsOutput
*/
// 3 (match no. 206)
			static int _FDwfDigitalIOOutputSet64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputSet64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputSet64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputSet64(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOOutputGet64 HDWF hdwf, unsigned long long *pfsOutput
HDWF 
hdwf
unsigned long long *
pfsOutput
*/
// 3 (match no. 207)
			static int _FDwfDigitalIOOutputGet64(json::iterator it)
			{
				cout << "	FDwfDigitalIOOutputGet64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOOutputGet64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOOutputGet64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOInputInfo64 HDWF hdwf, unsigned long long *pfsInputMask
HDWF 
hdwf
unsigned long long *
pfsInputMask
*/
// 3 (match no. 208)
			static int _FDwfDigitalIOInputInfo64(json::iterator it)
			{
				cout << "	FDwfDigitalIOInputInfo64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOInputInfo64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOInputInfo64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalIOInputStatus64 HDWF hdwf, unsigned long long *pfsInput
HDWF 
hdwf
unsigned long long *
pfsInput
*/
// 3 (match no. 209)
			static int _FDwfDigitalIOInputStatus64(json::iterator it)
			{
				cout << "	FDwfDigitalIOInputStatus64 called." << endl;
				
				if (it.key() != "FDwfDigitalIOInputStatus64") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned long long p2 = it0[2].begin().value().get<unsigned long long>();

							int p0 = FDwfDigitalIOInputStatus64(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInReset HDWF hdwf
HDWF 
hdwf
*/
// 3 (match no. 210)
			static int _FDwfDigitalInReset(json::iterator it)
			{
				cout << "	FDwfDigitalInReset called." << endl;
				
				if (it.key() != "FDwfDigitalInReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalInReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInConfigure(json::iterator it)
			{
				cout << "	FDwfDigitalInConfigure called." << endl;
				
				if (it.key() != "FDwfDigitalInConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalInConfigure(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInStatus(json::iterator it)
			{
				cout << "	FDwfDigitalInStatus called." << endl;
				
				if (it.key() != "FDwfDigitalInStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfState p3 = it0[3].begin().value().get<DwfState>();

							int p0 = FDwfDigitalInStatus(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInStatusSamplesLeft HDWF hdwf, int *pcSamplesLeft
HDWF 
hdwf
int *
pcSamplesLeft
*/
// 4 (match no. 213)
			static int _FDwfDigitalInStatusSamplesLeft(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusSamplesLeft called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusSamplesLeft") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusSamplesLeft(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInStatusSamplesValid HDWF hdwf, int *pcSamplesValid
HDWF 
hdwf
int *
pcSamplesValid
*/
// 3 (match no. 214)
			static int _FDwfDigitalInStatusSamplesValid(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusSamplesValid called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusSamplesValid") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusSamplesValid(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInStatusIndexWrite HDWF hdwf, int *pidxWrite
HDWF 
hdwf
int *
pidxWrite
*/
// 3 (match no. 215)
			static int _FDwfDigitalInStatusIndexWrite(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusIndexWrite called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusIndexWrite") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusIndexWrite(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInStatusAutoTriggered HDWF hdwf, int *pfAuto
HDWF 
hdwf
int *
pfAuto
*/
// 3 (match no. 216)
			static int _FDwfDigitalInStatusAutoTriggered(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusAutoTriggered called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusAutoTriggered") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusAutoTriggered(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInStatusData(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusData called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusData") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusData(p1,p2.data(),p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInStatusData2(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusData2 called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusData2") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusData2(p1,p2.data(),p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInStatusNoise2(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusNoise2 called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusNoise2") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							vector<char> p2 = it0[2].begin().value().get<vector<char>>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusNoise2(p1,p2.data(),p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInStatusRecord(json::iterator it)
			{
				cout << "	FDwfDigitalInStatusRecord called." << endl;
				
				if (it.key() != "FDwfDigitalInStatusRecord") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfDigitalInStatusRecord(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInInternalClockInfo HDWF hdwf, double *phzFreq
HDWF 
hdwf
double *
phzFreq
*/
// 5 (match no. 221)
			static int _FDwfDigitalInInternalClockInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInInternalClockInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInInternalClockInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalInInternalClockInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInClockSourceInfo HDWF hdwf, int *pfsDwfDigitalInClockSource
HDWF 
hdwf
int *
pfsDwfDigitalInClockSource
*/
// 3 (match no. 222)
			static int _FDwfDigitalInClockSourceInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInClockSourceInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInClockSourceInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInClockSourceInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInClockSourceSet HDWF hdwf, DwfDigitalInClockSource v
HDWF 
hdwf
DwfDigitalInClockSource 
v
*/
// 3 (match no. 223)
			static int _FDwfDigitalInClockSourceSet(json::iterator it)
			{
				cout << "	FDwfDigitalInClockSourceSet called." << endl;
				
				if (it.key() != "FDwfDigitalInClockSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfDigitalInClockSource p2 = it0[2].begin().value().get<DwfDigitalInClockSource>();

							int p0 = FDwfDigitalInClockSourceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInClockSourceGet HDWF hdwf, DwfDigitalInClockSource *pv
HDWF 
hdwf
DwfDigitalInClockSource *
pv
*/
// 3 (match no. 224)
			static int _FDwfDigitalInClockSourceGet(json::iterator it)
			{
				cout << "	FDwfDigitalInClockSourceGet called." << endl;
				
				if (it.key() != "FDwfDigitalInClockSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfDigitalInClockSource p2 = it0[2].begin().value().get<DwfDigitalInClockSource>();

							int p0 = FDwfDigitalInClockSourceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInDividerInfo HDWF hdwf, unsigned int *pdivMax
HDWF 
hdwf
unsigned int *
pdivMax
*/
// 3 (match no. 225)
			static int _FDwfDigitalInDividerInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInDividerInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInDividerInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInDividerInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInDividerSet HDWF hdwf, unsigned int div
HDWF 
hdwf
unsigned int 
div
*/
// 3 (match no. 226)
			static int _FDwfDigitalInDividerSet(json::iterator it)
			{
				cout << "	FDwfDigitalInDividerSet called." << endl;
				
				if (it.key() != "FDwfDigitalInDividerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInDividerSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInDividerGet HDWF hdwf, unsigned int *pdiv
HDWF 
hdwf
unsigned int *
pdiv
*/
// 3 (match no. 227)
			static int _FDwfDigitalInDividerGet(json::iterator it)
			{
				cout << "	FDwfDigitalInDividerGet called." << endl;
				
				if (it.key() != "FDwfDigitalInDividerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInDividerGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInBitsInfo HDWF hdwf, int *pnBits
HDWF 
hdwf
int *
pnBits
*/
// 3 (match no. 228)
			static int _FDwfDigitalInBitsInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInBitsInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInBitsInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInBitsInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleFormatSet HDWF hdwf, int nBits
HDWF 
hdwf
int 
nBits
*/
// 3 (match no. 229)
			static int _FDwfDigitalInSampleFormatSet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleFormatSet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleFormatSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInSampleFormatSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleFormatGet HDWF hdwf, int *pnBits
HDWF 
hdwf
int *
pnBits
*/
// 3 (match no. 230)
			static int _FDwfDigitalInSampleFormatGet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleFormatGet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleFormatGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInSampleFormatGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInInputOrderSet HDWF hdwf, bool fDioFirst
HDWF 
hdwf
bool 
fDioFirst
*/
// 3 (match no. 231)
			static int _FDwfDigitalInInputOrderSet(json::iterator it)
			{
				cout << "	FDwfDigitalInInputOrderSet called." << endl;
				
				if (it.key() != "FDwfDigitalInInputOrderSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							bool p2 = it0[2].begin().value().get<bool>();

							int p0 = FDwfDigitalInInputOrderSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInBufferSizeInfo HDWF hdwf, int *pnSizeMax
HDWF 
hdwf
int *
pnSizeMax
*/
// 3 (match no. 232)
			static int _FDwfDigitalInBufferSizeInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInBufferSizeInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInBufferSizeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInBufferSizeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInBufferSizeSet HDWF hdwf, int nSize
HDWF 
hdwf
int 
nSize
*/
// 3 (match no. 233)
			static int _FDwfDigitalInBufferSizeSet(json::iterator it)
			{
				cout << "	FDwfDigitalInBufferSizeSet called." << endl;
				
				if (it.key() != "FDwfDigitalInBufferSizeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInBufferSizeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInBufferSizeGet HDWF hdwf, int *pnSize
HDWF 
hdwf
int *
pnSize
*/
// 3 (match no. 234)
			static int _FDwfDigitalInBufferSizeGet(json::iterator it)
			{
				cout << "	FDwfDigitalInBufferSizeGet called." << endl;
				
				if (it.key() != "FDwfDigitalInBufferSizeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInBufferSizeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleModeInfo HDWF hdwf, int *pfsDwfDigitalInSampleMode
HDWF 
hdwf
int *
pfsDwfDigitalInSampleMode
*/
// 3 (match no. 235)
			static int _FDwfDigitalInSampleModeInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleModeInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleModeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInSampleModeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleModeSet HDWF hdwf, DwfDigitalInSampleMode v
HDWF 
hdwf
DwfDigitalInSampleMode 
v
*/
// 3 (match no. 236)
			static int _FDwfDigitalInSampleModeSet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleModeSet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfDigitalInSampleMode p2 = it0[2].begin().value().get<DwfDigitalInSampleMode>();

							int p0 = FDwfDigitalInSampleModeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleModeGet HDWF hdwf, DwfDigitalInSampleMode *pv
HDWF 
hdwf
DwfDigitalInSampleMode *
pv
*/
// 3 (match no. 237)
			static int _FDwfDigitalInSampleModeGet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleModeGet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleModeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfDigitalInSampleMode p2 = it0[2].begin().value().get<DwfDigitalInSampleMode>();

							int p0 = FDwfDigitalInSampleModeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleSensibleSet HDWF hdwf, unsigned int fs
HDWF 
hdwf
unsigned int 
fs
*/
// 3 (match no. 238)
			static int _FDwfDigitalInSampleSensibleSet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleSensibleSet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleSensibleSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInSampleSensibleSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInSampleSensibleGet HDWF hdwf, unsigned int *pfs
HDWF 
hdwf
unsigned int *
pfs
*/
// 3 (match no. 239)
			static int _FDwfDigitalInSampleSensibleGet(json::iterator it)
			{
				cout << "	FDwfDigitalInSampleSensibleGet called." << endl;
				
				if (it.key() != "FDwfDigitalInSampleSensibleGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInSampleSensibleGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInAcquisitionModeInfo HDWF hdwf, int *pfsacqmode
HDWF 
hdwf
int *
pfsacqmode
*/
// 3 (match no. 240)
			static int _FDwfDigitalInAcquisitionModeInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInAcquisitionModeInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInAcquisitionModeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInAcquisitionModeInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInAcquisitionModeSet HDWF hdwf, ACQMODE acqmode
HDWF 
hdwf
ACQMODE 
acqmode
*/
// 3 (match no. 241)
			static int _FDwfDigitalInAcquisitionModeSet(json::iterator it)
			{
				cout << "	FDwfDigitalInAcquisitionModeSet called." << endl;
				
				if (it.key() != "FDwfDigitalInAcquisitionModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

							int p0 = FDwfDigitalInAcquisitionModeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInAcquisitionModeGet HDWF hdwf, ACQMODE *pacqmode
HDWF 
hdwf
ACQMODE *
pacqmode
*/
// 3 (match no. 242)
			static int _FDwfDigitalInAcquisitionModeGet(json::iterator it)
			{
				cout << "	FDwfDigitalInAcquisitionModeGet called." << endl;
				
				if (it.key() != "FDwfDigitalInAcquisitionModeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							ACQMODE p2 = it0[2].begin().value().get<ACQMODE>();

							int p0 = FDwfDigitalInAcquisitionModeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF 
hdwf
TRIGSRC 
trigsrc
*/
// 3 (match no. 243)
			static int _FDwfDigitalInTriggerSourceSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSourceSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfDigitalInTriggerSourceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF 
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 244)
			static int _FDwfDigitalInTriggerSourceGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSourceGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfDigitalInTriggerSourceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF 
hdwf
DwfTriggerSlope 
slope
*/
// 3 (match no. 245)
			static int _FDwfDigitalInTriggerSlopeSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSlopeSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSlopeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfDigitalInTriggerSlopeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF 
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 246)
			static int _FDwfDigitalInTriggerSlopeGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSlopeGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSlopeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfDigitalInTriggerSlopeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerPositionInfo HDWF hdwf, unsigned int *pnSamplesAfterTriggerMax
HDWF 
hdwf
unsigned int *
pnSamplesAfterTriggerMax
*/
// 3 (match no. 247)
			static int _FDwfDigitalInTriggerPositionInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerPositionInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerPositionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerPositionInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerPositionSet HDWF hdwf, unsigned int cSamplesAfterTrigger
HDWF 
hdwf
unsigned int 
cSamplesAfterTrigger
*/
// 3 (match no. 248)
			static int _FDwfDigitalInTriggerPositionSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerPositionSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerPositionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerPositionSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerPositionGet HDWF hdwf, unsigned int *pcSamplesAfterTrigger
HDWF 
hdwf
unsigned int *
pcSamplesAfterTrigger
*/
// 3 (match no. 249)
			static int _FDwfDigitalInTriggerPositionGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerPositionGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerPositionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerPositionGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerPrefillSet HDWF hdwf, unsigned int cSamplesBeforeTrigger
HDWF 
hdwf
unsigned int 
cSamplesBeforeTrigger
*/
// 3 (match no. 250)
			static int _FDwfDigitalInTriggerPrefillSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerPrefillSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerPrefillSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerPrefillSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerPrefillGet HDWF hdwf, unsigned int *pcSamplesBeforeTrigger
HDWF 
hdwf
unsigned int *
pcSamplesBeforeTrigger
*/
// 3 (match no. 251)
			static int _FDwfDigitalInTriggerPrefillGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerPrefillGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerPrefillGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerPrefillGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerAutoTimeoutInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerAutoTimeoutInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerAutoTimeoutInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfDigitalInTriggerAutoTimeoutInfo(p1,&p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerAutoTimeoutSet HDWF hdwf, double secTimeout
HDWF 
hdwf
double 
secTimeout
*/
// 5 (match no. 253)
			static int _FDwfDigitalInTriggerAutoTimeoutSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerAutoTimeoutSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerAutoTimeoutSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalInTriggerAutoTimeoutSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerAutoTimeoutGet HDWF hdwf, double *psecTimeout
HDWF 
hdwf
double *
psecTimeout
*/
// 3 (match no. 254)
			static int _FDwfDigitalInTriggerAutoTimeoutGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerAutoTimeoutGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerAutoTimeoutGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalInTriggerAutoTimeoutGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();
							unsigned int p5 = it0[5].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerInfo(p1,&p2,&p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();
							unsigned int p5 = it0[5].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerSet(p1,p2,p3,p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerGet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerGet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();
							unsigned int p5 = it0[5].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerGet(p1,&p2,&p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerResetSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerResetSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerResetSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();
							unsigned int p5 = it0[5].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalInTriggerResetSet(p1,p2,p3,p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerCountSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerCountSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerCountSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalInTriggerCountSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerLengthSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerLengthSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerLengthSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfDigitalInTriggerLengthSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalInTriggerMatchSet(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerMatchSet called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerMatchSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalInTriggerMatchSet(p1,p2,p3,p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutReset HDWF hdwf
HDWF 
hdwf
*/
// 6 (match no. 262)
			static int _FDwfDigitalOutReset(json::iterator it)
			{
				cout << "	FDwfDigitalOutReset called." << endl;
				
				if (it.key() != "FDwfDigitalOutReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalOutReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutConfigure HDWF hdwf, int fStart
HDWF 
hdwf
int 
fStart
*/
// 2 (match no. 263)
			static int _FDwfDigitalOutConfigure(json::iterator it)
			{
				cout << "	FDwfDigitalOutConfigure called." << endl;
				
				if (it.key() != "FDwfDigitalOutConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalOutConfigure(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutStatus HDWF hdwf, DwfState *psts
HDWF 
hdwf
DwfState *
psts
*/
// 3 (match no. 264)
			static int _FDwfDigitalOutStatus(json::iterator it)
			{
				cout << "	FDwfDigitalOutStatus called." << endl;
				
				if (it.key() != "FDwfDigitalOutStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfState p2 = it0[2].begin().value().get<DwfState>();

							int p0 = FDwfDigitalOutStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutInternalClockInfo HDWF hdwf, double *phzFreq
HDWF 
hdwf
double *
phzFreq
*/
// 3 (match no. 265)
			static int _FDwfDigitalOutInternalClockInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutInternalClockInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutInternalClockInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutInternalClockInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutTriggerSourceSet HDWF hdwf, TRIGSRC trigsrc
HDWF 
hdwf
TRIGSRC 
trigsrc
*/
// 3 (match no. 266)
			static int _FDwfDigitalOutTriggerSourceSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTriggerSourceSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTriggerSourceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfDigitalOutTriggerSourceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutTriggerSourceGet HDWF hdwf, TRIGSRC *ptrigsrc
HDWF 
hdwf
TRIGSRC *
ptrigsrc
*/
// 3 (match no. 267)
			static int _FDwfDigitalOutTriggerSourceGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTriggerSourceGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTriggerSourceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							TRIGSRC p2 = it0[2].begin().value().get<TRIGSRC>();

							int p0 = FDwfDigitalOutTriggerSourceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutRunInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutRunInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutRunInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfDigitalOutRunInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRunSet HDWF hdwf, double secRun
HDWF 
hdwf
double 
secRun
*/
// 4 (match no. 269)
			static int _FDwfDigitalOutRunSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRunSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRunSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutRunSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRunGet HDWF hdwf, double *psecRun
HDWF 
hdwf
double *
psecRun
*/
// 3 (match no. 270)
			static int _FDwfDigitalOutRunGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRunGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRunGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutRunGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRunStatus HDWF hdwf, double *psecRun
HDWF 
hdwf
double *
psecRun
*/
// 3 (match no. 271)
			static int _FDwfDigitalOutRunStatus(json::iterator it)
			{
				cout << "	FDwfDigitalOutRunStatus called." << endl;
				
				if (it.key() != "FDwfDigitalOutRunStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutRunStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutWaitInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutWaitInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutWaitInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfDigitalOutWaitInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutWaitSet HDWF hdwf, double secWait
HDWF 
hdwf
double 
secWait
*/
// 4 (match no. 273)
			static int _FDwfDigitalOutWaitSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutWaitSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutWaitSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutWaitSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutWaitGet HDWF hdwf, double *psecWait
HDWF 
hdwf
double *
psecWait
*/
// 3 (match no. 274)
			static int _FDwfDigitalOutWaitGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutWaitGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutWaitGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalOutWaitGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutRepeatInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutRepeatInfo(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRepeatSet HDWF hdwf, unsigned int cRepeat
HDWF 
hdwf
unsigned int 
cRepeat
*/
// 4 (match no. 276)
			static int _FDwfDigitalOutRepeatSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutRepeatSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRepeatGet HDWF hdwf, unsigned int *pcRepeat
HDWF 
hdwf
unsigned int *
pcRepeat
*/
// 3 (match no. 277)
			static int _FDwfDigitalOutRepeatGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutRepeatGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRepeatStatus HDWF hdwf, unsigned int *pcRepeat
HDWF 
hdwf
unsigned int *
pcRepeat
*/
// 3 (match no. 278)
			static int _FDwfDigitalOutRepeatStatus(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatStatus called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned int p2 = it0[2].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutRepeatStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutTriggerSlopeSet HDWF hdwf, DwfTriggerSlope slope
HDWF 
hdwf
DwfTriggerSlope 
slope
*/
// 3 (match no. 279)
			static int _FDwfDigitalOutTriggerSlopeSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTriggerSlopeSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTriggerSlopeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfDigitalOutTriggerSlopeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutTriggerSlopeGet HDWF hdwf, DwfTriggerSlope *pslope
HDWF 
hdwf
DwfTriggerSlope *
pslope
*/
// 3 (match no. 280)
			static int _FDwfDigitalOutTriggerSlopeGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTriggerSlopeGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTriggerSlopeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfTriggerSlope p2 = it0[2].begin().value().get<DwfTriggerSlope>();

							int p0 = FDwfDigitalOutTriggerSlopeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRepeatTriggerSet HDWF hdwf, int fRepeatTrigger
HDWF 
hdwf
int 
fRepeatTrigger
*/
// 3 (match no. 281)
			static int _FDwfDigitalOutRepeatTriggerSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatTriggerSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatTriggerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalOutRepeatTriggerSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutRepeatTriggerGet HDWF hdwf, int *pfRepeatTrigger
HDWF 
hdwf
int *
pfRepeatTrigger
*/
// 3 (match no. 282)
			static int _FDwfDigitalOutRepeatTriggerGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutRepeatTriggerGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutRepeatTriggerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalOutRepeatTriggerGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutCount HDWF hdwf, int *pcChannel
HDWF 
hdwf
int *
pcChannel
*/
// 3 (match no. 283)
			static int _FDwfDigitalOutCount(json::iterator it)
			{
				cout << "	FDwfDigitalOutCount called." << endl;
				
				if (it.key() != "FDwfDigitalOutCount") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalOutCount(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutEnableSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutEnableSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalOutEnableSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutEnableGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutEnableGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalOutEnableGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutOutputInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutOutputInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutOutputInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalOutOutputInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutOutputSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutOutputSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutOutputSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutOutput p3 = it0[3].begin().value().get<DwfDigitalOutOutput>();

							int p0 = FDwfDigitalOutOutputSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutOutputGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutOutputGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutOutputGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutOutput p3 = it0[3].begin().value().get<DwfDigitalOutOutput>();

							int p0 = FDwfDigitalOutOutputGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutTypeInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutTypeInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutTypeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalOutTypeInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutTypeSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTypeSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTypeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutType p3 = it0[3].begin().value().get<DwfDigitalOutType>();

							int p0 = FDwfDigitalOutTypeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutTypeGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutTypeGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutTypeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutType p3 = it0[3].begin().value().get<DwfDigitalOutType>();

							int p0 = FDwfDigitalOutTypeGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutIdleInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutIdleInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutIdleInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalOutIdleInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutIdleSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutIdleSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutIdleSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutIdle p3 = it0[3].begin().value().get<DwfDigitalOutIdle>();

							int p0 = FDwfDigitalOutIdleSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutIdleGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutIdleGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutIdleGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							DwfDigitalOutIdle p3 = it0[3].begin().value().get<DwfDigitalOutIdle>();

							int p0 = FDwfDigitalOutIdleGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDividerInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutDividerInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutDividerInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDividerInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDividerInitSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutDividerInitSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutDividerInitSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDividerInitSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDividerInitGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutDividerInitGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutDividerInitGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDividerInitGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDividerSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutDividerSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutDividerSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDividerSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDividerGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutDividerGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutDividerGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDividerGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutCounterInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutCounterInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutCounterInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutCounterInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutCounterInitSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutCounterInitSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutCounterInitSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutCounterInitSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutCounterInitGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutCounterInitGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutCounterInitGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutCounterInitGet(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutCounterSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutCounterSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutCounterSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutCounterSet(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutCounterGet(json::iterator it)
			{
				cout << "	FDwfDigitalOutCounterGet called." << endl;
				
				if (it.key() != "FDwfDigitalOutCounterGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutCounterGet(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDataInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutDataInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutDataInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							unsigned int p3 = it0[3].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDataInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalOutDataSet(json::iterator it)
			{
				cout << "	FDwfDigitalOutDataSet called." << endl;
				
				if (it.key() != "FDwfDigitalOutDataSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<char> p3 = it0[3].begin().value().get<vector<char>>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalOutDataSet(p1,p2,p3.data(),p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartReset HDWF hdwf
HDWF 
hdwf
*/
// 5 (match no. 307)
			static int _FDwfDigitalUartReset(json::iterator it)
			{
				cout << "	FDwfDigitalUartReset called." << endl;
				
				if (it.key() != "FDwfDigitalUartReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalUartReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartRateSet HDWF hdwf, double hz
HDWF 
hdwf
double 
hz
*/
// 2 (match no. 308)
			static int _FDwfDigitalUartRateSet(json::iterator it)
			{
				cout << "	FDwfDigitalUartRateSet called." << endl;
				
				if (it.key() != "FDwfDigitalUartRateSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalUartRateSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartBitsSet HDWF hdwf, int cBits
HDWF 
hdwf
int 
cBits
*/
// 3 (match no. 309)
			static int _FDwfDigitalUartBitsSet(json::iterator it)
			{
				cout << "	FDwfDigitalUartBitsSet called." << endl;
				
				if (it.key() != "FDwfDigitalUartBitsSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalUartBitsSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartParitySet HDWF hdwf, int parity
HDWF 
hdwf
int 
parity
*/
// 3 (match no. 310)
			static int _FDwfDigitalUartParitySet(json::iterator it)
			{
				cout << "	FDwfDigitalUartParitySet called." << endl;
				
				if (it.key() != "FDwfDigitalUartParitySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalUartParitySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartStopSet HDWF hdwf, double cBit
HDWF 
hdwf
double 
cBit
*/
// 3 (match no. 311)
			static int _FDwfDigitalUartStopSet(json::iterator it)
			{
				cout << "	FDwfDigitalUartStopSet called." << endl;
				
				if (it.key() != "FDwfDigitalUartStopSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalUartStopSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartTxSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 312)
			static int _FDwfDigitalUartTxSet(json::iterator it)
			{
				cout << "	FDwfDigitalUartTxSet called." << endl;
				
				if (it.key() != "FDwfDigitalUartTxSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalUartTxSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalUartRxSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 313)
			static int _FDwfDigitalUartRxSet(json::iterator it)
			{
				cout << "	FDwfDigitalUartRxSet called." << endl;
				
				if (it.key() != "FDwfDigitalUartRxSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalUartRxSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalUartTx(json::iterator it)
			{
				cout << "	FDwfDigitalUartTx called." << endl;
				
				if (it.key() != "FDwfDigitalUartTx") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							char p2 = it0[2].begin().value().get<char>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalUartTx(p1,&p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalUartRx(json::iterator it)
			{
				cout << "	FDwfDigitalUartRx called." << endl;
				
				if (it.key() != "FDwfDigitalUartRx") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							char p2 = it0[2].begin().value().get<char>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalUartRx(p1,&p2,p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalSpiReset HDWF hdwf
HDWF 
hdwf
*/
// 6 (match no. 316)
			static int _FDwfDigitalSpiReset(json::iterator it)
			{
				cout << "	FDwfDigitalSpiReset called." << endl;
				
				if (it.key() != "FDwfDigitalSpiReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalSpiReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalSpiFrequencySet HDWF hdwf, double hz
HDWF 
hdwf
double 
hz
*/
// 2 (match no. 317)
			static int _FDwfDigitalSpiFrequencySet(json::iterator it)
			{
				cout << "	FDwfDigitalSpiFrequencySet called." << endl;
				
				if (it.key() != "FDwfDigitalSpiFrequencySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalSpiFrequencySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalSpiClockSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 318)
			static int _FDwfDigitalSpiClockSet(json::iterator it)
			{
				cout << "	FDwfDigitalSpiClockSet called." << endl;
				
				if (it.key() != "FDwfDigitalSpiClockSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalSpiClockSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiDataSet(json::iterator it)
			{
				cout << "	FDwfDigitalSpiDataSet called." << endl;
				
				if (it.key() != "FDwfDigitalSpiDataSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalSpiDataSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalSpiModeSet HDWF hdwf, int iMode
HDWF 
hdwf
int 
iMode
*/
// 4 (match no. 320)
			static int _FDwfDigitalSpiModeSet(json::iterator it)
			{
				cout << "	FDwfDigitalSpiModeSet called." << endl;
				
				if (it.key() != "FDwfDigitalSpiModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalSpiModeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalSpiOrderSet HDWF hdwf, int fMSBFirst
HDWF 
hdwf
int 
fMSBFirst
*/
// 3 (match no. 321)
			static int _FDwfDigitalSpiOrderSet(json::iterator it)
			{
				cout << "	FDwfDigitalSpiOrderSet called." << endl;
				
				if (it.key() != "FDwfDigitalSpiOrderSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalSpiOrderSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiSelect(json::iterator it)
			{
				cout << "	FDwfDigitalSpiSelect called." << endl;
				
				if (it.key() != "FDwfDigitalSpiSelect") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfDigitalSpiSelect(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWriteRead(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWriteRead called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWriteRead") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 8)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
							int p5 = it0[5].begin().value().get<int>();
							vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();
							int p7 = it0[7].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWriteRead(p1,p2,p3,p4.data(),p5,p6.data(),p7);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
							it0[7].begin().value() = p7;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWriteRead16(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWriteRead16 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWriteRead16") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 8)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
							int p5 = it0[5].begin().value().get<int>();
							vector<unsigned short> p6 = it0[6].begin().value().get<vector<unsigned short>>();
							int p7 = it0[7].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWriteRead16(p1,p2,p3,p4.data(),p5,p6.data(),p7);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
							it0[7].begin().value() = p7;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWriteRead32(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWriteRead32 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWriteRead32") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 8)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
							int p5 = it0[5].begin().value().get<int>();
							vector<unsigned int> p6 = it0[6].begin().value().get<vector<unsigned int>>();
							int p7 = it0[7].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWriteRead32(p1,p2,p3,p4.data(),p5,p6.data(),p7);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
							it0[7].begin().value() = p7;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiRead(json::iterator it)
			{
				cout << "	FDwfDigitalSpiRead called." << endl;
				
				if (it.key() != "FDwfDigitalSpiRead") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiRead(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiReadOne(json::iterator it)
			{
				cout << "	FDwfDigitalSpiReadOne called." << endl;
				
				if (it.key() != "FDwfDigitalSpiReadOne") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalSpiReadOne(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiRead16(json::iterator it)
			{
				cout << "	FDwfDigitalSpiRead16 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiRead16") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiRead16(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiRead32(json::iterator it)
			{
				cout << "	FDwfDigitalSpiRead32 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiRead32") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiRead32(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWrite(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWrite called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWrite") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned char> p4 = it0[4].begin().value().get<vector<unsigned char>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWrite(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWriteOne(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWriteOne called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWriteOne") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							unsigned int p4 = it0[4].begin().value().get<unsigned int>();

							int p0 = FDwfDigitalSpiWriteOne(p1,p2,p3,p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWrite16(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWrite16 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWrite16") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned short> p4 = it0[4].begin().value().get<vector<unsigned short>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWrite16(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalSpiWrite32(json::iterator it)
			{
				cout << "	FDwfDigitalSpiWrite32 called." << endl;
				
				if (it.key() != "FDwfDigitalSpiWrite32") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							vector<unsigned int> p4 = it0[4].begin().value().get<vector<unsigned int>>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalSpiWrite32(p1,p2,p3,p4.data(),p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cReset HDWF hdwf
HDWF 
hdwf
*/
// 6 (match no. 334)
			static int _FDwfDigitalI2cReset(json::iterator it)
			{
				cout << "	FDwfDigitalI2cReset called." << endl;
				
				if (it.key() != "FDwfDigitalI2cReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalI2cReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cClear HDWF hdwf, int *pfFree
HDWF 
hdwf
int *
pfFree
*/
// 2 (match no. 335)
			static int _FDwfDigitalI2cClear(json::iterator it)
			{
				cout << "	FDwfDigitalI2cClear called." << endl;
				
				if (it.key() != "FDwfDigitalI2cClear") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalI2cClear(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cStretchSet HDWF hdwf, int fEnable
HDWF 
hdwf
int 
fEnable
*/
// 3 (match no. 336)
			static int _FDwfDigitalI2cStretchSet(json::iterator it)
			{
				cout << "	FDwfDigitalI2cStretchSet called." << endl;
				
				if (it.key() != "FDwfDigitalI2cStretchSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalI2cStretchSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cRateSet HDWF hdwf, double hz
HDWF 
hdwf
double 
hz
*/
// 3 (match no. 337)
			static int _FDwfDigitalI2cRateSet(json::iterator it)
			{
				cout << "	FDwfDigitalI2cRateSet called." << endl;
				
				if (it.key() != "FDwfDigitalI2cRateSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalI2cRateSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cReadNakSet HDWF hdwf, int fNakLastReadByte
HDWF 
hdwf
int 
fNakLastReadByte
*/
// 3 (match no. 338)
			static int _FDwfDigitalI2cReadNakSet(json::iterator it)
			{
				cout << "	FDwfDigitalI2cReadNakSet called." << endl;
				
				if (it.key() != "FDwfDigitalI2cReadNakSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalI2cReadNakSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cSclSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 339)
			static int _FDwfDigitalI2cSclSet(json::iterator it)
			{
				cout << "	FDwfDigitalI2cSclSet called." << endl;
				
				if (it.key() != "FDwfDigitalI2cSclSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalI2cSclSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalI2cSdaSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 340)
			static int _FDwfDigitalI2cSdaSet(json::iterator it)
			{
				cout << "	FDwfDigitalI2cSdaSet called." << endl;
				
				if (it.key() != "FDwfDigitalI2cSdaSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalI2cSdaSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalI2cWriteRead(json::iterator it)
			{
				cout << "	FDwfDigitalI2cWriteRead called." << endl;
				
				if (it.key() != "FDwfDigitalI2cWriteRead") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 8)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned char p2 = it0[2].begin().value().get<unsigned char>();
							vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
							int p4 = it0[4].begin().value().get<int>();
							vector<unsigned char> p5 = it0[5].begin().value().get<vector<unsigned char>>();
							int p6 = it0[6].begin().value().get<int>();
							int p7 = it0[7].begin().value().get<int>();

							int p0 = FDwfDigitalI2cWriteRead(p1,p2,p3.data(),p4,p5.data(),p6,&p7);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
							it0[7].begin().value() = p7;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalI2cRead(json::iterator it)
			{
				cout << "	FDwfDigitalI2cRead called." << endl;
				
				if (it.key() != "FDwfDigitalI2cRead") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned char p2 = it0[2].begin().value().get<unsigned char>();
							vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalI2cRead(p1,p2,p3.data(),p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalI2cWrite(json::iterator it)
			{
				cout << "	FDwfDigitalI2cWrite called." << endl;
				
				if (it.key() != "FDwfDigitalI2cWrite") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned char p2 = it0[2].begin().value().get<unsigned char>();
							vector<unsigned char> p3 = it0[3].begin().value().get<vector<unsigned char>>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfDigitalI2cWrite(p1,p2,p3.data(),p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalI2cWriteOne(json::iterator it)
			{
				cout << "	FDwfDigitalI2cWriteOne called." << endl;
				
				if (it.key() != "FDwfDigitalI2cWriteOne") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							unsigned char p2 = it0[2].begin().value().get<unsigned char>();
							unsigned char p3 = it0[3].begin().value().get<unsigned char>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfDigitalI2cWriteOne(p1,p2,p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalCanReset HDWF hdwf
HDWF 
hdwf
*/
// 5 (match no. 345)
			static int _FDwfDigitalCanReset(json::iterator it)
			{
				cout << "	FDwfDigitalCanReset called." << endl;
				
				if (it.key() != "FDwfDigitalCanReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfDigitalCanReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalCanRateSet HDWF hdwf, double hz
HDWF 
hdwf
double 
hz
*/
// 2 (match no. 346)
			static int _FDwfDigitalCanRateSet(json::iterator it)
			{
				cout << "	FDwfDigitalCanRateSet called." << endl;
				
				if (it.key() != "FDwfDigitalCanRateSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfDigitalCanRateSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalCanPolaritySet HDWF hdwf, int fHigh
HDWF 
hdwf
int 
fHigh
*/
// 3 (match no. 347)
			static int _FDwfDigitalCanPolaritySet(json::iterator it)
			{
				cout << "	FDwfDigitalCanPolaritySet called." << endl;
				
				if (it.key() != "FDwfDigitalCanPolaritySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalCanPolaritySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalCanTxSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 348)
			static int _FDwfDigitalCanTxSet(json::iterator it)
			{
				cout << "	FDwfDigitalCanTxSet called." << endl;
				
				if (it.key() != "FDwfDigitalCanTxSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalCanTxSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalCanRxSet HDWF hdwf, int idxChannel
HDWF 
hdwf
int 
idxChannel
*/
// 3 (match no. 349)
			static int _FDwfDigitalCanRxSet(json::iterator it)
			{
				cout << "	FDwfDigitalCanRxSet called." << endl;
				
				if (it.key() != "FDwfDigitalCanRxSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalCanRxSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalCanTx(json::iterator it)
			{
				cout << "	FDwfDigitalCanTx called." << endl;
				
				if (it.key() != "FDwfDigitalCanTx") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 7)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();
							vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();

							int p0 = FDwfDigitalCanTx(p1,p2,p3,p4,p5,p6.data());

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfDigitalCanRx(json::iterator it)
			{
				cout << "	FDwfDigitalCanRx called." << endl;
				
				if (it.key() != "FDwfDigitalCanRx") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 9)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();
							vector<unsigned char> p6 = it0[6].begin().value().get<vector<unsigned char>>();
							int p7 = it0[7].begin().value().get<int>();
							int p8 = it0[8].begin().value().get<int>();

							int p0 = FDwfDigitalCanRx(p1,&p2,&p3,&p4,&p5,p6.data(),p7,&p8);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
							it0[6].begin().value() = p6;
							it0[7].begin().value() = p7;
							it0[8].begin().value() = p8;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceReset HDWF hdwf
HDWF 
hdwf
*/
// 9 (match no. 352)
			static int _FDwfAnalogImpedanceReset(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceReset called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogImpedanceReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceModeSet HDWF hdwf, int mode
HDWF 
hdwf
int 
mode
*/
// 2 (match no. 353)
			static int _FDwfAnalogImpedanceModeSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceModeSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceModeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogImpedanceModeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceModeGet HDWF hdwf, int *mode
HDWF 
hdwf
int *
mode
*/
// 3 (match no. 354)
			static int _FDwfAnalogImpedanceModeGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceModeGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceModeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogImpedanceModeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceReferenceSet HDWF hdwf, double ohms
HDWF 
hdwf
double 
ohms
*/
// 3 (match no. 355)
			static int _FDwfAnalogImpedanceReferenceSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceReferenceSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceReferenceSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceReferenceSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceReferenceGet HDWF hdwf, double *pohms
HDWF 
hdwf
double *
pohms
*/
// 3 (match no. 356)
			static int _FDwfAnalogImpedanceReferenceGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceReferenceGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceReferenceGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceReferenceGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceFrequencySet HDWF hdwf, double hz
HDWF 
hdwf
double 
hz
*/
// 3 (match no. 357)
			static int _FDwfAnalogImpedanceFrequencySet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceFrequencySet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceFrequencySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceFrequencySet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceFrequencyGet HDWF hdwf, double *phz
HDWF 
hdwf
double *
phz
*/
// 3 (match no. 358)
			static int _FDwfAnalogImpedanceFrequencyGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceFrequencyGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceFrequencyGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceFrequencyGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceAmplitudeSet HDWF hdwf, double volts
HDWF 
hdwf
double 
volts
*/
// 3 (match no. 359)
			static int _FDwfAnalogImpedanceAmplitudeSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceAmplitudeSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceAmplitudeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceAmplitudeSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceAmplitudeGet HDWF hdwf, double *pvolts
HDWF 
hdwf
double *
pvolts
*/
// 3 (match no. 360)
			static int _FDwfAnalogImpedanceAmplitudeGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceAmplitudeGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceAmplitudeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceAmplitudeGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceOffsetSet HDWF hdwf, double volts
HDWF 
hdwf
double 
volts
*/
// 3 (match no. 361)
			static int _FDwfAnalogImpedanceOffsetSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceOffsetSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceOffsetSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceOffsetSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceOffsetGet HDWF hdwf, double *pvolts
HDWF 
hdwf
double *
pvolts
*/
// 3 (match no. 362)
			static int _FDwfAnalogImpedanceOffsetGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceOffsetGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceOffsetGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceOffsetGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceProbeSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceProbeSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceProbeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceProbeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceProbeGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceProbeGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceProbeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceProbeGet(p1,&p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedancePeriodSet HDWF hdwf, int cMinPeriods
HDWF 
hdwf
int 
cMinPeriods
*/
// 4 (match no. 365)
			static int _FDwfAnalogImpedancePeriodSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedancePeriodSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedancePeriodSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogImpedancePeriodSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedancePeriodGet HDWF hdwf, int *cMinPeriods
HDWF 
hdwf
int *
cMinPeriods
*/
// 3 (match no. 366)
			static int _FDwfAnalogImpedancePeriodGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedancePeriodGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedancePeriodGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogImpedancePeriodGet(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceCompReset HDWF hdwf
HDWF 
hdwf
*/
// 3 (match no. 367)
			static int _FDwfAnalogImpedanceCompReset(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceCompReset called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceCompReset") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 2)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();

							int p0 = FDwfAnalogImpedanceCompReset(p1);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceCompSet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceCompSet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceCompSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceCompSet(p1,p2,p3,p4,p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceCompGet(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceCompGet called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceCompGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							double p2 = it0[2].begin().value().get<double>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();
							double p5 = it0[5].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceCompGet(p1,&p2,&p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceConfigure HDWF hdwf, int fStart
HDWF 
hdwf
int 
fStart
*/
// 6 (match no. 370)
			static int _FDwfAnalogImpedanceConfigure(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceConfigure called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceConfigure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogImpedanceConfigure(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogImpedanceStatus HDWF hdwf, DwfState *psts
HDWF 
hdwf
DwfState *
psts
*/
// 3 (match no. 371)
			static int _FDwfAnalogImpedanceStatus(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceStatus called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfState p2 = it0[2].begin().value().get<DwfState>();

							int p0 = FDwfAnalogImpedanceStatus(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceStatusInput(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceStatusInput called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceStatusInput") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceStatusInput(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogImpedanceStatusMeasure(json::iterator it)
			{
				cout << "	FDwfAnalogImpedanceStatusMeasure called." << endl;
				
				if (it.key() != "FDwfAnalogImpedanceStatusMeasure") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							DwfAnalogImpedance p2 = it0[2].begin().value().get<DwfAnalogImpedance>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogImpedanceStatusMeasure(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInMixedSet HDWF hdwf, int fEnable
HDWF 
hdwf
int 
fEnable
*/
// 4 (match no. 374)
			static int _FDwfDigitalInMixedSet(json::iterator it)
			{
				cout << "	FDwfDigitalInMixedSet called." << endl;
				
				if (it.key() != "FDwfDigitalInMixedSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInMixedSet(p1,p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfAnalogInTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF 
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 375)
			static int _FDwfAnalogInTriggerSourceInfo(json::iterator it)
			{
				cout << "	FDwfAnalogInTriggerSourceInfo called." << endl;
				
				if (it.key() != "FDwfAnalogInTriggerSourceInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfAnalogInTriggerSourceInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutTriggerSourceInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutTriggerSourceInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutTriggerSourceInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutTriggerSourceInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalInTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF 
hdwf
int *
pfstrigsrc
*/
// 4 (match no. 377)
			static int _FDwfDigitalInTriggerSourceInfo(json::iterator it)
			{
				cout << "	FDwfDigitalInTriggerSourceInfo called." << endl;
				
				if (it.key() != "FDwfDigitalInTriggerSourceInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalInTriggerSourceInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfDigitalOutTriggerSourceInfo HDWF hdwf, int *pfstrigsrc
HDWF 
hdwf
int *
pfstrigsrc
*/
// 3 (match no. 378)
			static int _FDwfDigitalOutTriggerSourceInfo(json::iterator it)
			{
				cout << "	FDwfDigitalOutTriggerSourceInfo called." << endl;
				
				if (it.key() != "FDwfDigitalOutTriggerSourceInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfDigitalOutTriggerSourceInfo(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutEnableSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutEnableSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutEnableSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutEnableSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutEnableGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutEnableGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutEnableGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutEnableGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFunctionInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutFunctionInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutFunctionInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();

							int p0 = FDwfAnalogOutFunctionInfo(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFunctionSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutFunctionSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutFunctionSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							FUNC p3 = it0[3].begin().value().get<FUNC>();

							int p0 = FDwfAnalogOutFunctionSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFunctionGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutFunctionGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutFunctionGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							FUNC p3 = it0[3].begin().value().get<FUNC>();

							int p0 = FDwfAnalogOutFunctionGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFrequencyInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutFrequencyInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutFrequencyInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutFrequencyInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFrequencySet(json::iterator it)
			{
				cout << "	FDwfAnalogOutFrequencySet called." << endl;
				
				if (it.key() != "FDwfAnalogOutFrequencySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutFrequencySet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutFrequencyGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutFrequencyGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutFrequencyGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutFrequencyGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutAmplitudeInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutAmplitudeInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutAmplitudeInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutAmplitudeInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutAmplitudeSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutAmplitudeSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutAmplitudeSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutAmplitudeSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutAmplitudeGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutAmplitudeGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutAmplitudeGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutAmplitudeGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutOffsetInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutOffsetInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutOffsetInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutOffsetInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutOffsetSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutOffsetSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutOffsetSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutOffsetSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutOffsetGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutOffsetGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutOffsetGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutOffsetGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutSymmetryInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutSymmetryInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutSymmetryInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutSymmetryInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutSymmetrySet(json::iterator it)
			{
				cout << "	FDwfAnalogOutSymmetrySet called." << endl;
				
				if (it.key() != "FDwfAnalogOutSymmetrySet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutSymmetrySet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutSymmetryGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutSymmetryGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutSymmetryGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutSymmetryGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutPhaseInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutPhaseInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutPhaseInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();
							double p4 = it0[4].begin().value().get<double>();

							int p0 = FDwfAnalogOutPhaseInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutPhaseSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutPhaseSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutPhaseSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutPhaseSet(p1,p2,p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutPhaseGet(json::iterator it)
			{
				cout << "	FDwfAnalogOutPhaseGet called." << endl;
				
				if (it.key() != "FDwfAnalogOutPhaseGet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 4)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							double p3 = it0[3].begin().value().get<double>();

							int p0 = FDwfAnalogOutPhaseGet(p1,p2,&p3);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutDataInfo(json::iterator it)
			{
				cout << "	FDwfAnalogOutDataInfo called." << endl;
				
				if (it.key() != "FDwfAnalogOutDataInfo") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutDataInfo(p1,p2,&p3,&p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutDataSet(json::iterator it)
			{
				cout << "	FDwfAnalogOutDataSet called." << endl;
				
				if (it.key() != "FDwfAnalogOutDataSet") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutDataSet(p1,p2,p3.data(),p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutPlayStatus(json::iterator it)
			{
				cout << "	FDwfAnalogOutPlayStatus called." << endl;
				
				if (it.key() != "FDwfAnalogOutPlayStatus") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 6)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							int p3 = it0[3].begin().value().get<int>();
							int p4 = it0[4].begin().value().get<int>();
							int p5 = it0[5].begin().value().get<int>();

							int p0 = FDwfAnalogOutPlayStatus(p1,p2,&p3,&p4,&p5);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
							it0[5].begin().value() = p5;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
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
			static int _FDwfAnalogOutPlayData(json::iterator it)
			{
				cout << "	FDwfAnalogOutPlayData called." << endl;
				
				if (it.key() != "FDwfAnalogOutPlayData") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 5)
					{
						try
						{
							json::iterator it0 = params->begin();
							HDWF p1 = it0[1].begin().value().get<HDWF>();
							int p2 = it0[2].begin().value().get<int>();
							vector<double> p3 = it0[3].begin().value().get<vector<double>>();
							int p4 = it0[4].begin().value().get<int>();

							int p0 = FDwfAnalogOutPlayData(p1,p2,p3.data(),p4);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
							it0[3].begin().value() = p3;
							it0[4].begin().value() = p4;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumAnalogInChannels int idxDevice, int *pnChannels
int 
idxDevice
int *
pnChannels
*/
// 5 (match no. 403)
			static int _FDwfEnumAnalogInChannels(json::iterator it)
			{
				cout << "	FDwfEnumAnalogInChannels called." << endl;
				
				if (it.key() != "FDwfEnumAnalogInChannels") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnumAnalogInChannels(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumAnalogInBufferSize int idxDevice, int *pnBufferSize
int 
idxDevice
int *
pnBufferSize
*/
// 3 (match no. 404)
			static int _FDwfEnumAnalogInBufferSize(json::iterator it)
			{
				cout << "	FDwfEnumAnalogInBufferSize called." << endl;
				
				if (it.key() != "FDwfEnumAnalogInBufferSize") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnumAnalogInBufferSize(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumAnalogInBits int idxDevice, int *pnBits
int 
idxDevice
int *
pnBits
*/
// 3 (match no. 405)
			static int _FDwfEnumAnalogInBits(json::iterator it)
			{
				cout << "	FDwfEnumAnalogInBits called." << endl;
				
				if (it.key() != "FDwfEnumAnalogInBits") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							int p2 = it0[2].begin().value().get<int>();

							int p0 = FDwfEnumAnalogInBits(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}


/*
FDwfEnumAnalogInFrequency int idxDevice, double *phzFrequency
int 
idxDevice
double *
phzFrequency
*/
// 3 (match no. 406)
			static int _FDwfEnumAnalogInFrequency(json::iterator it)
			{
				cout << "	FDwfEnumAnalogInFrequency called." << endl;
				
				if (it.key() != "FDwfEnumAnalogInFrequency") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == 3)
					{
						try
						{
							json::iterator it0 = params->begin();
							int p1 = it0[1].begin().value().get<int>();
							double p2 = it0[2].begin().value().get<double>();

							int p0 = FDwfEnumAnalogInFrequency(p1,&p2);

							it0 = params->begin();
							it0[0].begin().value() = p0;
							it0[1].begin().value() = p1;
							it0[2].begin().value() = p2;
						}			
						catch (json::exception& e)
						{
							// output exception information
							std::cout << "message: " << e.what() << '\n'
									  << "exception id: " << e.id << std::endl;
						}
						catch (...)
						{
							cout << "Exception occur." << endl;
						}
					}
				}

				return 1;
			}
			const map<string, FARPROCm> fn_map =
			{
				{ "FDwfGetLastError", (FARPROCm)&_FDwfGetLastError },
				{ "FDwfGetLastErrorMsg", (FARPROCm)&_FDwfGetLastErrorMsg },
				{ "FDwfGetVersion", (FARPROCm)&_FDwfGetVersion },
				{ "FDwfParamSet", (FARPROCm)&_FDwfParamSet },
				{ "FDwfParamGet", (FARPROCm)&_FDwfParamGet },
				{ "FDwfEnum", (FARPROCm)&_FDwfEnum },
				{ "FDwfEnumDeviceType", (FARPROCm)&_FDwfEnumDeviceType },
				{ "FDwfEnumDeviceIsOpened", (FARPROCm)&_FDwfEnumDeviceIsOpened },
				{ "FDwfEnumUserName", (FARPROCm)&_FDwfEnumUserName },
				{ "FDwfEnumDeviceName", (FARPROCm)&_FDwfEnumDeviceName },
				{ "FDwfEnumSN", (FARPROCm)&_FDwfEnumSN },
				{ "FDwfEnumConfig", (FARPROCm)&_FDwfEnumConfig },
				{ "FDwfEnumConfigInfo", (FARPROCm)&_FDwfEnumConfigInfo },
				{ "FDwfDeviceOpen", (FARPROCm)&_FDwfDeviceOpen },
				{ "FDwfDeviceConfigOpen", (FARPROCm)&_FDwfDeviceConfigOpen },
				{ "FDwfDeviceClose", (FARPROCm)&_FDwfDeviceClose },
				{ "FDwfDeviceCloseAll", (FARPROCm)&_FDwfDeviceCloseAll },
				{ "FDwfDeviceAutoConfigureSet", (FARPROCm)&_FDwfDeviceAutoConfigureSet },
				{ "FDwfDeviceAutoConfigureGet", (FARPROCm)&_FDwfDeviceAutoConfigureGet },
				{ "FDwfDeviceReset", (FARPROCm)&_FDwfDeviceReset },
				{ "FDwfDeviceEnableSet", (FARPROCm)&_FDwfDeviceEnableSet },
				{ "FDwfDeviceTriggerInfo", (FARPROCm)&_FDwfDeviceTriggerInfo },
				{ "FDwfDeviceTriggerSet", (FARPROCm)&_FDwfDeviceTriggerSet },
				{ "FDwfDeviceTriggerGet", (FARPROCm)&_FDwfDeviceTriggerGet },
				{ "FDwfDeviceTriggerPC", (FARPROCm)&_FDwfDeviceTriggerPC },
				{ "FDwfDeviceTriggerSlopeInfo", (FARPROCm)&_FDwfDeviceTriggerSlopeInfo },
				{ "FDwfDeviceParamSet", (FARPROCm)&_FDwfDeviceParamSet },
				{ "FDwfDeviceParamGet", (FARPROCm)&_FDwfDeviceParamGet },
				{ "FDwfAnalogInReset", (FARPROCm)&_FDwfAnalogInReset },
				{ "FDwfAnalogInConfigure", (FARPROCm)&_FDwfAnalogInConfigure },
				{ "FDwfAnalogInTriggerForce", (FARPROCm)&_FDwfAnalogInTriggerForce },
				{ "FDwfAnalogInStatus", (FARPROCm)&_FDwfAnalogInStatus },
				{ "FDwfAnalogInStatusSamplesLeft", (FARPROCm)&_FDwfAnalogInStatusSamplesLeft },
				{ "FDwfAnalogInStatusSamplesValid", (FARPROCm)&_FDwfAnalogInStatusSamplesValid },
				{ "FDwfAnalogInStatusIndexWrite", (FARPROCm)&_FDwfAnalogInStatusIndexWrite },
				{ "FDwfAnalogInStatusAutoTriggered", (FARPROCm)&_FDwfAnalogInStatusAutoTriggered },
				{ "FDwfAnalogInStatusData", (FARPROCm)&_FDwfAnalogInStatusData },
				{ "FDwfAnalogInStatusData2", (FARPROCm)&_FDwfAnalogInStatusData2 },
				{ "FDwfAnalogInStatusData16", (FARPROCm)&_FDwfAnalogInStatusData16 },
				{ "FDwfAnalogInStatusNoise", (FARPROCm)&_FDwfAnalogInStatusNoise },
				{ "FDwfAnalogInStatusNoise2", (FARPROCm)&_FDwfAnalogInStatusNoise2 },
				{ "FDwfAnalogInStatusSample", (FARPROCm)&_FDwfAnalogInStatusSample },
				{ "FDwfAnalogInStatusRecord", (FARPROCm)&_FDwfAnalogInStatusRecord },
				{ "FDwfAnalogInRecordLengthSet", (FARPROCm)&_FDwfAnalogInRecordLengthSet },
				{ "FDwfAnalogInRecordLengthGet", (FARPROCm)&_FDwfAnalogInRecordLengthGet },
				{ "FDwfAnalogInFrequencyInfo", (FARPROCm)&_FDwfAnalogInFrequencyInfo },
				{ "FDwfAnalogInFrequencySet", (FARPROCm)&_FDwfAnalogInFrequencySet },
				{ "FDwfAnalogInFrequencyGet", (FARPROCm)&_FDwfAnalogInFrequencyGet },
				{ "FDwfAnalogInBitsInfo", (FARPROCm)&_FDwfAnalogInBitsInfo },
				{ "FDwfAnalogInBufferSizeInfo", (FARPROCm)&_FDwfAnalogInBufferSizeInfo },
				{ "FDwfAnalogInBufferSizeSet", (FARPROCm)&_FDwfAnalogInBufferSizeSet },
				{ "FDwfAnalogInBufferSizeGet", (FARPROCm)&_FDwfAnalogInBufferSizeGet },
				{ "FDwfAnalogInNoiseSizeInfo", (FARPROCm)&_FDwfAnalogInNoiseSizeInfo },
				{ "FDwfAnalogInNoiseSizeSet", (FARPROCm)&_FDwfAnalogInNoiseSizeSet },
				{ "FDwfAnalogInNoiseSizeGet", (FARPROCm)&_FDwfAnalogInNoiseSizeGet },
				{ "FDwfAnalogInAcquisitionModeInfo", (FARPROCm)&_FDwfAnalogInAcquisitionModeInfo },
				{ "FDwfAnalogInAcquisitionModeSet", (FARPROCm)&_FDwfAnalogInAcquisitionModeSet },
				{ "FDwfAnalogInAcquisitionModeGet", (FARPROCm)&_FDwfAnalogInAcquisitionModeGet },
				{ "FDwfAnalogInChannelCount", (FARPROCm)&_FDwfAnalogInChannelCount },
				{ "FDwfAnalogInChannelEnableSet", (FARPROCm)&_FDwfAnalogInChannelEnableSet },
				{ "FDwfAnalogInChannelEnableGet", (FARPROCm)&_FDwfAnalogInChannelEnableGet },
				{ "FDwfAnalogInChannelFilterInfo", (FARPROCm)&_FDwfAnalogInChannelFilterInfo },
				{ "FDwfAnalogInChannelFilterSet", (FARPROCm)&_FDwfAnalogInChannelFilterSet },
				{ "FDwfAnalogInChannelFilterGet", (FARPROCm)&_FDwfAnalogInChannelFilterGet },
				{ "FDwfAnalogInChannelRangeInfo", (FARPROCm)&_FDwfAnalogInChannelRangeInfo },
				{ "FDwfAnalogInChannelRangeSteps", (FARPROCm)&_FDwfAnalogInChannelRangeSteps },
				{ "FDwfAnalogInChannelRangeSet", (FARPROCm)&_FDwfAnalogInChannelRangeSet },
				{ "FDwfAnalogInChannelRangeGet", (FARPROCm)&_FDwfAnalogInChannelRangeGet },
				{ "FDwfAnalogInChannelOffsetInfo", (FARPROCm)&_FDwfAnalogInChannelOffsetInfo },
				{ "FDwfAnalogInChannelOffsetSet", (FARPROCm)&_FDwfAnalogInChannelOffsetSet },
				{ "FDwfAnalogInChannelOffsetGet", (FARPROCm)&_FDwfAnalogInChannelOffsetGet },
				{ "FDwfAnalogInChannelAttenuationSet", (FARPROCm)&_FDwfAnalogInChannelAttenuationSet },
				{ "FDwfAnalogInChannelAttenuationGet", (FARPROCm)&_FDwfAnalogInChannelAttenuationGet },
				{ "FDwfAnalogInTriggerSourceSet", (FARPROCm)&_FDwfAnalogInTriggerSourceSet },
				{ "FDwfAnalogInTriggerSourceGet", (FARPROCm)&_FDwfAnalogInTriggerSourceGet },
				{ "FDwfAnalogInTriggerPositionInfo", (FARPROCm)&_FDwfAnalogInTriggerPositionInfo },
				{ "FDwfAnalogInTriggerPositionSet", (FARPROCm)&_FDwfAnalogInTriggerPositionSet },
				{ "FDwfAnalogInTriggerPositionGet", (FARPROCm)&_FDwfAnalogInTriggerPositionGet },
				{ "FDwfAnalogInTriggerPositionStatus", (FARPROCm)&_FDwfAnalogInTriggerPositionStatus },
				{ "FDwfAnalogInTriggerAutoTimeoutInfo", (FARPROCm)&_FDwfAnalogInTriggerAutoTimeoutInfo },
				{ "FDwfAnalogInTriggerAutoTimeoutSet", (FARPROCm)&_FDwfAnalogInTriggerAutoTimeoutSet },
				{ "FDwfAnalogInTriggerAutoTimeoutGet", (FARPROCm)&_FDwfAnalogInTriggerAutoTimeoutGet },
				{ "FDwfAnalogInTriggerHoldOffInfo", (FARPROCm)&_FDwfAnalogInTriggerHoldOffInfo },
				{ "FDwfAnalogInTriggerHoldOffSet", (FARPROCm)&_FDwfAnalogInTriggerHoldOffSet },
				{ "FDwfAnalogInTriggerHoldOffGet", (FARPROCm)&_FDwfAnalogInTriggerHoldOffGet },
				{ "FDwfAnalogInTriggerTypeInfo", (FARPROCm)&_FDwfAnalogInTriggerTypeInfo },
				{ "FDwfAnalogInTriggerTypeSet", (FARPROCm)&_FDwfAnalogInTriggerTypeSet },
				{ "FDwfAnalogInTriggerTypeGet", (FARPROCm)&_FDwfAnalogInTriggerTypeGet },
				{ "FDwfAnalogInTriggerChannelInfo", (FARPROCm)&_FDwfAnalogInTriggerChannelInfo },
				{ "FDwfAnalogInTriggerChannelSet", (FARPROCm)&_FDwfAnalogInTriggerChannelSet },
				{ "FDwfAnalogInTriggerChannelGet", (FARPROCm)&_FDwfAnalogInTriggerChannelGet },
				{ "FDwfAnalogInTriggerFilterInfo", (FARPROCm)&_FDwfAnalogInTriggerFilterInfo },
				{ "FDwfAnalogInTriggerFilterSet", (FARPROCm)&_FDwfAnalogInTriggerFilterSet },
				{ "FDwfAnalogInTriggerFilterGet", (FARPROCm)&_FDwfAnalogInTriggerFilterGet },
				{ "FDwfAnalogInTriggerLevelInfo", (FARPROCm)&_FDwfAnalogInTriggerLevelInfo },
				{ "FDwfAnalogInTriggerLevelSet", (FARPROCm)&_FDwfAnalogInTriggerLevelSet },
				{ "FDwfAnalogInTriggerLevelGet", (FARPROCm)&_FDwfAnalogInTriggerLevelGet },
				{ "FDwfAnalogInTriggerHysteresisInfo", (FARPROCm)&_FDwfAnalogInTriggerHysteresisInfo },
				{ "FDwfAnalogInTriggerHysteresisSet", (FARPROCm)&_FDwfAnalogInTriggerHysteresisSet },
				{ "FDwfAnalogInTriggerHysteresisGet", (FARPROCm)&_FDwfAnalogInTriggerHysteresisGet },
				{ "FDwfAnalogInTriggerConditionInfo", (FARPROCm)&_FDwfAnalogInTriggerConditionInfo },
				{ "FDwfAnalogInTriggerConditionSet", (FARPROCm)&_FDwfAnalogInTriggerConditionSet },
				{ "FDwfAnalogInTriggerConditionGet", (FARPROCm)&_FDwfAnalogInTriggerConditionGet },
				{ "FDwfAnalogInTriggerLengthInfo", (FARPROCm)&_FDwfAnalogInTriggerLengthInfo },
				{ "FDwfAnalogInTriggerLengthSet", (FARPROCm)&_FDwfAnalogInTriggerLengthSet },
				{ "FDwfAnalogInTriggerLengthGet", (FARPROCm)&_FDwfAnalogInTriggerLengthGet },
				{ "FDwfAnalogInTriggerLengthConditionInfo", (FARPROCm)&_FDwfAnalogInTriggerLengthConditionInfo },
				{ "FDwfAnalogInTriggerLengthConditionSet", (FARPROCm)&_FDwfAnalogInTriggerLengthConditionSet },
				{ "FDwfAnalogInTriggerLengthConditionGet", (FARPROCm)&_FDwfAnalogInTriggerLengthConditionGet },
				{ "FDwfAnalogInSamplingSourceSet", (FARPROCm)&_FDwfAnalogInSamplingSourceSet },
				{ "FDwfAnalogInSamplingSourceGet", (FARPROCm)&_FDwfAnalogInSamplingSourceGet },
				{ "FDwfAnalogInSamplingSlopeSet", (FARPROCm)&_FDwfAnalogInSamplingSlopeSet },
				{ "FDwfAnalogInSamplingSlopeGet", (FARPROCm)&_FDwfAnalogInSamplingSlopeGet },
				{ "FDwfAnalogInSamplingDelaySet", (FARPROCm)&_FDwfAnalogInSamplingDelaySet },
				{ "FDwfAnalogInSamplingDelayGet", (FARPROCm)&_FDwfAnalogInSamplingDelayGet },
				{ "FDwfAnalogOutCount", (FARPROCm)&_FDwfAnalogOutCount },
				{ "FDwfAnalogOutMasterSet", (FARPROCm)&_FDwfAnalogOutMasterSet },
				{ "FDwfAnalogOutMasterGet", (FARPROCm)&_FDwfAnalogOutMasterGet },
				{ "FDwfAnalogOutTriggerSourceSet", (FARPROCm)&_FDwfAnalogOutTriggerSourceSet },
				{ "FDwfAnalogOutTriggerSourceGet", (FARPROCm)&_FDwfAnalogOutTriggerSourceGet },
				{ "FDwfAnalogOutTriggerSlopeSet", (FARPROCm)&_FDwfAnalogOutTriggerSlopeSet },
				{ "FDwfAnalogOutTriggerSlopeGet", (FARPROCm)&_FDwfAnalogOutTriggerSlopeGet },
				{ "FDwfAnalogOutRunInfo", (FARPROCm)&_FDwfAnalogOutRunInfo },
				{ "FDwfAnalogOutRunSet", (FARPROCm)&_FDwfAnalogOutRunSet },
				{ "FDwfAnalogOutRunGet", (FARPROCm)&_FDwfAnalogOutRunGet },
				{ "FDwfAnalogOutRunStatus", (FARPROCm)&_FDwfAnalogOutRunStatus },
				{ "FDwfAnalogOutWaitInfo", (FARPROCm)&_FDwfAnalogOutWaitInfo },
				{ "FDwfAnalogOutWaitSet", (FARPROCm)&_FDwfAnalogOutWaitSet },
				{ "FDwfAnalogOutWaitGet", (FARPROCm)&_FDwfAnalogOutWaitGet },
				{ "FDwfAnalogOutRepeatInfo", (FARPROCm)&_FDwfAnalogOutRepeatInfo },
				{ "FDwfAnalogOutRepeatSet", (FARPROCm)&_FDwfAnalogOutRepeatSet },
				{ "FDwfAnalogOutRepeatGet", (FARPROCm)&_FDwfAnalogOutRepeatGet },
				{ "FDwfAnalogOutRepeatStatus", (FARPROCm)&_FDwfAnalogOutRepeatStatus },
				{ "FDwfAnalogOutRepeatTriggerSet", (FARPROCm)&_FDwfAnalogOutRepeatTriggerSet },
				{ "FDwfAnalogOutRepeatTriggerGet", (FARPROCm)&_FDwfAnalogOutRepeatTriggerGet },
				{ "FDwfAnalogOutLimitationInfo", (FARPROCm)&_FDwfAnalogOutLimitationInfo },
				{ "FDwfAnalogOutLimitationSet", (FARPROCm)&_FDwfAnalogOutLimitationSet },
				{ "FDwfAnalogOutLimitationGet", (FARPROCm)&_FDwfAnalogOutLimitationGet },
				{ "FDwfAnalogOutModeSet", (FARPROCm)&_FDwfAnalogOutModeSet },
				{ "FDwfAnalogOutModeGet", (FARPROCm)&_FDwfAnalogOutModeGet },
				{ "FDwfAnalogOutIdleInfo", (FARPROCm)&_FDwfAnalogOutIdleInfo },
				{ "FDwfAnalogOutIdleSet", (FARPROCm)&_FDwfAnalogOutIdleSet },
				{ "FDwfAnalogOutIdleGet", (FARPROCm)&_FDwfAnalogOutIdleGet },
				{ "FDwfAnalogOutNodeInfo", (FARPROCm)&_FDwfAnalogOutNodeInfo },
				{ "FDwfAnalogOutNodeEnableSet", (FARPROCm)&_FDwfAnalogOutNodeEnableSet },
				{ "FDwfAnalogOutNodeEnableGet", (FARPROCm)&_FDwfAnalogOutNodeEnableGet },
				{ "FDwfAnalogOutNodeFunctionInfo", (FARPROCm)&_FDwfAnalogOutNodeFunctionInfo },
				{ "FDwfAnalogOutNodeFunctionSet", (FARPROCm)&_FDwfAnalogOutNodeFunctionSet },
				{ "FDwfAnalogOutNodeFunctionGet", (FARPROCm)&_FDwfAnalogOutNodeFunctionGet },
				{ "FDwfAnalogOutNodeFrequencyInfo", (FARPROCm)&_FDwfAnalogOutNodeFrequencyInfo },
				{ "FDwfAnalogOutNodeFrequencySet", (FARPROCm)&_FDwfAnalogOutNodeFrequencySet },
				{ "FDwfAnalogOutNodeFrequencyGet", (FARPROCm)&_FDwfAnalogOutNodeFrequencyGet },
				{ "FDwfAnalogOutNodeAmplitudeInfo", (FARPROCm)&_FDwfAnalogOutNodeAmplitudeInfo },
				{ "FDwfAnalogOutNodeAmplitudeSet", (FARPROCm)&_FDwfAnalogOutNodeAmplitudeSet },
				{ "FDwfAnalogOutNodeAmplitudeGet", (FARPROCm)&_FDwfAnalogOutNodeAmplitudeGet },
				{ "FDwfAnalogOutNodeOffsetInfo", (FARPROCm)&_FDwfAnalogOutNodeOffsetInfo },
				{ "FDwfAnalogOutNodeOffsetSet", (FARPROCm)&_FDwfAnalogOutNodeOffsetSet },
				{ "FDwfAnalogOutNodeOffsetGet", (FARPROCm)&_FDwfAnalogOutNodeOffsetGet },
				{ "FDwfAnalogOutNodeSymmetryInfo", (FARPROCm)&_FDwfAnalogOutNodeSymmetryInfo },
				{ "FDwfAnalogOutNodeSymmetrySet", (FARPROCm)&_FDwfAnalogOutNodeSymmetrySet },
				{ "FDwfAnalogOutNodeSymmetryGet", (FARPROCm)&_FDwfAnalogOutNodeSymmetryGet },
				{ "FDwfAnalogOutNodePhaseInfo", (FARPROCm)&_FDwfAnalogOutNodePhaseInfo },
				{ "FDwfAnalogOutNodePhaseSet", (FARPROCm)&_FDwfAnalogOutNodePhaseSet },
				{ "FDwfAnalogOutNodePhaseGet", (FARPROCm)&_FDwfAnalogOutNodePhaseGet },
				{ "FDwfAnalogOutNodeDataInfo", (FARPROCm)&_FDwfAnalogOutNodeDataInfo },
				{ "FDwfAnalogOutNodeDataSet", (FARPROCm)&_FDwfAnalogOutNodeDataSet },
				{ "FDwfAnalogOutCustomAMFMEnableSet", (FARPROCm)&_FDwfAnalogOutCustomAMFMEnableSet },
				{ "FDwfAnalogOutCustomAMFMEnableGet", (FARPROCm)&_FDwfAnalogOutCustomAMFMEnableGet },
				{ "FDwfAnalogOutReset", (FARPROCm)&_FDwfAnalogOutReset },
				{ "FDwfAnalogOutConfigure", (FARPROCm)&_FDwfAnalogOutConfigure },
				{ "FDwfAnalogOutStatus", (FARPROCm)&_FDwfAnalogOutStatus },
				{ "FDwfAnalogOutNodePlayStatus", (FARPROCm)&_FDwfAnalogOutNodePlayStatus },
				{ "FDwfAnalogOutNodePlayData", (FARPROCm)&_FDwfAnalogOutNodePlayData },
				{ "FDwfAnalogIOReset", (FARPROCm)&_FDwfAnalogIOReset },
				{ "FDwfAnalogIOConfigure", (FARPROCm)&_FDwfAnalogIOConfigure },
				{ "FDwfAnalogIOStatus", (FARPROCm)&_FDwfAnalogIOStatus },
				{ "FDwfAnalogIOEnableInfo", (FARPROCm)&_FDwfAnalogIOEnableInfo },
				{ "FDwfAnalogIOEnableSet", (FARPROCm)&_FDwfAnalogIOEnableSet },
				{ "FDwfAnalogIOEnableGet", (FARPROCm)&_FDwfAnalogIOEnableGet },
				{ "FDwfAnalogIOEnableStatus", (FARPROCm)&_FDwfAnalogIOEnableStatus },
				{ "FDwfAnalogIOChannelCount", (FARPROCm)&_FDwfAnalogIOChannelCount },
				{ "FDwfAnalogIOChannelName", (FARPROCm)&_FDwfAnalogIOChannelName },
				{ "FDwfAnalogIOChannelInfo", (FARPROCm)&_FDwfAnalogIOChannelInfo },
				{ "FDwfAnalogIOChannelNodeName", (FARPROCm)&_FDwfAnalogIOChannelNodeName },
				{ "FDwfAnalogIOChannelNodeInfo", (FARPROCm)&_FDwfAnalogIOChannelNodeInfo },
				{ "FDwfAnalogIOChannelNodeSetInfo", (FARPROCm)&_FDwfAnalogIOChannelNodeSetInfo },
				{ "FDwfAnalogIOChannelNodeSet", (FARPROCm)&_FDwfAnalogIOChannelNodeSet },
				{ "FDwfAnalogIOChannelNodeGet", (FARPROCm)&_FDwfAnalogIOChannelNodeGet },
				{ "FDwfAnalogIOChannelNodeStatusInfo", (FARPROCm)&_FDwfAnalogIOChannelNodeStatusInfo },
				{ "FDwfAnalogIOChannelNodeStatus", (FARPROCm)&_FDwfAnalogIOChannelNodeStatus },
				{ "FDwfDigitalIOReset", (FARPROCm)&_FDwfDigitalIOReset },
				{ "FDwfDigitalIOConfigure", (FARPROCm)&_FDwfDigitalIOConfigure },
				{ "FDwfDigitalIOStatus", (FARPROCm)&_FDwfDigitalIOStatus },
				{ "FDwfDigitalIOOutputEnableInfo", (FARPROCm)&_FDwfDigitalIOOutputEnableInfo },
				{ "FDwfDigitalIOOutputEnableSet", (FARPROCm)&_FDwfDigitalIOOutputEnableSet },
				{ "FDwfDigitalIOOutputEnableGet", (FARPROCm)&_FDwfDigitalIOOutputEnableGet },
				{ "FDwfDigitalIOOutputInfo", (FARPROCm)&_FDwfDigitalIOOutputInfo },
				{ "FDwfDigitalIOOutputSet", (FARPROCm)&_FDwfDigitalIOOutputSet },
				{ "FDwfDigitalIOOutputGet", (FARPROCm)&_FDwfDigitalIOOutputGet },
				{ "FDwfDigitalIOInputInfo", (FARPROCm)&_FDwfDigitalIOInputInfo },
				{ "FDwfDigitalIOInputStatus", (FARPROCm)&_FDwfDigitalIOInputStatus },
				{ "FDwfDigitalIOOutputEnableInfo64", (FARPROCm)&_FDwfDigitalIOOutputEnableInfo64 },
				{ "FDwfDigitalIOOutputEnableSet64", (FARPROCm)&_FDwfDigitalIOOutputEnableSet64 },
				{ "FDwfDigitalIOOutputEnableGet64", (FARPROCm)&_FDwfDigitalIOOutputEnableGet64 },
				{ "FDwfDigitalIOOutputInfo64", (FARPROCm)&_FDwfDigitalIOOutputInfo64 },
				{ "FDwfDigitalIOOutputSet64", (FARPROCm)&_FDwfDigitalIOOutputSet64 },
				{ "FDwfDigitalIOOutputGet64", (FARPROCm)&_FDwfDigitalIOOutputGet64 },
				{ "FDwfDigitalIOInputInfo64", (FARPROCm)&_FDwfDigitalIOInputInfo64 },
				{ "FDwfDigitalIOInputStatus64", (FARPROCm)&_FDwfDigitalIOInputStatus64 },
				{ "FDwfDigitalInReset", (FARPROCm)&_FDwfDigitalInReset },
				{ "FDwfDigitalInConfigure", (FARPROCm)&_FDwfDigitalInConfigure },
				{ "FDwfDigitalInStatus", (FARPROCm)&_FDwfDigitalInStatus },
				{ "FDwfDigitalInStatusSamplesLeft", (FARPROCm)&_FDwfDigitalInStatusSamplesLeft },
				{ "FDwfDigitalInStatusSamplesValid", (FARPROCm)&_FDwfDigitalInStatusSamplesValid },
				{ "FDwfDigitalInStatusIndexWrite", (FARPROCm)&_FDwfDigitalInStatusIndexWrite },
				{ "FDwfDigitalInStatusAutoTriggered", (FARPROCm)&_FDwfDigitalInStatusAutoTriggered },
				{ "FDwfDigitalInStatusData", (FARPROCm)&_FDwfDigitalInStatusData },
				{ "FDwfDigitalInStatusData2", (FARPROCm)&_FDwfDigitalInStatusData2 },
				{ "FDwfDigitalInStatusNoise2", (FARPROCm)&_FDwfDigitalInStatusNoise2 },
				{ "FDwfDigitalInStatusRecord", (FARPROCm)&_FDwfDigitalInStatusRecord },
				{ "FDwfDigitalInInternalClockInfo", (FARPROCm)&_FDwfDigitalInInternalClockInfo },
				{ "FDwfDigitalInClockSourceInfo", (FARPROCm)&_FDwfDigitalInClockSourceInfo },
				{ "FDwfDigitalInClockSourceSet", (FARPROCm)&_FDwfDigitalInClockSourceSet },
				{ "FDwfDigitalInClockSourceGet", (FARPROCm)&_FDwfDigitalInClockSourceGet },
				{ "FDwfDigitalInDividerInfo", (FARPROCm)&_FDwfDigitalInDividerInfo },
				{ "FDwfDigitalInDividerSet", (FARPROCm)&_FDwfDigitalInDividerSet },
				{ "FDwfDigitalInDividerGet", (FARPROCm)&_FDwfDigitalInDividerGet },
				{ "FDwfDigitalInBitsInfo", (FARPROCm)&_FDwfDigitalInBitsInfo },
				{ "FDwfDigitalInSampleFormatSet", (FARPROCm)&_FDwfDigitalInSampleFormatSet },
				{ "FDwfDigitalInSampleFormatGet", (FARPROCm)&_FDwfDigitalInSampleFormatGet },
				{ "FDwfDigitalInInputOrderSet", (FARPROCm)&_FDwfDigitalInInputOrderSet },
				{ "FDwfDigitalInBufferSizeInfo", (FARPROCm)&_FDwfDigitalInBufferSizeInfo },
				{ "FDwfDigitalInBufferSizeSet", (FARPROCm)&_FDwfDigitalInBufferSizeSet },
				{ "FDwfDigitalInBufferSizeGet", (FARPROCm)&_FDwfDigitalInBufferSizeGet },
				{ "FDwfDigitalInSampleModeInfo", (FARPROCm)&_FDwfDigitalInSampleModeInfo },
				{ "FDwfDigitalInSampleModeSet", (FARPROCm)&_FDwfDigitalInSampleModeSet },
				{ "FDwfDigitalInSampleModeGet", (FARPROCm)&_FDwfDigitalInSampleModeGet },
				{ "FDwfDigitalInSampleSensibleSet", (FARPROCm)&_FDwfDigitalInSampleSensibleSet },
				{ "FDwfDigitalInSampleSensibleGet", (FARPROCm)&_FDwfDigitalInSampleSensibleGet },
				{ "FDwfDigitalInAcquisitionModeInfo", (FARPROCm)&_FDwfDigitalInAcquisitionModeInfo },
				{ "FDwfDigitalInAcquisitionModeSet", (FARPROCm)&_FDwfDigitalInAcquisitionModeSet },
				{ "FDwfDigitalInAcquisitionModeGet", (FARPROCm)&_FDwfDigitalInAcquisitionModeGet },
				{ "FDwfDigitalInTriggerSourceSet", (FARPROCm)&_FDwfDigitalInTriggerSourceSet },
				{ "FDwfDigitalInTriggerSourceGet", (FARPROCm)&_FDwfDigitalInTriggerSourceGet },
				{ "FDwfDigitalInTriggerSlopeSet", (FARPROCm)&_FDwfDigitalInTriggerSlopeSet },
				{ "FDwfDigitalInTriggerSlopeGet", (FARPROCm)&_FDwfDigitalInTriggerSlopeGet },
				{ "FDwfDigitalInTriggerPositionInfo", (FARPROCm)&_FDwfDigitalInTriggerPositionInfo },
				{ "FDwfDigitalInTriggerPositionSet", (FARPROCm)&_FDwfDigitalInTriggerPositionSet },
				{ "FDwfDigitalInTriggerPositionGet", (FARPROCm)&_FDwfDigitalInTriggerPositionGet },
				{ "FDwfDigitalInTriggerPrefillSet", (FARPROCm)&_FDwfDigitalInTriggerPrefillSet },
				{ "FDwfDigitalInTriggerPrefillGet", (FARPROCm)&_FDwfDigitalInTriggerPrefillGet },
				{ "FDwfDigitalInTriggerAutoTimeoutInfo", (FARPROCm)&_FDwfDigitalInTriggerAutoTimeoutInfo },
				{ "FDwfDigitalInTriggerAutoTimeoutSet", (FARPROCm)&_FDwfDigitalInTriggerAutoTimeoutSet },
				{ "FDwfDigitalInTriggerAutoTimeoutGet", (FARPROCm)&_FDwfDigitalInTriggerAutoTimeoutGet },
				{ "FDwfDigitalInTriggerInfo", (FARPROCm)&_FDwfDigitalInTriggerInfo },
				{ "FDwfDigitalInTriggerSet", (FARPROCm)&_FDwfDigitalInTriggerSet },
				{ "FDwfDigitalInTriggerGet", (FARPROCm)&_FDwfDigitalInTriggerGet },
				{ "FDwfDigitalInTriggerResetSet", (FARPROCm)&_FDwfDigitalInTriggerResetSet },
				{ "FDwfDigitalInTriggerCountSet", (FARPROCm)&_FDwfDigitalInTriggerCountSet },
				{ "FDwfDigitalInTriggerLengthSet", (FARPROCm)&_FDwfDigitalInTriggerLengthSet },
				{ "FDwfDigitalInTriggerMatchSet", (FARPROCm)&_FDwfDigitalInTriggerMatchSet },
				{ "FDwfDigitalOutReset", (FARPROCm)&_FDwfDigitalOutReset },
				{ "FDwfDigitalOutConfigure", (FARPROCm)&_FDwfDigitalOutConfigure },
				{ "FDwfDigitalOutStatus", (FARPROCm)&_FDwfDigitalOutStatus },
				{ "FDwfDigitalOutInternalClockInfo", (FARPROCm)&_FDwfDigitalOutInternalClockInfo },
				{ "FDwfDigitalOutTriggerSourceSet", (FARPROCm)&_FDwfDigitalOutTriggerSourceSet },
				{ "FDwfDigitalOutTriggerSourceGet", (FARPROCm)&_FDwfDigitalOutTriggerSourceGet },
				{ "FDwfDigitalOutRunInfo", (FARPROCm)&_FDwfDigitalOutRunInfo },
				{ "FDwfDigitalOutRunSet", (FARPROCm)&_FDwfDigitalOutRunSet },
				{ "FDwfDigitalOutRunGet", (FARPROCm)&_FDwfDigitalOutRunGet },
				{ "FDwfDigitalOutRunStatus", (FARPROCm)&_FDwfDigitalOutRunStatus },
				{ "FDwfDigitalOutWaitInfo", (FARPROCm)&_FDwfDigitalOutWaitInfo },
				{ "FDwfDigitalOutWaitSet", (FARPROCm)&_FDwfDigitalOutWaitSet },
				{ "FDwfDigitalOutWaitGet", (FARPROCm)&_FDwfDigitalOutWaitGet },
				{ "FDwfDigitalOutRepeatInfo", (FARPROCm)&_FDwfDigitalOutRepeatInfo },
				{ "FDwfDigitalOutRepeatSet", (FARPROCm)&_FDwfDigitalOutRepeatSet },
				{ "FDwfDigitalOutRepeatGet", (FARPROCm)&_FDwfDigitalOutRepeatGet },
				{ "FDwfDigitalOutRepeatStatus", (FARPROCm)&_FDwfDigitalOutRepeatStatus },
				{ "FDwfDigitalOutTriggerSlopeSet", (FARPROCm)&_FDwfDigitalOutTriggerSlopeSet },
				{ "FDwfDigitalOutTriggerSlopeGet", (FARPROCm)&_FDwfDigitalOutTriggerSlopeGet },
				{ "FDwfDigitalOutRepeatTriggerSet", (FARPROCm)&_FDwfDigitalOutRepeatTriggerSet },
				{ "FDwfDigitalOutRepeatTriggerGet", (FARPROCm)&_FDwfDigitalOutRepeatTriggerGet },
				{ "FDwfDigitalOutCount", (FARPROCm)&_FDwfDigitalOutCount },
				{ "FDwfDigitalOutEnableSet", (FARPROCm)&_FDwfDigitalOutEnableSet },
				{ "FDwfDigitalOutEnableGet", (FARPROCm)&_FDwfDigitalOutEnableGet },
				{ "FDwfDigitalOutOutputInfo", (FARPROCm)&_FDwfDigitalOutOutputInfo },
				{ "FDwfDigitalOutOutputSet", (FARPROCm)&_FDwfDigitalOutOutputSet },
				{ "FDwfDigitalOutOutputGet", (FARPROCm)&_FDwfDigitalOutOutputGet },
				{ "FDwfDigitalOutTypeInfo", (FARPROCm)&_FDwfDigitalOutTypeInfo },
				{ "FDwfDigitalOutTypeSet", (FARPROCm)&_FDwfDigitalOutTypeSet },
				{ "FDwfDigitalOutTypeGet", (FARPROCm)&_FDwfDigitalOutTypeGet },
				{ "FDwfDigitalOutIdleInfo", (FARPROCm)&_FDwfDigitalOutIdleInfo },
				{ "FDwfDigitalOutIdleSet", (FARPROCm)&_FDwfDigitalOutIdleSet },
				{ "FDwfDigitalOutIdleGet", (FARPROCm)&_FDwfDigitalOutIdleGet },
				{ "FDwfDigitalOutDividerInfo", (FARPROCm)&_FDwfDigitalOutDividerInfo },
				{ "FDwfDigitalOutDividerInitSet", (FARPROCm)&_FDwfDigitalOutDividerInitSet },
				{ "FDwfDigitalOutDividerInitGet", (FARPROCm)&_FDwfDigitalOutDividerInitGet },
				{ "FDwfDigitalOutDividerSet", (FARPROCm)&_FDwfDigitalOutDividerSet },
				{ "FDwfDigitalOutDividerGet", (FARPROCm)&_FDwfDigitalOutDividerGet },
				{ "FDwfDigitalOutCounterInfo", (FARPROCm)&_FDwfDigitalOutCounterInfo },
				{ "FDwfDigitalOutCounterInitSet", (FARPROCm)&_FDwfDigitalOutCounterInitSet },
				{ "FDwfDigitalOutCounterInitGet", (FARPROCm)&_FDwfDigitalOutCounterInitGet },
				{ "FDwfDigitalOutCounterSet", (FARPROCm)&_FDwfDigitalOutCounterSet },
				{ "FDwfDigitalOutCounterGet", (FARPROCm)&_FDwfDigitalOutCounterGet },
				{ "FDwfDigitalOutDataInfo", (FARPROCm)&_FDwfDigitalOutDataInfo },
				{ "FDwfDigitalOutDataSet", (FARPROCm)&_FDwfDigitalOutDataSet },
				{ "FDwfDigitalUartReset", (FARPROCm)&_FDwfDigitalUartReset },
				{ "FDwfDigitalUartRateSet", (FARPROCm)&_FDwfDigitalUartRateSet },
				{ "FDwfDigitalUartBitsSet", (FARPROCm)&_FDwfDigitalUartBitsSet },
				{ "FDwfDigitalUartParitySet", (FARPROCm)&_FDwfDigitalUartParitySet },
				{ "FDwfDigitalUartStopSet", (FARPROCm)&_FDwfDigitalUartStopSet },
				{ "FDwfDigitalUartTxSet", (FARPROCm)&_FDwfDigitalUartTxSet },
				{ "FDwfDigitalUartRxSet", (FARPROCm)&_FDwfDigitalUartRxSet },
				{ "FDwfDigitalUartTx", (FARPROCm)&_FDwfDigitalUartTx },
				{ "FDwfDigitalUartRx", (FARPROCm)&_FDwfDigitalUartRx },
				{ "FDwfDigitalSpiReset", (FARPROCm)&_FDwfDigitalSpiReset },
				{ "FDwfDigitalSpiFrequencySet", (FARPROCm)&_FDwfDigitalSpiFrequencySet },
				{ "FDwfDigitalSpiClockSet", (FARPROCm)&_FDwfDigitalSpiClockSet },
				{ "FDwfDigitalSpiDataSet", (FARPROCm)&_FDwfDigitalSpiDataSet },
				{ "FDwfDigitalSpiModeSet", (FARPROCm)&_FDwfDigitalSpiModeSet },
				{ "FDwfDigitalSpiOrderSet", (FARPROCm)&_FDwfDigitalSpiOrderSet },
				{ "FDwfDigitalSpiSelect", (FARPROCm)&_FDwfDigitalSpiSelect },
				{ "FDwfDigitalSpiWriteRead", (FARPROCm)&_FDwfDigitalSpiWriteRead },
				{ "FDwfDigitalSpiWriteRead16", (FARPROCm)&_FDwfDigitalSpiWriteRead16 },
				{ "FDwfDigitalSpiWriteRead32", (FARPROCm)&_FDwfDigitalSpiWriteRead32 },
				{ "FDwfDigitalSpiRead", (FARPROCm)&_FDwfDigitalSpiRead },
				{ "FDwfDigitalSpiReadOne", (FARPROCm)&_FDwfDigitalSpiReadOne },
				{ "FDwfDigitalSpiRead16", (FARPROCm)&_FDwfDigitalSpiRead16 },
				{ "FDwfDigitalSpiRead32", (FARPROCm)&_FDwfDigitalSpiRead32 },
				{ "FDwfDigitalSpiWrite", (FARPROCm)&_FDwfDigitalSpiWrite },
				{ "FDwfDigitalSpiWriteOne", (FARPROCm)&_FDwfDigitalSpiWriteOne },
				{ "FDwfDigitalSpiWrite16", (FARPROCm)&_FDwfDigitalSpiWrite16 },
				{ "FDwfDigitalSpiWrite32", (FARPROCm)&_FDwfDigitalSpiWrite32 },
				{ "FDwfDigitalI2cReset", (FARPROCm)&_FDwfDigitalI2cReset },
				{ "FDwfDigitalI2cClear", (FARPROCm)&_FDwfDigitalI2cClear },
				{ "FDwfDigitalI2cStretchSet", (FARPROCm)&_FDwfDigitalI2cStretchSet },
				{ "FDwfDigitalI2cRateSet", (FARPROCm)&_FDwfDigitalI2cRateSet },
				{ "FDwfDigitalI2cReadNakSet", (FARPROCm)&_FDwfDigitalI2cReadNakSet },
				{ "FDwfDigitalI2cSclSet", (FARPROCm)&_FDwfDigitalI2cSclSet },
				{ "FDwfDigitalI2cSdaSet", (FARPROCm)&_FDwfDigitalI2cSdaSet },
				{ "FDwfDigitalI2cWriteRead", (FARPROCm)&_FDwfDigitalI2cWriteRead },
				{ "FDwfDigitalI2cRead", (FARPROCm)&_FDwfDigitalI2cRead },
				{ "FDwfDigitalI2cWrite", (FARPROCm)&_FDwfDigitalI2cWrite },
				{ "FDwfDigitalI2cWriteOne", (FARPROCm)&_FDwfDigitalI2cWriteOne },
				{ "FDwfDigitalCanReset", (FARPROCm)&_FDwfDigitalCanReset },
				{ "FDwfDigitalCanRateSet", (FARPROCm)&_FDwfDigitalCanRateSet },
				{ "FDwfDigitalCanPolaritySet", (FARPROCm)&_FDwfDigitalCanPolaritySet },
				{ "FDwfDigitalCanTxSet", (FARPROCm)&_FDwfDigitalCanTxSet },
				{ "FDwfDigitalCanRxSet", (FARPROCm)&_FDwfDigitalCanRxSet },
				{ "FDwfDigitalCanTx", (FARPROCm)&_FDwfDigitalCanTx },
				{ "FDwfDigitalCanRx", (FARPROCm)&_FDwfDigitalCanRx },
				{ "FDwfAnalogImpedanceReset", (FARPROCm)&_FDwfAnalogImpedanceReset },
				{ "FDwfAnalogImpedanceModeSet", (FARPROCm)&_FDwfAnalogImpedanceModeSet },
				{ "FDwfAnalogImpedanceModeGet", (FARPROCm)&_FDwfAnalogImpedanceModeGet },
				{ "FDwfAnalogImpedanceReferenceSet", (FARPROCm)&_FDwfAnalogImpedanceReferenceSet },
				{ "FDwfAnalogImpedanceReferenceGet", (FARPROCm)&_FDwfAnalogImpedanceReferenceGet },
				{ "FDwfAnalogImpedanceFrequencySet", (FARPROCm)&_FDwfAnalogImpedanceFrequencySet },
				{ "FDwfAnalogImpedanceFrequencyGet", (FARPROCm)&_FDwfAnalogImpedanceFrequencyGet },
				{ "FDwfAnalogImpedanceAmplitudeSet", (FARPROCm)&_FDwfAnalogImpedanceAmplitudeSet },
				{ "FDwfAnalogImpedanceAmplitudeGet", (FARPROCm)&_FDwfAnalogImpedanceAmplitudeGet },
				{ "FDwfAnalogImpedanceOffsetSet", (FARPROCm)&_FDwfAnalogImpedanceOffsetSet },
				{ "FDwfAnalogImpedanceOffsetGet", (FARPROCm)&_FDwfAnalogImpedanceOffsetGet },
				{ "FDwfAnalogImpedanceProbeSet", (FARPROCm)&_FDwfAnalogImpedanceProbeSet },
				{ "FDwfAnalogImpedanceProbeGet", (FARPROCm)&_FDwfAnalogImpedanceProbeGet },
				{ "FDwfAnalogImpedancePeriodSet", (FARPROCm)&_FDwfAnalogImpedancePeriodSet },
				{ "FDwfAnalogImpedancePeriodGet", (FARPROCm)&_FDwfAnalogImpedancePeriodGet },
				{ "FDwfAnalogImpedanceCompReset", (FARPROCm)&_FDwfAnalogImpedanceCompReset },
				{ "FDwfAnalogImpedanceCompSet", (FARPROCm)&_FDwfAnalogImpedanceCompSet },
				{ "FDwfAnalogImpedanceCompGet", (FARPROCm)&_FDwfAnalogImpedanceCompGet },
				{ "FDwfAnalogImpedanceConfigure", (FARPROCm)&_FDwfAnalogImpedanceConfigure },
				{ "FDwfAnalogImpedanceStatus", (FARPROCm)&_FDwfAnalogImpedanceStatus },
				{ "FDwfAnalogImpedanceStatusInput", (FARPROCm)&_FDwfAnalogImpedanceStatusInput },
				{ "FDwfAnalogImpedanceStatusMeasure", (FARPROCm)&_FDwfAnalogImpedanceStatusMeasure },
				{ "FDwfDigitalInMixedSet", (FARPROCm)&_FDwfDigitalInMixedSet },
				{ "FDwfAnalogInTriggerSourceInfo", (FARPROCm)&_FDwfAnalogInTriggerSourceInfo },
				{ "FDwfAnalogOutTriggerSourceInfo", (FARPROCm)&_FDwfAnalogOutTriggerSourceInfo },
				{ "FDwfDigitalInTriggerSourceInfo", (FARPROCm)&_FDwfDigitalInTriggerSourceInfo },
				{ "FDwfDigitalOutTriggerSourceInfo", (FARPROCm)&_FDwfDigitalOutTriggerSourceInfo },
				{ "FDwfAnalogOutEnableSet", (FARPROCm)&_FDwfAnalogOutEnableSet },
				{ "FDwfAnalogOutEnableGet", (FARPROCm)&_FDwfAnalogOutEnableGet },
				{ "FDwfAnalogOutFunctionInfo", (FARPROCm)&_FDwfAnalogOutFunctionInfo },
				{ "FDwfAnalogOutFunctionSet", (FARPROCm)&_FDwfAnalogOutFunctionSet },
				{ "FDwfAnalogOutFunctionGet", (FARPROCm)&_FDwfAnalogOutFunctionGet },
				{ "FDwfAnalogOutFrequencyInfo", (FARPROCm)&_FDwfAnalogOutFrequencyInfo },
				{ "FDwfAnalogOutFrequencySet", (FARPROCm)&_FDwfAnalogOutFrequencySet },
				{ "FDwfAnalogOutFrequencyGet", (FARPROCm)&_FDwfAnalogOutFrequencyGet },
				{ "FDwfAnalogOutAmplitudeInfo", (FARPROCm)&_FDwfAnalogOutAmplitudeInfo },
				{ "FDwfAnalogOutAmplitudeSet", (FARPROCm)&_FDwfAnalogOutAmplitudeSet },
				{ "FDwfAnalogOutAmplitudeGet", (FARPROCm)&_FDwfAnalogOutAmplitudeGet },
				{ "FDwfAnalogOutOffsetInfo", (FARPROCm)&_FDwfAnalogOutOffsetInfo },
				{ "FDwfAnalogOutOffsetSet", (FARPROCm)&_FDwfAnalogOutOffsetSet },
				{ "FDwfAnalogOutOffsetGet", (FARPROCm)&_FDwfAnalogOutOffsetGet },
				{ "FDwfAnalogOutSymmetryInfo", (FARPROCm)&_FDwfAnalogOutSymmetryInfo },
				{ "FDwfAnalogOutSymmetrySet", (FARPROCm)&_FDwfAnalogOutSymmetrySet },
				{ "FDwfAnalogOutSymmetryGet", (FARPROCm)&_FDwfAnalogOutSymmetryGet },
				{ "FDwfAnalogOutPhaseInfo", (FARPROCm)&_FDwfAnalogOutPhaseInfo },
				{ "FDwfAnalogOutPhaseSet", (FARPROCm)&_FDwfAnalogOutPhaseSet },
				{ "FDwfAnalogOutPhaseGet", (FARPROCm)&_FDwfAnalogOutPhaseGet },
				{ "FDwfAnalogOutDataInfo", (FARPROCm)&_FDwfAnalogOutDataInfo },
				{ "FDwfAnalogOutDataSet", (FARPROCm)&_FDwfAnalogOutDataSet },
				{ "FDwfAnalogOutPlayStatus", (FARPROCm)&_FDwfAnalogOutPlayStatus },
				{ "FDwfAnalogOutPlayData", (FARPROCm)&_FDwfAnalogOutPlayData },
				{ "FDwfEnumAnalogInChannels", (FARPROCm)&_FDwfEnumAnalogInChannels },
				{ "FDwfEnumAnalogInBufferSize", (FARPROCm)&_FDwfEnumAnalogInBufferSize },
				{ "FDwfEnumAnalogInBits", (FARPROCm)&_FDwfEnumAnalogInBits },
				{ "FDwfEnumAnalogInFrequency", (FARPROCm)&_FDwfEnumAnalogInFrequency },
			};

		public:

			Server ()
			{
			}
			
			~Server ()
			{
			}
			
			void InvokeAPICall(string fn, json::iterator it)
			{
				auto iter = fn_map.find(fn);
				if (iter != end(fn_map)) {
					(iter->second)(it);
				}
				else {
					std::cout << "not exists" << std::endl;
				}
			}
			
			void CloseAllDevices()
			{
				FDwfDeviceCloseAll();
			}
		};
	}
}

