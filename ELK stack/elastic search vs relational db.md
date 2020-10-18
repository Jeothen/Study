

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

```
curl -XGET http://localhost:9200/classes?pretty
```

 

