# Elastic Search



| Elastic Search | Relational DB |
| -------------- | ------------- |
| Index          | Database      |
| Type           | Table         |
| Document       | Row           |
| Field          | Column        |
| Mapping        | Schema        |



* Elastic Search는 REST API를 사용

| Elastic Search | Relational DB | CRUD   |
| -------------- | ------------- | ------ |
| GET            | Select        | Read   |
| PUT            | Update        | Update |
| POST           | Insert        | Create |
| DELETE         | Delete        | Delete |





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

