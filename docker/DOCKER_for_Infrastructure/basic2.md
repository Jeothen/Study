### Container

- 호스트 OS상에 논리적인 구획(컨테이너)를 만들고, 애플리케이션을 작동시키기 위해 필요한 라이브러리나 애플리케이션 등을 하나로 모아서 하나의 서버처럼 사용할 수 있게 만든 것
- 호스트 OS의 리소스를 분리시키고, 여러개의 컨테이너를 공유하여 사용
- 오버헤드가 적어 고속으로 사용 가능
- 애플리케이션의 실행에 필요한 모듈을 컨테이너로 모을 수 있기 때문에, 여러개의 컨테이너를 조합하여 하나의 애플리케이션을 구축하는 MSA형 애플리케이션과 친화성이 높음

---

#### Host Server 가상화 / Hyper-V Server 가상화

* Host형 Server 가상화

  * 호스트 OS에 가상화 소프트웨어를 설치하고, 이 가상화 스프트웨어 상에서 게스트OS를 작동시키는 기술
  * VirtualBox, VMWare Workstation Player 등 존재

  * 호스트상에서 여러개의 게스트 OS를 작동시키기 때문에, 가상화를 수행하기 위한 CPU 자원, 디스크 용량, 메모리 사용량 등의 오버헤드가 증가
  * 하드웨어를 에뮬레이트하기 때문에 게스트 OS의 종류에는 제약이 거의 없음ㅇ
  * 자체 운영체제를 포함하고 있어 여러 리소스의 집약적인 기능을 한 번에 수행할 수 있음
  * 응용 프로그램에서 하드웨어 엑세스를 요청할 때, 4개의 매핑 계층 (host virtualization ->  VMM -> Host operating System -> HW)

  

* 하이퍼바이저형 Server 가상화 : https://www.redhat.com/ko/topics/virtualization/what-is-a-hypervisor
  * 하드웨어 상에 가상화를 전문으로 수행하는 하이퍼바이저를 배치하여 하드웨어와 가상환경을 제어
  * MS Windows Server, XenServer 등 존재
  * 호스트 OS 없이 하드웨어를 직접 제어할 수 있기 때문에 리소스(CPU, Memory, Storage 등)를 효율적으로 사용할 수 있음
  * 단, 가상환경마다 별도의 OS가 존재하므로, 가상 환경의 시작에 걸리는 오버헤드가 증가
  * 자체적인 관리 기능이 없어 별도의 관리 콘솔(관리 컴퓨터)가 필요

---





 ### DOCKER

* 애플리케이션의 실행에 필요한 환경을 하나의 이미지로 모아두고, 그 이미지를 사용하여 다양한 환경에서 애플리케이션 실행 환경을 구축 및 운용하기 위한 오픈소스 플랫폼
* 내부에서 Container기술을 사용하고 있는 것이 특징
* 인프라 환경을 컨테이너로 관리하기 때문에, 테스트 환경과 스테이징 환경 / 제품 환경 전개시 작동하지 않는 이슈 해결
  * 스테이징 환경 : Continuous Delivery가 일어나지 않는 시스템 환경에서 개발한 애플리케이션을 제품 환경에 전개하기 직전에 테스트하는 환경





* 유저는 애플리케이션 실행에 필요한 모든 것이 포함되어 있는 docker 이미지를 (git repository에 등록한 후 ) docker registry로 빌드  
* 각각의 컨테이너에서 docker registry로부터 이미지를 가져온 후 실행 
  * Docker가 설치되어 있는 환경이라면 어디서든지 작동됨
* 애플리케이션 개발부터 테스트 및 제품 환경 전개까지 모두 애플리케이션 엔지니어가 수행 가능해짐 -> 지속적 딜리버리 가능

-----

#### 애플리케이션 이식성(portability)

* 이식성 : 한 번 만들면 어디서든지 작동하는 소프트웨어의 특성
* Docker 이미지만 있으면 애플리케이션을 동일한 환경에서 가동시킬 수 있음
  * 개발한 업무 애플리케이션을  온프레미스 환경으로 이전 가능 / 온프레미스 -> 클라우드 -> 온프레미스 간에도 실행환경을 선택 가능
* 실행 환경에 제약이 많으면, 특정 업체에 의존하는 시스템이 되어버릴 수 있음
  * 온프레미스에서 이러한 인프라에 얽매여, 필요 이상으로 복잡한 구성의 시스템을 운영할 수밖에 없거나 기술 정체 현상 발생



----

### Docker 기능



#### 이미지를 만드는 기능 (Build)

* 애플리케이션 실행에 필요한 프로그램 본체, 라이브러리, 미들웨어, OS나 네트워크 설정 등을 하나로 모아서 Docker Image 생성
* Docker에서는 하나의 이미지에 하나의 애플리케이션만 넣어 두고, 여러 개의 컨테이너를 조합하여 서비스 구축을 권장
* Docker Image는 애플리케이션 실행에 필요한 파일들이 저장된 디렉토리 -> 명령을 통해 tar 파일로 출력
* Docker Image는 명령을 통해 수동으로 만들 수도 있으나, Dockerfile이라는 설정 파일을 만들어 자동으로 이미지 만들 수 있음
* CI/CD 관점에서 Dockerfile을 만들어 사용하는 것이 바람직
* Docker Image는 겹쳐서 사용할 수 있음
  * ex) OS용 이미지에 웹 애플리케이션용 이미지를 겹쳐서 다른 새로운 이미지를 만들 수 있음
* Docker에서는 구성에 변경이 있었던 부분을 이미지 레이어로 관리
  * Docker Image가 빌드될 때,  Dockerfile에 정의된 순서대로 실행하면서 만들어 짐
  * 레이어들은 독립적으로 저장되며 읽기 전용이기에 임의로 수정할 수 없음
  * ``docker image inspect `` 명령어를 실행하면 출력된 결과의 HASH값(다이제스트)을 볼 수 있음
    * 도커 데이터는 시스템 상의 /var/lib/docker에 저장되며, overlay2 드라이버로 저장된 레이어는 다시 image/overlay2/layerdb/sha256에 저장됨
      * ``docker info | grep Storage``  명령을 통해 Storage 드라이버 확인
    * 해당 디렉터리에서 ``ls -l`` 를 한 결과값과 ``docker image inspect `` 에서 출력된 결과가 같음을 확인할 수 있음
    * 해당 다이제스트 디렉터리에 들어가면 cache-id, diff, size, tar-split.json.gz 등의 파일을 확인할 수 있음
    * ``cat cache-id ; echo`` 명령을 통해 실제 데이터가 있는 디렉터리 다이제스트 값 출력
      * cache-id는 고유한 값이 아니므로, 이미지를 풀 받은 시스템마다 달라짐
    * ``/var/lib/docker/overlay2/ `` 로 이동하여 cache-id로 얻은 다이즈스트 값 아래 diff 디렉터리의 레이어 컨텐츠
      * 리눅스 기본 디렉토리로 구성되어 있음
  * docker를 pull 받을 때, 디스트리뷰션 id가 출력되지만 거의 사용되지 않음
    * `` `/image/overlay2/distribution/diffid-by-digest/sha256`` 아래에 있는 디스트리뷰션 id를 확인할 수 있음
    * ``$ cat distribution_id ; echo`` 를 실행하면 레이어 id가 출력되어 매핑 관계를 확인할 수 있음
  * Read only layer가 순서대로 쌓이며 특정 위치에 마운트되고, 마지막에 신규 Read-Write layer를 추가
    * 마지막에 추가된 쓰기 가능 layer에 컨테이너 내에서 발생하는 모든 변경사항을 저장



#### 이미지를 공유하는 기능 (Ship)

* Docker 이미지는 Docker Registry에서 공유
* Docker의 공식 레지스트리인 Docker Hub에서는 Ubuntu나 Centos같은 Linux 배포판의 기본 기능을 제공하는 베이스 이미지를 배포
* 베이스 이미지에 미들웨어나 라이브러리, 전개할 애플리케이션 등을 넣은 이미지를 겹쳐서 독자적인 Docker 이미지를 생성

* Docker Hub는 Github이나 Bitbucket과 연계할 수 있음
  * Automated Build : 자동 생성 기능
    * ex) Github 상에서 Dockerfile을 관리하고, Docker Image를 자동으로 생성하여 Docker Hub에서 공개하는 것이 가능



#### 이미지를 실행하는 기능 (Run)

* Docker는 Linux상에서 컨테이너 단위로 서버 기능을 작동하는데 컨테이너는 Docker Image를 이용해 기동
* Docker가 설치된 환경에서는 어디서든지 Docker Image를 이용하여 컨테이너를 작동시킬 수 있음
  * Docker 명령을 통해 컨테이너의 기동, 중지, 파기
* Docker Image를 이용해 여러 개의 컨테이너를 기동시킬 수도 있음
* 다른 가상화 기술로 서버를 실행하려면 OS의 실행부터 시작하기 때문에 시간이 많이 소요되지만, Docker의 경우 이미 움직이고 있는 OS 상에서 프로세스를 실행시키는 것과 거의 같은 속도로 실행할 수 있음
* Docker는 하나의 리눅스 커널을 여러 개의 컨테이너에서 공유
  * 컨테이너 안에서 작동하는 프로세스를 하나의 그룹으로 관리하고, 그룹마다 각각 파일 시스템, 호스트명, 네트워크 등을 할당
  * ex) Apache용 애플리케이션 이미지, Centos용 애플리케이션 이미지
* 제품 환경에서는 모든 Container를 한 대의 호스트 머신(물리 서버)에서 작동시키는 일은 드물다.
  * 시스템의 트래픽 증가, 가용성 요건, 신뢰도 요건 등을 고려한 후에 여러 대의 호스트 머신으로 된 분산 환경을 구축
    * 대부분 Kubernetes와 같은 오케스트레이션 툴을 이용하여 컨테이너 관리
    * 오케스트레이션 툴은 분산 환경에서 컨테이너를 가동시키기 위해 필요한 기능을 제공

---

#### Docker Image 변조 방지 및 취약성 검사 기능

* Docker Container Trust는 Docker의 제공자를 검증할 수 있는 기능
* Image 제공자는 Registry에 이미지를 보내기 전, 로컬 환경에서 비밀키를 사용하여 Image에 Sign
* 이미지를 사용할 때는 이미지 제공자의 공개키를 사용하여 실행하려고 하는 Image가 제공자가 작성한 것인지 확인
  * 만약 변조된 경우 Image를 무효로 만듦
* Docker Security Scanning은 이미 알려진 보안상의 취약점을 바탕으로 Docker 이미지를 검사하여 안정성 확인

---

#### Moby Project

* 컨테이너 기술을 베이스로 한 컴포넌트를 조합하여 시스템을 구축할 수 있다는 것을 지향하는 오픈소스 프로젝트
* 다양한 컴포넌트가 제공되며, 컨테이너 런타임, 오케스트레이션, 네트워킹 보안, 빌드 툴, 프레임워크 등을 조합해 다양한 플랫폼 위에서 실행 가능한 컨테이너 환경 구축
  * Containerd : 컨테이너 런타임
  * LinuxKit : containerd를 작동시키기 위한 Linux 환경
  * InfraKit : 인프라를 추상화하여 자동화하는 컴포넌트
* Docker는 Moby Project에서 개발이 진행되고 있는 툴 중 하나 - Docker의 GitHub repository명이 Moby

---

### Docker Component

* Docker Engine (Docker의 핵심 기능)
  * Docker Image를 생성하고 컨테이너를 기동시키기 위한 Docker의 핵심 기능
  * Docker 명령의 실행이나 Dockerfile에 의한 이미지도 생성

* Docker Registry (이미지 공개 및 공유)
  * 컨테이너의 바탕이 되는 Docker Image를 공개 및 공유하기 위한 Registry 기능
  * Docker의 공식 Registry인 Docker Hub도 Docker Registry를 사용

* Docker Compose
  * 여러 개의 컨테이너 구상 정보를 코드로 정의하고, 명령을 실행함으로써 애플리케이션의 실행환경을 구성하는 컨테이너들을 일원 관리하기 위한 툴

* Docker Machine
  * 로컬 호스트용인 VirtualBox를 비롯해, AWS EC2, MS Azure 같은 Cloud 환경에서 Docker의 실행 환경을 명령으로 자동 생성하기 위한 툴

* Docker Swarm
  * 여러 Docker Host를 클러스터하기 위한 툴
  * 클러스터를 관리하거나 API를 제공하는 역할은 Manager, Docker 컨테이너를 실행하는 역할은 Node가 담당
  * 오픈소스인 Kubernetes를 이용할 수도 있음

---

### Docker의 작동 구조

* Docker는 Linux 커널의 기술이 베이스
* Linux 커널은 OS의 핵심 기능이며, HW나 Network와 같은 하위 레이어 기술과 밀접한 관련이 있기 때문에 앱 단위의 개발자에게는 익숙하지 않음

---

#### 컨테이너를 구획화하는 장치 (Namespace)

* Docker는 컨테이너라는 독립된 환경을 만들고, 컨테이너를 구획화하여 애플리케이션 실행 환경을 만듦
* 컨테이너를 구획화하는 기술은 Linux 커널의 namespace라는 기능을 사용
  * namespace : 이름 공간이라는 한 덩어리의 데이터에 이름을 붙여 분할함으로써 충돌 가능성을 줄이고, 쉽게 참조할 수 있게 함
  * name과 연결된 실체는 그 name이 어떤 namespace에 속해 있는지 고유하게 정해짐
    * 동일한 name이라도 namespace가 다르면 다른 실체로 처리됨
* Linux 커널의 namespace는 Linux 오브젝트에 이름을 붙이며 다음과 같은 6개의 환경을 구축할 수 있음



1. **PID namespace**
   * PID란 Linux에서 각 프로세스에 할당된 고유 ID를 의미
   * PID namespace는 PID와 process를 격리
   * namespace가 다른 프로세스끼리는 서로 엑세스 할 수가 없음

2. **Network namespace**
   * 네트워크 디바이스, IP 주소, 포트 번호, 라우팅 테이블, 필터링 테이블 등과 같은 네트워크 리소스를 격리된 namespace마다 독립적으로 가질 수 있음
   * 이 기능을 사용하면 Host OS 상에서 사용중인 포트 번호가 있더라도 컨테이너 안에서 동일한 포트 번호를 사용할 수 있음
3. **UID namespace**
   * UID (User ID), GID (Group ID)를 namespace 별로 독립적으로 가질 수 있음
   * Namespace 안과 Host OS 상의 UID/GID가 서로 연결되어 namespace 안과 밖에서 서로 다른 UID/GID를 가질 수 있음
     * ex) namespace 안에서는 UID/GID가 0인 root 사용자를 Host OS 상에서는 일반 사용자로 취급할 수 있음
4. **Mount namespace**
   * Linux에서 파일 시스템을 사용하기 위해서는 mount가 필요
     * Mount : 컴퓨터에 연결된 기기나 기억장치를 OS에 인식시켜 이용 가능한 상태로 만드는 것
   * mount namespace는 마운트를 조작하면 namespace 안에 격리된 파일 시스템 트리를 만듦
   * 다른 namespace 기능과 마찬가지로 namespace 안에서 수행 가능한 마운트는 Host OS나 다른 namespace에서 엑세스 불가
5. **UTS namespace**
   * namespace 별로 호스트명이나 도메인명을 독자적으로 가질 수 있음
6. **IPC namespace**
   * 프로세스 간 통신(IPC) 오브젝트를 namespace 별로 독립적으로 가질 수 있음
     * IPC : System V 프로세스 간 통신 오브젝트라고 하는 공유 메모리나 세마포어 / 메시지 큐를 의미
     * 세마포어 : 프로세스가 요구하는 자원 관리에 이용되는 베타제어 장치
     * 메시지 큐 : 여러 프로세스 간 비동기 통신을 할 때 사용되는 큐잉 장치

---

#### 릴리즈 관리 장치 (cgroups)

* Docker에서는 물리 머신 상의 자원을 여러 컨테이너가 공유하여 작동
* Linux 커널의 기능인 Control groups(croups) 기능을 사용하여 자원의 할당 등을 관리
* cgroups는 프로세스와 스레드를 그룹화하여, 그 그룹 안에 존재하는 프로세스와 스레드에 대한 관리를 수행하기 위한 기능
  * Host OS의 CPU와 메모리 같은 자원을 그룹별로 제한을 둘 수 있음

* cgroups는 계층 구조를 사용하여 프로세스를 그룹화하여 관리할 수 있음
  * 사용자 애플리케이션과 서버와 같은 데몬 프로세스를 나눠 각각의 그룹에 CPU 할당 가능
* cgroups의 부모자식 관계에서는 자식이 부모의 제한을 물려 받음
  * 자식에 부모의 제한을 초과하는 설정을 하더라도,  부모 cgroups의 제한에 걸림

---

#### 네트워크 구성 (가상 브리지 / 가상 NIC)

* Linux는 Docker를 설치하면 서버의 물리 NIC가 docker0라는 가상 브리지 네트워크로 연결
  * Network Interface Controller : 랜 카드라고도 부르며, 컴퓨터를 네트워크에 연결하여 통신하기 위해 사용하는 하드웨어 장치 
* docker0은 Docker를 실행시킨 후에 디폴트로 생성
* Docker container가 실행되면 컨테이너에 172.17.0.0/16이라는 서브넷 마스크를 가진 프라이빗 IP 주소가 eth0으로 자동 할당
* 이 가상 NIC는 OSI 2계층인 가상 네트워크 인터페이스로, 페어인 NIC와 터널링 통신
* Docker 컨테이너와 외부 네트워크가 통신을 할 때 가상 브리지 docker0와 Host OS의 물리 NIC에서 패킷을 전송하는 장치가 필요
  * Docker에서는 NAPT기능을 사용하여 연결
  * NAPT(Network Address Port Translation) : 하나의 IP 주소를 여러 컴퓨터에 공유하는 기술로, IP주소와 포트 번호를 변환하는 기능
    * 프라이빗 IP주소와 글로벌 IP 주소를 투과적으로 상호 변환하는 기술로, TCP/IP의 포트 번호까지 동적으로 변환하기 때문에 하나의 글로벌 IP 주소로 여러 대의 머신에 동시에 연결 가능
    * Docker에서는 NAPT에 Linux의 iptables(리눅스 상에서 방화벽을 설정하는 도구)를 이용
  * Docker에서 이 기능을 사용할 때는 컨테이너 시작 시에 컨테이너 안에서 사용하고 있는 포트를 가상 브리지인 docker0에 대해 개방
    * ex) 컨테이너 시작 시에 컨테이너 안의 웹 서버가 사용하는 80번 포트를 Host OS의 8080 포트로 전송하도록 설정
    * 외부 네트워크에서 Host OS의 8080 포토에 엑세스하면 컨테이너 안의 80번 포트로 연결

---

#### NAT와 IP 마스커레이드

* 프라이빗 IP 주소와 글로벌 IP 주소를 변환하여 프라이빗 IP 주소가 할당된 컴퓨터에 대해 인터넷 엑세스를 가능하게 할 때 사용하는 기술로 NAT 와 NAPT (IP 마스커레이드)가 있음

##### NAT (Nerwork Address Translation)

* 프라이빗 IP 주소가 할당된 클라이언트가 인터넷 상에 있는 서버에 엑세스 할 때 **NAT 라우터**는 클라이언트 프라이빗 IP 주소를 NAT가 가지고 있는 글로벌 IP 주소로 변환하여 요청을 송신
* 응답은 NAT 라우터가 송신처를 클라이언트의 프라이빗 IP 주소로 변환하여 송신
* NAT는 프라이빗 IP 주소를 1:1로 변환하기 때문에 동시에 여러 클라이언트가 엑세스 할 수 없음

##### NAPT (Network Address Port Translation)

* 프라이빗 IP 주소와 함께 포트 번호도 변환하는 기술
* 프라이빗 IP 주소를 글로벌 IP 주소로 변환할 때 프라이빗 IP 주소별로 서로 다른 포트로 변환
  * ex) 클라이언트 A(192.168.0.1)이 보낸 요청은 포트번호 1500으로 하고 클라이언트 B(192.168.0.2)가 보낸 요청은 포트번호 1600으로 설정
  * 인터넷상의 서버로부터 NAPT의 글로벌 IP 주소의 서로 다른 포트로 응답 ( global IP : port)
* 하나의 글로벌 IP 주소와 여러개의 프라이빗 IP 주소를 변환할 수 있음

---

#### Docker 이미지의 데이터 관리 장치

* Docker에서는 Copy on Write 방식으로 데이터를 관리
  * Copy on Write 
    * 복사를 수행할 때 바로 복사하지 않고, 원래의 데이터를 그대로 참조
    * 원본 또는 복사 어느 쪽에 수정이 되었을 때, 새로운 빈 영역을 확보하고 데이터를 복사



#### Docker Image의 데이터 관리 장치

* AUFS

  * 다른 파일 시스템의 파일이나 디렉토리를 투과적으로 겹쳐서 하나의 파일 트리를 구성할 수 있는 파일 시스템
  * 현재 표준 Linux 커널의 일부가 아님

* Btrfs

  * Oracle이 개발한 Linux용 Copy On Write 파일 시스템
  * 과거의 상태로 돌아갈 수 있는 롤백 기능과 어떤 시점의 상태를 저장할 수 있는 스냅샷 기능이 있음

* Device Mapper

  * Linux 커널 2.6에 들어간 Linux의 블록 디바이스 드라이버와 그것을 지원하는 라이브러리

  * 파일 시스템의 블록 I/O와 디바이스의 매핑 관계를 관리

  * Thin-provisioning 기능과 스냅샷 기능을 가지고 있음

    * Thin-provisioning 

      * 스토리지에 남아있는 용량 없이, 필요할 때 필요한 만큼 사용할 수 있도록 스토리지를 관리

      * 스토리지의 용량 활용도를 최대로 높이는 기술
      * 실제 데이터가 저장될 때 빈 공간을 찾아야하고, 폐기된 데이터를 청소하고 저장하기 때문에 속도가 느렸으나, SSD의 보급으로 디스크 섹터를 찾아다니는 스핀들이 필요 없는 환경에서는 매우 효율이 높음

  * Centos나 Fedora와 같은 RedHat Os나 Ubuntu 등에서 Docker를 이용할 때 사용

* OverlayFS

  * UnionFS 중 하나로, 파일 시스템에 다른 파일 시스템을 투과하여 merging하는 기술
    * Linux 커널 3.18에 도입되어, 읽기(readout) 전용 파일 시스템에 읽어들이기(readin)가 가능한 파일 시스템을 겹침으로써, 읽기 전용 파일 시스템상의 디렉토리나 파일에 대한 읽어들이기 및 변경이 가능해짐
    * Docker에서는 overlay와 overlay2 라는 2종류의 드라이버를 이용할 수 있음 (Linux 4.0 이상에서 overlay2 권장)

* ZFS 

  * Oracle이 개발한 새로운 파일 시스템
  * 볼륨 관리, 스냅샷, 체크섬 처리, 리플리케이션 등을 지원



