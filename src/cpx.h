#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "com.h"

typedef enum {
  STM32 = 1,
  ESP32 = 2,
  HOST = 3,
  GAP8 = 4
} __attribute__((packed)) CPXTarget_t; // Rename to Destination

typedef enum {
  SYSTEM = 1,
  CONSOLE = 2,
  CRTP = 3,
  WIFI_CTRL = 4,
  APP = 5,
  TEST = 0x0E,
  BOOTLOADER = 0x0F,
} __attribute__((packed)) CPXFunction_t;

typedef struct {
  CPXTarget_t destination : 4;
  CPXTarget_t source : 4;
  CPXFunction_t function;
} __attribute__((packed)) CPXRouting_t;

typedef struct {
    CPXRouting_t route;
    uint8_t data[MTU-2];
} __attribute__((packed)) CPXPacket_t;

// Return length of packet
uint32_t cpxReceivePacketBlocking(CPXPacket_t * packet);

void cpxSendPacketBlocking(CPXPacket_t * packet, uint32_t size);

bool cpxSendPacket(CPXPacket_t * packet, uint32_t timeoutInMS);