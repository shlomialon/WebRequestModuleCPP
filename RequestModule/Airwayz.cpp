#include "client_http.hpp"
#include "server_http.hpp"
#include <future>

#include "Airwayz.h"
// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main() {
  // Client examples
  string json_string = "{\"api_key\":\"cw642787609\", \"sid\":\"poc1\", \"drone_id\":\"cw001\", \"token\":\"cw001token\",\"sc\":\"1359\", \"poi\":{\"latitude\":31.279869, \"longitude\": 34.440641, \"altitude\":30.0}}";

  // Synchronous request examples
  {
    HttpClient client("airwayz-euc.appspot.com:80");
    try {
      /*
      cout << "Example GET request to http://localhost:8080/match/123" << endl;
      auto r1 = client.request("GET", "/match/123");
      cout << "Response content: " << r1->content.rdbuf() << endl << endl; // Alternatively, use the convenience function r1->content.string()
	  */
      cout << "Example POST request to airwayz-euc.appspot.com:80" << endl;
      auto r2 = client.request("POST", "/dcFlyTogether/sendDroneToPoiRequest", json_string);
      cout << "Response content: " << r2->content.rdbuf() << endl
           << endl;
    }
    catch(const SimpleWeb::system_error &e) {
      cerr << "Client request error: " << e.what() << endl;
    }
  }

  // Asynchronous request example
  {
    HttpClient client("airwayz-euc.appspot.com:80");
    cout << "Example POST request to airwayz-euc.appspot.com:80" << endl;
    client.request("POST", "/dcFlyTogether/sendDroneToPoiRequest", json_string, [](shared_ptr<HttpClient::Response> response, const SimpleWeb::error_code &ec) {
      if(!ec)
        cout << "Response content: " << response->content.rdbuf() << endl;
    });
    client.io_service->run();
  }

  // server_thread.join();
}