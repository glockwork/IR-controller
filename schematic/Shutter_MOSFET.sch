EESchema Schematic File Version 2  date Чт 02 апр 2015 10:40:58
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
LIBS:ft2232
LIBS:my_elements
LIBS:STM32f103
LIBS:vreg
LIBS:open-project
LIBS:ALL-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 12 12
Title "Power load module"
Date "2 apr 2015"
Rev ""
Comp "SAO RAS"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2350 3550 0    61   Output ~ 0
OUT1
Text HLabel 2350 2000 0    61   Input ~ 0
GND
$Comp
L GND #PWRp0137
U 1 1 53BC59AD
P 2450 2100
AR Path="/53BBC16A/53BC59AD" Ref="#PWRp0137"  Part="1" 
AR Path="/53C73959/53BC59AD" Ref="#PWRp0134"  Part="1" 
AR Path="/53C7395A/53BC59AD" Ref="#PWRp0140"  Part="1" 
AR Path="/53C73958/53BC59AD" Ref="#PWRp086"  Part="1" 
AR Path="/53A8FBFD/53BC59AD" Ref="#PWRp0129"  Part="1" 
AR Path="/53AA0E2D/53BC59AD" Ref="#PWRp0132"  Part="1" 
AR Path="/53AA0E2C/53BC59AD" Ref="#PWRp0135"  Part="1" 
AR Path="/53AE6F08/53BC59AD" Ref="#PWRp0133"  Part="1" 
F 0 "#PWRp0133" H 2450 2100 30  0001 C CNN
F 1 "GND" H 2450 2030 30  0001 C CNN
F 2 "" H 2450 2100 60  0000 C CNN
F 3 "" H 2450 2100 60  0000 C CNN
	1    2450 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2000 2450 2000
Wire Wire Line
	2450 1950 2450 2100
$Comp
L TLE5205 DA2
U 1 1 53C09F3E
P 3500 3650
F 0 "DA2" H 3650 4050 60  0000 C CNN
F 1 "TLE5205" H 3500 3650 60  0000 C CNN
F 2 "TO220-7-12" H 3500 3650 60  0001 C CNN
F 3 "" H 3500 3650 60  0000 C CNN
	1    3500 3650
	-1   0    0    -1  
$EndComp
Text HLabel 2350 5050 0    60   Input ~ 0
IN1
Text HLabel 2350 5200 0    60   Input ~ 0
IN2
Text HLabel 2350 3750 0    61   Output ~ 0
OUT2
Wire Wire Line
	4200 3650 4400 3650
Wire Wire Line
	4600 3800 4200 3800
Wire Wire Line
	2350 3550 2800 3550
Wire Wire Line
	2350 3750 2800 3750
Text HLabel 2350 4850 0    60   Output ~ 0
EF
Wire Wire Line
	2350 4850 4300 4850
Wire Wire Line
	4300 4850 4300 3500
Wire Wire Line
	4300 3500 4200 3500
Wire Wire Line
	4400 5050 2350 5050
Wire Wire Line
	4600 5200 2350 5200
$Comp
L GND #PWRp0134
U 1 1 53C0B3EC
P 3500 4350
F 0 "#PWRp0134" H 3500 4350 30  0001 C CNN
F 1 "GND" H 3500 4280 30  0001 C CNN
F 2 "" H 3500 4350 60  0000 C CNN
F 3 "" H 3500 4350 60  0000 C CNN
	1    3500 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4250 3500 4350
Text HLabel 2350 2400 0    60   Input ~ 0
+36V
$Comp
L GND #PWRp0135
U 1 1 53C0BE69
P 3900 2500
F 0 "#PWRp0135" H 3900 2500 30  0001 C CNN
F 1 "GND" H 3900 2430 30  0001 C CNN
F 2 "" H 3900 2500 60  0000 C CNN
F 3 "" H 3900 2500 60  0000 C CNN
	1    3900 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2400 3900 2500
$Comp
L R R25
U 1 1 53C10962
P 3000 2400
F 0 "R25" V 3080 2400 40  0000 C CNN
F 1 "300 (II)" V 3007 2401 40  0000 C CNN
F 2 "R7" V 2930 2400 30  0001 C CNN
F 3 "~" H 3000 2400 30  0000 C CNN
	1    3000 2400
	0    -1   -1   0   
$EndComp
Text Notes 2900 2550 0    60   ~ 0
2W!
Wire Wire Line
	2350 2400 2750 2400
Wire Wire Line
	3250 2400 3500 2400
Wire Wire Line
	3500 850  3500 3050
Connection ~ 3500 2400
$Comp
L CP1 C4
U 1 1 53C10BBB
P 3700 2400
F 0 "C4" H 3750 2500 50  0000 L CNN
F 1 "2200u, 40V" H 3750 2300 50  0000 L CNN
F 2 "CP36V" H 3700 2400 60  0001 C CNN
F 3 "~" H 3700 2400 60  0000 C CNN
	1    3700 2400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 3650 4400 5050
Wire Wire Line
	4600 3800 4600 5200
$Comp
L PWR_FLAG #FLG0136
U 1 1 53CB51C4
P 3350 2400
F 0 "#FLG0136" H 3350 2495 30  0001 C CNN
F 1 "PWR_FLAG" H 3350 2580 30  0000 C CNN
F 2 "" H 3350 2400 60  0000 C CNN
F 3 "" H 3350 2400 60  0000 C CNN
	1    3350 2400
	1    0    0    -1  
$EndComp
Connection ~ 3350 2400
$Comp
L R0603 R42
U 1 1 5465870A
P 2450 1700
F 0 "R42" V 2530 1700 40  0000 C CNN
F 1 "4.7k" V 2457 1701 40  0000 C CNN
F 2 "SM0603" V 2380 1700 30  0001 C CNN
F 3 "~" H 2450 1700 30  0000 C CNN
	1    2450 1700
	1    0    0    -1  
$EndComp
$Comp
L R0603 R41
U 1 1 54658717
P 2450 1100
F 0 "R41" V 2530 1100 40  0000 C CNN
F 1 "56k" V 2457 1101 40  0000 C CNN
F 2 "SM0603" V 2380 1100 30  0001 C CNN
F 3 "~" H 2450 1100 30  0000 C CNN
	1    2450 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 850  3500 850 
Wire Wire Line
	2450 1350 2450 1450
Wire Wire Line
	2350 1400 2450 1400
Connection ~ 2450 1400
Text HLabel 2350 1400 0    60   Output ~ 0
Sense
Connection ~ 2450 2000
$EndSCHEMATC
