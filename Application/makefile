all:client	server	

client:client_main.o	client_dpendency.o
	cc -w client_main.c	client_dpendency.c -o	client	

server:server_main.o	server_dpendency.o	app_dll.o app_thread.o app_ipc.o
	cc -w server_main.c	server_dpendency.c 	app_dll.c	app_thread.c app_ipc.c -o server	


client_main.o:client_main.c
	cc -c client_main.c

client_dpendency.o:client_dpendency.c
	cc -c client_dpendency.c


server_main.o:server_main.c
	cc -c server_main.c

server_dpendency.o:server_dpendency.c
	cc -c server_dpendency.c

app_dll.o:app_dll.c
	cc -c app_dll.c
	
app_thread.o:app_thread.c
	cc -c app_thread.c
	
app_ipc.o:app_ipc.c
	cc -c app_ipc.c

clean:
	rm -f $(all)*.o *.exe *.stackdump 
	@echo clean done
