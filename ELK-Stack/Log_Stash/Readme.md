# LogStash



### mac Setting



* Install

```shell
$ brew install
```

* start logstash

```shell 
$ logstash -e 'input {stdin {}} output {stdout {}}'


# add stdin { } stdout { } on /usr/local/Cellar/logstash/7.9.3_1/libexec/config/logstash-sample.conf
# then $ logstash
```



