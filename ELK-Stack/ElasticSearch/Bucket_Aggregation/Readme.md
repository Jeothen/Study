### Bucket Aggregation

* Create Bucket by Group



* Create Index

```shell
$ curl -XPUT localhost:9200/basketball
{"acknowledged":true,"shards_acknowledged":true}

```

* add mapping to index

```shell
$ curl -XPUT 'localhost:9200/basketball/record/_mapping' -d @basketball_mapping.json 
{"acknowledged":true}
```

* Insert document

```shell
$ curl -XPOST 'localhost:9200/_bulk' --data-binary @twoteam_basketball.json 
{"took":18,"errors":false,"items":[{"index":{"_index":"basketball","_type":"record","_id":"1","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"2","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"3","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}},{"index":{"_index":"basketball","_type":"record","_id":"4","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"created":true,"status":201}}]}
```

* Aggregation by team (terms - field : team)

```shell
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
```

* Apply stat (metric aggregation)

```shell

# bucket aggretation은 sub aggregation을 넣을 수 있음
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

