# Benchmark for ver.0.1.0

Commit ID: c8bddf6185b2558335f6f16c3483a3591ce109dd

## Environment

USB Hub Usage: No

```powershell
PS C:\Users\kiyomaro> function prompt { "> " }
> (Get-CimInstance Win32_Processor).Name         
13th Gen Intel(R) Core(TM) i7-13620H
> (Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB
15.6787643432617
> (Get-CimInstance Win32_OperatingSystem).Caption                 
Microsoft Windows 11 Home
> (Get-CimInstance Win32_OperatingSystem).Version
10.0.26200
> $PSVersionTable.PSVersion.ToString()
7.6.6
> python --version
Python 3.13.14
> pip freeze
pyserial==3.5
> 
```

## CDC Speed Test

```powershell
> python ./test/cdc_speed_test.py COM8 --rx --chunk-size 16 --iteration 2 --duration 10
usb port name: COM8

serial number: NEC01
slcan version: VL2K0
detail:
    v: hardware="CANable2.0", software="v0.1.0", url="github.com/Nakakiyo092/canable2kai"

can port status: closed

ping: [303, 187, 163, 175, 161] us

tx speed:    207.76 kB/s          1662.05 kbits/s
rx speed:    623.27 kB/s          4986.16 kbits/s
message loss:  0  /  1038784

device status: 
detail:
    z: time_ms=0x5404, time_us=0x16BD5B60, cycle_time_us_ave_max=[0x00A, 0x058]

tx speed:    212.00 kB/s          1696.03 kbits/s
rx speed:    636.01 kB/s          5088.08 kbits/s
message loss:  0  /  1060016

device status: 
detail:
    z: time_ms=0x7CC2, time_us=0x175C80A0, cycle_time_us_ave_max=[0x00A, 0x058]

> python ./test/cdc_speed_test.py COM8 --tx --chunk-size 16 --iteration 2 --duration 10
usb port name: COM8

serial number: NEC01
slcan version: VL2K0
detail:
    v: hardware="CANable2.0", software="v0.1.0", url="github.com/Nakakiyo092/canable2kai"

can port status: closed

ping: [249, 175, 200, 164, 208] us

tx speed:    427.45 kB/s          3419.62 kbits/s
rx speed:      3.08 kB/s            24.60 kbits/s
message loss:  0  /  30752

device status: 
detail:
    z: time_ms=0x0B9E, time_us=0x19361600, cycle_time_us_ave_max=[0x00A, 0x05C]

tx speed:    427.68 kB/s          3421.40 kbits/s
rx speed:      3.08 kB/s            24.61 kbits/s
message loss:  0  /  30768

device status: 
detail:
    z: time_ms=0x345D, time_us=0x19D53CAE, cycle_time_us_ave_max=[0x00A, 0x05C]

> 
```

## CAN Communication Test

```powershell
> python ./test/communication_test.py                                                  
.
================================================================
test_full_grid_report  (S = nominal index, Y = data index)
Legend: .=pass  E=bus_error  P=passive  O=bus-off  -=skip  ?=other

      Y0  Y1  Y2  Y3  Y4  Y5  Y6  Y7  Y8  Y9 
 S0   E   O   O   -   P   O   -   -   -   - 
 S1   .   P   O   -   O   O   -   -   -   - 
 S2   .   .   E   -   P   P   -   -   -   - 
 S3   .   .   .   -   E   E   -   -   -   - 
 S4   .   .   .   -   .   E   -   -   -   - 
 S5   .   .   .   -   .   .   -   -   -   - 
 S6   .   .   .   -   .   .   -   -   -   - 
 S7   .   .   .   -   .   .   -   -   -   - 
 S8   .   .   .   -   .   .   -   -   -   - 
 S9   .   .   .   -   E   P   -   -   -   - 

summary:  pass=33  busErr=6  passive=5  busOff=6  skip=50  other=0
================================================================
.
================================================================
test_sp_grid_report  (nominal S8, rows = data SP, columns = data bit rate)
CAN clock: DUT 80 MHz, AUX 80 MHz
Legend: .=pass  E=bus_error  P=passive  O=bus-off  -=not representable  ?=other

         1M   2M   4M   5M   8M  10M  16M  20M
  20%    .    .    .    -    O    -    -    - 
  25%    .    .    .    .    -    O    -    - 
  30%    .    .    .    -    O    -    -    - 
  35%    .    .    .    -    -    -    -    - 
  40%    .    .    .    -    .    -    O    - 
  45%    .    .    .    -    -    -    -    - 
  50%    .    .    .    .    .    .    -    O 
  55%    .    .    .    -    -    -    -    - 
  60%    .    .    .    -    .    -    O    - 
  65%    .    .    .    -    -    -    -    - 
  70%    .    .    .    -    .    -    -    - 
  75%    .    .    .    .    -    .    -    O 
  80%    .    .    .    -    .    -    .    - 
  85%    .    .    .    -    -    -    -    - 
  90%    .    .    .    -    .    -    -    - 
  95%    .    .    .    -    -    -    -    - 

summary:  pass=60  busErr=0  passive=0  busOff=7  skip=61  other=0
================================================================
.
----------------------------------------------------------------------
Ran 3 tests in 374.618s

OK
> 
```

## CAN Stress Test

```powershell
> python ./test/can_stress_test.py --rate 2000

=========================================================
 stress_test target devices
=========================================================
 DUT (COM9):
   slcan version: VL2K0-DEBUG
   serial number: NEC01
 AUX (COM8):
   slcan version: VL2K0
   serial number: NEC01
=========================================================
Starting: frame_type=b, S8/Y5, payload=64 bytes, rate=2000.0 fps, duration=60 s, ping_id=0x100, echo_id=0x101
Press Ctrl-C to stop early.

  t+    10s  sent=   20057  recv=   20046  loss=   11  corrupt=  0  ~ 2000.1 fps
  t+    20s  sent=   40011  recv=   40006  loss=    5  corrupt=  0  ~ 2000.1 fps
  t+    30s  sent=   60065  recv=   60060  loss=    5  corrupt=  0  ~ 2000.1 fps
  t+    40s  sent=   80037  recv=   80031  loss=    6  corrupt=  0  ~ 2000.0 fps
  t+    50s  sent=  100006  recv=  100001  loss=    5  corrupt=  0  ~ 2000.0 fps

======================================================================
 stress_test summary  (elapsed 60.0 s, target 2000.0 fps)
======================================================================
  Pings sent (DUT->AUX):           120061
  Pings observed at AUX:           120061
  Echos sent (AUX->DUT):           120061
  Echos observed at DUT:           120061
  Echos with corrupted payload:    0
  Unexpected frames at DUT:        0
  Unexpected frames at AUX:        0
  Rejected commands ([BELL]):      DUT=0  AUX=0
  End-to-end loss:                 0 (0.00 %)
  Actual achieved rate:            2000.0 fps

  DUT final F: F00
  AUX final F: F00
======================================================================
> python ./test/can_stress_test.py --rate 4000

=========================================================
 stress_test target devices
=========================================================
 DUT (COM9):
   slcan version: VL2K0-DEBUG
   serial number: NEC01
 AUX (COM8):
   slcan version: VL2K0
   serial number: NEC01
=========================================================
Starting: frame_type=b, S8/Y5, payload=64 bytes, rate=4000.0 fps, duration=60 s, ping_id=0x100, echo_id=0x101
Press Ctrl-C to stop early.

  t+    10s  sent=   29067  recv=   29002  loss=   65  corrupt=  0  ~ 2901.4 fps
  t+    20s  sent=   58219  recv=   58194  loss=   25  corrupt=  0  ~ 2905.2 fps
  t+    30s  sent=   87115  recv=   87063  loss=   52  corrupt=  0  ~ 2903.4 fps
  t+    40s  sent=  116323  recv=  116271  loss=   52  corrupt=  0  ~ 2906.3 fps
  t+    50s  sent=  145643  recv=  145571  loss=   72  corrupt=  0  ~ 2910.2 fps

======================================================================
 stress_test summary  (elapsed 60.0 s, target 4000.0 fps)
======================================================================
  Pings sent (DUT->AUX):           174779
  Pings observed at AUX:           174779
  Echos sent (AUX->DUT):           174779
  Echos observed at DUT:           174779
  Echos with corrupted payload:    0
  Unexpected frames at DUT:        0
  Unexpected frames at AUX:        0
  Rejected commands ([BELL]):      DUT=0  AUX=0
  End-to-end loss:                 0 (0.00 %)
  Actual achieved rate:            2911.5 fps

  DUT final F: F00
  AUX final F: F00
======================================================================
> 
```

## Long Time Test

```powershell
> python ./test/long_time_test.py COM8 --with-receiver
usb port name: COM8

serial number: NEC01
slcan version: VL2K0
detail:
    v: hardware="CANable2.0", software="v0.1.0", url="github.com/Nakakiyo092/canable2kai"

can port status: open/normal (1M/5Mbps)

ping: [226, 314, 303, 303, 295, 290, 365, 319, 308, 348] us


--- Stats at 0.017 hours ---

sent frames: 1657 / 1657 (-0)
  resync-detected drops: 0

status check: 1657 samples
  no error: 1657
  buffer error: 0
  can bus error: 0

timestamp comparison (host - device): 1656 samples
  ave abs error: 104.5 us
  max abs error: 2838 us
  failures: 0
    of which >32767 us: 0
    of which sentinel: 0

clock accuracy: 59 sec
  clock offset: 141.7 ms
  drift upper bound: 2426.5 ppm
  drift lower bound: 2303.6 ppm
  (reference, time.time() based):
    host perf_counter vs wall clock: -0.1 ppm
    device drift vs wall clock:      +2362.2 ppm


... snip ...


--- Stats at 1.033 hours ---

sent frames: 91834 / 91834 (-0)
  resync-detected drops: 0

status check: 91834 samples
  no error: 91834
  buffer error: 0
  can bus error: 0

timestamp comparison (host - device): 91833 samples
  ave abs error: 123.4 us
  max abs error: 17231 us
  failures: 0
    of which >32767 us: 0
    of which sentinel: 0

clock accuracy: 3719 sec
  clock offset: 8970.4 ms
  drift upper bound: 2412.5 ppm
  drift lower bound: 2410.5 ppm
  (reference, time.time() based):
    host perf_counter vs wall clock: -0.0 ppm
    device drift vs wall clock:      +2411.4 ppm

> 
```
