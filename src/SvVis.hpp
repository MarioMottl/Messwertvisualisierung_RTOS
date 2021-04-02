
#pragma once

#include <stdint.h>
#include <string.h>

#include "serial_interface.hpp"

namespace SvVis
{
    const size_t data_max_len = 32;

    typedef uint8_t channel_t;
    namespace channel
    {
        const size_t             count      = 9;
        const ::SvVis::channel_t string     = 10;
        const ::SvVis::channel_t int16_base = 11;
        const ::SvVis::channel_t float_base = 21;
    } // namespace channel

    namespace priority
    {
        const size_t none = 0;
        const size_t max = 0xFFFFFFFF;
    } // namespace priority
    
    namespace flags
    {
        const uint32_t done_sending = 0x00000001;
        const uint32_t n_flushing   = 0x00000002;
        const uint32_t aq_on        = 0x00000004;
    } // namespace flags

    struct message_t
    {
        ::SvVis::channel_t channel;
        int8_t len;
        union data
        {
            int16_t i16;
            float   f;
            char    raw[::SvVis::data_max_len];
        } data;
        bool is_string();
    };

    class SvVis
    {
    private:
        serial::interface *interface;
        osMessageQueueId_t queue_send, queue_recv;
        osThreadId_t thread_send, thread_recv;
        osEventFlagsId_t event_flags;
        //bool done_sending, flushing;
        static __NO_RETURN void func_send(void *this_void);
        static __NO_RETURN void func_recv(void *this_void);
    public:
        SvVis() : interface(nullptr)/*, done_sending(true), flushing(false)*/ {} // constructor because uvision c++ compiler cant automatically initialise member data
        bool init(serial::interface &interface, size_t send_queue_size = 4, size_t recv_queue_size = 4);

        size_t     max_priority();
        osStatus_t send_msg(::SvVis::message_t &msgbuf, uint32_t timeout = osWaitForever);
        osStatus_t send_str(const char *str,  uint32_t timeout = osWaitForever);
        osStatus_t send_i16(::SvVis::channel_t channel, int16_t data, uint32_t timeout = osWaitForever);
        osStatus_t send_float(::SvVis::channel_t channel, float data, uint32_t timeout = osWaitForever);
        osStatus_t flush();
        size_t available();
        void recv_msg(::SvVis::message_t &msgbuf, uint32_t timeout = osWaitForever);
    };
} // namespace SvVis
