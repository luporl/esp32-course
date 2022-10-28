#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"

#define TXD_PIN 17
#define RXD_PIN 16

#define RX_BUF_SIZE 1024

#define UART    UART_NUM_2

void app_main(void)
{
  uart_config_t uart_config = {
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_DEFAULT
  };
  uart_param_config(UART ,&uart_config);

  uart_set_pin(UART, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART, RX_BUF_SIZE, 0, 0, NULL, 0);

  char message[] = "ping";
  printf("sending: %s\n", message);
  uart_write_bytes(UART, message, sizeof(message));

  char incoming_message[RX_BUF_SIZE];
  memset(incoming_message, 0, sizeof(incoming_message));
  uart_read_bytes(UART, (uint8_t *) incoming_message, RX_BUF_SIZE, pdMS_TO_TICKS(500));
  printf("received: %s\n", incoming_message);

  printf("test test test\n");
}
