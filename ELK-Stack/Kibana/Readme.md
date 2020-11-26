# Kibana

* Open Source data visualization DashBoard
* visualization capability on indexed ElasticSearch Cluster





### Settings



```shell
# /etc/kibana/kibana.yml

# ubuntu
elasticsearch.url / server.host  setup

#mac 
/usr/local/etc/kibana/kibana.yml
$ brew info kibana
```





### Management

* Create Index

```shell
$ curl -XPUT localhost:9200/basketball
{"acknowledged":true,"shards_acknowledged":true,"index":"basketball"}
```

* Insert mapping

```shell
$ curl -XPOST 'localhost:9200/basketball/record' -H 'Content-Type:application/json' -d @basketball_mapping.json

# above elasticsearch 6.0 - insert -H 'Content-Type:application/json' and change string type to text type on mapping.json and not add /_option/ in url

{"_index":"basketball","_type":"record","_id":"x1P1_3UBnNLNfaWjUVMh","_version":1,"result":"created","_shards":{"total":2,"successful":1,"failed":0},"_seq_no":1,"_primary_term":1}

$ curl -XPOST 'localhost:9200/_bulk'  -H 'Content-Type:application/json' --data-binary @bulk_basketball.json


```

* start kibana (localhost:5601)

---

#### Create Index Pattern

* In the case of large capacity, overload may occur if managed in one pattern, so index patterns are created by dividing them into several units.

### Discover

* setting dates range based on the date set in the data
* there's a many function like select specific columns (toggle) and data transformation(json, table)...

#### Visualize

* there's a many visualization graph.
* search graph and index pattern. then setting axis
* select aggregation / field / orderby...







#### Canvas

* presented by kibana, canvas pulls live data from elasticsearch then make presentaion and slide deck.
* ...