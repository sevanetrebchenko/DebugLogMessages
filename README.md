# Debug Logging Messages
Logging messages that capture file, function, and line number of the callee at runtime as part of the log message records without requiring any additional information in the function call. 

## Sample Output
Debug messages turned off:

```
Single-line log messages: 
---------------------------------------------------------------------------------------
[ DEBUG ]
[ 000m 00s 0000ms ] - Hello, world!

[ WARNING ]
[ 000m 00s 0100ms ] - My favorite number is 7.

[ SEVERE ]
[ 000m 00s 0201ms ] - Do you like green eggs and ham?


Multi-line log messages: 
---------------------------------------------------------------------------------------
[ DEBUG ]
[ 000m 00s 0201ms ] - Hello, world...
[ 000m 00s 0201ms ] - Hello, again!

[ WARNING ]
[ 000m 00s 0201ms ] - I thought my favorite number was 7 before...
[ 000m 00s 0201ms ] - but it's now 5.400000!

[ SEVERE ]
[ 000m 00s 0302ms ] - I do not like them,
[ 000m 00s 0302ms ] - Sam-I-am.
[ 000m 00s 0302ms ] - I do not like
[ 000m 00s 0302ms ] - Green eggs and ham.
```


Debug messages turned off:
```
Single-line log messages: 
---------------------------------------------------------------------------------------
[ DEBUG ]
[ 000m 00s 0000ms ] - Hello, world!
	: called from file: main, at main.cpp:14

[ WARNING ]
[ 000m 00s 0100ms ] - My favorite number is 7.
	: called from file: main, at main.cpp:21

[ SEVERE ]
[ 000m 00s 0201ms ] - Do you like green eggs and ham?
	: called from file: main, at main.cpp:28


Multi-line log messages: 
---------------------------------------------------------------------------------------
[ DEBUG ]
[ 000m 00s 0201ms ] - Hello, world...
	: called from file: main, at main.cpp:36
[ 000m 00s 0201ms ] - Hello, again!
	: called from file: main, at main.cpp:37

[ WARNING ]
[ 000m 00s 0201ms ] - I thought my favorite number was 7 before...
	: called from file: main, at main.cpp:41
[ 000m 00s 0201ms ] - but it's now 5.400000!
	: called from file: main, at main.cpp:42

[ SEVERE ]
[ 000m 00s 0302ms ] - I do not like them,
	: called from file: main, at main.cpp:49
[ 000m 00s 0302ms ] - Sam-I-am.
	: called from file: main, at main.cpp:50
[ 000m 00s 0302ms ] - I do not like
	: called from file: main, at main.cpp:51
[ 000m 00s 0302ms ] - Green eggs and ham.
	: called from file: main, at main.cpp:52
```
