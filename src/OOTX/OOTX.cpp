#include "OOTX.hpp"

void OOTX::ResetState()
{
    this->m_bitStack.reset();
    // this->m_byteStack.clear();
    memset(this->m_byteStack, 0, sizeof(this->m_byteStack));
    this->m_bitIndex = 0;
    this->m_hasPreambleStarted = false;
    DEBUG_PRINT("OOTX Frame reset");
}

void OOTX::AppendDataBit(bool bit)
{
    this->m_bitStack.set(16 - this->m_bitIndex++, bit);
    DEBUG_PRINT("[m_bitStack] " + this->m_bitIndex + '\t' + this->m_bitStack.to_string().c_str());
    if (this->m_bitIndex == 17) // when the sync bit is reached
    {
        if (this->m_bitStack.to_string().substr(16, 1) != "1") // corrupt ootx frame
        {
            DEBUG_PRINT("[OOTX Parser] Corrupt frame: non-true sync bit");
            this->ResetState();
            return;
        }
        // divide the bitset into 2 8-bit bitsets (2 bytes)
        std::bitset<8> firstByte(this->m_bitStack.to_string().substr(0, 8));
        std::bitset<8> secondByte(this->m_bitStack.to_string().substr(8, 8));
        // for (int i = 0; i < 8; i++)
        // {
        //     firstByte[i] = this->m_bitStack[i];
        //     secondByte[i] = this->m_bitStack[i + 8];
        // }
        // and append them to the ootx frame accumulator
        this->m_byteStack[this->m_stackIndex++] = firstByte;
        this->m_byteStack[this->m_stackIndex++] = secondByte;
        DEBUG_PRINT("[OOTX Parser] Current parsed bytes: " + firstByte.to_string().c_str() + '\t' + secondByte.to_string().c_str());
        // this->m_byteStack.push_back(firstByte);
        // this->m_byteStack.push_back(secondByte);
        // flush the bitset accumulator
        this->m_bitStack.reset();
        this->m_bitIndex = 0;
        DEBUG_PRINT("[OOTX Parser] New frame added to buffer");
        // switch (this->m_byteStack.size())
        switch (this->m_stackIndex)
        {
        case 2: // when the first 2 bytes have been received
            // check if they are a valid ootx preamble sequence
            {
                if (this->m_byteStack[0].to_ulong() || this->m_byteStack[1].to_ulong()) // if not
                {
                    DEBUG_PRINT("[OOTX Parser] Corrupt frame: non-zero preamble bytes");
                    this->ResetState();
                }
                // if (this->m_byteStack.at(0).to_ulong()  
                // || this->m_byteStack.at(1).to_ulong()) // if not
                //     this->ResetState();
            }
            break;
        case 4: // when the payload length bytes have been received
            {
                std::bitset<16> lengthBytes(this->m_byteStack[2].to_string() + this->m_byteStack[3].to_string());
                // if the length of the payload is different from 33 bytes, then an unknown ootx frame has been received
                if (lengthBytes.to_ulong() != 33) 
                {
                    DEBUG_PRINT("[OOTX Parser] Unknown frame: unknown payload length");
                    this->ResetState();
                    return;
                }
                DEBUG_PRINT("[OOTX Parser] Correct payload length received: " + (String) lengthBytes.to_ulong());
            }
            break;
        case 37: // when the last payload byte has been received (it should be a padding byte)
            if (this->m_byteStack[36].to_ulong())
            {
                DEBUG_PRINT("[OOTX Parser] Malformed payload: last payload byte was not a padding byte");
                this->ResetState();
            }
            break;
        case 41: // when the full frame has been received
            {
                std::bitset<6> protocolVersion(this->m_byteStack[3 + 0x00].to_string().substr(0, 6));
                std::bitset<10> firmwareVersion((this->m_byteStack[3 + 0x00].to_string() + this->m_byteStack[3 + 0x01].to_string()).substr(6, 10));
                this->basestationData.protocolVersion = protocolVersion.to_ulong();
                this->basestationData.firmwareVersion = firmwareVersion.to_ulong();
                std::bitset<32> uuid(this->m_byteStack[3 + 0x02].to_string() 
                                    + this->m_byteStack[3 + 0x03].to_string()
                                    + this->m_byteStack[3 + 0x04].to_string()
                                    + this->m_byteStack[3 + 0x05].to_string());
                this->basestationData.uuid = uuid.to_ulong();
                this->basestationData.mode = this->m_byteStack[3 + 0x1F].to_ulong();
                this->basestationData.hardwareVersion = this->m_byteStack[3 + 0x0F].to_ulong();
                this->ResetState();
                DEBUG_PRINT("[OOTX Parser] Full OOTX Frame parsed sucessfully");
            }
            break;
        }
    }
}
