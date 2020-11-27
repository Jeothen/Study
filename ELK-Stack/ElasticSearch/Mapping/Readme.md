



### mapping

* same as DBMS Schema
* The data saved as a string due to no mapping is not calculated because it is saved as a string when visualized.



* Create Index

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

```



* Add Mapping
  * Update Properties

```shell

$ curl -XPUT 'http://localhost:9200/classes/class/_mapping' -d @classesRating_mapping.json 
{"acknowledged":true}

# above 6.8.  _mapping' -> _mapping?include_type_name=true'

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
```



* Bulk

```shell
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


# Check

$ curl -XGET http://localhost:9200/classes/class/1?pretty

```

