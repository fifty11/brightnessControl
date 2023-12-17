all:
	clang -O2 -O server server.c
	clang -O2 -O client client.c
server:
	clang -O2 -O server server.c
client:
	clang -O2 -O client client.c
clean:
	rm -rf client server
