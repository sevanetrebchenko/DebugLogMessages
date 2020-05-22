# DebugLogMessages
Logging messages that provide file, function, and line number of the callee as part of the message without requiring any additional information from the user. 

## Sample Output
With debug log messages turned off:

```
Single-line log messages: 
---------------------------------------------------------------------------------------
Severity: 21, Message: hello from test 1, here's a floating point number: 0.530000

Severity: 42, Message: hello from test 2, here's a sentence: "incredible!"


Multi-line log messages: 
---------------------------------------------------------------------------------------
Severity: 16, Message: from kickstart with number: 235
Severity: 16, Message: from testMultiple1 with floating point: 0.240000
Severity: 16, Message: from testMultiple2 with character: ?
Severity: 16, Message: from testMultiple3 with hex number: e
Severity: 16, Message: from testMultiple4 with exponent: 6.500000e+00
```

With debug log messages turned on:
```
Single-line log messages: 
---------------------------------------------------------------------------------------
Supply() called in function: void test1(), at main.cpp:7
	Severity: 21, Message: hello from test 1, here's a floating point number: 0.530000

Supply() called in function: void test2(), at main.cpp:14
	Severity: 42, Message: hello from test 2, here's a sentence: "incredible!"


Multi-line log messages: 
---------------------------------------------------------------------------------------
Supply() called in function: void kickstart(), at main.cpp:40
	Severity: 16, Message: from kickstart with number: 235
Supply() called in function: void testMultiple1(DBG_LOG_MESSAGE&), at main.cpp:34
	Severity: 16, Message: from testMultiple1 with floating point: 0.240000
Supply() called in function: void testMultiple2(DBG_LOG_MESSAGE&), at main.cpp:29
	Severity: 16, Message: from testMultiple2 with character: ?
Supply() called in function: void testMultiple3(DBG_LOG_MESSAGE&), at main.cpp:24
	Severity: 16, Message: from testMultiple3 with hex number: e
Supply() called in function: void testMultiple4(DBG_LOG_MESSAGE&), at main.cpp:20
	Severity: 16, Message: from testMultiple4 with exponent: 6.500000e+00
```
