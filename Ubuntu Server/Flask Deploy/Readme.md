## Flask Deploy

* Web Server : nginx  /  uwsgi 를 이용하여 배포





---

#### Env. setting

* ``$ sudo adduser thj ``  : useradd

  * `$ sudo visudo` 명령어를 통해서 유저 권한 등록

  * ``su - thj`` : user change

  * ``/etc/apt/source.list `` 에서 패키지 다운로드 path를 설정 - 패키지 install 속도에 영향

    * sed 명령어를 통해 아카이브 페이지 변경

    * 아카이브가 충돌시 땐 초기화 진행 (ubuntu version에 맞는 archice 사용...)

      * ```shell
        $ sudo dpkg -S apt | grep sources.list
        $ sudo cp /usr/share/doc/apt/examples/sources.list /etc/apt/
        ```

  * API Server와 동일하게 setting

  

* Uwsgi-plugin--python  패키지는 미리 설치하지만, uwsgi 는 virtualenv 내에서 설치


