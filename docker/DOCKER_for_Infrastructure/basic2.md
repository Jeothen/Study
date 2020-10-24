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





---

#### Docker Image 변조 방지 및 취약성 검사 기능





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

* 