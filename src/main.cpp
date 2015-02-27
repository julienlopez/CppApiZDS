#include <iostream>

#include <pplx/pplx.h>
#include <pplx/pplxtasks.h>

#include <cpprest/http_client.h>

#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/ws_client.h>                    // WebSocket client
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

using web::http::client::http_client;



using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

using namespace web::http::experimental::listener;          // HTTP server
using namespace web::experimental::web_sockets::client;     // WebSockets client
using namespace web::json;                                  // JSON library

int main()
{
	auto requestTask = pplx::create_task([=]()
	{
		// Create http_client to send the request.
		http_client client(U("https://zestedesavoir.com/api/"));

		http_request request;
		request.set_method(methods::GET);
		request.set_request_uri("membres/");
		request.headers().add(U("User-Agent"), U("Mozilla/5.0")); // (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko

		return client.request(request); //client.request(methods::GET, "membres");
	})
	.then([=](http_response response) // Handle response headers arriving.
	{
		std::cout << "Received response status code: " << response.status_code() << std::endl;
		if(response.status_code() != 200)
			throw std::runtime_error("Impossible d'achever la requête: " + response.to_string());

        std::cout << response.to_string() << std::endl << std::endl;

        auto json = response.extract_json().get();

        const auto count = json["count"];
        const auto next = json["next"];
        const auto results = json["results"];
        std::cout << "count = " << json["count"] << std::endl;
        std::cout << "next = " << json["next"] << std::endl;
        const auto membres = json["results"].as_array();
        std::cout << "results = " << membres.size() << std::endl;
        for(const auto& j : membres)
        {
            std::cout << j.at("username") << " (" << j.at("pk") << ")" << std::endl;
        }
	});

	// Wait for all the outstanding I/O to complete and handle any exceptions
	try
	{
		requestTask.wait();
	}
	catch(const std::exception& e)
	{
		printf("Error exception:%s\n", e.what());
	}

	return EXIT_SUCCESS;
}