EESchema Schematic File Version 2  date Пн 02 мар 2015 16:29:57
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:my_elements
LIBS:LEDs_in_box-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "2 mar 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED D1
U 1 1 54F40B18
P 5850 2400
F 0 "D1" H 5850 2500 50  0000 C CNN
F 1 "LED" H 5850 2300 50  0000 C CNN
F 2 "~" H 5850 2400 60  0000 C CNN
F 3 "~" H 5850 2400 60  0000 C CNN
	1    5850 2400
	1    0    0    -1  
$EndComp
$Comp
L LED D2
U 1 1 54F40B25
P 5850 2700
F 0 "D2" H 5850 2800 50  0000 C CNN
F 1 "LED" H 5850 2600 50  0000 C CNN
F 2 "~" H 5850 2700 60  0000 C CNN
F 3 "~" H 5850 2700 60  0000 C CNN
	1    5850 2700
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 54F40B2D
P 6700 2700
F 0 "K1" V 6650 2700 50  0000 C CNN
F 1 "CONN_3" V 6750 2700 40  0000 C CNN
F 2 "" H 6700 2700 60  0000 C CNN
F 3 "" H 6700 2700 60  0000 C CNN
	1    6700 2700
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 54F40B3C
P 5300 2700
F 0 "R2" V 5380 2700 40  0000 C CNN
F 1 "330" V 5307 2701 40  0000 C CNN
F 2 "SM0603" V 5230 2700 30  0001 C CNN
F 3 "~" H 5300 2700 30  0000 C CNN
	1    5300 2700
	0    -1   -1   0   
$EndComp
$Comp
L R R1
U 1 1 54F40B6D
P 5300 2400
F 0 "R1" V 5380 2400 40  0000 C CNN
F 1 "330" V 5307 2401 40  0000 C CNN
F 2 "SM0603" V 5230 2400 30  0001 C CNN
F 3 "~" H 5300 2400 30  0000 C CNN
	1    5300 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 2400 5050 2950
Wire Wire Line
	5550 2700 5650 2700
Wire Wire Line
	5550 2400 5650 2400
Wire Wire Line
	6050 2400 6350 2400
Wire Wire Line
	6350 2400 6350 2600
Wire Wire Line
	6350 2700 6050 2700
Wire Wire Line
	5050 2950 6350 2950
Wire Wire Line
	6350 2950 6350 2800
Connection ~ 5050 2700
$Comp
L LED D4
U 1 1 54F40BD8
P 5950 4000
F 0 "D4" H 5950 4100 50  0000 C CNN
F 1 "LED" H 5950 3900 50  0000 C CNN
F 2 "~" H 5950 4000 60  0000 C CNN
F 3 "~" H 5950 4000 60  0000 C CNN
	1    5950 4000
	-1   0    0    1   
$EndComp
$Comp
L LED D5
U 1 1 54F40BDE
P 5950 4300
F 0 "D5" H 5950 4400 50  0000 C CNN
F 1 "LED" H 5950 4200 50  0000 C CNN
F 2 "~" H 5950 4300 60  0000 C CNN
F 3 "~" H 5950 4300 60  0000 C CNN
	1    5950 4300
	-1   0    0    1   
$EndComp
$Comp
L CONN_4 K2
U 1 1 54F40BE4
P 6800 4250
F 0 "K2" V 6750 4250 50  0000 C CNN
F 1 "CONN_4" V 6850 4250 40  0000 C CNN
F 2 "" H 6800 4250 60  0000 C CNN
F 3 "" H 6800 4250 60  0000 C CNN
	1    6800 4250
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 54F40BEA
P 5400 4300
F 0 "R5" V 5480 4300 40  0000 C CNN
F 1 "6.8k" V 5407 4301 40  0000 C CNN
F 2 "SM1206" V 5330 4300 30  0001 C CNN
F 3 "~" H 5400 4300 30  0000 C CNN
	1    5400 4300
	0    -1   -1   0   
$EndComp
$Comp
L R R4
U 1 1 54F40BF0
P 5400 4000
F 0 "R4" V 5480 4000 40  0000 C CNN
F 1 "2.2k" V 5407 4001 40  0000 C CNN
F 2 "SM0603" V 5330 4000 30  0001 C CNN
F 3 "~" H 5400 4000 30  0000 C CNN
	1    5400 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 3650 5150 4550
Wire Wire Line
	5650 4300 5750 4300
Wire Wire Line
	5650 4000 5750 4000
Wire Wire Line
	5150 4550 6450 4550
Wire Wire Line
	6450 4550 6450 4400
Connection ~ 5150 4300
$Comp
L LED D3
U 1 1 54F40BFF
P 5950 3650
F 0 "D3" H 5950 3750 50  0000 C CNN
F 1 "LED" H 5950 3550 50  0000 C CNN
F 2 "~" H 5950 3650 60  0000 C CNN
F 3 "~" H 5950 3650 60  0000 C CNN
	1    5950 3650
	-1   0    0    1   
$EndComp
$Comp
L R R3
U 1 1 54F40C05
P 5400 3650
F 0 "R3" V 5480 3650 40  0000 C CNN
F 1 "2.2k" V 5407 3651 40  0000 C CNN
F 2 "SM0603" V 5330 3650 30  0001 C CNN
F 3 "~" H 5400 3650 30  0000 C CNN
	1    5400 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 3650 5750 3650
Wire Wire Line
	6150 3650 6450 3650
Wire Wire Line
	6450 3650 6450 4100
Connection ~ 5150 4000
Wire Wire Line
	6150 4000 6300 4000
$Comp
L HOLE HOLE1
U 1 1 54F40D0F
P 750 650
F 0 "HOLE1" H 750 650 60  0000 C CNN
F 1 "HOLE" H 750 550 60  0000 C CNN
F 2 "~" H 750 650 60  0000 C CNN
F 3 "~" H 750 650 60  0000 C CNN
	1    750  650 
	1    0    0    -1  
$EndComp
$Comp
L HOLE HOLE2
U 1 1 54F40D1C
P 1050 650
F 0 "HOLE2" H 1050 650 60  0000 C CNN
F 1 "HOLE" H 1050 550 60  0000 C CNN
F 2 "~" H 1050 650 60  0000 C CNN
F 3 "~" H 1050 650 60  0000 C CNN
	1    1050 650 
	1    0    0    -1  
$EndComp
$Comp
L HOLE HOLE3
U 1 1 54F40D22
P 1400 650
F 0 "HOLE3" H 1400 650 60  0000 C CNN
F 1 "HOLE" H 1400 550 60  0000 C CNN
F 2 "~" H 1400 650 60  0000 C CNN
F 3 "~" H 1400 650 60  0000 C CNN
	1    1400 650 
	1    0    0    -1  
$EndComp
$Comp
L HOLE HOLE4
U 1 1 54F40D28
P 1700 650
F 0 "HOLE4" H 1700 650 60  0000 C CNN
F 1 "HOLE" H 1700 550 60  0000 C CNN
F 2 "~" H 1700 650 60  0000 C CNN
F 3 "~" H 1700 650 60  0000 C CNN
	1    1700 650 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4300 6150 4200
Wire Wire Line
	6150 4200 6450 4200
Wire Wire Line
	6450 4300 6300 4300
Wire Wire Line
	6300 4300 6300 4000
$EndSCHEMATC