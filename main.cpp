/*
   _____    ____________________________ 
  /  _  \  /   _____/\_   ___ \______   \
 /  /_\  \ \_____  \ /    \  \/|     ___/
/    |    \/        \\     \___|    |    
\____|__  /_______  / \______  /____|    
        \/        \/         \/          

        Created by:ASCP11
        Source Server Query Pinger(SSQP)
        @2020
*/

#include <iostream>
#include <unistd.h>

#include "lib/uil.hpp"
#include "lib/argparse.hpp"
#include "lib/ssq.hpp"

using namespace std;


int main(int argc, const char** argv) {

	argparse::ArgumentParser parser;

	//parser.addArgument("-v", "--verbose", 0);			//TO-DO Verbose Debug mode
	parser.addArgument("-h","--host", 1);
	parser.addArgument("-p","--port", 1);
	parser.addArgument("-r","--repeat", 1);
	parser.addArgument("-w","--wait", 1);

	parser.parse(argc, argv);


	if( parser.gotArgument("host") and parser.gotArgument("port") ) {


		Server_info serv;
		string host		= parser.retrieve<string>("host");
		string port		= parser.retrieve<string>("port");


		char *cport,*chost;

		IP_util ip;
		if (ip.validateIP(host)){
			chost = &host[0];
		}else{
			std::cout<<"[ERROR]Invalid IP address!"<<endl;
			exit(1);
		}

		if (ip.ValidatePort(port)){
			cport = &port[0];
		}else{
			std::cout<<"[ERROR]Invalid Port!"<<endl;
			exit(1);
		}

		int wait_time = 3;
		if ( parser.gotArgument("wait") ){
			wait_time		= parser.retrieve<int>("wait");
		}

		int loops = 0;
		if ( parser.gotArgument("repeat") ){
			loops		= parser.retrieve<int>("repeat");
			if (loops == 0){
				loops = 99999;
			}
		}else{
			loops = 1;
		}

		for(int i=0;i < loops; i++){
			serv.start_query(chost, cport);
			cout<<"#------------------------------------------------------------------------#"<<endl;
			cout<<"Hostanme:"<<serv.GetHostname()<<"\n";
			cout<<"Map:"<<serv.GetMap()<<"\n";
			cout<<"Game:"<<serv.GetGameFolder()<<"\n";

			cout<<"Players:"<<serv.GetCurPlayers() << "/" << serv.GetMaxPlayers()<<"\n";
			cout<<"Bots:"<<serv.GetCurBots()<<"\n";
			cout<<"System:"<<serv.GetOS()<<"\n";

			if (i+1 < loops){
				sleep(wait_time);
			}
		}
	}else{
		cout<<parser.usage()<<endl;
	}
}