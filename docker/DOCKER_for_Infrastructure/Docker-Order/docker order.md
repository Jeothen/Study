





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

* Docker container run 명령의 자원 지정

```shell
$ docker container run [자원 옵션] 이미지명[:태그] [인수]
```

* 지정할 수 있는 자원 옵션

| 옵션                                                 | 설명                                                    |
| ---------------------------------------------------- | ------------------------------------------------------- |
| --cpu-shares, -c                                     | CPU의 사용 배분(비율)                                   |
| --memory, -m                                         | 사용할 메모리를 제한하여 실행 (단위 : byte, kb, mb, gb) |
| --volume=[호스트의 디렉토리]:[컨테이너 디렉토리], -v | 호스트와 컨테이너의 디렉토리 공유                       |

* cpu-shares의 기본 값은 1024가 들어감 (시간)
* cpu시간의 상대 비율과 메모리 사용량을 지정

`` $ docker container run --cpu-shares=512 --memory=1g centos``

* 디렉토리 공유 (호스트의 /Users/test/subapp 의 폴더를 컨테이너의 /usr/share/nginx/html 디렉토리에 공유

``$ docker container run -v /Users/test/subapp:/usr/share/nginx/html nginx``

---

#### 컨테이너를 생성 및 시작하는 환경을 지정 (docker container run)

* docker conatiner run 명령의 환경 설정

```shell
$ docker container run [환경설정 옵션] 이미지명[:태그명] [인수]
```

* 지정할 수 있는 주요 옵션

| 옵션                        | 설명                                        |
| --------------------------- | ------------------------------------------- |
| --env=[환경 변수], -e       | 환경변수를 설정                             |
| --env-file=[파일명]         | 환경변수를 파일로부터 설정                  |
| --read-only=[true \| false] | 컨테이너의 파일 시스템을 읽기 전용으로 만듦 |
| --workdir=[패스], -w        | 컨테이너의 작업 디렉토리를 지정             |
| --u, --user=[사용자명]      | 사용자명 또는 UID를 지정                    |

* 환경변수 설정

```shell
$ docker container run -it -e foo=bar centos /bin/bash
[root@f1f16e695c2e /]# set
BASH=/bin/bash
...
_=/etc/bashrc
foo=bar
```

* 환경변수를 정의한 파일로부터 일괄적으로 등록하고 싶은 경우 파일(env_list) 안에 환경변수를 정의

```shell
$ cat env_list
hoge=fuga
foo=bar

$ docker container run -it --env-file=env_list centos /bin/bash
[root@851c8b96c420 /]# set
BASH=/bin/bash
...
_=/etc/bashrc
foo=bar
hoge=fuga

```

* 작업 디렉토리를 설정

```shell
$ docker container run -it -w=/docker centos /bin/bash
[root@115a768660cf docker]# pwd
/docker
```

---

#### 가동 컨테이너 목록 표시

* 가동중인 컨테이너의 상태를 확인할 때는 ``$docker container ls`` 명령을 사용

```shell
CONTAINER ID        IMAGE              COMMAND          CREATED       STATUS              PORTS       NAMES
f1e4e44f77ad   arisu1000/simple-container-app   "sh -c 'echo The app…"   22 minutes ago      Up 22 minutes                              k8s_kubernetes-simple-pod_kubernetes-simple-pod2_default_5ab1ea09-b37c-49ac-ae48-f99c65293ba1_39
74e6e532931f        wordpress:latest      "docker-entrypoint.s…"   7 weeks ago  Up 23 minutes       0.0.0.0:8000->80/tcp   workpress-docker_wordpress_1
```

* docker container ls 명령 결과

| 항목         | 설명                                                        |
| ------------ | ----------------------------------------------------------- |
| CONTAINER ID | 컨테이너 ID                                                 |
| IMAGE        | 컨테이너의 바탕이 된 이미지                                 |
| COMMAND      | 컨테이너 안에서 실행되고 있는 명령                          |
| CREATED      | 컨테이너 작성 후 경과 시간                                  |
| STATUS       | 컨테이너의 상태 (restarting \| running \| paused \| exited) |
| PORTS        | 할당된 포트                                                 |
| NAMES        | 컨테이너 이름                                               |

* 지정할 수 있는 주요 옵션

| 옵션         | 설명                                                   |
| ------------ | ------------------------------------------------------ |
| --all, -a    | 실행 중 / 정지 중인 것도 포함하여 모든 컨테이너를 표시 |
| --filter, -f | 표시할 컨테이너 필터링                                 |
| --format     | 표시 포맷을 지정                                       |
| --last, -n   | 마지막으로 실행된 n건의 컨테이너만 표시                |
| --latest, -l | 마지막으로 실행된 컨테이너만 표시                      |
| --no-trunc   | 정보를 생략하지 않고 표시                              |
| --quiet, -q  | 컨테이너의 ID만 표시                                   |
| --size, -s   | 파일 크기 표시                                         |

* 필터링 조건은 key=value로 지정

```shell
$ docker container ls -a -f name=elastic_hugle 
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
19abcf3d2385        centos              "/bin/bash"         20 hours ago        Up 30 minutes                           elastic_hugle
```

* 컨테이너 목록의 필터링 (종료 코드가 0인 것을 출력)

```shell
$ docker container ls -a -f exited=0
CONTAINER ID        IMAGE               COMMAND                 CREATED             STATUS                    PORTS               NAMES
a47231281775        centos              "/bin/bash"             19 hours ago        Exited (0) 19 hours ago                       gracious_darwin

```

* 컨테이너 목록의 출력 형식 지정

```shell
$ docker container ls -a --format="{{.Names}} : {{.Status}}"
happy_kare : Exited (127) 12 minutes ago
thirsty_montalcini : Exited (127) 17 minutes ago
```

* 컨테이너 목록을 표 형식으로 출력

```shell
$ docker container ls -a --format "table {{.Names}}\t{{.Status}}\t {{.Mounts}}"
NAMES                                    STATUS                         MOUNTS
happy_kare                        Exited (127) 22 minutes ago      
thirsty_montalcini                Exited (127) 26 minutes ago     
lucid_dubinsky                    Exited (1) 29 minutes ago      
workpress-docker_wordpress_1      Up 2 hours                        a736991813ff96…,/Users/thjeong…
workpress-docker_db_1             Up 2 hours                           workpress-dock…

```

* 출력형식 지정

| 플레이스 홀더 | 설명                   |
| ------------- | ---------------------- |
| .ID           | 컨테이너 ID            |
| .Image        | 이미지 ID              |
| .Command      | 실행 명령              |
| .CreateAt     | 컨테이너가 작성된 시간 |
| .RunningFor   | 컨테이너 가동 시간     |
| .Ports        | 공개 포트              |
| .Size         | 컨테이너 디스크 크기   |
| .Names        | 컨테이너명             |
| .Mounts       | 볼륨 마운트            |
| .Networks     | 네트워크명             |

----

#### 컨테이너 가동 확인 (docker container stats)

* Docker 상에서 작동하는 컨테이너 가동 상태를 확인할 때 
* `$ docker container stats` 명령 사용

```shell
$ docker container stats [컨테이너 식별자]
```

* 컨테이너 가동 확인

```powershell
$ docker container stats elastic_hugle

CONTAINER ID       NAME          CPU %   MEM USAGE / LIMIT     MEM %     NET I/O       BLOCK I/O           PIDS
19abcf3d2385     elastic_hugle    0.00%     924KiB / 1.944GiB   0.05%     1.58kB / 0B     4.1kB / 0B          1
```

* docker container stats 명령 결과

| 항목            | 설명                                                    |
| --------------- | ------------------------------------------------------- |
| CONTAINER ID    | 컨테이너 식별자                                         |
| NAME            | 컨테이너명                                              |
| CPU %           | CPU 사용률                                              |
| MEN USAGE/LIMIT | 메모리 사용량 / 컨테이너에서 사용할 수 있는 메모리 제한 |
| MEN %           | 메모리 사용률                                           |
| NET I/O         | 네트워크 I/O                                            |
| BLOCK I/O       | 블록 I/O                                                |
| PIDS            | PID (Windows 컨테이너 제외)                             |

* 프로세스 확인

```shell
$ docker container top elastic_hugle
PID                 USER                TIME                COMMAND
2338                root                0:00                /bin/bash
2330                999                 0:04                mysqld
```

---

#### 컨테이너 시작 (docker container start)

* 정지하고 있는 컨테이너를 시작

```shell
$ docker run <옵션> <이미지 이름> <실행할 파일>
$ docker start <컨테이너 이름>
```

* ``$ docker container start`` 명령

```shell
$ docker container start [옵션] <컨테이너 식별자> [컨테이너 식별자]
```

* 지정할 수 있는 주요 옵션

| 옵션               | 설명                             |
| ------------------ | -------------------------------- |
| --attach, -a       | 표준 출력, 표준 오류 출력을 연다 |
| --interactive,  -i | 컨테이너의 표준 입력을 연다      |

* 컨테이너 ID 가 ce9dd74 로 시작하는 컨테이너 시작

```shell
$ docker container start ce9dd74
ce9dd74
```

---

#### 컨테이너 정지

* 실행중인 컨테이너를 정지

```shell
$ docker container stop [옵션] <컨테이너 식별자> [컨테이너 식별자]
```

* 지정할 수 있는 주요 옵션

| 옵션       | 설명                                        |
| ---------- | ------------------------------------------- |
| --time, -t | 컨테이너의 정지 시간을 지정 (기본값은 10초) |

* 2초후에 컨테이너 정지

```shell
$ docker container stop -t 2 ce9dd
ce9dd
```

* 강제로 정지 시킬때는 ``$ docker container kill ``

---

#### 컨테이너 재시작 (docker container restart)

* docker container restart 명령

```shell
$ docker container restart [옵션] <컨테이너 식별자> [컨테이너 식별자]
```

* 지정할 수 있는 주요 옵션

| 옵션       | 설명                                          |
| ---------- | --------------------------------------------- |
| --time, -t | 컨테이너의 재시작 시간을 지정 (기본값은 10초) |

* 2초 후에 컨테이너 재시작

```shell
$ docker container restart -t 2 ce9dd
```

* 컨테이너 안에서 실행하는 명령의 종료 status (정상 종료되었는지 아닌지)에 따라 컨테이너를 자동으로 재시작하고 싶은 경우

```shell
$ docker container run --restart=[no | on-failure | always ...] image명 [인수]
```

---

#### 컨테이너 삭제 (docker container rm)

* 정지하고 있는 컨테이너를 삭제할 때 사용
* docker container rm 명령

```shell
$ docker container rm [옵션] <컨테이너 식별자> [컨테이너 식별자]
```

* 지정할 수 있는 주요 옵션

| 옵션          | 설명                            |
| ------------- | ------------------------------- |
| --force, -f   | 실행중인 컨테이너를 강제로 삭제 |
| --volumes, -v | 할당한 볼륨을 삭제              |

* 컨테이너 삭제

```shell
$ docker container rm ce9dd
You cannot remove a running container ce9dd7462af0ecf52fc8b16606915fa343893a4f56d2a4aaeccaa005a0211764. Stop the container before attempting removal or force remove
# 정지중인 컨테이너만 삭제 가능
```

* 정지중인 모든 컨테이너를 삭제

```shell
$ docker container prune
59018d0aee6b3f0e16268e2614f1b739a0655bda57fd0bf0443fb6299a7ac382
efe962dfefc8fcdd6557f1e78762220c3cc7f830b3b716e7f6d278dba75f5066
7cb7a4457ac4e139fc33e22072ccb50633669939c84bd8bd597baa35b11f8d55
1617885a560a65a244197f92154773e25a6fe7292fbf1f61aca2080dd3ea4ca2
3a810a5eba384bb4d85d58e81d382e58693d31be198463c2f458e3e53dc1d7a4
29da6ba15db0ca1fc15fc013a689fd416756d4d783c97b9a84fad95af25c7ea6
78066f1a717714fe41ac01ecfa19107cf88e6cfb0ffa6ee64860ffaf4f59b9c3
5a9d6d9848291a3cf5e2a8fc89b8dede43fad52f7125447eedf33bd5e8779c60

Total reclaimed space: 10.16kB
```

----

#### 컨테이너 중단 / 재개 (docker container pause / docker container unpause)

* 실행중인 컨테이너에서 작동하고 있는 모든 컨테이너를 중단할 때 

```shell
$ docker container pause <컨테이너 식별자>
$ docker container ls
CONTAINER ID   IMAGE    COMMAND    CREATED             STATUS                PORTS                  NAMES
7207d7a8c91a      arisu1000/simple-container-app   "./simple-container-…"   3 hours ago         Up 3 hours                                 k8s_kubernetes-simple-pod_kubernetes-simple-pod_default_e9b7dcee-2c15-47f3-86c8-255729b3cd27_7
$ docker container pause 72
72
$ docker container ls
CONTAINER ID   IMAGE    COMMAND    CREATED             STATUS                PORTS                  NAMES
7207d7a8c91a      arisu1000/simple-container-app   "./simple-container-…"   3 hours ago    Up 3 hours (Paused)         k8s_kubernetes-simple-pod_kubernetes-simple-pod_default_e9b7dcee-2c15-47f3-86c8-255729b3cd27_7

$ docker container unpause 72
72
$ docker container ls
CONTAINER ID   IMAGE    COMMAND    CREATED             STATUS                PORTS                  NAMES
7207d7a8c91a      arisu1000/simple-container-app   "./simple-container-…"   3 hours ago         Up 3 hours                                 k8s_kubernetes-simple-pod_kubernetes-simple-pod_default_e9b7dcee-2c15-47f3-86c8-255729b3cd27_7
```

---

### Docker Container Network

* Docker 컨테이너끼리 통신을 할 떄는 Docker 네트워크를 통해 수행



#### 네트워크 목록 표시 (docker network ls)

* docker network 목록 확인 명령

```shell
$ docker network ls
NETWORK ID     NAME            DRIVER       SCOPE
46ca6b91bee2    bridge           bridge       local
34640987f442    host            host        local
```

* 지정할 수 있는 주요 옵션

| 옵션            | 설명                         |
| --------------- | ---------------------------- |
| -f, --filter=[] | 출력을 필터링 (key=value 형) |
| --no-trunc      | 상세 정보를 출력             |
| -q, --quiet     | 네트워크 ID만 표시           |

* 필터링에 이용할 수 있는 키

| 값     | 설명                                                         |
| ------ | ------------------------------------------------------------ |
| driver | 드라이버 지정                                                |
| id     | 네트워크 ID                                                  |
| label  | 네트워크에 설정된 라벨(label=<key>) 또는 label=<key>=<value>로 지정 |
| name   | 네트워크명                                                   |
| scope  | 네트워크의 스코피(swarm/global/local)                        |
| type   | 네트워크 타입 (사용자 정의 네트워크 custom/정의 완료 네트워크 bulitin) |



* 네트워크 목록 표시의 필터링

```shell
$ docker network ls -q --filter driver=bridge  # 네트워크 ID만 출력
46ca6b91bee2  
189eb340981d
4f38469f4f0e
f177aad772ca
```

* 네트워크를 명시적으로 시작하지 않고 Docker Container를 실행하면 bridge 네트워크로 Docker 컨테이너 실행
* 'sample_ubuntu'라는 이름으로 베이스 이미지가 'ubuntu:latest'인 컨테니어 실행 (네트워크 지정x)

```shell
$ docker container run -itd --name=sample_ubuntu ubuntu:latest

$ docker container inspect sample_ubuntu
.....
		"Networks": {
		  	"bridge": {
      		"IPAMConfig": null,
          "Links": null,
          "Aliases": null,
          "NetworkID": "46ca6b91bee267a18cf6eeb6b722f12ba747a91b1fb7aff1bf88cae92609e668",
          "EndpointID": "6b984bc261f926fc3f392b1ff7a18a0ff7e1eb9a1c408deba1a83c5cf8106ddf",
          "Gateway": "172.17.0.1",
          "IPAddress": "172.17.0.4",
          "IPPrefixLen": 16,
          "IPv6Gateway": "",
          "GlobalIPv6Address": "",
          "GlobalIPv6PrefixLen": 0,
          "MacAddress": "02:42:ac:11:00:04",
          "DriverOpts": null
          }
         }
       }
    }
]

```



---

#### 오버레이 네트워크 (Overlay Network)

* 물리 네트워크 상에서 소프트웨어 적으로 에뮬레이트한 네트워크
* 물리 네트워크를 덮듯이 가상 네트워크가 구성되기 때문에 가상 네트워크라고도 함 (소프트웨어로 구성된 네트워크 - 자유롭게 구성 변경 가능)
* 물리 네트워크의 구조가 은폐되어 그 아래에 있는 물리 계층의 형태나 제어 방식 등을 고려하지 않고 이용 가능
* 여러 개의 호스트에 걸친 네트워크를 구성할 때 사용

---

#### 네트워크 작성 (docker network create)

* 새로운 네트워크를 작성할 때 사용

```shell
$ docker network create [옵션] 네트워크
```

* 지정할 수 있는 옵션

| 옵션         | 설명                                            |
| ------------ | ----------------------------------------------- |
| --driver, -d | 네트워크 브리지 또는 오버레이 (기본값은 bridge) |
| --ip-range   | 컨테이너에 할당하는 IP 주소의 범위를 지정       |
| --subnet     | 서브넷을 CIDR 형식으로 지정                     |
| --ipv6       | IPv6 네트워크를 유효화할지 여부 (true/false)    |
| -label       | 네트워크에 설정하는 레이블                      |

  			-- CIDR (사이더) : https://server-talk.tistory.com/47

* 브리지 네트워크 작성

```shell
$ docker network create --driver=bridge web-network
39e58626de17bc3da754298b7aba1ac000124544ba5273bda99fbeb49b002440
$ docker network ls
NETWORK ID          NAME                       DRIVER              SCOPE
39e58626de17        web-network                bridge              local
```

* --driver 옵션에서 지정할 수 있는 네트워크 드라이브는 bridge / overlay / custom network driver

* 컨테이너 생성 시 docker container run 명령으로 --link 옵션을 붙여 컨테이너 안의 /etc/hosts 파일에 컨테이너명과 할당된 IP주소가 등록됨

---

#### 네트워크 연결 (docker network connect/disconnect)

* ```shell
  $ docker network connect [옵션] 네트워크 컨테이너
  ```

* 지정할 수 있는 옵션

| 옵션    | 설명                      |
| ------- | ------------------------- |
| --ip    | IPv4 주소                 |
| --ip6   | IPv6 주소                 |
| --alias | 앨리어스명                |
| --link  | 다른 컨테이너에 대한 링크 |



```shell
# 네트워크를 지정한 컨테이너 시작 
$ docker container run -itd --name=web_connect nginx
f710c50d94de6075a05e1fb42619523896b1700f2f1e10134af1a0a5d311c358
# 베이스 이미지 : nginx / 'webap3' 라는 이름의 컨테이너를  'web-network' 네트워크에 생성


$ docker network inspect bridge 
...
	"Containers": {
            "f710c50d94de6075a05e1fb42619523896b1700f2f1e10134af1a0a5d311c358": {
                "Name": "web_connect",
                "EndpointID": "8218081d5d120836eef323407bdb7975b7174a76270bb40ef1f562a474b6cfcd",
                "MacAddress": "02:42:ac:11:00:05",
                "IPv4Address": "172.17.0.5/16",
                "IPv6Address": ""
            }
        },
   ...
]

$ docker network connect web-network web_connect  # 컨테이너와 네트워크 연결
$ docker container inspect web_connect

...
"web-network": {
                    "IPAMConfig": {},
                    "Links": null,
                    "Aliases": [
                        "f710c50d94de"
                    ],
                    "NetworkID": "39e58626de17bc3da754298b7aba1ac000124544ba5273bda99fbeb49b002440",
                    "EndpointID": "e102727027c65a64c0339137c954dd15b9f18f0168c1be44feb2f19bd9169a60",
                    "Gateway": "172.21.0.1",
                    "IPAddress": "172.21.0.3",
                    "IPPrefixLen": 16,
                    "IPv6Gateway": "",
                    "GlobalIPv6Address": "",
                    "GlobalIPv6PrefixLen": 0,
                    "MacAddress": "02:42:ac:15:00:03",
                    "DriverOpts": {}
                }
...


$ docker network disconnect web-network web_connect
```

---

#### 네트워크 상세 정보 확인 (docker network inspect)

* 

  ```shell
  $ docker network inspect [옵션] 네트워크
  ```

```shell
$ docker network inspect web-network
[
    {
        "Name": "web-network",
        "Id": "39e58626de17bc3da754298b7aba1ac000124544ba5273bda99fbeb49b002440",
        "Created": "2020-10-26T14:00:51.1944562Z",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "172.21.0.0/16",
                    "Gateway": "172.21.0.1"
                }
            ]
				"Containers": {
            "0b098ef7eb3d2fa5484accdf93fad7f0c6180bdec33ceb007dcbb4993f86d900": {
                "Name": "webap3",
                "EndpointID": "68700cfdbaae9abbe9c383e1167fa5971ade66e91823853d0b4e46b232c76892",
                "MacAddress": "02:42:ac:15:00:02",
                "IPv4Address": "172.21.0.2/16",
                "IPv6Address": ""
            },
            "f710c50d94de6075a05e1fb42619523896b1700f2f1e10134af1a0a5d311c358": {
                "Name": "web_connect",
                "EndpointID": "dfe2585ad054d21ddd5742ac35e41900b4c378994b1b594033f4cf546bd0ab69",
                "MacAddress": "02:42:ac:15:00:03",
                "IPv4Address": "172.21.0.3/16",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {}
   	}
]

# 서브넷이 172.21.0.0/16 이고 게이트웨이 172.21.0.1
# webap3 와 web_connect 2개의 컨테이너가 connect 상태임을 확인
```



---

#### 네트워크 삭제

```shell
$ docker network rm [옵션] 네트워크
```

* 네트워크 삭제를 하기 위해서는 연결중인 모든 컨테이너와 연결을 해지해야 함

```
$ docker network rm web_connect
Error response from daemon: error while removing network: network web-network id 39e58626de17bc3da754298b7aba1ac000124544ba5273bda99fbeb49b002440 has active endpoints
```

---



### 가동중인 Docker 컨테이너 조작

* 실제 환경에서 운용할 때, 이미 가동중인 컨테이너의 상태를 확인하거나 임의의 프로세스를 실행할 때 하는 조작

#### 가동 컨테이너 연결 (docker container attach)

```shell
$ docker container attach elastic_hugle
[root@19abcf3d2385 /]#
# ctrl + p , ctrl + q 입력하면 컨테이너는 시작한 채로 컨테이너 안에서 움직이는 프로세스만 종료
$
```

---

#### 가동 컨테이너에서 프로세스 실행 (docker container exec)

* 가동 중인 컨테이너에서 새로운 프로세스를 실행할 때는 ``$ docker container exec`` 명령을 사용
* 웹 서버와 같이 백그라운드에서 실행되고 있는 컨테이너에 엑세스 할 때는 ``$ docker container attach`` 명령으로 연결해도 쉘이 작동하지 않을 때는 명령을 할 수가 없음. ``docker container exec``  명령을 사용하여 임의의 명령 실행

```shell
$ docker container exec [옵션] <컨테이너 식별자> <실행할 명령> [인수]
```

* 지정할 수 있는 주요 옵션

| 옵션              | 설명                          |
| ----------------- | ----------------------------- |
| --detach, -d      | 명령을 백그라운드에서 실행    |
| --interactive, -i | 컨테이너의 표준 입력을 연다   |
| --tty, -t         | tty(단말 디바이스)를 사용한다 |
| --user, -u        | 사용자명 지정                 |

* 이미 가동중인 컨테이너에서 /bin/bash를 실행

```shell
$ docker container start elastic_hugle
elastic_hugle
$ docker container exec -it elastic_hugle /bin/bash
[root@19abcf3d2385 /]# 
$ docker container exec -it elastic_hugle /bin/echo "Hello world"
Hello world
```

* docker container exec 명령은 실행중인 컨테이너에서만 실행할 수 있음
* 정지중인 컨테이너는 start 명령을 통해서 실행 후 exec 실행

---

#### 가동 컨테이너의 프로세스 확인 (docker container top)

* 가동중인 컨테이너에서 실행되고 있는 프로세스를 확인할 때는 ``docker container top`` 명령
* 프로세스 확인

```shell
$ docker container top elastic_hugle
PID                 USER                TIME                COMMAND
2549                root                0:00                /bin/bash
```

#### 가동 컨테이너의 포트 전송 확인 (docker container port)

* 가동중인 컨테이너에서 실행되고 있는 프로세스가 전송되고 있는 포트를 확인할 때 사용

```shell
$ docker container port workpress-docker_wordpress_1
80/tcp -> 0.0.0.0:8000
```

* 컨테이너의 80번 포트가 호스트의 8000번 포트로 전송

```shell
# 포트를 추가해서 image 실행
$ docker run -p 5000:3400 -d arisu1000/simple-container-app
ec4237a2b2ed4d89e67cbf6d54c1db6938f804a3682092648f81c4ba68f0e19f
$ docker container ls
CONTAINER ID        IMAGE                            COMMAND                  CREATED             STATUS              PORTS                    NAMES
ec4237a2b2ed        arisu1000/simple-container-app   "./simple-container-…"   3 seconds ago       Up 3 seconds        0.0.0.0:5000->3400/tcp   relaxed_robinson
```



#### 잘 알려진 포트

| 번호 | TCP/IP  | 서비스/프로토콜 | 설명                      |
| ---- | ------- | --------------- | ------------------------- |
| 20   | TCP     | FTP(데이터)     | 파일 전송 (데이터)        |
| 21   | TCP     | FTP(제어)       | 파일 전송 (제어)          |
| 22   | TCP/UDP | ssh             | secure shell              |
| 23   | TCP     | Telnet          | 원격 엑세스               |
| 25   | TCP/UDP | SMTP            | 메일 전송                 |
| 43   | TCP     | WHOIS           | 도메인 정보 검색          |
| 53   | TCP/UDP | DNS             | 도메인 네임 시스템        |
| 80   | TCP/UDP | HTTP            | 웹 엑세스                 |
| 88   | TCP/UDP | Kerberos        | Kerberos 인증             |
| 110  | TCP     | POP3            | 메일 수신                 |
| 123  | UDP     | NTP             | 시간 조정                 |
| 135  | TCP     | Microsoft RPC   | Microsoft의 원격 엑세스   |
| 143  | TCP/UDP | IMAP2/4         | 인터넷 메일 엑세스        |
| 161  | TCP/UDP | SNMP            | 네트워크 감시             |
| 162  | TCP/UDP | SNMP 트랩       | 네트워크 감시(트랩)       |
| 389  | TCP/UDP | LDAP            | 디렉토리 서비스           |
| 443  | TCP/UDP | HTTPS           | HTTP의 암호화 통신        |
| 465  | TCP     | SMTPS           | SMTP의 암호화 통신        |
| 514  | UDP     | Syslog          | 로그 수집                 |
| 989  | TCP/UDP | FTPS(데이터)    | FTP(데이터)의 암호화 통신 |
| 990  | TCP/UDP | FTPS(제어)      | FTP(제어)의 암호화 통신   |
| 992  | TCP/UDP | Telnets         | Telnet의 암호화 통신      |
| 993  | TCP     | IMAPS           | IMAP의 암호화 통신        |
| 995  | TCP     | POP3S           | POP3의 암호화 통신        |

---

#### 컨테이너 이름 변경 (docker container rename)

* 컨테이너의 이름을 변경할 때 `` docker container rename` 명령을 사용

```shell
$ docker container ls
CONTAINER ID        IMAGE                            COMMAND                  CREATED             STATUS              PORTS                  NAMES
80c2ca2c4589        arisu1000/simple-container-app   "sh -c 'echo The app…"   21 minutes ago      Up 21 minutes                              k8s_kubernetes-simple-pod_kubernetes-simple-pod2_default_5ab1ea09-b37c-49ac-ae48-f99c65293ba1_44
$ docker container rename k8s_kubernetes-simple-pod_kubernetes-simple-pod2_default_5ab1ea09-b37c-49ac-ae48-f99c65293ba1_44 test_rename
$ docker container ls
80c2ca2c4589        arisu1000/simple-container-app   "sh -c 'echo The app…"   22 minutes ago           Up 22 minutes                                  test_rename
```

---

#### 컨테이너 안의 파일 복사 (docker container cp)

* docker container cp 명령

```shell
$ docker container cp <컨테이너 식별자>:<컨테이너 안의 파일 경로> <호스트의 디렉토리 경로>

$ docker container cp <호스트 파일> <컨테이너 식별자>:<컨테이너 안의 파일 경로>
```

* 파일 복사

```shell
$ docker container cp webap3:/etc/nginx/nginx.conf /tmp/nginx.conf  # container to host
$ ls -la /tmp/nginx.conf
-rw-r--r--  1 thjeong  wheel  643  9 29 23:12 /tmp/nginx.conf

$ docker container cp ./basic.md webap3:/etc/nginx/basic.md   # host to container
```

#### 컨테이너 조작의 차분 확인 (docker container diff)

* 컨테이너 안에서 어떤 조작을 하여 컨테이너 이미지가 생성되었을 때와 다른 경우 변경점을 확인하려면 `` docker container diff`` 명령 사용

```shell
$ docker container diff <컨테이너 식별자>
```

* 변경의 구분

| 구분 | 설명      |
| ---- | --------- |
| A    | 파일 추가 |
| D    | 파일 삭제 |
| C    | 파일 수정 |

* 신규 작성자 등록 및 변경사항 확인

````shell
$ docker container run -it --name "test_diff" nginx /bin/bash
root@580b2fce32eb:/# useradd newuser
root@580b2fce32eb:/# exit
exit
$docker container diff test_diff 
C /root
A /root/.bash_history
C /var
C /var/log
C /var/log/faillog
C /var/log/lastlog
C /etc
C /etc/shadow
C /etc/subuid
C /etc/subgid
C /etc/group-
C /etc/gshadow-
C /etc/passwd-
C /etc/group
A /etc/subuid-
C /etc/gshadow
A /etc/subgid-
C /etc/passwd
````

---

### Docker 이미지 생성

* 컨테이너를 바탕으로 Docker 이미지 생성
* 이미지 -> 컨테이너 (환경에 맞추어 변경) -> 이미지 생성으로 환경에 맞는 이미지를 만들 수 있음



#### 컨테이로부터 이미지 작성 (docker container commit)

* docker container commit 명령

```shell
$ docker container commit [옵션] <컨테이너 식별자> [이미지명[:태그명]]
```

* 지정할 수 있는 옵션

| 옵션          | 설명                                            |
| ------------- | ----------------------------------------------- |
| --author, -a  | 작성자를 지정한다[ ex) test<<test@google.com>>] |
| --message, -m | 메시지를 지정                                   |
| --change, -c  | commit 시 Dockerfile 명령을 지정한다            |
| --pause, -p   | 컨테이너를 일시정지하고 commit                  |

* 컨테이너로부터 이미지 작성

```shell
$ docker container commit -a "jeothen" webap3 jeothen/webap3:1.0
sha256:d6bf85c8801e28d9fed8e03d4b0e05f604c5fe865737c6a27d2b0383093a4fe2

$ docker image ls
REPOSITORY           TAG        IMAGE ID            CREATED             SIZE
jeothen/webap3       1.0       d6bf85c8801e        6 seconds ago       133MB
```

* 이미지 상세 정보 확인

```shell
$ docker image inspect jeothen/webap3:1.0
[
    {
        "Id": "sha256:d6bf85c8801e28d9fed8e03d4b0e05f604c5fe865737c6a27d2b0383093a4fe2",
        "RepoTags": [
            "jeothen/webap3:1.0"
        ],
        ...
        "Author": "jeothen",
  ...
]
```

---

#### 컨테이너를 tar 파일로 출력 (docker container export)

* docker에서 가동중인 컨테이의 디렉토리 / 파일을 모아 tar파일 생성
* tar 파일을 바탕으로 다른 서버에서 컨테이너를 가동시킬 수 있음

* docker container export 명령

```shell
$ docker container export <컨테이너 식별자>
```

* 파일 출력

```powershell
$ docker container export webap3 > webap3.tar
$ ls -la
-rw-r--r--   1 thjeong  staff  135349248 10 28 00:01 webap3.tar
# tar 파일 상세 정보 출력
$ tar -tf webap3.tar
tar -tf webap3.tar
.dockerenv
bin/
bin/bash
bin/cat
bin/chgrp
bin/chmod
bin/chown
bin/cp
bin/dash
bin/date
bin/dd
bin/df
bin/dir
bin/dmesg
bin/dnsdomainname
bin/domainname
....
```

---

#### tar 파일로부터 이미지 작성 (docker image import)

* Linux OS 이미지의 디렉토리 / 파일로부터 Docker Image를 만들 수 있음
* docker image import 명령

```shell
$ docker image import <파일 또는 URL> | - [이미지명[:태그명]]
```

* 압축된 디렉토리나 파일도 취급할 수 있음
* root 권한으로 실행 - 엑세스 권한이 없는 파일은 생략되기 때문
* docker image import 명령으로 지정할 수 있는 archive(압축) 파일 
  * tar  / tar.gz / tgz / bzip / tar.xz / txz 

* 이미지 작성 (webap3.tar 를 바탕으로 jeothen/webap3라는 태그명이 1.1인 이미지 작성)

```shell
$ cat webap3.tar | docker image import - jeothen/webap3:1.1
sha256:c99712e80befcf4ab8c45e0c97c4a1fdc182fac2c81dd75894a7bf838c010062
$ docker image ls
REPOSITORY        TAG       IMAGE ID            CREATED             SIZE
jeothen/webap3    1.1       c99712e80bef        17 seconds ago      131MB
```

---

#### 이미지 저장 (docker image save)

