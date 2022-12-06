TOF10120

UART 
Data Sending format
1 Read the deviation value, command r1#, return value D=xx means xx=00~99mm before calibration is 0
2 Read the serial port sending interval, command r2#, return value T=xxxx means xxxx=10~9999ms default 100ms
3 Read distance mode, command r3#, return value M=x means x=0 distance after filtering x=1 real-time distance default=0 distance after filtering
4 Read the maximum distance, command r4#, return value Max=x means x=100~2000mm, the default does not limit the maximum distance>2000mm
5 Reading distance sending mode command r5#, return value S=x means x=0 active sending (UART) x=1 passive reading (UART/I2C) default=0 active sending
6 Reading distance Command r6#, return value L=xxxx means xxxx=100~2000mm Only valid when the sending mode is passive reading
7 Read module I2C slave ID r7#, return value I=xxx means xxx=1~254(0x01~0xFE) default 164(0xA4)

Write command
1 Set the positive and negative deviation of the deviation value, command s1+xx#, return information > set successfully: ok set failed: fail
Command s1-xx#, s1+xx# (positive deviation) or s1-xx# (negative deviation)
    Note, xx=00~99mm s1+0# or s1-0# deviation is cleared to 0
2 Set the serial port sending interval, command s2-xxxx#, return information>setting success: ok setting failure: fail
    Note, xxxx=10~9999ms default 100ms
3 Set the distance mode, command s3-x#, return information > set successfully: ok set failed: fail
    Note, x=0 distance after filtering x=1 real-time distance default=0 distance after filtering
4 Set the maximum distance, command s4-xxxx#, return information>set successfully: ok set failed: fail
    Note, xxxx=100~2000mm xxxx=0 means unlimited maximum distance
5 Set the distance sending method, command s5-x#, return information>setting success: ok setting failure: fail
    Note, x=0 active transmission (UART only) x=1 passive reading (UART, I2C)
6 Set the I2C slave ID, command s7-xxx#, return information>set successfully: ok set failed: fail
    Note, xxx=1~254(0x01~0xFE) default 164(0xA4)

ROUTINE
command: string input box
send: s4-1000#
explanation: ok
Return information: the setting is successful: ok, indicating that the maximum distance setting is 1000mm


I2C Data Register addresses
0x00-0x01 real-time distance
0x04-0x05 filter distance
0x06-0x07 distance deviation
0x08 distance data mode 0-filter 1-real time
0x09 Distance sending method 0-module sending (serial port) 1-host reading (serial port, i2c)
0x0c-0x0d Maximum measuring distance 2 Read only mm Hex code 100mm-1800mm
0x0f I2C slave address read and write 0x02~0xfe bit7~bit1 valid bit0=0

Note: The host should delay at least 30uS to prepare data for the module after sending the register address, otherwise I2C will be abnormal.

(translated from the chinese manual)
