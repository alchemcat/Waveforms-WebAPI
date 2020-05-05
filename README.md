# Waveforms WebAPI

Waveforms WebAPI is a REST API for Digilent Waveforms software. This API enables you to operate your Digilent AnalogDiscovery 2 at a distant place over the Internet with the HTTP(S) protocol.

Like other REST APIs, this API exchanges a JSON object that contains which native API call with parameters should be invoked in a server and its response to a client. This repository presents two libraries for such API written in C++11. One is for a server and the other for a client. A example of the JSON object generated in a client is as follows in the case of one of native APIs, *FDwfGetVersion(char szVersion[32])* defined in `dwf.h`:

```json
{
	{
        "FDwfGetVersion",
        {
            {{"(return)", 0}},
            {{"char", (std::vector<char>(&szVersion[0], &szVersion[32])) }},
        }
    },
}	
```
Importantly, in your client program only what you have to do is: (1) include `dwf-webapi-client.hpp` (that is the library on the client-side); and (2) call a API,  `Dwf::WebAPI::Client::SetServer(hostname, port, "user-name", "password");`. If you want to use HTTPS rather than HTTP, define `CPPHTTPLIB_OPENSSL_SUPPORT` as a preprocessor directive prior to including `dwf-webapi-client.hpp`, providing the sever is already set up. That's it. You don't need to fix your original code at all, except these two things.

## Example

This repository consists of a set of server-side and client-side program examples. First of all, the original Digilent Waveform API library has to be installed. For example, in Ubuntu system,

```sh
$ sudo apt install ./digilent.adept.runtime_2.20.1-amd64.deb
$ sudo apt install ./digilent.waveforms_3.12.2_amd64.deb
```

Then, after pulling this repository,

```c++
$ g++ -pthread server.cpp -ldwf -lssl -lcrypto -o server.o
$ g++ -pthread client.cpp -lssl -lcrypto -o client.o
```

For Windows, use Visual Studio 2017 or later in which `waveforms-webapi-server.sln` and `waveforms-webapi-client.sln` is the solution files. Please make sure that [Win32/Win64 OpenSSL library](http://slproweb.com/products/Win32OpenSSL.html) is installed *a priori*.

Finally, invoke `server.o` and `client.o` (in this order) in two different terminals. You would see the simple JSON communication between the server and the client.  

## Inside of the library

The two header library, `dwf-webapi-server.hpp` and `dwf-webapi-client.hpp` are generated from the original Digilent Waveforms API header, `dwf.h` by using Perl scripts as follows:

```sh
$ perl convert-dwf-to-webapiclient.pl < dwf.h > dwf-webapi-client.hpp
$ perl convert-dwf-to-webapiserver.pl < dwf.h > dwf-webapi-server.hpp
```

As of May 6, 2020, these scripts are prepared for the header library (ver. 3.13.8).

## Dependency

This implement uses quite nice libraries below. Thanks a lot!

-  [nlohmann / json](https://github.com/nlohmann/json), JSON for Modern C++
-  [yhirose / cpp-httplib](https://github.com/yhirose/cpp-httplib), A C++ header-only HTTP/HTTPS server and client library

The example programs also use very helpful library below. Thank you!

- [arro2783 / cxxopts](https://github.com/jarro2783/cxxopts), Lightweight C++ command line option parser 

## License

MIT License (2020, Yasuo Matsubara)