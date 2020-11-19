## Flask Deploy

* Web Server : nginx  /  uwsgi 를 이용하여 배포





---

#### Env. setting

* ``$ sudo adduser thj ``  : useradd

  * `$ sudo visudo` 명령어를 통해서 유저 권한 등록
  * ``su - thj`` : user change (super user).   ``su the`` : just change user
  * ``/etc/apt/source.list `` 에서 패키지 다운로드 path를 설정 - 패키지 install 속도에 영향

    * sed 명령어를 통해 아카이브 페이지 변경

    * ubuntu version에 맞는 archice 사용

  * API Server와 동일하게 setting
  * 가상환경에서 uwsgi install




#### nginx setting

* nginx setting
  
  ```shell
$ sudo vim /etc/nginx/sites-available/default
  ```
  
  * 내용 추가
  
  * error 발생 (ubuntu 20.04 )
  
    ```
    pam_unix(sudo:auth): Couldn't open /etc/securetty: No such file or directory
    pam_unix(polkit-1:auth): authentication failure;
    ```
  
  * 
  
* uwsgi setting

  ```shell
  $ sudo vim /etc/uwsgi/apps-available/uwsgi.ini
  ```

  * 내용 추가



