# Socket Programming
컴퓨터네트워크(12510, 조인휘 교수님) 기말 과제

컴퓨터소프트웨어학부 2017029425 김선웅

## 개발환경 및 개요
### 개발환경
ubuntu 18.04.1 LTS

vim version 8.0.1453

### 개요
client-server model에서 TCP/IP protocol을 이용한 소켓 프로그래밍.

server에서 client로 파일(*.txt*)을 전송할 수 있도록 구현하였다.
편의상 server에서 client로 ```sending.txt```파일을 전송하고, client에서 해당 파일을 ```received.txt```로 저장한다.
파일 전송이 완료될 경우 server는 client로 부터 ***Thank you*** 라는 메세지를 받고 종료가 되고, client는 그냥 종료가 된다.

client의 ip adress는 *127.0.0.1*이고, port number는 50000으로 설정하였다.

----------

## [Server/Client 공통] Error handling
server.c와 client.c에서 모두 error handle을 위하여 ```error_handling()```함수를 구현하였다. 만약 에러가 발생할 경우 ```error_handling()```의 인자로 error message를 넣고 호출하여, 해당 message와 개행문자(\n)를 **STDERR**로 출력을 보내고 프로그램을 종료하게 구현하였다.

-----------

## Server
### 실행
server에서 client로 파일을 전송하기 위해서 server을 실행할 때 client의 port number를 main의 인자로 보내야한다. 때문에 실행 format인 ```./server [client_port_number]```을 준수하지 않았을 경우,
```
if(argc != 2)
  error_handling("Format : server [port]");
```
을 실행시켜 프로그램을 종료한다.

### 개요
server에서 client로 파일을 전송하기 위해서는 크게 아래의 함수 호출의 과정을 거친다.

**순서: *socket -> bind -> listen -> accept -> send -> close***

### socket
TCP protocol에서 사용하는 socket을 생성하기 위해서 3번째 argument로 6을 설정하였다. socket은 close하더라도 커널은 socket을 바로 kill하지 않고 일정 시간동안 alive한 상태(TIME_WAIT)로 유지한다. 이는 client로 아직 전송하지 않은 파일을 처리할 수 있도록 하기 위함이다. 이 때문에 프로그램을 종료한 뒤 일정시간 동안은 프로그램을 다시 실행시킬 경우 bind error가 발생한다.

이를 해결하기 위해서 ```server_socket```을 생성할 때 option을 부여해야한다. socket에 ```SO_REUSEADDR```이라는 옵션을 부여할 경우, 같은 port에 대해 다른 socket이 bind되는 것을 가능하게 해준다. 따라서 아래와 같은 코드를 추가하였다.

```
option = 1;
setsockopt( server_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option) );
```

```option = 1```을 통해서 ```SO_REUSEADDR```의 option을 1(TRUE)하게 설정하고, ```setsockopt()```을 통해서 socket의 option을 설정해주었다.


### 파일 오픈
