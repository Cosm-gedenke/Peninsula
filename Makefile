PORT=8080
SERVER=./peninsula
all: 
	gcc -o peninsula ErrorT.c hash/hash.c Connection/clientIP.c Connection/rawhttp.c  transportlayer/tcp.c Requestparsing/request.c Requestparsing/parsing.c conf/parseconfig.c  peninsula.c
