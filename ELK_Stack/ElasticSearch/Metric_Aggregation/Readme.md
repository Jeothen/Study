##### Aggregation :  Deriving values through combinations



### Metric Aggregation 

* Metric Aggregation : Mathmatics 
  * Perform mathematical calculations

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


