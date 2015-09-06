# Colin T. Ward
# M.X. Grey ( mxgrey@gatech.edu )
# CRITR development

export LD_LIBRARY_PATH=/usr/lib:

SERVER_IP = '127.0.0.1'
CLIENT_IP = '127.0.0.1'

SCLIENT = 'sclient'
SSERVER = 'sserver'

MakeAch()
{

	ach mk $SCLIENT -m 10 -n 64
	ach mk $SSERVER -m 10 -n 64
    sudo chmod 777 /dev/shm/achshm-CRITR-*
}

Remote()
{
	MakeAch
	achd -r push $SSERVER_IP $SCLIENT
	achd -r push $SCLIENT_IP $SSERVER 
}

gcc Ach_Communication.c -o run_ach
MakeAch
