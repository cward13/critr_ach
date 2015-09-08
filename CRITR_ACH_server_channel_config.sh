# Colin T. Ward
# M.X. Grey ( mxgrey@gatech.edu )
# CRITR development

export LD_LIBRARY_PATH=/usr/lib:

SERVER_IP='104.131.172.175'
CLIENT_IP='192.168.1.179'

SCLIENT='sclient'
SSERVER='sserver'

MakeAch()
{

	ach mk $SCLIENT -m 10 -n 64
	ach mk $SSERVER -m 10 -n 64
   	sudo chmod 777 /dev/shm/achshm-*
}
Client_Remote()
{
	MakeAch
	achd -r pull $SSERVER_IP $SSERVER
}
Server_Remote()
{

	MakeAch
	achd -r pull $SCLIENT_IP $SCLIENT
}
gcc Ach_Communication_server.c -lach -o run_ach
MakeAch
./run_ach
