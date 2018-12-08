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
### 개요
server에서 client로 파일을 전송하기 위해서는 크게 아래의 함수 호출의 과정을 거친다.

***socket -> bind -> listen -> accept -> send -> close***

- socket

### 실행
server에서 client로 파일을 전송하기 위해서 server을 실행할 때 client의 port number를 main의 인자로 보내야한다. 때문에 실행 format인 ```./server [client_port_number]```을 준수하지 않았을 경우,
```
if(argc != 2)
  error_handling("Format : server [port]");
```
을 실행시켜 프로그램을 종료한다.

### 파일 오픈
