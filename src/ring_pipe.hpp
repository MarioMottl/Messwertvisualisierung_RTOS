/**
 * @file ring_pipe.hpp
 * @author Pruggmayer Clemens
 * @brief Definition of a RT-capable byte-wise data pipe
 * @version 0.1
 * @date 2021-03-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cmsis_os2.h>

#define nullptr NULL

class ring_pipe
{
    osMemoryPoolId_t _mem;
    osSemaphoreId_t  _slots_data, _slots_empty;
    uint8_t *_m_start, *_m_end,
            *_d_start, *_d_end;
    bool _enable_put;
protected:
    uint8_t &access(uint8_t *p);
public:
    osStatus_t init(size_t maxsize);
    osStatus_t enaple_put(bool newstate);
    osStatus_t put(uint8_t data, uint32_t timeout);
    osStatus_t pop(uint8_t &data, uint32_t timeout);
    bool       is_empty(void);
};

struct ring_pipe_pair
{
    ring_pipe *src, *dst;
};
