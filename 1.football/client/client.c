/*************************************************************************
	> File Name: client.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月04日 星期四 19时50分40秒
 ************************************************************************/
/*
#include "../common/head.h"
#include "../common/udp_client.h"

char server_ip[20] = {0};
int server_port = 0;
char *conf = "./football.conf";
int main(int argc, char **argv) {
    int opt, sockfd;
    struct LogRequest request;
    struct LogResponse reponse;
    bzero(&request, sizeof(request));
    while((opt = getopt(argc, argv, "h:p:n:t:m:"))!=-1) {
        switch(opt) {
            case 'h':
                strcpy(server_ip, optarg);
                break;
            case 'p':
                server_port = atoi(optarg);
                break;
            case 'n':
                strcpy(request.name, optarg);
                break;
            case 't':
                request.team = atoi(optarg);
                break;
            case 'm':
                strcpy(request.msg, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s [-h host] [-p port] !\n", argv[0]);
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);
    if(argc > 1) {
        fprintf(stderr, "Usage : %s [-h host] [-p port] !\n", argv[0]);
        exit(1);        
    }
    char buf[512] = {0};
    if(!server_port) server_port = atoi(get_value(conf, "SERVERPORT"));
    if(!strlen(server_ip)) strcpy(server_ip, get_value(conf, "SERVERIP"));
    if(!strlen(request.name))strcpy(request.name, get_value(conf, "NAME"));
    if(!strlen(request.msg))strcpy(request.msg, get_value(conf, "LOGMSG"));
    if(!request.team)request.team = atoi(get_value(conf, "TEAM"));
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    DBG(GREEN"INFO"NONE" : server_ip =%s : server_port = %d, name = %s, team = %s, logmsg = %s \n", server_ip, server_port, request.name, (request.team ? "BLUe" : "RED"));

    if((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);
//    int ret = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&server, &len);
    int ret = recvfrom(sockfd, (void *)&reponse, sizeof(reponse), 0, (struct sockaddr *)&server, &len);
    if(ret != sizeof(reponse) || reponse.type) {
        DBG(RED"ERROR : "NONE"The Game Server refused your login.\n\t This may be helpfull: %s\n", reponse.msg);
        exit(1);
    }
    DBG(GREEN"SERVER : "NONE" %s \n", reponse.msg);   
    connect(sockfd, (struct sockaddr *)&server, len);
    sleep(10);
    return 0;
}
*/
/*************************************************************************
	> File Name: client.c
	> Author:
	> Mail:
	> Created Time: Thu 04 Jun 2020 07:50:11 PM CST
 ************************************************************************/

#include "../common/head.h"
#include "../common/udp_client.h"

char server_ip[20] = {0};
int server_port = 0;
char *conf = "./football.conf";

int main(int argc, char **argv)  {
    int opt, sockfd;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    while ((opt = getopt(argc, argv, "h:p:n:t:m:")) != -1) {
        switch (opt) {
            case 'h':
                strcpy(server_ip, optarg);
                break;
            case 'p':
                server_port = atoi(optarg);
                break;
            case 'n':
                strcpy(request.name, optarg);
                break;
            case 't':
                request.team = atoi(optarg);
                break;
            case 'm':
                strcpy(request.msg, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
                exit(1);

        }
    }

    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc  > 1) {
        fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
        exit(1);
    }

    if (!server_port) server_port = atoi(get_value(conf, "SERVERPORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_value(conf, "SERVERIP"));
    if (!strlen(request.name)) strcpy(request.name, get_value(conf, "NAME"));
    if (!strlen(request.msg)) strcpy(request.msg, get_value(conf, "LOGMSG"));
    if (!request.team) request.team = atoi(get_value(conf, "TEAM"));

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    DBG(GREEN"INFO"NONE" : server_ip = %s, server_port = %d, name = %s, team = %s logmsg = %s\n", server_ip, server_port, request.name, (request.team ? "BLUE" : "RED"), request.msg);

    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);

    int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
    if (ret != sizeof(response) || response.type) {
        DBG(RED"ERROR : "NONE"The Game Server refused your login.\n\tThis May be helpfull: %s\n", response.msg);
        exit(1);
    }

    DBG(GREEN"SERVER : "NONE" %s \n", response.msg);
    connect(sockfd, (struct sockaddr *)&server, len);

    sleep(10);

    return 0;
}
