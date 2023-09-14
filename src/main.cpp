#include <Arduino.h>
#include <OOTX/OOTX.hpp>
#include <Emissions/Emissions.hpp>
#include <bitset>


volatile uint64_t startTime = 0;
OOTX* currentOOTX = new OOTX();

void setup()
{
    Serial.begin(2000000);
    Serial.println("[LOGGER STARTED]");
    pinMode(PA8, INPUT_PULLDOWN);
    attachInterrupt(PA8, 
                    [] () {
                        if (digitalRead(PA8))
                        {
                            startTime = micros();
                            return;
                        }
                        uint32_t timeDifference = micros() - startTime;
                        DEBUG_PRINT((String) timeDifference);
                        Pulse currentPulse = ParsePulse(timeDifference);
                        if (currentPulse.emissionType == LightEmmisions::null) return;
                        currentOOTX->AppendDataBit(currentPulse.skip);
                        // DEBUG_PRINT('\t' + (String) currentPulse.skip + '\t' + (String) currentPulse.data + '\t' + (String) currentPulse.axis);
                    },
                    CHANGE);
}

void loop() {}