# Curator

* Disk capacity management system
* performs the function of storing and executing repetitive tasks in the form of ymal files for the management of elasticsearch.
* Delete/create index, create/delete snapshot, change shard routing allocation, etc.



---



### Setting

* install

```shell
$ pip install elasticsearch-curator
```



### Ubuntu

* Command Shell script ()

```shell
$ sh delete_indices_size_base.sh
# delete_indices_size_base.sh
/usr/local/bin/curator delete_indices_size_base.yml --config curator.yml 
```



#### Crontap

* By setting the cycle, the specified function works

