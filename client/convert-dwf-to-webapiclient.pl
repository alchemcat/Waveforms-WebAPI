#!/usr/bin/perl 

#    ___  __      __  ___  
#   |   \ \ \    / / | __| 
#   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI-client generator
#   |___/   \_/\_/___|_|_    version 0.1.0 for Waveforms API 3.13.8
#  |"""""| |"""""""""""""|   https://github.com/
# _|     |_|   Web API   | 
# "`-0-0-'"`-0-0-----0-0-' 
#
# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# Copyright (c) 2020 Yasuo Matsubara
# 
# Permission is hereby  granted, free of charge, to any  person obtaining a copy
# of this software and associated  documentation files (the "Software"), to deal
# in the Software  without restriction, including without  limitation the rights
# to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
# copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
# IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
# FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
# AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
# LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# 

# usage: convert-dwf-to-webapiclient.pl < dwf.h > dwf-webapi-client.hpp


print <<'EOM';

/*
    ___  __      __  ___  
   |   \ \ \    / / | __| 
   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI-client wrapper
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
EOM


@function_names = ();


print <<'EOM';

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

EOM

$c = 0;
while(<>)
{

	@words0 = ($_ =~ /^DWFAPI int (FDwf.+)\((.*?)\);/);
	
	if(@words0 > 1)
	{
		$,="\n";
		
		$function_name = $1;
		$parameters = $2;
		
		print "\n\n/*\n";
		print "$function_name $parameters\n";
		push(@function_names, $function_name);
				
		#@params = ($parameters =~ /(?:([^*, ]+ +\*?)([^*, ]+?))?(?:, ([^*, ]+ +\*?)([^*,]+?))+/);
		@params = ($parameters =~ / *([^*,]+ +\*?)([^*, ]+)/g); 
	
		print @params;
		print "\n*/";
		
		$c++;
		
		print "\n// $number_params (match no. $c)\n";
		
		$number_params = ($number_params = @params)/2 + 1;
	
		# A paramter of which name starts with "rg" is the pointer to an array. The type is dependent on the array.
		# A paramter of which name ends with "[\d+]" is an array. In the declaration, it does not take '*' like the declaration of a pointer.
		
print <<EOM;

	int ${function_name}(${parameters})
	{
		using namespace std;
		using json = nlohmann::json;
	
		int p0 = 0;

		json jreq = {
			{
				"${function_name}",
				{
					{{"(return)", 0}},
EOM


#					{{"device", device}},
#					{{"handle", (*handle)}},// nullptr
#					{{"data", (std::vector<int>(&data[0], &data[cdData]))}},

		for ($i = 1; $i < $number_params; $i++)
		{
			$is_pointer = 0; 
			$is_array = 0; $array_size = 0;
			
			$type_native = $params[($i-1) * 2];
			$param_name_native = $params[($i-1) * 2 + 1];
			
			print "\t\t\t\t\t";
			
			if( $type_native =~ /^(.+?)\*$/ )
			{ 
				$is_pointer = 1; $type_native = $1;
				if( $param_name_native =~ /^rg/ ) 
				{ 
					$is_array = 1; 
					if($type_native =~ /void/) { $type_native = "char" }
					
					if ( $param_name_native =~ /^rgTX/)
					{
						if ( $function_name eq "FDwfDigitalCanTx" ) {
							$array_size = "cDLC";
						} else {
							$array_size = "cTX";
						}
						
					}
					elsif ( $param_name_native =~ /^rgRX/)
					{
						$array_size = "cRX";
					}
					elsif ( $param_name_native =~ /^rgRx/)
					{
						$array_size = "cRx";
					}
					elsif ( $param_name_native =~ /^rgData/)
					{
						$array_size = "countOfDataBytes";
						$param_name_native = "((char*)rgData)";
					}
					elsif ( $param_name_native =~ /^rgBits/)
					{
						$array_size = "countOfBits";
						$param_name_native = "((char*)rgBits)";
					}
					elsif ( $param_name_native =~ /^rgbRx/)
					{
						$array_size = "cRx";
					}
					elsif ( $param_name_native =~ /^rgbTx/)
					{
						$array_size = "cTx";
					}
					else
					{
						$array_size = "cdData";
					}
				}
				else
				{
				}
			}
			elsif( $param_name_native =~ /(.+?)\[(\d+)\]$/ ) 
			{
				$is_array = 1; $param_name_native = $1; $array_size = $2;
			}
			else
			{
			}
			
			$type_native =~ s/\s+$//;
			if($is_array)
			{
				# vector<int>     v(array, array + (sizeof(array)/sizeof(int)) );
				print "{{\"$type_native\", (std::vector<$type_native>(&$param_name_native\[0\], &$param_name_native\[$array_size\])) }},\n";
			}
			elsif($is_pointer)
			{
				print "{{\"$type_native\", (*$param_name_native) }},\n";
			}
			else
			{
				print "{{\"$type_native\", $param_name_native }},\n";
			}
		}
		#print "\n";


print <<EOM;
				}
			},
		};

		json jres = Dwf::WebAPI::Client::DispatchAPICall(jreq);

		json::iterator it = jres.begin();
		if (it == jres.end()) return p0;
		if (it.key() != "${function_name}") return p0;

		if (it.value().is_array())
		{
			json* params = &(it.value());

			if (params->size() == ${number_params})
			{
				try
				{
					json::iterator it0 = params->begin();

						p0 = it0[0].begin().value().get<int>();
EOM


#					int p1 = it0[1].begin().value().get<int>();
#					int p2 = it0[2].begin().value().get<int>();
#					vector<int> p3 = it0[3].begin().value().get<vector<int>>();

		for ($i = 1; $i < $number_params; $i++)
		{
			$is_pointer = 0; 
			$is_array = 0;  $array_size = 0;
			
			$type_native = $params[($i-1) * 2];
			$param_name_native = $params[($i-1) * 2 + 1];
			
			print "\t\t\t\t\t";
			
			if( $type_native =~ /^(.+?)\*$/ )
			{ 
				$is_pointer = 1; $type_native = $1;
				if( $param_name_native =~ /^rg/ ) 
				{ 
					$is_array = 1;
					if($type_native =~ /void/) { $type_native = "char" }
				}
				else
				{
				}
			}
			elsif( $param_name_native =~ /(.+?)\[(\d+)\]$/ ) 
			{
				$is_array = 1; $param_name_native = $1; $array_size = $2;
			}
			else
			{
			}
			
			$type_native =~ s/\s+$//;
			if($is_array)
			{
				print "vector<$type_native> p$i = it0[$i].begin().value().get<vector<$type_native>>();\n";
			}
			else
			{
				print "$type_native p$i = it0[$i].begin().value().get<$type_native>();\n";
			}
		}
		print "\n";


#					device = p1;
#					*handle = p2;
#					std::memmove(data, p3.data(), cdData * sizeof(int));

		for ($i = 1; $i < $number_params; $i++)
		{
			$is_pointer = 0; 
			$is_array = 0; $array_size = 0;
			
			$type_native = $params[($i-1) * 2];
			$param_name_native = $params[($i-1) * 2 + 1];
			
			print "\t\t\t\t\t";
			
			if( $type_native =~ /^(.+?)\*$/ )
			{ 
				$is_pointer = 1; $type_native = $1;
				if( $param_name_native =~ /^rg/ ) 
				{ 
					$is_array = 1;
					if($type_native =~ /void/) { $type_native = "char" }
				}
				else
				{
				}
			}
			elsif( $param_name_native =~ /(.+?)\[(\d+)\]$/ ) 
			{
				$is_array = 1; $param_name_native = $1; $array_size = $2;
			}
			else
			{
			}
			
			$type_native =~ s/\s+$//;
			if($is_array)
			{
				print "std::memmove($param_name_native, p$i.data(), $array_size * sizeof($type_native));\n";
			}
			elsif($is_pointer)
			{
				print "(*$param_name_native) = p$i;\n";
			}
			else
			{
				print "($param_name_native) = p$i;\n";
			}
		}
		#print "\n";

print <<EOM;
				}
				catch (json::exception& e)
				{
					// output exception information
					std::cout << "message: " << e.what() << '\\n'
							  << "exception id: " << e.id << std::endl;
				}
				catch (...)
				{
					cout << "Exception occur." << endl;
				}
			}
		}

		return p0;
	}
EOM

	}
}

print <<EOM;

EOM

