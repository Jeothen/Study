# Mongo DB



### Setting on Mac

* using terminal

```shell
$ brew install mongodb
```

* server defaultly saved data on ``/data/db ``
* mkdir ``/data/db``

```shell
$ sudo bash
# mkdir -p /data/db
# chmod 777 /data
# chmod 777 /data/db
```

* start mongodb

```shell
$ ./mongo   # using on pwd
```

* environment setting. (bash)

```shell
$ vi ~/.bashrc

# add below lines
export MONGO_PATH=/usr/local/mongodb
export PATH=PATH:MONGO_PATH/bin
```



#### mongod vs mongo

* mongod is mongo daemon
  * basically host process for the database
* mongo is command line shell
  * connects to specific instance of mongod



