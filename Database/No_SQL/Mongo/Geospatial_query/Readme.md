# Geospatial Queries Operator

* In mongodb, geospatial data saved as GeoJson object or legacy coordinates pairs
* When using spactial query Operator, location information designated  to 2d or 2dsphere



#### GeoJson Objects

* 



#### Legacy Coordinates Pairs

* 



#### mongo

* Create Index / Insert query
* db.collection.createIndex() method used for making 2dsphere index

```shell
> db.collection.createIndex( { test_place : "2dsphere" } )
{
	"createdCollectionAutomatically" : true,
	"numIndexesBefore" : 1,
	"numIndexesAfter" : 2,
	"ok" : 1
}

> db.test_place.insert(
{
  loc : { type: "Point", coordinates: [ 30.72, -20.11 ] },
  name: "Jeothen",
  category : "test"
})
WriteResult({ "nInserted" : 1 })


```

* make 2dsphere on loc field of test_place

```shell
> db.test_place.createIndex( {loc : "2dsphere"})
{
	"createdCollectionAutomatically" : false,
	"numIndexesBefore" : 2,
	"numIndexesAfter" : 3,
	"ok" : 1
}
```

