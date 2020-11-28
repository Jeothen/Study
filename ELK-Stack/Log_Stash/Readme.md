# LogStash

* Logstash dynamically collects, transforms, and transmits data 



### mac Setting



* Install

```shell
$ brew install
```

* start logstash

```shell 
$ logstash -e 'input {stdin {}} output {stdout {}}'
```

* config setting

```shell
# /usr/local/etc/logstash/logstash_test.conf
input {
	stdin { }
}
output {
	stdout { }
}
$ logstash
```

* Setting pipelines.yml

```shell
# sudo vim /usr/local/etc/logstash/pipelines.yml

- pipeline.id: my-pipeline_1
  path.config: "/usr/local/etc/logstash/logstash_test.conf"
```

* start logstash 

```
$ logstash
```



### Ubuntu

* Install

```
$ sudo apt-get update && sudo apt-get install logstash
```



* setting logstash-simple.conf

```shell
input {
	stdin { }
}

output {
	stdout { }
}
```

* Start logstash

```shell
cd /usr/share/logstash/bin
$ sudo ./logstash-f logstash-simple.conf
```



---



### Worlds' Popular



* from https://catalog.data.gov/dataset  get ``Population by Country (1980 - 2010)``

* setting logstash_population.conf 

* start logstash

```shell
$ sudo logstash -f logstash_population.conf 
```





