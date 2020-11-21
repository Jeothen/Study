

## Concept



#### 가상환경 구축

* python : virtualenv
* java : JDK (JVM + JRE) 
* python3에서는 vena 명령을 통해 패키지 설치 없이 가상환경 구축

---

#### CGI (Common Gatewat Interface)

* 정적인 웹 서버를 동적으로 서비스로 제공하기 위한 웹 서비스의 표준
* 웹 서버에서 직접 웹 애플리케이션을 작동시키기 위한 Interface
* 과거에는 외부 프로그램이 필요한 Request가 들어오면 CGI를 통해 Process를 Fork 하고 외부 프로그램을 실행시켰지만, 근래에는 웹서버에 Interpreter를 내장시켜 외부 프로그램을 실행시키지 않고 내부에서 처리
* 요청 -> 웹서버 -> 프로그램(웹서버가 직접 실행)

#### WAS (Web Application Server)

* CGI 표준을 바탕으로 실행할 수 있는 웹 서버
* Web Server (nginx, apache 등 이미지나 html 같은 정적인 리소스를 전달하는 역할 ) + CGI
* jsp, php 같은 웹 프로그래밍이 WAS에서 작동
* 동적으로 동작하며 DB와 연동되어 있고, 비지니스 로직을 포함
* 일반적으로 Java EE (enterprise edition)을 WAS라고 부르며 Tomcat, JBoss 등이 WAS
* 클라이언트에서 http 요청이 Web Server에 전송되고, Web Server가 리버스 프록시로 설정되어 캐싱 파일이나 포트로 연결된 WAS 등을 호출
  * 리버스 프록시 : 노출되어 있는 네트워크에 단일 서버 및 http 서비스에 대한 단일 엑세스 지점을 제공하여 내부 서버를 보호
    * 리버스 프록시 서버와 연결된 URL만 사용자에게 제공
    * 공유기에서 웹 서버로 바로 접근하는 경우 포트포워딩을 이용하지만, 리버스 프록시 서버가 있는 경우 리버스 프록시 서버에서 각 웹 서버로 접속
    * 로드밸런싱 기능

#### WSGI (Web Server Gateway Interface)

* 파이썬 스크립트 (웹 애플리케이션)가 웹서버와 통신하기 위한 interface

* WSGI Server (middleware) : 웹 서버와 WSGI를 지원하는 웹 애플리케이션(DJango, Falsk) 사이에서 동작

  * 환경 변수 변경시, Target URL에 따라 Request 경로 변경

  * 하나의 프로세스에서 여러 애플리케이션 실행
  * 로드밸런싱 기능

* Web Server 내 WSGI Module을 통해서 WSGI Process 구동
* `managy.py runserver`  대신 Gunicorn(WSGI Proess)을 이용하여 서버 실행
  * Django는 단일 프로세스, 쓰레드인데 (Green Unicorn)은 여러 프로세스를 작동시켜 request 요청을 효율적으로 처리

* CGI 는 프레임워크, 웹 서버에 의존적이지만, WSGI 는 프레임워크, 웹 서버의 종류에 독립적
* WSGI는 Web Server를 변경하여도 애플리케이션 코드를 변경할 필요가 없고 WSGI를 (GUnicorn -> uWSGI)로 변경 가능

---

프로세스 상태를 모니터링하고 죽은 프로세스를 다시 살리는 로직 등을 auto로 구현

#### Upstart

* 서비스 간 의존성을 설정할 수 있어 순서대로 진행
* 비동기 로직에서도 서비스를 직렬로 작동하여 비효율적

#### Systemd

* Linux 운영체제 용 시스템 및 서비스 관리자
* systemd는 기본 init 시스템으로 upstart를 대체
* 소켓에서 수신 대기하고, 트래픽에 대한 응답으로 G Unicorn을 자동으로 시작
* 부팅 속도도 빠르고, 불필요한 서비스는 올라가지 않아 시스템 자원 절약
* /etc/systemd/system/ 내 서비스 파일 정의 / ``$ sudo systemctl 명령어 사용

#### Supervisor

* init 시스템 없이 실행할 수 없음

* supervisord : 백그라운드 데몬 프로세스 /  ``$ sudo supervisord`` 명령어 사용
* /etc/supervisor/supervisor.conf 내 프로그램 및 실행할 명령을 설정하고 `` $ sudo supervisorctl`` 명령어를 이용해 실행

---



### Ubuntu Server 20.04 LTS 



#### VDI

**Processor Architecture : 64 bits**

**VID Size : 10 GB**



#### Network

**SSH : Enable (Bridge to adapter).**  

Bridge -> port forwarding not operated



#### env Setting

* MAC : Internet Share Settings

* router ip에 접속해서  SSH port 22 / 80 

  * ``$ nano .bashrc`` 명령에서   alias ->  user @local ip 확인
  * Local linux

* openssh-server 설치

* ssh serve / client 설치

* 22번 포트 방화벽 해제

* ssh service start



#### 학습 할 내용

* host - client 간 통신
  * Flask Framework를 Linux 환경에서 구현
  * api server test
* Flask nginx / wsgi 를 이용하여 deploy (~11/20)



* Cloud Deploy (~11/22)







