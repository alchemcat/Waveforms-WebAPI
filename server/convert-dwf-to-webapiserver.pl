#!/usr/bin/perl 

#    ___  __      __  ___  
#   |   \ \ \    / / | __| 
#   | |) | \ \/\/ /  | _|    a Waveforms-WebAPI-server generator
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

# usage: convert-dwf-to-webapiserver.pl < dwf.h > dwf-webapi-server.hpp


print <<'EOM';

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
EOM


@function_names = ();


print <<EOM;

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
		
		print "\n// $number_params (match no. $c)";
		
		$number_params = ($number_params = @params)/2 + 1;
	
		# A paramter of which name starts with "rg" is the pointer to an array. The type is dependent on the array.
		# A paramter of which name ends with "[\d+]" is an array. In the declaration, it does not take '*' like the declaration of a pointer.
		
		
print <<EOM;

			static int _${function_name}(json::iterator it)
			{
				cout << "	${function_name} called." << endl;
				
				if (it.key() != "${function_name}") return 0;

				if (it.value().is_array())
				{
					json* params = &(it.value());

					if (params->size() == ${number_params})
					{
						try
						{
							json::iterator it0 = params->begin();
EOM
		$tabs = "\t\t\t\t\t\t\t";
		
		for ($i = 1; $i < $number_params; $i++)
		{
			$is_pointer = 0; 
			$is_array = 0;
			#$is_string = 0;
			
			$type_native = $params[($i-1) * 2];
			$param_name_native = $params[($i-1) * 2 + 1];
			
			print $tabs;
			
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
			elsif( $param_name_native =~ /\[\d+\]$/ ) 
			{
				$is_array = 1;
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

		print $tabs."int p0 = $function_name(";
		for ($i = 1; $i < $number_params; $i++)
		{
			$is_pointer = 0; 
			$is_array = 0;
			
			$type_native = $params[($i-1) * 2];
			$param_name_native = $params[($i-1) * 2 + 1];
			
			if( $type_native =~ /^(.+?)\*$/ )
			{ 
				$is_pointer = 1; $type_native = $1;
				if( $param_name_native =~ /^rg/ ) 
				{ 
					$is_array = 1;
				}
				else
				{
				}
			}
			elsif( $param_name_native =~ /\[\d+\]$/ ) 
			{
				$is_array = 1;
			}
			else
			{
			}
			
			if($is_array)
			{
				print "p${i}.data()";
			}
			elsif($is_pointer)
			{
				print "&p${i}";
			}
			else
			{
				print "p${i}";
			}
			
			if($i < ($number_params-1)) { print "," };
		}
		print ");\n\n";
		
		print $tabs."it0 = params->begin();\n";
		for ($i = 0; $i < $number_params; $i++){
			print $tabs."it0[$i].begin().value() = p$i;\n";
		}
		
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

				return 1;
			}
EOM
	}
}

print "			const map<string, FARPROCm> fn_map =\n";
print "			{\n";

foreach $i (@function_names) {
    print "				{ \"$i\", (FARPROCm)&_$i },\n";
}

print "			};\n";


print <<EOM;

		public:

			Server ()
			{
			}
			
			~Server ()
			{
			}
EOM

print <<EOM;
			
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

EOM

