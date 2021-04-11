

### Search



* Insert bulk data

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


```



* Search - URI Option

```shell
# query - search only point : 30 
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

```

* Search - Request Body
  * https://www.elastic.co/guide/en/elasticsearch/reference/6.8/search-request-body.html
  * There's many parameters

```shell
$ curl -XGET "localhost:9200/basketball/record/_search?pretty" -d '{"query":{"term" :{"points" :30 }}}'
```

* above elasticsearch 6.0 version 

```shell
$ curl -XGET "localhost:9200/basketball/record/_search?pretty" -H "Content-Type: application/json" -d '{"query":{"term" :{"points" :30 }}}'
```

