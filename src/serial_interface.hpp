/**
 * @file serial_interface.hpp
 * @author Pruggmayer Clemens
 * @brief Definition of a serial Interface for sending/received data
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "ring_pipe.hpp"

namespace serial
{
    class interface
    {
    public:
        virtual osStatus_t pop(uint8_t &data, uint32_t timeout) = 0;
        virtual osStatus_t put(uint8_t data, uint32_t timeout) = 0;
        virtual osStatus_t flush(void) = 0;
        virtual void       put_blocking(const void *data, size_t len) = 0;
    };
} // namespace serial
