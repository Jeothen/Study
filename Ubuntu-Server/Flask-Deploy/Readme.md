## Flask Deploy

* Deploy using nginx  /  uwsgi 



#### Env. setting

* ``$ sudo adduser thj ``  : user add shell

  * `$ sudo visudo`  : register user authentication
  
  * ``su - thj`` : user change (super user).   ``su the`` : just change user

  * Package download on ``/etc/apt/source.list ``  : archive influence parkage install speed

    * ``sed``  : change archive page
* using archive on ubuntu versions
    
  * setting on like API Server
  
    

#### Uwsgi setting

```shell
$ python3 -m pip install uwsgi
```

* Add ``app = Flask(__name__) ``   on app.py

  * because uwsgi find on application, so add  `` application = app ``  on last line 

* app.py running on port 9090

  ```shell
  $ uwsgi --wsgi-file app.py --http :9090
  ```

* below context save on uswgi.ini 

  ````shell
  [uwsgi]
  http = :9090
  wsgi-file = app.py
  single-interpreter = true  # single or multiple interpreter mode
  enable-threads = true  # additional thread possible
  master = true  # master node
  
  # etc setting exists
  ````

* then just using 

  ```shell
  $ uwsgi --ini uwsgi.ini
  ```

  

#### nginx setting

```shell
$ sudo apt-get install nginx

$ sudo vim /etc/nginx/sites-available/flask_config.ini
```

* below context save on flask_config.ini

```shell
server {
    listen 80;  # listen port
    server_name localhost; 

    location / {
        include uwsgi_params; 
        uwsgi_pass unix:/tmp/flask.sock;  # nginx just convey to flask.sock - proxy role 
    }
}
```

* activated through link

```shell
$ sudo ln -s /etc/nginx/sites-available/flask_config.ini /etc/nginx/sites-enabled/
# if default is activated, then remove default file
$ sudo service nginx restart
```

* nginx is operated but, add below context to uwsgi.ini beacause there's no socket

```shell
socket = /tmp/flask.sock # socket create in that path
chmod-socket = 666  # other user include nginx can read / write socket
```

* remove http setting on uwsgi and only using through nginx

```shell
# http = :9090
```

* then restart uwsgi

```shell
$ sudo service uwsgi restart

# operate uwsgi 
$ uwsgi --ini uwsgi.ini

# client 
$ curl localhost  # not using specific port
```

