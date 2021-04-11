# Elastic Search

### Architecture

* **Cluster**
  * It is composed of a set of several nodes, and each node is composed of indexes.
  * Indexes are basically distributed and stored on each node by shard. The shard is a search instance of the lucene engine.
  * Node
    * One or more nodes exist in one server, and each node transmits data through tcp/ip communication.
    * One node has more than one index.
  * Shard
    * Primary Shard : The first created Shard is called the primary shard, and 5 shard are created by default.
    * Replica Shard : Replica of the primary shard created for high availability, and 1 shard is created by default.
    * So, Primary Shard created 5 shard, and 1 Replica Shard (==1Primary Shard == 5 Shard) are exists. These shards are distributed and stored in nodes.
  * Discovery
    * When the node first runs, bind nodes included in seed_host or nodes belonging to the same server to one cluster



### Routing

* When a search is executed, it broadcasts to all indexes or index fragments, which can be controlled by providing routing parameters.



### ElasticSearch vs DBMS 

* ElasticSearch represents best profit result to the top, but DBMS has not this function
* The results of ElasticSearch are ordered based on the score, but DBMS randomly show results based on index

| Elastic Search | Relational DB |
| -------------- | ------------- |
| Index          | Database      |
| Type           | Table         |
| Document       | Row           |
| Field          | Column        |
| Mapping        | Schema        |



* Elastic Search uses REST API

| Elastic Search | Relational DB | CRUD   |
| -------------- | ------------- | ------ |
| GET            | Select        | Read   |
| PUT            | Update        | Update |
| POST           | Insert        | Create |
| DELETE         | Delete        | Delete |



### Analyzer

* Generate token when querying by getting text from string field
* **process**
  * Abbreviation
    * Include words with the same meaning when searching the index
  * transform
    * Transforming a verb into a noun form or expressing it in similar words
  * typo handling
    * Correction if incorrect word is included when searching index





### Using on Python

...