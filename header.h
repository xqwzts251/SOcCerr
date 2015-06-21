#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define clear() printf("\033[H\033[J")
#define PITCH_X_SIZE 8
#define PITCH_Y_SIZE 10
#define GOAL_WIDTH 2
#include <stdio.h>
/**
  TODO: Zmienic sterowanie - popatrz na numpad!

*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <signal.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "header.h"
extern char id[30];
extern char ip[30];
extern int port;
///TODO: POMYSLEC NAD TRYBEM VIEWERA

pthread_t ioThread;
pthread_t parent;
pid_t parentPid;
extern int mySocket; //-1 by sprawdzic czy sie polaczylismy gdzies po prostu
extern int iAmFirst; //Czy jestem graczem nr 1
extern struct sockaddr_in remoteAddr;
extern struct sockaddr_in myAddr;
extern struct pitch myPitch;

extern int currX, currY;


enum gameStatus
{
    GAME_PLAYING,
    PLAYER_ONE_WINS,
    PLAYER_TWO_WINS,
    PLAYER_ONE_SURRENDING,
    PLAYER_TWO_SURRENDING,
    DRAW_REQUEST,
    DRAW,
    ENDED,
    DISCONNECTED
};

enum playerStatus
{
    PLAYING,
    WAITING,
    BEING
};

enum serverRequest
{
    REGISTER,
    FIND_SPECIFIC,
    FIND,
    FOUNDED, //?
    HIGH_SCORE,
    TURN

};

enum borderStatus
{
    BORDER_UP,
    BORDER_DOWN,
    BORDER_LEFT,
    BORDER_RIGHT,
};

enum pointStatus
{
    NORMAL,
    TAKEN, //Znaczy sie mozna sie odbic od niego
    GOAL
};

enum serverResponse
{
    ACCEPTED,
    NOTACCEPTED
};

struct message
{
    int x, y;
    int idOneTurn; //Czy id1 ma teraz ture
    int sock1, sock2; //Nr socketow, aby nie szukac niepotrzebnie w tablicy
    int isEnded;
    enum gameStatus status;
};

struct serverCaller
{
    char id[30];
    char id2[30];
    enum serverRequest request;
    enum serverResponse response;
    struct message msg; //Niechserwer decyduje kto ma grac pierwszy itd.

};

struct clientCaller
{
    enum serverResponse response;
    char id[30];
    char id2[30];

};

struct point
{
    enum pointStatus status;
    int neighbours[8];
    int isItBall;
    /*
    1 2 3
    0 x 4
    7 6 5
    */
};

struct pitch
{
    struct point points[PITCH_X_SIZE][PITCH_Y_SIZE + 2];///TODO: Zdefine'owac wymiary boikska i sprawdzic czy to zadziala
};

struct playerInfo
{
    char id[30];
    int sock;
    enum playerStatus status;

};

extern void menu();
extern void drawLogo();
extern void printOptions();
extern void prepareToGame();
extern void getHighScore();
extern void manual();
extern void findPlayer(int type); //1 - specific, 0 - normal
extern void playGame(struct serverCaller);
extern void registerName();
extern void drawPitch();
extern struct serverCaller move(struct serverCaller caller);
extern struct serverCaller receive();
extern void actualize(struct serverCaller call);
extern void initPitch();
extern void sender(struct serverCaller call);
extern int canILeave(struct point p);
extern void fill(int i, int j, int val, int status);
extern void estabilishNetConnection();
extern void cleaner();
extern void printPointStatus(struct point p);
#endif // HEADER_H_INCLUDED
