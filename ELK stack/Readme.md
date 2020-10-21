

elastic seart start / stop

```
sudo service elasticsearch start
sudo service elasticsearch stop
```





| E lastic Search | Relational DB |
| --------------- | ------------- |
| Index           | Database      |
| Type            | Table         |
| Document        | Row           |
| Field           | Column        |
| Mapping         | Schema        |





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
$curl -XPOST http://localhost:9200/classes/class/1/ -
d @oneclass.json
{"_index":"classeclass","_type":"1","_id":"AXU6TcWqQneg6MMtXzyM","_version":1,"result":"created","_shards":{"total"
:2,"successful":1,"failed":0},"created":true}

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





* BULK
  - 여러개의 document를 elasticsearch에 한번에 삽입 

```shell
curl -XPOST http://localhost:9200/_bulk?pretty --data-binary @classes.json

{
  "took" : 172,
  "errors" : false,
  "items" : [
    {
      "index" : {
        "_index" : "classes",
        "_type" : "class",
        "_id" : "1",
        "_version" : 11,
        "result" : "updated",
        "_shards" : {
          "total" : 2,
          "successful" : 1,
          "failed" : 0
        },
        "created" : false,
        "status" : 200
      }
    },
    ...
    {
      "index" : {
        "_index" : "classes",
        "_type" : "class",
        "_id" : "25",
        "_version" : 1,
        "result" : "created",
        "_shards" : {
          "total" : 2,
          "successful" : 1,
          "failed" : 0
        },
        "created" : true,
        "status" : 201
      }
    }
  ]
}

$ curl -XGET http://localhost:9200/classes/class/25?pretty

{
  "_index" : "classes",
  "_type" : "class",
  "_id" : "25",
  "_version" : 1,
  "found" : true,
  "_source" : {
    "title" : "Anatomy",
    "Professor" : "Tom Johnson",
    "major" : "Medical",
    "semester" : [
      "fall"
    ],
    "student_count" : 30,
    "unit" : 5,
    "rating" : 3,
    "submit_date" : "2016-11-12",
    "school_location" : {
      "lat" : 28.22,
      "lon" : -81.87
    }
  }
}
```



* mapping

```shell
$ curl -XGET http://localhost:9200/classes

$ curl -XGET http://localhost:9200/classes?pretty
{
  "classes" : {
    "aliases" : { },
    "mappings" : { },
    "settings" : {
      "index" : {
        "creation_date" : "1603023779478",
        "number_of_shards" : "5",
        "number_of_replicas" : "1",
        "uuid" : "RfIFiB1NTX6pvEJqulxRBQ",
        "version" : {
          "created" : "5050199"
        },
        "provided_name" : "classes"
      }
    }
  }
}

$ curl -XPUT 'http://localhost:9200/classes/class/_mapping' -d @classesRating_mapping.json 
{"acknowledged":true}

$ $ curl -XGET http://localhost:9200/classes?pretty
{
  "classes" : {
    "aliases" : { },
    "mappings" : {
      "class" : {
        "properties" : {
          "major" : {
            "type" : "text"
          },
          "professor" : {
            "type" : "text"
          },
          "rating" : {
            "type" : "integer"
          },
          "school_location" : {
            "type" : "geo_point"
          },
          "semester" : {
            "type" : "text"
          },
          "student_count" : {
            "type" : "integer"
          },
          "submit_date" : {
            "type" : "date",
            "format" : "yyyy-MM-dd"
          },
          "title" : {
            "type" : "text"
          },
          "unit" : {
            "type" : "integer"
          }
        }
      }
    },
    "settings" : {
      "index" : {
        "creation_date" : "1603023779478",
        "number_of_shards" : "5",
        "number_of_replicas" : "1",
        "uuid" : "RfIFiB1NTX6pvEJqulxRBQ",
        "version" : {
          "created" : "5050199"
        },
        "provided_name" : "classes"
      }
    }
  }
}


# bulk

$ curl -XPOST http://localhost:9200/_bulk?pretty --data-binary @classes.json

{
  "took" : 175,
  "errors" : false,
  "items" : [
    {
      "index" : {
        "_index" : "classes",
        "_type" : "class",
        "_id" : "1",
        "_version" : 1,
        "result" : "created",
        "_shards" : {
          "total" : 2,
          "successful" : 1,
          "failed" : 0
        },
        "created" : true,
        "status" : 201
      }
    },
    ...
    {
      "index" : {
        "_index" : "classes",
        "_type" : "class",
        "_id" : "25",
        "_version" : 1,
        "result" : "created",
        "_shards" : {
          "total" : 2,
          "successful" : 1,
          "failed" : 0
        },
        "created" : true,
        "status" : 201
      }
    }
  ]
}
```





* Search

```shell
$ curl -XPOST http://localhost:9200/_bulk --data-binary @simple_basketball.json
# search  address/type/search(option)
$ curl -XGET http://localhost:9200/basketball/record/_search?pretty
{
  "took" : 229,
  "timed_out" : false,
  "_shards" : {
    "total" : 5,
    "successful" : 5,
    "failed" : 0
  },
  "hits" : {
    "total" : 2,
    "max_score" : 1.0,
    "hits" : [
      {
        "_index" : "basketball",
        "_type" : "record",
        "_id" : "2",
        "_score" : 1.0,
        "_source" : {
          "team" : "Chicago Bulls",
          "name" : "Michael Jordan",
          "points" : 20,
          "rebounds" : 5,
          "assists" : 8,
          "submit_date" : "1996-10-11"
        }
      },
      {
        "_index" : "basketball",
        "_type" : "record",
        "_id" : "1",
        "_score" : 1.0,
        "_source" : {
          "team" : "Chicago Bulls",
          "name" : "Michael Jordan",
          "points" : 30,
          "rebounds" : 3,
          "assists" : 4,
          "submit_date" : "1996-10-11"
        }
      }
    ]
  }
}


# search - URI

$ curl -XGET 'localhost:9200/basketball/record/_search?q=points:30&pretty'
{
  "took" : 2,
  "timed_out" : false,
  "_shards" : {
    "total" : 5,
    "successful" : 5,
    "failed" : 0
  },
  "hits" : {
    "total" : 1,
    "max_score" : 1.0,
    "hits" : [
      {
        "_index" : "basketball",
        "_type" : "record",
        "_id" : "1",
        "_score" : 1.0,
        "_source" : {
          "team" : "Chicago Bulls",
          "name" : "Michael Jordan",
          "points" : 30,
          "rebounds" : 3,
          "assists" : 4,
          "submit_date" : "1996-10-11"
        }
      }
    ]
  }
}
$ curl -XGET "localhost:9200/basketball/record/_search?pretty" -d '{"query":{"term" :{"points" :30 }}}'

# above elastic 6.0 vers ion 
$ curl -XGET "localhost:9200/basketball/record/_search?pretty" -H "Content-Type: application/json" -d '{"query":{"term" :{"points" :30 }}}'


```



* Aggregation 

  * 조합을 통해서 값을 도출
  * Metric Aggregation : Mathmatics

  

```shell
$ curl -XGET localhost:9200/_search?pretty --data-binary @avg_points_aggs.json 
{
  "took" : 167,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 27,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "avg_score" : {
      "value" : 25.0
    }
  }
}

$ curl -XGET localhost:9200/_search?pretty --data-binary @max_points_aggs.json 
{
  "took" : 9,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 27,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "max_score" : {
      "value" : 30.0
    }
  }
}

$ curl -XGET localhost:9200/_search?pretty --data-binary @min_points_aggs.json 
{
  "took" : 8,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 27,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "min_score" : {
      "value" : 20.0
    }
  }
}

$ curl -XGET localhost:9200/_search?pretty --data-binary @sum_points_aggs.json 
{
  "took" : 8,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 27,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "sum_score" : {
      "value" : 50.0
    }
  }
}

$ curl -XGET localhost:9200/_search?pretty --data-binary @stats_points_aggs.json 
{
  "took" : 12,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 27,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "stats_score" : {
      "count" : 2,
      "min" : 20.0,
      "max" : 30.0,
      "avg" : 25.0,
      "sum" : 50.0
    }
  }
}
```



* Bucket Aggregation

```shell
$ curl -XPUT localhost:9200/basketball
{"acknowledged":true,"shards_acknowledged":true}

$ curl -XPUT 'localhost:9200/basketball/record/_mapping' -d @basketball_mapping.json 
{"acknowledged":true}

$ curl -XPOST 'localhost:9200/_bulk' --data-binary @twoteam_basketball.json 
{"took":18,"errors":false,"items":[{"index":{"_index":"basketball","_type":"record","_id":"1","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"2","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"3","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"4","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}}]}

$ curl -XGET localhost:9200/_search?pretty --data-binary @terms_aggs.json 
{
  "took" : 75,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 29,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "players" : {
      "doc_count_error_upper_bound" : 0,
      "sum_other_doc_count" : 0,
      "buckets" : [
        {
          "key" : "chicago",
          "doc_count" : 2
        },
        {
          "key" : "la",
          "doc_count" : 2
        }
      ]
    }
  }
}

// terms -> aggs
$ curl -XGET localhost:9200/_search?pretty --data-binary @stats_by_team.json 
{
  "took" : 20,
  "timed_out" : false,
  "_shards" : {
    "total" : 15,
    "successful" : 15,
    "failed" : 0
  },
  "hits" : {
    "total" : 29,
    "max_score" : 0.0,
    "hits" : [ ]
  },
  "aggregations" : {
    "team_stats" : {
      "doc_count_error_upper_bound" : 0,
      "sum_other_doc_count" : 0,
      "buckets" : [
        {
          "key" : "chicago",
          "doc_count" : 2,
          "stats_score" : {
            "count" : 2,
            "min" : 20.0,
            "max" : 30.0,
            "avg" : 25.0,
            "sum" : 50.0
          }
        },
        {
          "key" : "la",
          "doc_count" : 2,
          "stats_score" : {
            "count" : 2,
            "min" : 30.0,
            "max" : 40.0,
            "avg" : 35.0,
            "sum" : 70.0
          }
        }
      ]
    }
  }
}
```

