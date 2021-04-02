#include "USART.hpp"
#include "SvVis.hpp"

usart::usart usart1;

SvVis::SvVis svvis;
SvVis::message_t msg;

void __NO_RETURN main_thread(void *arg)
{
    for(;;)
    {
        svvis.recv_msg(msg);
        svvis.send_msg(msg);
    }
}

const int16_t data_tri[] = {0, 10, 20, 30, 40, 50, 40, 30, 20, 10};
const size_t data_tri_len = sizeof(data_tri) / sizeof(data_tri[0]);

void __NO_RETURN send_tri_data(void *arg)
{
    for(;;)
    {
        for(size_t i=0; i<data_tri_len; i++)
        {
            svvis.send_i16(1, data_tri[i]);
            osDelay(1000);
        }
    }
}

int main()
{
    osKernelInitialize();
    usart1.init(USART1, 9600);
    svvis.init(usart1);
    osThreadNew(main_thread, nullptr, nullptr);
    osThreadNew(send_tri_data, nullptr, nullptr);
    osKernelStart();
}
