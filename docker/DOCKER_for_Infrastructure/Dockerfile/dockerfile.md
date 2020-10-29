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

* 

