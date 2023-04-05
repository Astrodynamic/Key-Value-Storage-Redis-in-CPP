# Redis

Implementation of in-memory key-value store for storing various financial transaction data.

## Introduction

In this project, you will need to recall and learn more about such data structures as hash tables and self-balancing
binary trees, and implement a key-value store based on them.

## Implementation on hashtable, binary tree, b+tree

### Description of key-value store functions

### SET

This command is used to set the key and its value. In the example below, the key is the string `foo`, and the value is
the structure described above. The values of the new record fields are entered in the order they are described in the
structure. `EX` is used as an optional parameter to specify the lifetime of the record you are creating. If the optional
field is not specified, the record lifetime is not limited by default.

Description of the `SET` command parameters:

```
SET <key> <Last name> <First name> <Year of birth> <City> <Number of current coins> EX <time in seconds>
```

An example of using the `SET` command to create a record with no time limit:

```
SET foo Vasilev Ivan 2000 Moscow 55 
> OK
SET foo Vasilev 123 aaaaa Moscow 55 
> ERROR: unable to cast value "aaaa" to type int 
```

An example of using the `SET` command to create a record with a time limit. The record will exist for 10 seconds, and
then it will be automatically deleted:

```
SET foo Vasilev Ivan 2000 Moscow 55 EX 10 
> OK
```

### GET

This command is used to get the value associated with the key. If there is no such record, `(null)` will be returned:

```
GET foo
> Vasilev Ivan 2000  Moscow   55 
GET unknownkey
> (null)
```

### EXISTS

This command checks if a record with the given key exists. It returns `true` if the object exists or `false` if it
doesn't:

```
EXISTS foo
> true
```

### DEL

This command deletes the key and the corresponding value, then returns `true` if the record was successfully deleted,
otherwise `false`:

```
DEL foo
> true
```

### UPDATE

This command updates the value by the corresponding key if such a key exists:

```
SET foo Vas I 20 Mos 5 
> OK
UPDATE foo Vasilev Ivan 2000 Moscow 55 
> OK

GET foo
> Vasilev Ivan 2000 Moscow 55
```

If there is a field that is not planned to change, it is replaced by a dash "-":

```
SET foo Vas I 20 Mos 5 
> OK
UPDATE foo Vasilev - - - 55
> OK

GET foo
> Vasilev I 20 Mos 55 
```

### KEYS

Returns all the keys that are in the store:

```
KEYS
1) boo
2) foo
3) bar
```

### RENAME

This command is used to rename keys:

```
RENAME foo foo2
> OK

GET foo
> (null)

GET foo2
> Vasilev I 20 Mos 55
```

### TTL

When the key is set with the time limit, this command can be used to view the remaining time. If there is no record with
the given key, `(null)` will be returned:

```
SET Vasilev Ivan 2000 Moscow 55 EX
10
> OK
TTL foo
> 6
TTL foo
> 5
TTL foo
> 4
TTL foo
> (null)
```

### FIND

This command is used to restore the key (or keys) according to a given value. Similarly to the `UPDATE` command, you
don’t have to specify all the values from the structure of the School 21 students. If any fields will not be searched,
it is replaced by a dash "-".

An example of using the `FIND` command to search through all fields of a student structure:

```
FIND Vasilev Ivan 2000 Moscow 55 
> 1) foo
FIND Vasilev Anton 1997 Tver 55
> 1) boo
```

An example of using the `FIND` command to search by last name and number of coins:

```
FIND Vasilev - - - 55
> 1) foo
> 2) boo
```

### SHOWALL

This command is used for getting all records that are in the key-value store at the moment:

```
SHOWALL
> № | Last name |   First name   | Year |  City   | Number of coins |
> 1   "Vasilev"       "Ivan"       2000  "Moscow"         55 
> 2   "Ivanov"       "Vasily"      2000  "Moscow"         55 
```

### UPLOAD

This command is used to upload data from a file. The file contains a list of uploaded data in the format:

```
key1 "Vasilev" "Ivan" 2001 " Rostov" 55
key2 "Ivanov" "Vasiliy" 2000 "Москва" 55 
...
key101 " Sidorov" "Sergei" 1847 "Suzdal" 12312313 
```

Command call:

```
UPLOAD ~/Desktop/TestData/file.dat
> OK 101
```

After the `OK` the number of strings uploaded from the file is displayed.

### EXPORT

This command is used to export the data that are currently in the key-value store to a file. The output of the file must
contain a list of data in the format:

```
key1 "Vasilev" "Ivan" 2001 " Rostov" 55
key2 "Ivanov" "Vasiliy" 2000 "Москва" 55 
...
key101 " Sidorov" "Sergei" 1847 "Suzdal" 12312313 
```

Command call:

```
EXPORT ~/Desktop/TestData/export.dat
> OK 101
```

After the `OK` the number of strings exported from the file is displayed.

##  Implementation of in-memory key-value store

- The program be developed in C++ language of C++17 standard
- When writing code it is necessary to follow the Google style
- Prepare full coverage with unit-tests