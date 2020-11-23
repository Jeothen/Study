### CRUD

* ubuntu   (-Xget) Index find

```shell
$ curl -XGET http://localhost:9200/classes?pretty
{
  "error" : {
    "root_cause" : [
      {
        "type" : "index_not_found_exception",
        "reason" : "no such index",
        "resource.type" : "index_or_alias",
        "resource.id" : "classes",
        "index_uuid" : "_na_",
        "index" : "cl2asses"
      }
    ],
    "type" : "index_not_found_exception",
    "reason" : "no such index",
    "resource.type" : "index_or_alias",
    "resource.id" : "classes",
    "index_uuid" : "_na_",
    "index" : "classes"
  },
  "status" : 404
}
```



* index Update

```shell
$curl -XPUT http://localhost:9200/classes
{"acknowledged":true,"shards_acknowledged":true}


$curl -XGET http://localhost:9200/classes?pretty
{
  "classes" : {
    "aliases" : { },
    "mappings" : { },
    "settings" : {
      "index" : {
        "creation_date" : "1602997987967",
        "number_of_shards" : "5",
        "number_of_replicas" : "1",
        "uuid" : "lAKr5TkxSCeRhsE0bRoxUA",
        "version" : {
          "created" : "5050199"
        },
        "provided_name" : "classes"
      }
    }
  }
}
```



* Index delete

```shell
$curl -XDELETE http://localhost:9200/classes
{"acknowledged":true}
$curl -XGET http://localhost:9200/classes?pretty
{
  "error" : {
    "root_cause" : [
      {
        "type" : "index_not_found_exception",
        "reason" : "no such index",
        "resource.type" : "index_or_alias",
        "resource.id" : "classes",
        "index_uuid" : "_na_",
        "index" : "classes"
      }
    ],
    "type" : "index_not_found_exception",
    "reason" : "no such index",
    "resource.type" : "index_or_alias",
    "resource.id" : "classes",
    "index_uuid" : "_na_",
    "index" : "classes"
  },
  "status" : 404
}
```

* Index Create (/index/type/id  -d(option))

```shell
$curl -XPOST http://localhost:9200/classes/class/1/ -d '{"title":"Algorithm", "professor": "John"}'

{"_index":"classes","_type":"class","_id":"1","_version":1,"result":"created","_shards":{"total":2,"successful":1,"
failed":0},"created":true}

$ curl -XGET http://localhost:9200/classes/class/1/?pretty
{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 1,
  "found" : true,
  "_source" : {
    "title" : "Algorithm",
    "professor" : "John"
  }
}
```



* POST (file)

```shell
# oneclass.json
{
    "title" : "ELK",
    "Professor" : "John",
    "major" : "Computer Science",
    "semester" : ["spring", "fall"],
    "student_count" : 100,
    "unit" : 3,
    "rating" : 5
}
```



```shell
$curl -XPOST http://localhost:9200/classes/class/1/ -d @oneclass.json
{"_index":"classeclass","_type":"1","_id":"AXU6TcWqQneg6MMtXzyM","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true}

$ curl -XGET http://localhost:9200/classes/class/1/?pretty
{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 2,
  "found" : true,
  "_source" : {
    "title" : "ELK",
    "Professor" : "John",
    "major" : "Computer Science",
    "semester" : [
      "spring",
      "fall"
    ],
    "student_count" : 100,
    "unit" : 3,
    "rating" : 5
  }
}
```



### Data Update

```shell
$ curl -XPOST http://localhost:9200/classes/class/1/ -d '{"title":"Algorithm", "professor": "John"}'

$ curl -XGET http://localhost:9200/classes/class/1?pretty

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 7,
  "found" : true,
  "_source" : {
    "title" : "Algorithm",
    "professor" : "John"
  }
}

$ curl -XPOST http://localhost:9200/classes/class/1/_update?pretty -d '{"doc" : {"unit":1}}'

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 8,
  "result" : "updated",
  "_shards" : {
    "total" : 2,
    "successful" : 1,
    "failed" : 0
  }
}

$ curl -XGET http://localhost:9200/classes/class/1?pretty

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 8,
  "found" : true,
  "_source" : {
    "title" : "Algorithm",
    "professor" : "John",
    "unit" : 1
  }
}

$ curl -XPOST http://localhost:9200/classes/class/1/_update?pretty -d '{"doc" : { "unit":2}}'

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 9,
  "result" : "updated",
  "_shards" : {
    "total" : 2,
    "successful" : 1,
    "failed" : 0
  }
}
$ curl -XGET http://localhost:9200/classes/class/1?pretty

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 9,
  "found" : true,
  "_source" : {
    "title" : "Algorithm",
    "professor" : "John",
    "unit" : 2
  }
}

# property : script / 
# ctx field : https://knight76.tistory.com/entry/elasticsearch-ctx-%ED%95%98%EC%9C%84-%ED%95%84%EB%93%9C-%EC%84%A4%EB%AA%85


$ curl -XPOST http://localhost:9200/classes/class/1/_update?pretty -d '{"script":"ctx._source.unit+=5"}'

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 10,
  "result" : "updated",
  "_shards" : {
    "total" : 2,
    "successful" : 1,
    "failed" : 0
  }
}

$ curl -XGET http://localhost:9200/classes/class/1?pretty

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "1",
  "_version" : 10,
  "found" : true,
  "_source" : {
    "title" : "Algorithm",
    "professor" : "John",
    "unit" : 7
  }
}
```



