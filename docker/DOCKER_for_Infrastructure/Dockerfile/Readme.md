## Dockerfile을 사용한 코드에 의한 서버 구축

* Docker에서는 인프라 구성 관리를 Dockerfile로 기술
* Dockerfile에는 베이스 이미지에 각종 미들웨어를 설치 및 설정하고, 개발한 애플리케이션 실행 모듈을 전개하기 위한 애플리케이션 실행 기반의 모든 구성 정보를 기술

---

### Dockerfile을 사용한 구성 관리

* 이미지 생성, 컨테이너 생성, 생성한 컨테이너 내 OS의 설정이나 미들웨어 설치, 파라미터 설정 같은 정보를 인프라 설계서나 parameter sheet 등에 별도로 기재할 필요가 있음
  * 베이스가 될 Docker Image
  * Docker 컨테이너 안에서 수행한 조작 (명령)
  * 환경변수 등 설정
  * Docker 컨테이너 안에서 작동시켜둘 데몬 실행
* Dockerfile : Docker 상에서 작동시킬 컨테이의 구성 정보를 기술하기 위한 파일
* docker build 명령 : Dockerfile에 기술된 구성정보를 바탕으로 Docker Image 작성

---

#### Dockerfile의 기본 구문

* Dockerfile은 텍스트 형식의 파일로, 에디터 등을 사용하여 작성
* 확장자가 필요 없으며, Dockerfile 이라는 파일에 인프라의 구성 정보를 기술
* Dockerfile 이외의 파일 명으로도 작동하지만, Dockerfile에 이미지를 빌드할 때 파일명을 명시적으로 지정
* Dockerfile의 명령

| 명령        | 설명                       |
| ----------- | -------------------------- |
| FROM        | 베이스 이미지 지정         |
| RUN         | 명령 실행                  |
| CMD         | 컨테이너 실행 명령         |
| LABEL       | 라벨 설정                  |
| EXPOSE      | 포트 익스포트              |
| ENV         | 환경 변수                  |
| ADD         | 파일 / 디렉토리 추가       |
| COPY        | 파일 복사                  |
| ENTRYPOINT  | 컨테이너 실행 명령         |
| VOLUME      | 볼륨 마운트                |
| USER        | 사용자 지정                |
| WORKDIR     | 작업 디렉토리              |
| ARG         | Dockerfile안의 변수        |
| ONBUILD     | 빌드 완료 후 실행되는 명령 |
| STOPSIGNAL  | 시스템 콜 시그널 설정      |
| HEALTHCHECK | 컨테이너의 헬스 체크       |
| SHELL       | 기본 쉘 설정               |

- RUN은 새로운 레이어에서 명령을 실행하고 새로운 이미지를 생성.  소프트웨어 패키지를 설치하는 데 주로 사용
- CMD는 기본 명령 또는 파라미터를 설정하며, 도커 컨테이너가 실행될 때 명령 줄에서 덮어 쓸 수 있음
- ENTRYPOINT는 실행 파일로 실행될 컨테이너를 구성

---

### Dockerfile 작성

* From 명령 (어떤 Docker Image로부터 생성할지)

```shell
FROM [이미지명]
FROM [이미지명]:[태그명]
FROM [이미지명]:[다이제스트]
# 태그 생략시 최신 버전(latest)
```

* 이미지명이나 태그명은 작성자가 임의의 값을 붙일 수 있기 때문에, Dockerfile을 수정해도 똑같은 이름을 중복하여 이미지 생성 가능

* 이미지를 고유하게 특정할 때는 다이제스트 사용
  * 다이제스트 : Docker Hub로 업로드하면 자동으로 부여되는 식별자 / 고유한 식별자라 이미지를 고유하게 지정할 수 있음

```shell
$ docker image ls --digests centos
REPOSITORY          TAG                 DIGEST             IMAGE ID            CREATED             SIZE
centos              latest              sha256:76d24f3...  0d120b6ccaa8        2 months ago        215MB
```

* 다이제스트를 지정한 Dockerfile

```shell
# 베이스 이미지 설정
FROM centos@sha256:76d24f3ba3317fa945743bb3746fbaf3a...
```

---

### Dockerfile 빌드와 이미지 레이어

* Dockerfile로부터 Docker Image 생성

* docker build 명령

```shell
$ docker build -t [생성할 이미지명]:[태그명] [Dockerfile의 path]
```

* docker build 명령

```shell
$ docker build -t sample_iamge:1.0 ./  # 절대경로도 가능
Sending build context to Docker daemon  6.656kB
Step 1/1 : FROM centos:centos7
centos7: Pulling from library/centos
75f829a71a1c: Pull complete 
Digest: sha256:19a79828ca2e505eaee0ff38c2f3fd9901f4826737295157cc5212b7a372cd2b
Status: Downloaded newer image for centos:centos7
 ---> 7e6257c9f8d8  # Image ID
Successfully built 7e6257c9f8d8
Successfully tagged sample_iamge:1.0

$ docker image ls # 2개의 이미지가 생성됨을 확인할 수 있음  (FROM centos:centos7)
REPOSITORY           TAG         IMAGE ID            CREATED             SIZE
centos             centos7     7e6257c9f8d8        2 months ago        203MB
sample_iamge         1.0       7e6257c9f8d8        2 months ago        203MB

$ docker build -t sample_image:2.0 ./  # Docker 레지스터에서 다운로드 하지 않기 때문에 이미지를 바로 생성
Sending build context to Docker daemon   7.68kB
Step 1/1 : FROM centos:centos7
 ---> 7e6257c9f8d8
Successfully built 7e6257c9f8d8
Successfully tagged sample_image:2.0
$ docker image ls
REPOSITORY         TAG              IMAGE ID            CREATED             SIZE
centos           centos7          7e6257c9f8d8        2 months ago        203MB
sample_iamge      1.0             7e6257c9f8d8        2 months ago        203MB
sample_image      2.0             7e6257c9f8d8        2 months ago        203MB
```

* 같은 Dockerfile에서 생성한 이미지들은 다른 이른 Repository/Tag을 가지고 있지만, Image ID는 동일 (모두 동일한 이미지
* 파일명을 지정한 docker build 명령 실행 (-f 옵션)
  * 파일명을 지정할 때는 Docker Hub에서 이미지 자동 생성 기능을 사용할 수 없음

```shell
$ docker build -t sample -f Dockerfile.test ./
Sending build context to Docker daemon  9.728kB
Step 1/1 : FROM centos:centos7
 ---> 7e6257c9f8d8
Successfully built 7e6257c9f8d8
Successfully tagged sample:latest
```

* 표준 입력을 경유하여 Dockerfiledd을 지정한 후 빌드
  * 빌드에 필요한 파일을 추가할 수 없기 때문에, 다른 명령(ex) ADD)으로 이미지 안에 파일을 추가할 수 없음
  * Dockerfile의 내용을 docker build 명령의 인수로 전달하므로 -(하이픈)을 지정

```shell
$  docker build - < Dockerfile
Sending build context to Docker daemon  2.048kB
Step 1/1 : FROM centos:centos7
 ---> 7e6257c9f8d8
Successfully built 7e6257c9f8d8
```

* -> Dockerfile과 빌드에 필요한 파일을 tar파일로 묶은 후 표준 입력 (p158)

---

##### 중간이미지의 재이용

* Docker는 이미지를 빌드할 때 자동으로 중간 이미지를 생성
* 다른 이미지를 빌드할 때 중간 이미지를 내부적으로 재이용하여 빌드를 고속에서 수행
* 중간 이미지 캐시를 사용하고 싶지 않을 땐 build 할 때, --no-cache 옵션 지정

---

#### Docker Image의 레이어 구조

* 이미지 레이어 구조

```shell
$ docker build -t webap_test2 . 
Sending build context to Docker daemon  289.8kB
Step 1/4 : FROM ubuntu:latest
 ---> d70eaf7277ea  # 첫번째 이미지 생성
Step 2/4 : RUN apt-get update && apt-get install -y -q nginx
 ---> Using cache  # 중간 이미지 캐시를 사용
 ---> c8ace2e7e1aa # 두번째 이미지 생성
Step 3/4 : COPY google_search.html ./
 ---> ce1ed1cfbb0f  # 세번째 이미지 생성
Step 4/4 : CMD ["nginx", "-g", "daemon off;"]
 ---> Running in ab8805043499 
Removing intermediate container ab8805043499
 ---> f67fbf410716  # 네번째 이미지 생성
Successfully built f67fbf410716
Successfully tagged webap_test2:latest
```

* 공통 베이스를 바탕으로 여러개의 이미지를 작성할 때, 베이스 이미지를 겹침으로써 레이어가 공유되며 Docker에서 디스크 용량을 효율적으로 이용
* 이미지가 OS파일을 포함하고 있기 떄문에 용량이 커서 Docker Hub에서도 같은 이미지를 겹쳐서 용량을 효율적으로 관리

---

### 멀티스테이지 빌드를 사용한 애플리케이션 개발

* 애플리케이션 개발 시 개발 환경에서 사용한 라이브러리나 개발 지원 툴이 제품 환경에 반드시 적용되는 건 아님
* 제품 환경에서 애플리케이션을 구동하기 위한 최소한의 실행 모듈만 배치하는 것이 리소스를 효율적으로 활용 (보안 관점에서 중요)

```shell

# 1. Build Image
FROM golang:1.13 AS builder

# Install dependencies
WORKDIR /go/src/github.com/asashiho/dockertext-greet
RUN go get -d -v github.com/urfave/cli

# Build modules
COPY main.go .
RUN GOOS=linux go build -a -o greet .

# ------------------------------
# 2. Production Image
FROM busybox
WORKDIR /opt/greet/bin

# Deploy modules
COPY --from=builder /go/src/github.com/asashiho/dockertext-greet/ .
ENTRYPOINT ["./greet"]
```

1. 개발 환경용 Docker Image
   * Go:1.8.4를 베이스 이미지로 지정 
   * 로컬 환경에 있는 소스코드를 컨테이너 안으로 복사
   * 이 소스코드를 go build 명령으로 빌드하여 greet 이라는 이름의 실행 가능 바이너리 파일 작성
2. 제품 환경용 Docker Image
   * busybox를 베이스 이미지로 지정 (busybox는 기본적인 Linux 명령들을 하나의 파일로 모은 것, Linux shell 환경을 제공하는 경우 이용)
   * Docker Image로 빌드한 greet이라는 실행 가능 바이너리 파일을 제품 환경용 Docker 이미지로 복사
     * --from 옵션을 사용하여 'builder'라는 이름의 이미지로부터 복사함을 선언
   * 복사한 실행 가능 바이너리 파일을 실행하는 명령

```shell
$ docker build -t greet .
Sending build context to Docker daemon  3.584kB
Step 1/9 : FROM golang:1.13 AS builder
1.13: Pulling from library/golang
d6ff36c9ec48: Pull complete 
c958d65b3090: Pull complete 
edaf0a6b092f: Pull complete 
80931cf68816: Pull complete 
813643441356: Pull complete 
799f41bb59c9: Pull complete 
16b5038bccc8: Pull complete 
Digest: sha256:8ebb6d5a48deef738381b56b1d4cd33d99a5d608e0d03c5fe8dfa3f68d41a1f8
Status: Downloaded newer image for golang:1.13
 ---> d6f3656320fe
Step 2/9 : WORKDIR /go/src/github.com/asashiho/dockertext-greet
 ---> Running in 69388b86d732
Removing intermediate container 69388b86d732
 ---> 03b3b835b662
Step 3/9 : RUN go get -d -v github.com/urfave/cli
 ---> Running in b81f8b90c09a
github.com/urfave/cli (download)
github.com/cpuguy83/go-md2man (download)
Removing intermediate container b81f8b90c09a
 ---> 45cc0ea4c82d
Step 4/9 : COPY main.go .
 ---> 330012865119
Step 5/9 : RUN GOOS=linux go build -a -o greet .
 ---> Running in 2ec2492d5f6d
Removing intermediate container 2ec2492d5f6d
 ---> 68bb346e0512
 
Step 6/9 : FROM busybox
latest: Pulling from library/busybox
9758c28807f2: Pull complete 
Digest: sha256:a9286defaba7b3a519d585ba0e37d0b2cbee74ebfe590960b0b1d6a5e97d1e1d
Status: Downloaded newer image for busybox:latest
 ---> f0b02e9d092d
Step 7/9 : WORKDIR /opt/greet/bin
 ---> Running in d54475e009fd
Removing intermediate container d54475e009fd
 ---> d728a2f626d9
Step 8/9 : COPY --from=builder /go/src/github.com/asashiho/dockertext-greet/ .
 ---> 6fe370f87066
Step 9/9 : ENTRYPOINT ["./greet"]
 ---> Running in 23b496c23c64
Removing intermediate container 23b496c23c64
 ---> ab5782a77fee
Successfully built ab5782a77fee
Successfully tagged greet:latest
```

* Docker Hub에서 개발용 환경의 베이스 이미지인 'golang:1.8.4-jessie'를 다운로드하여 개발 환경용 이미지 'builder' 생성
* builder 이미지로 소스코드를 빌드하여 실행 가능한 바이너리 파일 생성
* 제품 환경용 이미지에 실행 가능한 바이너리 파일 복사

```shell
$ docker image ls
REPOSITORY      TAG       IMAGE ID            CREATED             SIZE
greet         latest     ab5782a77fee        2 minutes ago       6.03MB
busybox       latest     f0b02e9d092d        2 weeks ago         1.23MB
golang         1.13      d6f3656320fe        2 months ago        803MB
```

* 개발 환경용 이미지인 golang은 803MB
* 제품 환경용 이미지은 great는 6.03MB - 제품 환경용 베이스 이미지인 busybox의 실행에 필요한 모듈만 추가
* 가능한 한 용량이 적은 이미지를 사용하여 시스템 리소를 효율적으로 활용

#### Docker 컨테이너 시작

```shell
$ docker container run -it --rm greet asa
Hello asa
$ docker container run -it --rm greet --lang=es asa
Hola asa
```

---

### 명령 및 데몬 실행

* Docker Image를 만들려면 필요한 미들웨어를 설치하고, 사용자 계정이나 디렉토리를 작성하는 등의 명령을 실행

#### 명령 실행 (RUN 명령)

* 컨테이너에는 FROM 명령에서 지정한 베이스 이미지에 대해 '애플리케이션/미들웨어를 설치 및 설정'

* Run 명령 ``Run [실행하고 싶은 명령]``



* Shell 형식으로 기술

  * Shell 형식의 RUN 명령 실행

  ```shell
  # Nginx의 설치
  RUN apt-get install -y nginx
  ```

  * Docker 컨테이너 안에서 ``/bin/sh -c`` 를 사용하여 명령을 실행했을 때와 같이 동작
  * Docker Container에서 실행할 기본 쉘을 변경하고 싶을 땐 SHELL 명령을 사용

* Exec 형식으로 기술

  * Shell 형식으로 명령을 기술하면, ``/bin/sh` 에서 실행되지만, Exec 형식으로 기술하면 쉘을 경유하지 않고 직접 실행
    * 명령 인수에 따라 $HOME과 같은 환경변수를 저장할 수 없음
    * Exec 형식에서 실행하고 싶은 명령을 JSON 배열로 지정

  * Shell 경로를 지정한 후 명령 (-c : cpu shares)

    ```shell
    # Nginx의 설치
    RUN ["/bin/bash", "-c", "apt-get install -y nginx"]
    ```

  * RUN 명령의 예시

  ```shell
  # 베이스 이미지 설정
  FROM ubuntu:latest
  
  # RUN 명령의 실행
  RUN echo Hello Shell type
  RUN ["echo", " Hello Exec type"]
  RUN ["/bin/bash", "-c", "echo ' Hello Using bash on Exec type']
  ```

  * RUN 명령은 순서대로 실행됨.

  * RUN 명령의 실행 로그

  ```shell
  docker build -t run-sample .
  Sending build context to Docker daemon  2.562MB
  Step 1/4 : FROM ubuntu:latest
   ---> d70eaf7277ea
  Step 2/4 : RUN echo Hello Shell type
   ---> Running in d70d073fbee7
  Hello Shell type
  Removing intermediate container d70d073fbee7
   ---> 7144de2e6467
  Step 3/4 : RUN ["echo", " Hello Exec type "]
   ---> Running in ad16b1e14db2
   Hello Exec type 
  Removing intermediate container ad16b1e14db2
   ---> 3dc0bb47ecdd
  Step 4/4 : RUN ["/bin/bash", "-c", "echo ' Hello Using bash on Exec type ' "]
   ---> Running in 4559d21a7b48
   Hello Using bash on Exec type 
  Removing intermediate container 4559d21a7b48
   ---> d8bc9b71ab28
  Successfully built d8bc9b71ab28
  Successfully tagged run-sample:latest
  
  $ docker image ls      
  REPOSITORY       TAG           IMAGE ID            CREATED              SIZE
  run-sample      latest         d8bc9b71ab28        About a minute ago   72.9MB
  ```

  * 이미지 구성 History

  ```shell
  $ docker history run-sample
  IMAGE           CREATED              CREATED BY                                      SIZE        COMMENT
  d8bc9b71ab28    About a minute ago   /bin/bash -c echo ' Hello Using bash on Exec…   0B                  
  3dc0bb47ecdd    About a minute ago   echo  Hello Exec type                           0B                  
  7144de2e6467    About a minute ago   /bin/sh -c echo Hello Shell type                0B                  
  ```

  * 실행 결과가 쉘을 통하지 않고 실행됨
  * layer가 아래부터 쌓이는 것을 확인할 수 있음

  ---

  #### 이미지 레이어

  * Dockerfile을 빌드하면 명령마다 내부 이미지가 하나씩 작성

  ```shell
  RUN yum -y install httpd
  RUN yum -y install php
  RUN yum -y install php-mbstring
  RUN yum -y install php-pear
  ```

  * RUN 명령을 한 줄로 지정

  ```
  RUN yum -y install httpd php php-mbstring php-pear
  ```

  * RUN 명령의 줄 바꿈

  ```shell
  RUN yum -y install \
  					 httpd\
  					 php\
  					 php-mbstring\
  					 php-pear
  ```

---

### 데몬 실행 (CMD 명령)

* RUN 명령은 이미지 작성을 위해 실행하는 명령을 기술하지만, CMD 명령을 사용해 이미지를 바탕으로 생성된 컨테이너 안에서 명령을 실행

* Dockerfile에는 하나의 CMD 명령을 기술할 수 있음 (만약 여러개를 지정할 경우 마지막 명령만 유효함)

* CMD 명령

  ```shell
  CMD [실행하고 싶은 명령]
  ```

* Exec 형식으로 기술

  * Exec 형식은 shell을 호출하지 않음. 인수는 JSON 베열로 지정

  ```shell
  CMD ["nginx", "-g", "daemon off;"]
  ```

* Shell 형식으로 기술

  * 쉘을 호출하여 실행

  ```shell
  CMD nginx -g 'daemon off'
  ```

* ENTRYPOINT 명령의 파라미터로 기술
  
  * ENTRYPOINT 명령의 인수로 CMD 명령을 사용. (daemon 실행 : ENTRYPOINT 명령)



* CMD 명령 (ubuntu:16.04 에서 nginx 설치 후 데몬 실행.  웹 서버로 액세스하기 위해 EXPOSE 명령을 사용하여 80번 포트 지정 )

```shell
# 베이스 이미지 설정
FROM ubuntu:16.04

# Nginx 설치
RUN apt-get -y update && apt-get -y upgrade
RUN apt-get -y install nginx

# 포트 지정
EXPOSE 80

# 서버 실행
CMD ["nginx", "-g", "daemon off;"]
```



* 컨테이너 실행 

```shell
# docker image 생성
$ docker build -t cmd-sample .
# 이미지를 바탕으로 컨테이너 실행
$ docker container run -p 80:80 -d cmd-sample
CONTAINER ID        IMAGE       COMMAND                   CREATED            STATUS          PORTS         NAMES
18a1eb88a591     cmd-sample   "nginx -g 'daemon of…"   7 seconds ago    Up 6 seconds   0.0.0.0:80->80/tcp     clever_hodgkin
```

---

#### 패키지 관리 시스템

* 애플리케이션 설치 시에 발생하는 의존 관계를 모아서 관리하는 시스템
* Linux의 패키지 관리 시스템으로 YUM, APT
  * YUM (Yellowdog Updater Modified)
    * Centos나 Fedora와 같은 RedHat 계열 디스트리뷰션에서 이용하는 패키지 관리 시스템
    * 패키지를 설치하면 관련된 패키지까지 자동으로 설치
    * 최근에는 YUM의 후계자?인 DNF(Dandified Yum)도 사용 중
  * APT (Advanced Packaging Tool)
    * Debian이나 Unbuntu와 같은 Debian 계열 디스트리뷰션에서 이용하는 패키지 관리 시스템
    * 패키지의 의존 관계를 모아서 관리할 수 있음

----

### 데몬 실행 (ENTRYPOINT 명령)

* Dockerfile에서 빌드한 이미지로부터 Docker Container가 시작하기 때문에 ``docker container run`` 명령을 실행했을 때 실행됨

``` shell
ENTRYPOINT [실행하고 싶은 명령]
```

* Exec 형식으로 실행

  ```shell
  ENTRYPOINT ["nginx", "-g", "daemon off;"]
  ```

* Shell 형식으로 실행

  ```shell
  ENTRYPOINT nginx -g 'daemon off;'
  ```

* ENTRYPOINT 명령과 CMD 명령의 차이는 docker container run 명령 실행 시 동작

* ENTRYPOINT 명령에서 지정한 명령은 반드시 컨테이너에서 실행. 

* 실행 시 명령 인수를 지정하고 싶을 때는 CMD 명령과 조합하여 사용. ENTRYPOINT는 명령 자체를 지정

* ENTRYPOINT로 top 명령 실행. CMD 명령으로 갱신 간격인 -d 옵션을 10초로 지정

```shell
# Docker 이미지 취득
FROM ubuntu:16.04

# top 실행
ENTRYPOINT ["top"]
CMD ["-d", "10"]
```

* docker container run 으로 실행

```shell
$ docker build -t sample .  # 이미지 생성

$ docker container run -it sample   

$ docker container run -it sample -d 2 # 2초 간격으로 갱신

top - 14:13:18 up  1:47,  0 users,  load average: 0.33, 0.21, 0.23
Tasks:   1 total,   1 running,   0 sleeping,   0 stopped,   0 zombie
%Cpu(s):  1.2 us,  1.1 sy,  0.0 ni, 97.6 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
KiB Mem :  2034356 total,    83608 free,  1029476 used,   921272 buff/cache
KiB Swap:  1048572 total,  1036284 free,    12288 used.   853636 avail Mem 

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND    
    1 root      20   0   36664   3096   2680 R   0.0  0.2   0:00.03 top  
```

* CMD 명령은 docker container run 명령 실행 시에 덮어 쓸 수 있는 구조

---

### 빌드 완료 후에 실행되는 명령 (ONBUILD 명령)

* ONBUILD 명령은 그 다음 빌드에서 실행할 명령을 이미지 안에 설정하기 위한 명령
* ONBUILD 명령을 사용하여 어떤 명령을 실행하도록 설정하여 빌드하고 이미지를 작성
* 이미지를 다른 Dockerfile에서 베이스 이미지로 설정하여 빌드했을 때, ONBUILD 명령에서 지정한 명령을 실행시킬 수 있음

```shell
ONBUILD [실행하고 싶은 명령]
```

* 자신의 Dockerfile로부터 생성한 이미지를 베이스 이미지로 한 다른 Dockerfile에 빌드할 때 실행하고 싶은 명령을 기술
* 웹 시스템을 구축할 때 OS 설치 및 환경 설정이나 웹 서버 설치 및 각종 플러그인 설치 등과 같은 인프라 환경 구축과 관련된 부분을 베이스 이미지로 작성. 
* 이때, ONBUILD 명령으로 이미지 안에 개발한 프로그램을 전개하는 명령(ADD나 COPY)을 지정

---

##### 베이스 이미지 작성 (Dockerfile2.base)

* tar 파일 생성

```shell
$ docker container export interesting_saha > centos.tar
```



```shell
RUN apt-get -y update && apt-get -y upgrade

# 베이스 이미지 설정
FROM ubuntu:16.04

# Nginx
RUN apt-get -y install nginx

# 포트 지정
EXPOSE 80

# 웹 콘텐츠 배치
ONBUILD ADD centos.tar ./

# Nginx 실행
CMD ["nginx", "-g", "daemon off;"]
```



* dockfer build 명령을 사용하여 파일명을 지정할 때는 -f 옵션

```shell
$ docker build -t web-base -f Dockerfile2.base .
Sending build context to Docker daemon  224.9MB
Step 1/6 : FROM ubuntu:16.04
 ---> dfeff22e96ae
Step 2/6 : RUN apt-get -y update && apt-get -y upgrade
 ---> Using cache
 ---> 4e95baaeaba1
Step 3/6 : RUN apt-get -y install nginx
 ---> Using cache
 ---> adbcc5d7f06e
Step 4/6 : EXPOSE 80
 ---> Using cache
 ---> cd6c76d5940e
Step 5/6 : ONBUILD ADD centos.tar ./
 ---> Running in ef0e5d68b67a
Removing intermediate container ef0e5d68b67a
 ---> 902455720114
Step 6/6 : CMD ["nginx", "-g", "daemon off;"]
 ---> Running in 474caf3bad62
Removing intermediate container 474caf3bad62
 ---> 748e3c3e5ef7
Successfully built 748e3c3e5ef7
Successfully tagged web-base:latest
```

##### 웹 서버용 이미지 작성

```shell
$ docker image ls
REPOSITORY          TAG         IMAGE ID            CREATED             SIZE
web-base         latest        748e3c3e5ef7        2 minutes ago       223MB


# DockerTest
# Docker 이미지 취득
FROM web-base


$ docker build -t 
docker build -t web_base_container -f DockerTest .
Sending build context to Docker daemon  224.9MB
Step 1/1 : FROM web-base
# Executing 1 build trigger
 ---> 9ac417c59bd7
Successfully built 9ac417c59bd7
Successfully tagged web_base_container:latest
```

#####  웹 서버용 컨테이너 시작

```shell
$ docker container run -d -p 80:80 web_base_container
b9aee2ef7a9f987edc1d9f3445375191708181a65ded452fb3ed8b30283d3d90  (포트 중복 여부 확인)

$ docker container ls -a 
CONTAINER ID        IMAGE           COMMAND              CREATED         STATUS             PORTS     NAMES
b9aee2ef7a9f  web_base_container "nginx -g 'daemon of…" 3 minutes ago   Exited (127)3 minutes ago  goofy_easley

$ docker container start 
```

docker image inspect 명령으로 ONBUILD 명령 유무 확인

* 이미지의 상세 정보 확인

```shell
$ docker image inspect --format="{{ .Config.OnBuild }}" web-base
[ADD centos.tar ./]
```

---

#### 시스템 콜 시그널의 설정 (STOPSIGNAL 명령)

* 컨테이너를 종료할 때 ``STOPSIGNAL [시그널] `` 옵션을 이용하여 송신 시그널을 설정
* 시그널 번호 또는 시그널명(SIGKILL 등)을 지정

#### 컨테이너 헬스 체크 명령 (HEALTHCHECK 명령)

* 컨테이너 안의 프로세스가 정상적으로 작동하고 있는지를 체크하고 싶을 때 사용

```
HEALTHCHECK [옵션] CMD 실행할 명령
```

* 지정할 수 있는 옵션

| 옵션         | 설명               | 기본값 |
| ------------ | ------------------ | ------ |
| --interval=n | 헬스 체크 간격     | 30s    |
| --timeout=n  | 헬스 체크 타임아웃 | 30s    |
| --retries=N  | 타임아웃 횟수      | 3      |

* 헬스 체크

````shell
HEALTHCHECK --interval=5m ---timeout=3s CMD curl -f http://localhost/ || exit 1

# 이미지 생성
$ docker build -t healthcheck ./
Step 2/4 : HEALTHCHECK --interval=100s --timeout=3s CMD curl -f http://localhost/ || exit 1
 ---> Running in 0381a7cae021
Successfully built 243af3a9219e
Successfully tagged healthcheck:latest

# 컨테이너 생성
$ docker create healthcheck
90da43d58d9fff1b42edb25c050d65dc896638d23f3d2f83151ab78155531374

$ docker container inspect wizardly_moore
[
    {
        "Id": "b7ee0b4bcf0129089528e830ade59611f01c2a0a03e6ebf6b9b3b8608178cd64",
        "Created": "2020-11-05T14:52:47.2215652Z",
       ...
            "Healthcheck": {
                "Test": [
                    "CMD-SHELL",
                    "curl -f http://localhost/ || exit 1"
                ],
                "Interval": 100000000000,
                "Timeout": 3000000000
            },
    }
]
````



---

###  환경 및 네트워크 설정

#### 환경변수 설정 (ENV 명령)

