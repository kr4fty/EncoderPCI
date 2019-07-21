# EncoderPCI
A quadrature encoder library that can use hardware or pin-change interrupts by using the [EnableInterrupt](https://github.com/NicoHood/PinChangeInterrupt) library.<br />
Based on the [Encoder](https://github.com/PaulStoffregen/Encoder) library by PaulStoffregen

## Usage:
Define Encoder objects using this :
```cpp
Encoder myEnc= Encoder(pinA, pinB);
```

Read encoder output
```cpp
int32_t encoderOutput = myEnc.read
```
Reset encoder count to 0 (in home position):
```cpp
myEnc.write(0)  
```
Reset encoder count to a value
```cpp
myEnc.write(value)
```


## PinchangeInterrupt Table

Pins with * are not broken out/deactivated by default.
You may activate them in the setting file (advanced).

Each row section represents a port(0-3).
Not all MCUs have all Ports/Pins physically available.

**ATTENTION!**<br />
If you use the EnableInterrup library in your program to enable one or more interrupts, you should define *LIBCALL_ENABLEINTERRUPT* before #includes. This is to avoid compilation problems<br />

For more information read this [issue](https://github.com/GreyGnome/EnableInterrupt/issues/13#issuecomment-123439620)

### Official Arduinos

| PCINT |  Uno/Nano/Mini  |   Mega/2560    | Leonardo/Micro | HL2 (8/16/32u2) |
| ----- | --------------- | -------------- | -------------- | --------------- |
|     0 |  8       (PB0)  | 53 SS   (PB0)  |    SS   (PB0)* |  0 SS   (PB0)*  |
|     1 |  9       (PB1)  | 52 SCK  (PB1)  |    SCK  (PB1)  |  1 SCK  (PB1)   |
|     2 | 10 SS    (PB2)  | 51 MOSI (PB2)  |    MOSI (PB2)  |  2 MOSI (PB2)   |
|     3 | 11 MISO  (PB3)  | 50 MISO (PB3)  |    MISO (PB3)  |  3 MISO (PB3)   |
|     4 | 12 MOSI  (PB4)  | 10      (PB4)  |  8/A8   (PB4)  |  4      (PB4)   |
|     5 | 13 SCK   (PB5)  | 11      (PB5)  |  9/A9   (PB5)  |  5      (PB5)   |
|     6 |    XTAL1 (PB6)* | 12      (PB6)  | 10/A10  (PB6)  |  6      (PB6)   |
|     7 |    XTAL2 (PB7)* | 13      (PB7)  | 11      (PB7)  |  7      (PB7)   |
| ----- | --------------- | -------------- | -------------- | --------------- |
|     8 | A0       (PC0)  |  0 RX   (PE0)* |                |         (PC6)*  |
|     9 | A1       (PC1)  | 15 RX3  (PJ0)* |                |         (PC5)*  |
|    10 | A2       (PC2)  | 14 TX3  (PJ1)* |                |         (PC4)*  |
|    11 | A3       (PC3)  |    NC   (PJ2)* |                |         (PC2)*  |
|    12 | A4 SDA   (PC4)  |    NC   (PJ3)* |                |         (PD5)*  |
|    13 | A5 SDC   (PC5)  |    NC   (PJ4)* |                |                 |
|    14 |    RST   (PC6)* |    NC   (PJ5)* |                |                 |
|    15 |                 |    NC   (PJ6)* |                |                 |
| ----- | --------------- | -------------- | -------------- | --------------- |
|    16 |  0 RX    (PD0)  | A8      (PK0)  |                |                 |
|    17 |  1 TX    (PD1)  | A9      (PK1)  |                |                 |
|    18 |  2 INT0  (PD2)  | A10     (PK2)  |                |                 |
|    19 |  3 INT1  (PD3)  | A11     (PK3)  |                |                 |
|    20 |  4       (PD4)  | A12     (PK4)  |                |                 |
|    21 |  5       (PD5)  | A13     (PK5)  |                |                 |
|    22 |  6       (PD6)  | A14     (PK6)  |                |                 |
|    23 |  7       (PD7)  | A15     (PK7)  |                |                 |
| ----- | --------------- | -------------- | -------------- | --------------- |


### Atmel Attinys

| PCINT |   Attiny13   |    Attiny x4    |   Attiny x5   |     Attiny x41      |
| ----- | ------------ | --------------- | ------------- | ------------------- |
|     0 | 0 MOSI (PB0) |  0       (PA0)  | 0 MOSI  (PB0) | A0/D0         (PA0) |
|     1 | 1 MISO (PB1) |  1       (PA1)  | 1 MISO  (PB1) | A1/D1         (PA1) |
|     2 | 2 SCK  (PB2) |  2       (PA2)  | 2 SCK   (PB2) | A2/D2         (PA2) |
|     3 | 3      (PB3) |  3       (PA3)  | 3 XTAL1 (PB3) | A3/D3         (PA3) |
|     4 | 4      (PB4) |  4 SCK   (PA4)  | 4 XTAL2 (PB4) | A4/D4         (PA4) |
|     5 | 5 RST  (PB5) |  5 MISO  (PA5)  | 5 RST   (PB5) | A5/D5   PWM   (PA5) |
|     6 |              |  6 MOSI  (PA6)  |               | A7/D7   PWM   (PA6) |
|     7 |              |  7       (PA7)  |               | A6/D6   PWM   (PA7) |
| ----- | ------------ | --------------- | ------------- | ------------------- |
|     8 |              | 10 XTAL1 (PB0)* |               | A10/D10 XTAL1 (PB0) |
|     9 |              |  9 XTAL2 (PB1)* |               | A9/D9   XTAL2 (PB1) |
|    10 |              |  8 INT0  (PB2)* |               | A8/D8   PWM   (PB2) |
|    11 |              |    RST   (PB3)* |               |         RST   (PB3) |
|    12 |              |                 |               |                     |
|    13 |              |                 |               |                     |
|    14 |              |                 |               |                     |
|    15 |              |                 |               |                     |
| ----- | ------------ | --------------- | ------------- | ------------------- |


### Other Atmel MCUs

| PCINT | ATmega644P/1284P  |
| ----- | ----------------- |
|     0 | A0/D24      (PA0) |
|     1 | A1/D25      (PA1) |
|     2 | A2/D26      (PA2) |
|     3 | A3/D27      (PA3) |
|     4 | A4/D28      (PA4) |
|     5 | A5/D29      (PA5) |
|     6 | A6/D30      (PA6) |
|     7 | A7/D31      (PA7) |
| ----- | ----------------- |
|     8 |  0          (PB0) |
|     9 |  1          (PB1) |
|    10 |  2 INT2     (PB2) |
|    11 |  3 PWM      (PB3) |
|    12 |  4 SS/PWM   (PB4) |
|    13 |  5 MOSI/PWM (PB5) |
|    14 |  6 MISO/PWM (PB6) |
|    15 |  7 SCK      (PB7) |
| ----- | ----------------- |
|    16 | 16 SCL      (PC0) |
|    17 | 17 SDA      (PC1) |
|    18 | 18 TCK      (PC2) |
|    19 | 19 TMS      (PC3) |
|    20 | 20 TDO      (PC4) |
|    21 | 21 TDI      (PC5) |
|    22 | 22          (PC6) |
|    23 | 23          (PC7) |
| ----- | ----------------- |
|    24 |  8 RX0      (PD0) |
|    25 |  9 TX0      (PD1) |
|    26 | 10 RX1/INT0 (PD2) |
|    27 | 11 TX1/INT1 (PD3) |
|    28 | 12 PWM      (PD4) |
|    29 | 13 PWM      (PD5) |
|    30 | 14 PWM      (PD6) |
|    31 | 15 PWM      (PD7) |
| ----- | ----------------- |
