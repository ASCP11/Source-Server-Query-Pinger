/*
   _____    ____________________________ 
  /  _  \  /   _____/\_   ___ \______   \
 /  /_\  \ \_____  \ /    \  \/|     ___/
/    |    \/        \\     \___|    |    
\____|__  /_______  / \______  /____|    
        \/        \/         \/          

        Created by:ASCP11
        Source Server Query (SSQ)
        @2020
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>


char A2S_INFO[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0x54, 0x53, 0x6F, 0x75, 0x72, 0x63,
	0x65, 0x20, 0x45, 0x6E, 0x67, 0x69, 0x6E, 0x65, 0x20, 0x51,
	0x75, 0x65, 0x72, 0x79, 0x00
};


class Server_info{
	public:
		int  start_query(char ip_addr[], char port[])
		{
		    int udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		    if (udp_sock == -1)
		    {
		        std::cout<<"[ERROR]Failed to create UDP socket\n";
		        return 1;
		        exit(1);
		    }
		    struct addrinfo hints;
		    struct addrinfo *result;
		    memset(&hints, 0, sizeof(struct addrinfo));
		    hints.ai_family = AF_UNSPEC;
		    hints.ai_socktype = SOCK_DGRAM;
		    hints.ai_flags = 0;
		    hints.ai_protocol = 0;
		    int src_addr = getaddrinfo(ip_addr, port, &hints, &result);
		    if (src_addr != 0)
		    {
		        std::cout<<"[ERROR]Failed to resolve remote socket address:"<<gai_strerror(src_addr)<<"\n";
		        return 1;
		        exit(1);
		    }

		    int resp = sendto(udp_sock, A2S_INFO, strlen(A2S_INFO) + 1, 0,
		                      result->ai_addr, result->ai_addrlen);
		    if (resp == -1)
		    {
		        std::cout<<"[ERROR]Sending packet failed:"<<strerror(errno)<<"\n";
		    }
		    char buffer[1472];
		    ssize_t recv = recvfrom(udp_sock, buffer, sizeof(buffer), 0,
		                            NULL, NULL);
		    if (recv < 1)
		    {
		        std::cout<<"[ERROR]Response was empty or error occurred.\n";
		    }
		    //Global discard						//
		    int discard;
		    //String Method							//
		    std::pair<std::string, int> answer_string;
		    //std::string string;
		    //										//

		    //Short Method							//
		    std::pair<short, int> answer_short;
		    //short tshort;
		    //										//
		    //Byte Method							//
		    std::pair<int, int> answer_byte;
		    //int byte;
		    //										//


		    //hostname								//
		    answer_string = __get_string(buffer,5);

		    hostname 			= answer_string.first;
		    discard 			= answer_string.second;
		    //										//

			//Map									//
		    answer_string = __get_string(buffer,discard);

			map 				= answer_string.first;
			discard 			= answer_string.second;
			//										//

			//game_directory						//
		    answer_string = __get_string(buffer,discard);

			game_directory 		= answer_string.first;
			discard 			= answer_string.second;
			//										//

			//game_description						//
		    answer_string = __get_string(buffer,discard);

			game_description	= answer_string.first;
			discard 			= answer_string.second;
			//										//

			//App_id								//
			answer_short = __get__short(buffer,discard);

			app_id 				= answer_short.first;
			discard 			= answer_short.second;
			//										//

			//num_players							//
			answer_byte = __get__byte(buffer,discard+1);
			num_players 		= answer_byte.first;
			discard 			= answer_byte.second;
			//										//

			//max_players							//
			answer_byte = __get__byte(buffer,discard);
			max_players 		= answer_byte.first;
			discard 			= answer_byte.second;
			//										//

			//num_of_bots							//
			answer_byte = __get__byte(buffer,discard);
			num_of_bots 		= answer_byte.first;
			discard 			= answer_byte.second;
			//										//
			//dedicated								//
			answer_byte = __get__byte(buffer,discard);
			dedicated 			= answer_byte.first;
			discard 			= answer_byte.second;
			//										//
			//os									//
			answer_byte = __get__byte(buffer,discard);
			os 					= answer_byte.first;
			discard 			= answer_byte.second;
			//										//

			//password								//
			answer_byte = __get__byte(buffer,discard);
			password 			= answer_byte.first;
			discard 			= answer_byte.second;
			//										//

			//secure								//
			answer_byte = __get__byte(buffer,discard);
			secure	 			= answer_byte.first;
			discard 			= answer_byte.second;
			//										//
			Initialized = 1;
			return 0;
		}

		std::string GetHostname(){
			if (Initialized==1){
				return hostname;
			}else{
				return "[ERROR]Not Initialized!";
			}
		}

		std::string GetMap(){
			if (Initialized==1){
				return map;
			}else{
				return "[ERROR]Not Initialized!";
			}
		}

		std::string GetGameFolder(){
			if (Initialized==1){
				return game_directory;
			}else{
				return "[ERROR]Not Initialized!";
			}
		}

		std::string GetGame(){
			if (Initialized==1){
				return game_description;
			}else{
				return "[ERROR]Not Initialized!";
			}
		}
		int GetAppId(){
			if (Initialized==1){
				return app_id;
			}else{
				return -1;
			}
		}
		int GetCurPlayers(){
			if (Initialized==1){
				return num_players;
			}else{
				return -1;
			}
		}

		int GetMaxPlayers(){
			if (Initialized==1){
				return max_players;
			}else{
				return -1;
			}
		}
		int GetCurBots(){
			if (Initialized==1){
				return num_of_bots;
			}else{
				return -1;
			}		
		}
		std::string GetServerType(){
			if (Initialized==1){
				switch(dedicated){
					case 100:
						return "Dedicated";
						break;
					case 108:
						return "Non-dedicated";
						break;
					case 112:
						return "SourceTV Relay";
						break;
				}
			}else{
				return "[ERROR]Not Initialized!";
			}		
		}

		std::string GetOS(){
			if (Initialized==1){
				switch(os){
					case 108:
						return "Linux";
						break;
					case 119:
						return "Windows";
						break;
					case 109:
						return "MacOS";
						break;
				}
			}else{
				return "[ERROR]Not Initialized!";
			}		
		}

		std::string GetVisibility(){
			if (Initialized==1){
				switch(password){
					case 0:
						return "Public";
						break;
					case 1:
						return "Private";
						break;
				}
			}else{
				return "[ERROR]Not Initialized!";
			}
		}
		std::string GetSecure(){
			if (Initialized==1){
				switch(secure){
					case 0:
						return "Unsecure";
						break;
					case 1:
						return "Secure";
						break;
				}
			}else{
				return "[ERROR]Not Initialized!";
			}
		}
	private:
		int Initialized;

		std::string hostname;
		std::string map;
		std::string game_directory;
		std::string game_description;
		short app_id;
		int num_players;
		int max_players;
		int num_of_bots;
		int dedicated;
		int os;
		int password;
		int secure;
		//char game_version[32];

		std::pair<short,int> __get__byte(char buffer[], int discard){
			int p = (int)buffer[discard];
			return std::make_pair(p,discard+1);
		}

		std::pair<short,int> __get__short(char buffer[], int discard){
			short app_id = *(short*)&buffer[discard];
			return std::make_pair(app_id,discard+1);
		}

		std::pair<std::string, int> __get_string(char buffer[],int discard){
			char string[256]="";
			int i = 0;
			int k = 0+discard;
			for (i = 0; i < 128;i++){
				if (buffer[i+discard] == '\0'){
					k++;
					break;
				}
				else{
					string[i] += buffer[i+discard];
					k++;
				}
			}
			return std::make_pair(string,k);
		}

};