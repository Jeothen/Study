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

