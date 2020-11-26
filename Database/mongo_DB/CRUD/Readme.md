# CRUD



### Database

* show database

```json
> show dbs
admin   0.000GB
config  0.000GB
local   0.000GB
test1   0.000GB

```



* use database

```json
> use test1
switched to db test1

> show collections
products

```



* drop database

```json
> db.dropDatabase()
{ "dropped" : "test1", "ok" : 1 }


```



* Create database

```json
> use acme
switched to db acme
> show dbs
admin   0.000GB
config  0.000GB
local   0.000GB

> db
acme


> db.createCollection('posts')
{ "ok" : 1 }
> show collections
posts


```

### Query

---

#### Insert

* Insert query

```json
> db.posts.insert({
		title: 'Post One',
		body: 'Body of post one',
		category: 'News',
		likes: 4,
		tags: ['news','events'],
	  user: {
    name: 'Jong Doe',
    status: 'author'
 },
 date: Date()
})
WriteResult({ "nInserted" : 1 })
> 

```



* Insert Many queries

```json

db.posts.insertMany([
  {
    title: 'Post Two',
    body: 'Body of post two',
    category: 'Technology',
    data: Date()
  },
  {
    title: 'Post Three',
    body: 'Body of post three',
    category: 'News',
    data: Date()
  },
  {
    title: 'Post Four',
    body: 'Body of post four',
    category: 'Entertainment',
    data: Date()
  }
])


```





* update

```json
> db.posts.update({title:'Post Two'},
 {
   title: 'Post Two',
   body: 'New post 2 body',
   date: Date()
 },
 {
   upsert: true
 }
)

WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })


> db.posts.find({title:'Post Two'}).pretty()
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48124"),
	"title" : "Post Two",
	"body" : "New post 2 body",
	"date" : "Sat Sep 26 2020 11:05:27 GMT+0900 (KST)"
}


db.posts.update({title: 'Post Two'}, 
  {
    $set: {
      body: 'Body of post 2',
      category: 'Technology'
    }
  }
)
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })

> db.posts.find({title:'Post Two'}).pretty()
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48124"),
	"title" : "Post Two",
	"body" : "Body of post 2",
	"date" : "Sat Sep 26 2020 11:05:27 GMT+0900 (KST)",
	"category" : "Technology"
}

```



* count update

```json
> db.posts.find({title: 'Post One'}).pretty()
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)"
}
> db.posts.update({title: 'Post One'},{$inc:{likes:2}})
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.posts.find({title: 'Post One'}).pretty()
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 6,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)"
}

```

* rename

```json
> db.posts.update({title:'Post One'}, {$rename: {likes: 'views'}})
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.posts.find({title: 'Post One'}).pretty()
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)",
	"views" : 10
}
```

* remove

```json
> db.posts.remove({title:'Post Four'})
WriteResult({ "nRemoved" : 1 })

> db.posts.find().pretty()
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)",
	"views" : 10
}
{
	"_id" : ObjectId("5f6ea0ac5ecb3a5d78d4812a"),
	"title" : "Post Two",
	"body" : "Body of post two",
	"category" : "Technology",
	"data" : "Sat Sep 26 2020 11:00:12 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6ea0ac5ecb3a5d78d4812b"),
	"title" : "Post Three",
	"body" : "Body of post three",
	"category" : "News",
	"data" : "Sat Sep 26 2020 11:00:12 GMT+0900 (KST)"
}

```

* Update Comment

```json
> db.posts.update({title: 'Post One'}, 
... {
...   $set: {
...     comments: [
...     {
...       user: 'Mary Wiliams',
...       body: 'Comment One',
...       date: Date()
...     },
...     {
...     user: 'Harry White',
...     body: 'Comment Two',
...     date: Date()
...     }]
...   } 
... })
WriteResult({ "nMatched" : 1, "nUpserted" : 0, "nModified" : 1 })
> db.posts.find({title: 'Post One'}).pretty()
{
	"_id" : ObjectId("5f6ecc2465d6b86155b6d796"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 14:05:40 GMT+0900 (KST)",
	"comments" : [
		{
			"user" : "Mary Wiliams",
			"body" : "Comment One",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		},
		{
			"user" : "Harry White",
			"body" : "Comment Two",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		}
	]
}


>db.posts.find({
  comments:{
    $elemMatch: {
      user: 'Mary Wiliams'
    }
  }
}).pretty()

{
	"_id" : ObjectId("5f6ecc2465d6b86155b6d796"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 14:05:40 GMT+0900 (KST)",
	"comments" : [
		{
			"user" : "Mary Wiliams",
			"body" : "Comment One",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		},
		{
			"user" : "Harry White",
			"body" : "Comment Two",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		}
	]
}
```









### Read Database

* Read database

```json
> db.posts.find()
{ "_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"), "title" : "Post One", "body" : "Body of post one", "category" : "News", "likes" : 4, "tags" : [ "news", "events" ], "user" : { "name" : "Jong Doe", "status" : "author" }, "date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)" }
{ "_id" : ObjectId("5f6e9c085ecb3a5d78d48124"), "title" : "Post Two", "body" : "Body of post two", "category" : "Technology", "data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)" }
{ "_id" : ObjectId("5f6e9c085ecb3a5d78d48125"), "title" : "Post Three", "body" : "Body of post three", "category" : "News", "data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)" }
{ "_id" : ObjectId("5f6e9c085ecb3a5d78d48126"), "title" : "Post Four", "body" : "Body of post four", "category" : "Entertainment", "data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)" }

```



* Pretty show database

```json
> db.posts.find().pretty()
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48124"),
	"title" : "Post Two",
	"body" : "Body of post two",
	"category" : "Technology",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48125"),
	"title" : "Post Three",
	"body" : "Body of post three",
	"category" : "News",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48126"),
	"title" : "Post Four",
	"body" : "Body of post four",
	"category" : "Entertainment",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}




> db.posts.find().sort({title: 1}).pretty()
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48125"),
	"title" : "Post Three",
	"body" : "Body of post three",
	"category" : "News",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48126"),
	"title" : "Post Four",
	"body" : "Body of post four",
	"category" : "Entertainment",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6e9c085ecb3a5d78d48124"),
	"title" : "Post Two",
	"body" : "Body of post two",
	"category" : "Technology",
	"data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)"
}

```



* column  count

```json
> db.posts.find({category: 'News'}).count()
2

> db.posts.find().limit(2)
{ "_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"), "title" : "Post One", "body" : "Body of post one", "category" : "News", "likes" : 4, "tags" : [ "news", "events" ], "user" : { "name" : "Jong Doe", "status" : "author" }, "date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)" }
{ "_id" : ObjectId("5f6e9c085ecb3a5d78d48124"), "title" : "Post Two", "body" : "Body of post two", "category" : "Technology", "data" : "Sat Sep 26 2020 10:40:24 GMT+0900 (KST)" }

```



* use find() with javascript

```javascript
> db.posts.find().forEach(function(doc) {print('Blog Post: ' + doc.title)})
Blog Post: Post One
Blog Post: Post Two
Blog Post: Post Three
Blog Post: Post Four

```



* findone

```json
> db.posts.findOne({ category: 'News'})
{
	"_id" : ObjectId("5f6e9ab35ecb3a5d78d48123"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 10:34:43 GMT+0900 (KST)"
}

```



* Create Index

```json
> db.posts.createIndex({title: 'text'})
{
	"createdCollectionAutomatically" : false,
	"numIndexesBefore" : 1,
	"numIndexesAfter" : 2,
	"ok" : 1
}

db.posts.find({
  $text: {
    $search: "\"Post 0\""
  }
})
 

```



* find - sentense included

```json
> db.posts.find({   $text: {     $search: "\"Post O\""   } }).pretty()
{
	"_id" : ObjectId("5f6ecc2465d6b86155b6d796"),
	"title" : "Post One",
	"body" : "Body of post one",
	"category" : "News",
	"likes" : 4,
	"tags" : [
		"news",
		"events"
	],
	"user" : {
		"name" : "Jong Doe",
		"status" : "author"
	},
	"date" : "Sat Sep 26 2020 14:05:40 GMT+0900 (KST)",
	"comments" : [
		{
			"user" : "Mary Wiliams",
			"body" : "Comment One",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		},
		{
			"user" : "Harry White",
			"body" : "Comment Two",
			"date" : "Sat Sep 26 2020 14:16:28 GMT+0900 (KST)"
		}
	]
}

> db.posts.find({   $text: {     $search: "\"post T\""   } }).pretty()
{
	"_id" : ObjectId("5f6ecbfa65d6b86155b6d794"),
	"title" : "Post Three",
	"body" : "Body of post three",
	"category" : "News",
	"data" : "Sat Sep 26 2020 14:04:58 GMT+0900 (KST)"
}
{
	"_id" : ObjectId("5f6ecbfa65d6b86155b6d793"),
	"title" : "Post Two",
	"body" : "Body of post 2",
	"date" : "Sat Sep 26 2020 14:06:05 GMT+0900 (KST)",
	"category" : "Technology"
}
```



* value compare view
  * gte :   (greater than  || equal)

```json
> db.posts.find({views: {$gt:3}})
{ "_id" : ObjectId("5f6ecbfa65d6b86155b6d793"), "title" : "Post Two", "body" : "Body of post 2", "date" : "Sat Sep 26 2020 14:06:05 GMT+0900 (KST)", "category" : "Technology", "views" : 10 }
```

