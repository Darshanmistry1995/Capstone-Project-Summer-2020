#include <iostream>
#include <sstream>
#include <fstream>
#include "SocketClient.h"

using namespace std;
using namespace exploringBB

int main()
{
   int iss = 1;
    int ret =0;
    
    int book;
    cout<<"Plese Enter please tell us if you are returing or issue book(1 for issue and 0 for return ) = ";
    cin >>book;
    if (book == iss)
    {
     	ostringstream head, data;
		SocketClient sc("api.thingspeak.com", 80);
		data << "field1=" << "1" << endl;
		sc.connectToServer();
		head << "POST /update HTTP/1.1\n" << "Host: api.thingspeak.com\n"
			<< "Connection: close\n" << "X-THINGSPEAKAPIKEY: ZUTZ2VW15UJALHO4\n"
			<< "Content-Type: application/x-www-form-urlencoded\n"
			<< "Content-Length:" << string(data.str()).length() << "\n\n";
		sc.send(string(head.str()));
		sc.send(string(data.str()));
		string rec = sc.receive(1024);
    }
    
    else if(book == ret)
    {
        ostringstream head, data;
		SocketClient sc("api.thingspeak.com", 80);
		data << "field2=" << "1" << endl;
		sc.connectToServer();
		head << "POST /update HTTP/1.1\n" << "Host: api.thingspeak.com\n"
			<< "Connection: close\n" << "X-THINGSPEAKAPIKEY: ZUTZ2VW15UJALHO4\n"
			<< "Content-Type: application/x-www-form-urlencoded\n"
			<< "Content-Length:" << string(data.str()).length() << "\n\n";
		sc.send(string(head.str()));
		sc.send(string(data.str()));
		string rec = sc.receive(1024);

    }

    return 0;
}
