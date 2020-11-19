# Flask API Server

### Environment Setting

* Virtualenv : 패키지나 파이썬 버전이 상이할 경우 호환성 문제로 하나의 가상환경 내에서 구성

  * pyenv, pyenv-virtualenv 설치
  * 쉘 설정 파일에 프로그램 초기화 코드 추가
  * pyenv로 python 설치(3.7.5) 및 전역으로 설정
    * ``$ pyenv global 3.7.5``
    * check pyenv 및 python version

  

  * Pyenv-virtualenv를 이용해 가상환경 생성

    * ``$ pyenv virtualenv 3.7.4 flask-env`` 로 flask-env라는 환경 생성

  * 가상환경을 프로젝트 폴더에 지정

    * 현재 폴더에 가상환경 적용.  ``$ pyenv local flask-env`` 
    * ``$ pyenv versions``시 * 표시에 경로가 설정되어 있어야 함

    

  * ``$ virtualenv venv``로 가상환경 생성

  * `` source venv/bin/activate `` 로 가상환경에 접속

  * 

  * Client 에서도 동일하게 venv에 접속한 후 `$ pytest-watch` 로 실행하면 계속 test 진행

  

* ngrok : 외부 ip에서 로컬 서버에 접속하게 해주는 터널 프로그램
  
  * ngrok 의 5000번 포트를 공용으로 설정



---

### Test

```python
# app.py
from flask import Flask
  
@app.route("/")
def communicate_test():
    return "Success"
```

* ``FLASK_APP=python.py flask run`` 으로 실행하지만, app.py인 경우 default로 설정되어 ``$ flask run``

* `Flask_DEBUG=1 flask run` 으로 실행하면 서버를 재실행하지 않아도 변경 내용 반영



```shell
$ curl localhost:5000/json
{
  "test": "SUCCESS"
}

$ http GET localhost:5000
HTTP/1.0 200 OK
```


