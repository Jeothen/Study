# Update / Create / Delete





* Data Update

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



