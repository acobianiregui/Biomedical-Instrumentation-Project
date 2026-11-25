#include "PressureSensorDriver.h"

namespace {
    constexpr uint32_t OUTPUT_MIN_COUNTS = 1677722UL;
    constexpr uint32_t OUTPUT_MAX_COUNTS = 15099494UL;
    constexpr float MMHG_PER_BAR = 750.062f;
    constexpr uint8_t COMMAND[] = {0xAA, 0x00, 0x00};
    constexpr uint8_t STATUS_BUSY = 0x20;
    constexpr uint8_t STATUS_MEMORY_ERROR = 0x04;
    constexpr uint8_t STATUS_MATH_SATURATION = 0x01;
}

PressureSensorDriver::PressureSensorDriver(TwoWire& bus,
                                           float minimumPressureBar,
                                           float maximumPressureBar,
                                           uint8_t address)
    : bus_(bus),
      address_(address),
      pMinBar_(minimumPressureBar),
      pMaxBar_(maximumPressureBar) {}

bool PressureSensorDriver::begin() {
    bus_.beginTransmission(address_);
    return bus_.endTransmission() == 0;
}

bool PressureSensorDriver::readPressureMmHg(float& pressureMmHg) {
    pressureMmHg = NAN;
    bus_.beginTransmission(address_);
    if (bus_.write(COMMAND, sizeof(COMMAND)) != sizeof(COMMAND)) {
        Serial.println("ERROR: Could not write command");
        bus_.endTransmission();
        return false;
    }
    if (bus_.endTransmission() != 0) {

        return false;
    }

    //At least 5ms delay
    delay(10);

    if (bus_.requestFrom(address_, static_cast<uint8_t>(4)) != 4) {
        Serial.println("No es 4");
        return false;
    }

    const uint8_t status = static_cast<uint8_t>(bus_.read());
    const uint32_t b1 = static_cast<uint8_t>(bus_.read());
    const uint32_t b2 = static_cast<uint8_t>(bus_.read());
    const uint32_t b3 = static_cast<uint8_t>(bus_.read());

    if (status & (STATUS_BUSY | STATUS_MEMORY_ERROR | STATUS_MATH_SATURATION)) {
        Serial.println("Aqui melon");
        return false;
    }

    const uint32_t counts = (b1 << 16) | (b2 << 8) | b3;
    const float pressureBar =
        (static_cast<float>(counts) - OUTPUT_MIN_COUNTS) *
        (pMaxBar_ - pMinBar_) /
        (OUTPUT_MAX_COUNTS - OUTPUT_MIN_COUNTS) + pMinBar_;

    pressureMmHg = pressureBar * MMHG_PER_BAR;
    return true;
}
