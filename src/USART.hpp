/**
 * @file USART.hpp
 * @author Pruggmayer Clemens
 * @brief Definition for USART Interface implementing the serial::interface
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "stm32f10x_usart.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"

#include "serial_interface.hpp"
#include "ring_pipe.hpp"

namespace usart
{
    class usart : public serial::interface
    {
    private:
        USART_TypeDef *usartn;
        osThreadId_t send_thread;
        ring_pipe *recv_pipe;
        bool done_sending;
    public:
        bool init(USART_TypeDef *usartn, uint32_t baud, size_t recv_pipe_size = 64);
        virtual osStatus_t pop(uint8_t &data, uint32_t timeout);
        virtual osStatus_t put(uint8_t data, uint32_t timeout);
        virtual osStatus_t flush(void);
        virtual void       put_blocking(const void *data, size_t len);
    };

    namespace usart1
    {
        extern ring_pipe queue;
        extern ::usart::usart *handler;
    } // namespace usart1
    namespace usart2
    {
        extern ring_pipe queue;
        extern ::usart::usart *handler;
    } // namespace usart2
    namespace usart3
    {
        extern ring_pipe queue;
        extern ::usart::usart *handler;
    } // namespace usart3

    namespace flags
    {
        const uint32_t done_sending = 0x00000001;
    } // namespace flags   
} // namespace usart
