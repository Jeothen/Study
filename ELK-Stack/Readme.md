# ELK



#### Ubuntu Setting

* jdk install

```shell
$ sudo add-apt-repository -y ppa:webupd8team/java
$ sudo apt-get update
$ sudo apt-get install openjdk-8-jdk
$ java -version
```

* jdk env.  setting

```shell
$ sudo vi /etc/profile
# add

export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export PATH=$JAVA_HOME/bin:$PATH
export Class_PATH=$JAVA_HOME/lib:$CLASS_PATH
```

* firewall

```shell
$ sudo apt-get install firewalld
$ sudo firewall-cmd --permanent --zone=public --add-port=9200/tcp
$ sudo firewall-cmd --reload
$ sudo firewall-cmd --list-ports
```



https://www.elastic.co/kr/support/matrix



* elasticsearch / logstash / kibana / filebeat install

```shell
$ wget https://artifacts.elastic.co/downloads/elasticsearch/elasticsearch-7.3.0-amd64.deb

$ wget https://artifacts.elastic.co/downloads/logstash/logstash-7.3.0.deb

$ wget https://artifacts.elastic.co/downloads/kibana/kibana-7.3.0-amd64.deb
```

* Dpkg

```shell
$ sudo dpkg -i elasticsearch-7.3.0-amd64.deb

$ sudo dpkg -i logstash-7.3.0.deb

$ sudo dpkg -i kibana-7.3.0-amd64.deb
```

* network connection 

```shell
/etc/elasticsearch/elasticsearch.yml chagne on test environment
  * network.host: 0.0.0.0
  * Discovery.seed_hosts = ["0.0.0.0"]
  
  -----
  network:
  	host: 0.0.0.0
  http:
  	port: 9200
```



* start / stop

```shell
$ sudo systemctl enable elasticsearch.service

$ sudo service elasticsearch start
# $ sudo service elasticsearch stop

$ sudo service kibana start

$ sudo service logstash start
```

* status

```shell
$ sudo service elasticsearch status

# check Active status
```



---

#### Mac Setting

* openjdk install

```shell
$ brew cask install homebrew/cask-versions/adoptopenjdk8

# environment setting to jdk8
```

* homebrew update

```shell
$ /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

* install elasticsearch

```shell
$ brew install elasticsearch
```

* start elasticsearch

````shell
$ elasticsearch
````

* kibana install

````shell
$ brew install kibana
````


