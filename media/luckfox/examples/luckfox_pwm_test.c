/*****************************************************************************
* | File        :   luckfox_pwm_test.c
* | Author      :   luckfox team
* | Function    :   pwm output test
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-08-01
* | Info        :   Basic version
*
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> //exit()
#include <signal.h> //signal()
#include "luckfox_pwm.h"

int PWMS[] = {0, 1, 10, 11};

void Delay_ms(uint32_t xms)
{
  uint32_t i;
  for (i = 0; i < xms; i++)
  {
    usleep(1000);
  }
}

void Handler(int signo)
{
  // System Exit
  printf("\r\nHandler:exit\r\n");
  for (int x = 0; x < 4; x++)
  {
    luckfox_pwm_set_duty(PWMS[x], 0);
    luckfox_pwm_deinit(PWMS[x]);
    printf("PWM%dM0 deinit\r\n", PWMS[x]);
  }

  exit(0);
}

int main(int argc, char *argv[])
{
  signal(SIGINT, Handler);
  for (int x = 0; x < 4; x++)
  {
    luckfox_pwm_init(PWMS[x], 100000, 15000 * (x + 1), PWM_POLARITY_NORMAL);
    luckfox_pwm_set_enable(PWMS[x], true);
    printf("PWM%dM0 period=%d duty=%d\r\n", PWMS[x], luckfox_pwm_get_period(PWMS[x]), luckfox_pwm_get_duty(PWMS[x]));
  }
  while (1)
  {
    Delay_ms(1000);
  }

  return 0;
}
