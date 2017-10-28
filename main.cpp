#include "common.h"
#include "log.h"

#include "lib/rs.h"
#include "packet.h"
#include "connection.h"
#include "fd_manager.h"
#include "delay_manager.h"
#include "fec_manager.h"
#include "misc.h"
#include "tunnel.h"
#include "tun_dev.h"
using namespace std;


int main(int argc, char *argv[])
{
	//working_mode=tunnel_mode;

	assert(sizeof(u64_t)==8);
	assert(sizeof(i64_t)==8);
	assert(sizeof(u32_t)==4);
	assert(sizeof(i32_t)==4);
	assert(sizeof(u16_t)==2);
	assert(sizeof(i16_t)==2);
	dup2(1, 2);		//redirect stderr to stdout
	int i, j, k;
	process_arg(argc,argv);

	delay_manager.set_capacity(delay_capacity);
	local_ip_uint32=inet_addr(local_ip);
	remote_ip_uint32=inet_addr(remote_ip);
	sub_net_uint32=inet_addr(sub_net);

	if(strlen(tun_dev)==0)
	{
		sprintf(tun_dev,"tun%u",get_true_random_number()%1000);
	}

	if(working_mode==tunnel_mode)
	{
		if(client_or_server==client_mode)
		{
			tunnel_client_event_loop();
		}
		else
		{
			tunnel_server_event_loop();
		}
	}
	else
	{
		//disable_fec=1;
		if(client_or_server==client_mode)
		{
			tun_dev_client_event_loop();
		}
		else
		{
			tun_dev_server_event_loop();
		}
	}

	return 0;
}

