





#### 이미지 다운로드

| 옵션        | 설명                     |
| ----------- | ------------------------ |
| -all, -a    | 모든 이미지를 표시       |
| --digests   | 다이제스트를 표시 여부   |
| --no-trunc  | 결과를 모두 표시         |
| --quiet, -q | Docker Image의 ID만 표시 |



* Centos 버전7(태그명: 7)을 다운로드

```shell
$ docker image centos:7
```

* 태그명을 생략하면 latest를 다운로드
* 모든 태그의 Docker Image 다운로드

```shell
$ docker image pull -a centos
```

* 취득할 url을 지정하여 이미지를 다운로드 할 수도 있음

```shell
$ docker image pull gcr.io/tensorflow
```

* 도커 이미지 목록 표시

```shell
$ docker image ls       
REPOSITORY    TAG       IMAGE ID            CREATED             SIZE
mysql        latest    b5c10a3624ce        4 days ago          545MB
nginx        latest    992e3b7be046        2 weeks ago         133MB
```

| 항목       | 설명          |
| ---------- | ------------- |
| Repository | 이미지 이름   |
| TAG        | 이미지 태그명 |
| IMAGE ID   | 이미지 ID     |
| CREATED    | 작성일        |
| SIZE       | 이미지 크기   |



---

#### Image 위장이나 변조 방지

* DCT (Docker Content Trust) 기능을 사용하여 이미지의 정당성 확인
* 서명
  * 이미지 작성자가 Docker Registry에 이미지를 업로드 하기 전,  로컬 환경에서 이미지 작성자의 비밀 키(Offline Key)를 이용하여 이미지에 서명
* 검증
  * 서명된 이미지를 다운르드 할 때는, 이미지 작성자의 공개키(Tagging Key)를 사용하여 이미지가 진짜인지 아닌지 확인
  * 변조된 경우 이미지 무효화 처리
* DCT 기능 유효화

```shell
$ export DOCKER_CONTENT_TRUST=1
```

* 위 명령을 수행하면 pull 과정에서 Tagging Key를 이용하여 검증
* 서명이 되어 있지 않은 이미지를 다운로드 할 때 에러 발생
* value를 0으로 변경하여 무효화 처리

---

#### 이미지 상세 정보 확인 (docker Image Inspect)

* 이미지 상세 정보 표시

```shell
$ docker image inspect centos
```

* 주요 정보 : 이미지 ID / 작성일 / Docker 버전 / CPU 아키텍처

* ex) --format 옵션에서 JSON 형식 데이터의 계층 구조를 지정

```shell
$ docker image inspect --format="{{.Os}}" centos
linux
$ docker image inspect --format="{{.ContainerConfig.Image}}" centos
sha256:69587a438b2c9b803db8ed4f6e6b5abce25a6b8ec2583a394807cf82bfd23693
```

---

#### 이미지 태그 설정 (docker image tag)

* ``<Docker Hub 사용자명>/이미지명:[태그명]`` 을 이용하여 태그 설정

```shell
$ docker image ls
REPOSITORY     TAG        IMAGE ID            CREATED             SIZE
mysql        latest       b5c10a3624ce        4 days ago          545MB
nginx        latest       992e3b7be046        2 weeks ago         133MB

$ docker image tag nginx thjeong/webserver:1.0
$ docker image ls

REPOSITORY     TAG        IMAGE ID            CREATED             SIZE
mysql        latest       b5c10a3624ce        4 days ago          545MB
nginx        latest       992e3b7be046        2 weeks ago         133MB
thjeong/webserver   1.0   992e3b7be046        2 weeks ago         133MB

```

* 태그를 붙인 이미지와 original 이미지의 IMAGE ID는 동일
* 이미지의 이름이나 복사한 것이 아닌 태깅(별명)만 한 것

---

#### 이미지 검색 (docker search)

| 옵션             | 설명                          |
| ---------------- | ----------------------------- |
| --no-trunc       | 결과를 모두 표시              |
| --limit          | n건의 검색 결과를 표시        |
| --filter=stars=n | 즐겨찾기의 수 (n 이상)을 지정 |

```shell
$ docker search nginx
# --> 수많은 결과가 나옴

$ docker search --filter=stars=1000 nginx
NAME                DESCRIPTION               STARS            OFFICIAL            AUTOMATED
nginx          Official build of Nginx.       13912               [OK]         
```

* docker search 명령 결과

| 항목        | 설명                                                |
| ----------- | --------------------------------------------------- |
| NAME        | 이미지 이름                                         |
| DESCRIPTION | 이미지 설명                                         |
| STARS       | 즐겨찾기 수                                         |
| OFFICIAL    | 공식 이미지인지 아닌지                              |
| AUTOMATED   | Dockerfile을 바탕으로 자동 생성된 이미지인지 아닌지 |

---

#### 이미지 삭제

* docker image rm 명령

```shell
$ docker image rm [옵션] 이미지명 [이미지명]
```

* 지정할 수 있는 주요 옵션

| 옵션        | 설명                        |
| ----------- | --------------------------- |
| --force, -f | 이미지를 강제로 삭제        |
| --no-prune  | 중간 이미지를 삭제하지 않음 |



* 이미지 삭제

```shell
# 태깅된 이미지 삭제
$ docker image rmi -f thjeong/webserver:1.0
Untagged: thjeong/webserver:1.0
Deleted: sha256:992e3b7be0465856d44bed9b3d5596267205a4cfaec4241439be42f77b3539a3

$ docker image ls
REPOSITORY      TAG          IMAGE ID          CREATED             SIZE
nginx           <none>     7e4d58f0e5f3        6 weeks ago         133MB

# 정지되어 있는 모든 컨테이너 삭제
$ docker rm $(docker ps -a -q)

#이름 없는 image를 모두 삭제하는 기능
$ docker image prune -a
```

---

#### Docker Hub에 로그인 (docker login)

* docker login 옵션

```shell
$ docker login [옵션] [서버]
```

* 지정할 수 있는 주요 옵션

| 옵션           | 설명     |
| -------------- | -------- |
| --password, -p | 비밀번호 |
| --username, -u | 사용자명 |

---

#### 이미지 업로드 (docker image push)

```shell
$ docker image push 이미지명:[태그명]
```



```shell
$ docker image ls                       
REPOSITORY                           TAG                 IMAGE ID            CREATED             SIZE
jeothen/centos                       latest              0d120b6ccaa8        2 months ago        215MB
centos                               latest              0d120b6ccaa8        2 months ago        215MB
$ docker image push jeothen/centos 
...
latest: digest: sha256:fc4a234b91cc4b542bac8a6ad23b2ddcee60ae68fc4dbd4a52efb5f1b0baad71 size: 529

```

---

**컨테이너 생성 (docker container create 명령)**

* 이미지로부터 컨테이너 생성
* 이미지의 실체는 "Docker에서 서버 기능을 작동시키기 위해 필요한 디렉토리 및 파일들"
  * Linux의 작동에 필요한 /etc나 /bin 등과 같은 디렉토리 및 파일들
* docker container create 명령을 통해 이미지에 포함될 Linux의 디렉토리와 파일들이 스냅샷을 취함
  * 스토리지 안에 존재하는 파일과 디렉토리를 특정 시점에 추출
* Create 명령은 생성만 할 뿐, 컨테이너를 시작하지는 않음

**컨테이너 생성 및 시작 (docker container run 명령)**

* 이미지로부터 컨테이너를 생성하고, 컨테이너 상에서 임의의 프로세스를 시작
* Nginx나 Redis와 같은 서버 기능을 프로세스로 작동 (백그라운드에서 항시 실행하거나 강제 종료할 수 있음)
* 포트번호와 같은 네트워크도 설정함으로써 외부에서 컨테이너의 프로세스에 엑세스할 수 있음

**컨테이너 시작 (docker container run)**

* 정지 중인 컨테이너를 시작할 때 사용. 컨테이너에 할당된 컨테이너 식별자를 지정하여 컨테이너 시작

**컨테이너 정지**

* 실행중인 컨테이너를 정지할 때 사용. 컨테이너에 할당된 컨테이너 식별자를 지정하여 컨테이너 정지
* 컨테이너를 삭제할 땐, ``docker container stop`` 명령을 통해 사용중인 컨테이너를 정지 후 진행
* 컨테이너를 재시작하고 싶을 땐, ``docker container restart`` 명령 수행

**컨테이너 삭제**

* ``docker container rm`` 명령을 사용하여 정지 중인 컨테이너와 프로세스를 삭제

**컨테이너 상태 확인** : ``docker container ps``

**컨테이너 일시정지** : ``docker container pause``

---

#### 컨테이너 생성 및 시작 (docker container run)

* docker container run 명령

``docker container run [옵션] 이미지명:[태그명] [인수]``

| 옵션              | 설명                                                         |
| ----------------- | ------------------------------------------------------------ |
| --attach, -a      | 표준 입력(STDIN), 표준 출력(STDOUT), 표준 오류 출력 (STDERR)에 어태치 |
| --cidfile         | 컨테이너 ID를 파일로 출력                                    |
| --detach, -d      | 컨테이너를 생성하고, 백그라운드에서 실행                     |
| --interactive, -i | 컨테이너의 표준 입력을 연다                                  |
| --tty, -t         | 단말기 디바이스를 사용                                       |



* docker container run 실행

```` shell
$ docker container run -it --name "test1" centos  /bin/cal


docker container run : 컨테이너를 생성 및 실행
-it : 콘솔에 결과를 출력하는 옵션
--name "test1" : 컨테이너명
centos : 이미지명
/bin/cal : 컨테이너에서 실행한 명령

# centos라는 이름의 이미지를 바탕으로 test1 이라는 컨테이너를 실행
# 컨테이너 안에서 /bin/cal 명령을 실행  - Linux의 표준 명령으로 달력을 콘솔에 출력하는 명령 (/bin/bash 등 실행)
# -it : -i 옵션과 -t 옵션을 한번에 진행
````

* 컨테이너 이름은 --name 다음에 임의의 이름으로 지정 (생략시 컨테이너명 랜덤으로 지정)

----

**프롬프트** :  "$"나 "#" 같은 명령을 입력할 수 있는 표시

```shell
docker@default: ~$

# docker : 사용자명
# default : 호스트명
# ~ : 작업 디렉토리  (~: 틸다. 작업하고 있는 사용자의 홈 디렉토리)
# $ : 사용자 권한  ($ or % : 일반 사용자 / # : root 권한)
```

---

#### 컨테이너를 백그라운드에서 실행

``docker container run [실행옵션] 이미지명[:태그명] [인수]`` 를 통해 실행

* 지정할 수 있는 주요 옵션

| 옵션                                                         | 설명                                         |
| ------------------------------------------------------------ | -------------------------------------------- |
| --detach, -d                                                 | 백그라운드에서 실행                          |
| --user, -u                                                   | 사용자명을 지정                              |
| --restart=[no \| on-failure \| on-failure:횟수n \| always \| unless-stopped] | 명령의 실행 결과에 따라 재시작을 하는 옵션   |
| --rm                                                         | 명령 실행 완료 후에 컨테이너를 자동으로 삭제 |

* docker container run의 백그라운드 실행

```shell
$ docker container run -d centos /bin/ping localhost
605daf9d3b7eb2697a28b787d9c6ce0238b5b15e93d61c9d44f6f21adb3abd58
# docker container run : 컨테이너 생성 및 실행
# -d : 백그라운드에서 실행하는 옵션
# centos : 이미지명
# 컨테이너에서 실행할 명령 : /bin/ping localhost

# 백그라운드에서 실행되었는지 확인할 때 : docker containers log - 컨테이너 로그 확인
$ docker container logs -t 605daf9d3b7eb2697a28b787d9c6ce0238b5b15e93d61c9d44f6f21adb3abd58
2020-10-25T14:09:28.595861205Z PING localhost (127.0.0.1) 56(84) bytes of data.
2020-10-25T14:09:28.595882979Z 64 bytes from localhost (127.0.0.1): icmp_seq=1 ttl=64 time=0.050 ms
2020-10-25T14:09:29.595875430Z 64 bytes from localhost (127.0.0.1): icmp_seq=2 ttl=64 time=0.053 ms
2020-10-25T14:09:30.659061367Z 64 bytes from localhost (127.0.0.1): icmp_seq=3 ttl=64 time=0.037 ms

$ docker container stop 605daf9d3b7eb2697a28b787d9c6ce0238b5b15e93d61c9d44f6f21adb3abd58
605daf9d3b7eb2697a28b787d9c6ce0238b5b15e93d61c9d44f6f21adb3abd58
```



* restart 옵션

| 설정값           | 설명                                             |
| ---------------- | ------------------------------------------------ |
| no               | 재시작하지 않는다                                |
| on-failure       | 종료 status가 0이 아닐 때 재시작                 |
| on-failure:횟수n | 종료 status가 0이 아닐 때 n번 재시작             |
| always           | 항상 재시작                                      |
| unless-stopped   | 최근 컨테이너가 정지 상태가 아니라면 항상 재시작 |

``$ docker container run -it --restart=always centos /bin/bash`` 와 같이 restart 옵션 지정

----

#### 컨테이너의 네트워크 설정 (docker container run)

```shell
$ docker container run [네트워크 옵션] 이미지명[:태그명] [인수]
```

* 지정할 수 있는 주요 옵션

| 옵션                                                         | 설명                                             |
| ------------------------------------------------------------ | ------------------------------------------------ |
| --add-host=[호스트명:IP 주소]                                | 컨테이너의 /etc/host에 호스트명과 IP 주소를 정의 |
| --dns=[IP 주소]                                              | 컨테이너용 DNS 서버의 IP 주소 지정               |
| --expose                                                     | 지정한 범위의 포트 번호를 할당                   |
| --mac-address=[MAC 주소]                                     | 컨테이너의 MAC 주소를 지정                       |
| --net=[bridge \| none \| container:<<name:id>> \| host \| NETWORK] | 컨테이너의 네트워크 지정                         |
| --hostname, -h                                               | 컨테이 자신의 호스트명을 지정                    |
| --publish, -p[호스의 포트 번호]:[컨테이너의 포트 번호]       | 호스트와 컨테이너 포트 매핑                      |
| --publish-all, -p                                            | 호스트의 임의의 포토를 컨테이너에 할당           |

```shell
$ docker container run -d -p 8080:80 nginx

# nginx라는 이름의 이미지를 바탕으로 컨테이너를 생성하고, 백그라운드에서 실행
# 호스트 포트 번호 8080과 컨테이너의 포트 번호 80을 매핑
# 이 명령을 실행한  호스트의 8080 포트에 엑세스하면 컨테이너에서 작동하고 있는 nginx(80번 포트)의 서비스에 엑세스할 수 있음 
```

* 컨테이의 DNS 서버 지정

```shell
$ docker container run -d --dns 192.168.1.1 nginx
```

* 컨테이너의 MAC 주소 지정

```shell
$ docker container run -d --mac-address="92:d0:c6:0a:29:33" centos
fab4f67a39c179e229c2156d15dfa1e159ac6df96bac0a5068f10cca2768401e

$ docker container inspect --format="{{.Config.MacAddress}}" fab
92:d0:c6:0a:29:33
```

* 호스트명과 IP 주소 정의

```shell
$ docker container run -it --add-host test.com:192.168.1.1 centos
[root@777056cb38d2 /]# cat /etc/hosts
127.0.0.1	localhost
::1	localhost ip6-localhost ip6-loopback
fe00::0	ip6-localnet
ff00::0	ip6-mcastprefix
ff02::1	ip6-allnodes
ff02::2	ip6-allrouters
192.168.1.1	test.com

$ docker container run -it --hostname www.test.com --add-host node1.test.com:192.168.1.2 centos 
[root@www /]# cat /etc/hosts 
127.0.0.1	localhost
::1	localhost ip6-localhost ip6-loopback
fe00::0	ip6-localnet
ff00::0	ip6-mcastprefix
ff02::1	ip6-allnodes
ff02::2	ip6-allrouters
192.168.1.2	node1.test.com
```

* Docker에서는 기본적으로 호스트 OS와 브리지 연결을 하지만, --net 옵션을 사용하여 네트워크 설정 가능

| 설정값                 | 설명                                   |
| ---------------------- | -------------------------------------- |
| bridge                 | 브리지 연결(기본값)을 사용             |
| none                   | 네트워크에 연결하지 않는다             |
| Container:[name \| id] | 다른 컨테이너의 네트워크를 사용        |
| host                   | 컨테이너가 호스트 OS의 네트워크를 사용 |
| NETWORK                | 사용자 정의 네트워크를 사용            |

* 사용자 정의 네트워크는 `$ docker network create` 명령으로 작성
  * Docker 네트워크 드라이버 또는 외부 네트워크 드라이 플러그인을 사용해야 함
  * 사용자 정의 네트워크에 연결하면 컨테이너는 컨테이너의 이름이나 IP 주소로 서로 통신할 수 있음
* 동일 네트워크에 여러 컨테이너를 연결할 수 있음
* 오버레이 네트워크나 커스텀 플러그을 사용하면 멀티 호스에 대한 연결을 할 수 있음
* 컨테이너가 동일한 멀티호스트 네트워크에 연결되어 있으면 이 네트워크를 통해 통신 가능
  * Overlay Network 
    * IP 네트워크 대역이 다른 여러 클러스터들을 동일한 IP 대역을 가지는 네트워로 묶어 서로 통신 가능하게 함
    * Docker node를 구성하면 Ingress로 Overlay Network가 자동으로 구성되어 실행되는 컨테이너마다 같은 network 대역의 ip를 할당

* 외부 네트워크 드라이버를 사용하여 'webap-net2'라는 이름의 네트워크를 작성하고, 작성한 네트워크 상에서 컨테이너를 실행

```shell
$ docker network create -d bridge webap-net2
4f38469f4f0e1da87423f0c8a21570957697d17eddfdc154080bd66b86496073
$ docker container run --net=webap-net2 -it centos
```

----

#### 자원을 지정하여 컨테이너 생성 및 실행 (docker container run)



