/*
 * hardware_ini.c - functions for HW initialisation
 *
 * Copyright 2014 Edward V. Emelianov <eddy@sao.ru, edward.emelianoff@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/*
 * All hardware-dependent initialisation & definition should be placed here
 * and in hardware_ini.h
 *
 */

#include "main.h"
#include "hardware_ini.h"
#include "onewire.h"
#include "flash.h"

/*
 * Due to inconvenient pins position on STM32F103VxT6 I had to make this strange location:
 * my channel #   ->   ADC1/2 channel #
 * 0 -> 9    PB1
 * 1 -> 8    PB0
 * 2 -> 15   PC5
 * 3 -> 14   PC4
 * 4 -> 7    PA7
 * 5 -> 6    PA6
 * 6 -> 5    PA5
 * 7 -> 4    PA4
 * U36 -> 1  PA1
 * U10 -> 0  PA0
 */
uint8_t adc_channel_array[16] = {9,8,15,14,7,6,5,4,1,0};
// ADC_value array have 9 records for each value for ability of median filtering
// values for channel num are ADC_value[num + ADC_CHANNELS_NUMBER*i]
volatile uint16_t ADC_value[ADC_CHANNELS_NUMBER*9]; // ADC DMA value

/*
 * Configure SPI ports
 */
/*
 *      SPI1 remapped:
 * SCK  - PB3
 * MISO - PB4
 * MOSI - PB5
 */
void SPI1_init(){
	// enable AFIO & other clocking
	rcc_peripheral_enable_clock(&RCC_APB2ENR,
			RCC_APB2ENR_SPI1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN);
	// remap SPI1 (change pins from PA5..7 to PB3..5); also turn off JTAG
	gpio_primary_remap(AFIO_MAPR_SWJ_CFG_JTAG_OFF_SW_OFF, AFIO_MAPR_SPI1_REMAP);
	// SCK, MOSI - push-pull output
	gpio_set_mode(GPIO_BANK_SPI1_RE_SCK, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_SPI1_RE_SCK);
	gpio_set_mode(GPIO_BANK_SPI1_RE_MOSI, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_SPI1_RE_MOSI);
	// MISO - opendrain in
	gpio_set_mode(GPIO_BANK_SPI1_RE_MISO, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_SPI1_RE_MISO);
	spi_reset(SPI1);
	/* Set up SPI in Master mode with:
	 * Clock baud rate: 1/128 of peripheral clock frequency (APB2, 72MHz)
	 * Clock polarity: Idle High
	 * Clock phase: Data valid on 2nd clock pulse
	 * Data frame format: 8-bit
	 * Frame format: MSB First
	 */
	spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_128, SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE,
		SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
	nvic_enable_irq(NVIC_SPI1_IRQ); // enable SPI interrupt
}

/*
 *     SPI2:
 * SCK  - PB13
 * MISO - PB14
 * MOSI - PB15
 */
void SPI2_init(){
	// turn on clocking
	//rcc_periph_clock_enable(RCC_SPI2 | RCC_GPIOB);
	rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_APB1ENR_SPI2EN);
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPBEN);
	// SCK, MOSI - push-pull output
	gpio_set_mode(GPIO_BANK_SPI2_SCK, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_SPI2_SCK);
	gpio_set_mode(GPIO_BANK_SPI2_MOSI, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_SPI2_MOSI);
	// MISO - opendrain in
	gpio_set_mode(GPIO_BANK_SPI2_MISO, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_SPI2_MISO);
	spi_reset(SPI2);
	/* Set up SPI in Master mode with:
	 * Clock baud rate: 1/64 of peripheral clock frequency (APB1, 36MHz)
	 * Clock polarity: Idle High
	 * Clock phase: Data valid on 2nd clock pulse
	 * Data frame format: 8-bit
	 * Frame format: MSB First
	 */
	spi_init_master(SPI2, SPI_CR1_BAUDRATE_FPCLK_DIV_64, SPI_CR1_CPOL_CLK_TO_1_WHEN_IDLE,
		SPI_CR1_CPHA_CLK_TRANSITION_2, SPI_CR1_DFF_8BIT, SPI_CR1_MSBFIRST);
	nvic_enable_irq(NVIC_SPI2_IRQ); // enable SPI interrupt
}

/**
 * GPIO initialisaion: clocking + pins setup
 */
void GPIO_init(){
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPAEN |
			RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_IOPDEN |
			RCC_APB2ENR_IOPEEN);
	// USB_DISC: push-pull
	gpio_set_mode(USB_DISC_PORT, GPIO_MODE_OUTPUT_2_MHZ,
				GPIO_CNF_OUTPUT_PUSHPULL, USB_DISC_PIN);
	// USB_POWER: open drain, externall pull down with R7 (22k)
	gpio_set_mode(USB_POWER_PORT, GPIO_MODE_INPUT,
				GPIO_CNF_INPUT_FLOAT, USB_POWER_PIN);
	// AD7794 addr + en
	gpio_set_mode(ADC_ADDR_PORT, GPIO_MODE_OUTPUT_2_MHZ,
				GPIO_CNF_OUTPUT_PUSHPULL, ADC_ADDR_MASK | ADC_EN_PIN); // ADDRESS: PD10..12; EN: PD13
	gpio_clear(ADC_ADDR_PORT, ADC_ADDR_MASK | ADC_EN_PIN); // clear address & turn switch off
	// LED status: opendrain
	gpio_set_mode(LED_STATUS_PORT, GPIO_MODE_OUTPUT_2_MHZ,
				GPIO_CNF_OUTPUT_OPENDRAIN, LED_STATUS_PIN);
	LED_STATUS_BAD(); // turn LED off
	// Shutter control: input pull up
	gpio_set(SHUTTER_CAM_PORT, SHUTTER_CAM_PIN);
	gpio_set(SHUTTER_MAN_PORT, SHUTTER_MAN_PIN);
	gpio_set(SHUTTER_FBSW_PORT, SHUTTER_FBSW_PIN);
	gpio_set_mode(SHUTTER_CAM_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, SHUTTER_CAM_PIN);
	gpio_set_mode(SHUTTER_MAN_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, SHUTTER_MAN_PIN);
	gpio_set_mode(SHUTTER_FBSW_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, SHUTTER_FBSW_PIN);
	// shutter status LED: opendrain
	gpio_set_mode(LED_SHUTTER_PORT, GPIO_MODE_OUTPUT_2_MHZ,
				GPIO_CNF_OUTPUT_OPENDRAIN, LED_SHUTTER_PIN);
	LED_SHUTTER_CLOSE(); // turn it off
}

/*
 * SysTick used for system timer with period of 1ms
 */
void SysTick_init(){
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8); // Systyck: 72/8=9MHz
	systick_set_reload(8999); // 9000 pulses: 1kHz
	systick_interrupt_enable();
	systick_counter_enable();
}

/**
 * Turn on ADC DMA for filling temperatures buffer
 */
void adc_dma_on(){
	// first configure DMA1 Channel1 (ADC1)
	nvic_disable_irq(NVIC_DMA1_CHANNEL1_IRQ);
	dma_channel_reset(DMA1, DMA_CHANNEL1);
	DMA1_CPAR1 = (uint32_t) &(ADC_DR(ADC1));
	DMA1_CMAR1 = (uint32_t) ADC_value;
	DMA1_CNDTR1 = ADC_CHANNELS_NUMBER * 9; // *9 for median filtering
	DMA1_CCR1 = DMA_CCR_MINC | DMA_CCR_PSIZE_16BIT | DMA_CCR_MSIZE_16BIT
			| DMA_CCR_CIRC | DMA_CCR_PL_HIGH | DMA_CCR_EN;
	adc_enable_dma(ADC1);
	adc_power_on(ADC1);
	/*
	dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t) &(ADC_DR(ADC1)));
	dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t) ADC_value);
	dma_set_number_of_data(DMA1, DMA_CHANNEL1, ADC_CHANNELS_NUMBER);
	dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
	dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
	dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL1);
	dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
	dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
	dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
	dma_set_priority(DMA1, DMA_CHANNEL1, DMA_CCR_PL_HIGH);
	dma_disable_transfer_error_interrupt(DMA1, DMA_CHANNEL1);
	dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
	dma_enable_channel(DMA1, DMA_CHANNEL1);
	*/
}

void ADC_init(){
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_ADC1EN); // enable clocking
//	rcc_periph_clock_enable(RCC_ADC1);
	rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV4);
	//rcc_periph_clock_enable(RCC_GPIOA | RCC_GPIOB | RCC_GPIOC); // clocking for ADC ports
	// channels 4-7: PA7-PA4 (ADC IN 4..7); U10 (PA0); U36 (PA1)
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO4|GPIO5|GPIO6|GPIO7|GPIO1|GPIO0);
	// channels 0,1: PB1, PB0 (ADC IN 8, 9)
	gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO0|GPIO1);
	// channels 2,3: PC5, PC4 (ADC IN14, 15)
	gpio_set_mode(GPIOC, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO4|GPIO5);

	// Make sure the ADC doesn't run during config
	adc_off(ADC1);
	rcc_periph_clock_enable(RCC_DMA1);

	// Configure ADC as continuous scan mode with DMA
	adc_set_dual_mode(ADC_CR1_DUALMOD_IND); // ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	adc_enable_scan_mode(ADC1); // ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	adc_set_continuous_conversion_mode(ADC1); // ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	adc_disable_external_trigger_regular(ADC1); // ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	adc_set_right_aligned(ADC1); // ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_239DOT5CYC); // ADC_SampleTime_239Cycles5
	//adc_set_sample_time(ADC1, ADC_CHANNEL8, ADC_SMPR_SMP_239DOT5CYC); // ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_239Cycles5);

	adc_dma_on();
}

/**
 * Starts ADC calibration & after it runs ADC in continuous conversion mode
 * First call ADC_init(), than wait a little and call this function
 */
void ADC_calibrate_and_start(){
	adc_set_regular_sequence(ADC1, ADC_CHANNELS_NUMBER, adc_channel_array);
	adc_reset_calibration(ADC1);
	adc_calibration(ADC1);
	adc_start_conversion_regular(ADC1); // ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	adc_start_conversion_direct(ADC1);
}

/**
 * get shutter voltage in value of U*100
 * 3.3V == 4096 ADU, 36V comes to ADC in through resistor divider 4.7k:56k, so
 * U36(V/100) = Uadc(ADU) * 607/47 * 33/40960 * 100 = Uadc(ADU) * 20031 / 19251
 * ==> approximately this is equal to val*26/25 or val + val/25
 */
int shutter_voltage(){
	uint32_t val = ADC_value[SHUTTER_SENSE_NUMBER]; // 8
	val *= ADC_multipliers[SHUTTER_SENSE_NUMBER];
	val /= ADC_divisors[SHUTTER_SENSE_NUMBER];
	return (int)val;
}

/**
 * get power voltage in value of U*100
 * 3.3V == 4096 ADU, 10..12V comes to ADC in through resistor divider 4.7k:12k, so
 * U10(V/100) = Uadc(ADU) * 167/47 * 33/40960 * 100 = Uadc(ADU) * 5511 / 19251
 * ==> approximately this is equal to val*2/7
 * (real: approx 17/58)
 */
int power_voltage(){
	uint32_t val = ADC_value[POWER_SENSE_NUMBER]; // 9
	val *= ADC_multipliers[POWER_SENSE_NUMBER];
	val /= ADC_divisors[POWER_SENSE_NUMBER];
	return (int)val;
}

// This is some data for optimal median filtering of array[9]
uint16_t temp;
#define PIX_SORT(a,b) { if ((a)>(b)) PIX_SWAP((a),(b)); }
#define PIX_SWAP(a,b) { temp=(a);(a)=(b);(b)=temp; }
uint16_t p[9]; // buffer for median filtering
uint16_t opt_med9(){
    PIX_SORT(p[1], p[2]) ; PIX_SORT(p[4], p[5]) ; PIX_SORT(p[7], p[8]) ;
    PIX_SORT(p[0], p[1]) ; PIX_SORT(p[3], p[4]) ; PIX_SORT(p[6], p[7]) ;
    PIX_SORT(p[1], p[2]) ; PIX_SORT(p[4], p[5]) ; PIX_SORT(p[7], p[8]) ;
    PIX_SORT(p[0], p[3]) ; PIX_SORT(p[5], p[8]) ; PIX_SORT(p[4], p[7]) ;
    PIX_SORT(p[3], p[6]) ; PIX_SORT(p[1], p[4]) ; PIX_SORT(p[2], p[5]) ;
    PIX_SORT(p[4], p[7]) ; PIX_SORT(p[4], p[2]) ; PIX_SORT(p[6], p[4]) ;
    PIX_SORT(p[4], p[2]) ; return(p[4]) ;
}
#undef PIX_SORT
#undef PIX_SWAP
/**
 * Resistance of TRD with median filtering
 * @param num - number of sensor
 * @return R*100
 */
int TRD_value(uint8_t num){
	int i, addr = num;
	for(i = 0; i < 9; i++, addr+=ADC_CHANNELS_NUMBER) // first we should prepare array for optmed
		p[i] = ADC_value[addr];
	uint32_t v = opt_med9();
	uint32_t r = v * ADC_multipliers[num];
	r /= (uint32_t)(4096 - v) * ADC_divisors[num];
	return (int) r;
}

