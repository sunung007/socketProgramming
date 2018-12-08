# Socket Programming

컴퓨터네트워크(12510, 조인휘 교수님) 기말 과제

컴퓨터소프트웨어학부 2017029425 김선웅

## 개발환경

ubuntu 18.04.1 LTS

vim version 8.0.1453


## 개요
client-server model에서 TCP/IP protocol을 이용한 소켓 프로그래밍.

server에서 client로 파일(*.txt*)을 전송할 수 있도록 구현하였다.
편의상 server에서 client로 ```sending.txt```파일을 전송하고, client에서 해당 파일을 ```received.txt```로 저장한다.
파일 전송이 완료될 경우 server는 client로 부터 ***Thank you*** 라는 메세지를 받고 종료가 되고, client는 그냥 종료가 된다.

client의 ip adress는 *127.0.0.1*이고, port number는 50000으로 설정하였다.

### server










This is a program to do file exchange in TCP/IP protocol using TCP, not UDP. I used Server-Client model, but in this program I implemented function, which is sending a file from server to client.
