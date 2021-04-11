###  BULK

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

# searching each id
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

