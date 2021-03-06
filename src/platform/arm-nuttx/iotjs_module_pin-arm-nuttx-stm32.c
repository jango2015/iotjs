/* Copyright 2016 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(__NUTTX__) && TARGET_BOARD == STM32F4DIS


#include "iotjs_def.h"
#include "module/iotjs_module_pin.h"
#include "stm32_gpio.h"


#if defined(ENABLE_MODULE_GPIO)

void iotjs_pin_initialize_gpio(const iotjs_jval_t* jobj) {
  iotjs_jval_t jgpio = iotjs_jval_create_object();
  iotjs_jval_set_property_jval(jobj, "GPIO", &jgpio);

// Set GPIO pin from configuration bits of nuttx.
// GPIO pin name is P(port)(pin)
#define SET_GPIO_CONSTANAT(port, pin)                    \
  iotjs_jval_set_property_number(&jgpio, "P" #port #pin, \
                                 (GPIO_PORT##port | GPIO_PIN##pin));

#define SET_GPIO_CONSTANAT_PORT(port) \
  SET_GPIO_CONSTANAT(port, 0);        \
  SET_GPIO_CONSTANAT(port, 1);        \
  SET_GPIO_CONSTANAT(port, 2);        \
  SET_GPIO_CONSTANAT(port, 3);        \
  SET_GPIO_CONSTANAT(port, 4);        \
  SET_GPIO_CONSTANAT(port, 5);        \
  SET_GPIO_CONSTANAT(port, 6);        \
  SET_GPIO_CONSTANAT(port, 7);        \
  SET_GPIO_CONSTANAT(port, 8);        \
  SET_GPIO_CONSTANAT(port, 9);        \
  SET_GPIO_CONSTANAT(port, 10);       \
  SET_GPIO_CONSTANAT(port, 11);       \
  SET_GPIO_CONSTANAT(port, 12);       \
  SET_GPIO_CONSTANAT(port, 13);       \
  SET_GPIO_CONSTANAT(port, 14);       \
  SET_GPIO_CONSTANAT(port, 15);

  SET_GPIO_CONSTANAT_PORT(A);
  SET_GPIO_CONSTANAT_PORT(B);
  SET_GPIO_CONSTANAT_PORT(C);
  SET_GPIO_CONSTANAT_PORT(D);
  SET_GPIO_CONSTANAT_PORT(E);

  SET_GPIO_CONSTANAT(H, 0);
  SET_GPIO_CONSTANAT(H, 1);

#undef SET_GPIO_CONSTANAT_PORT
#undef SET_GPIO_CONSTANAT

  iotjs_jval_destroy(&jgpio);
}

#endif /* ENABLE_MODULE_GPIO */


#if defined(ENABLE_MODULE_PWM)

void iotjs_pin_initialize_pwm(const iotjs_jval_t* jobj) {
  iotjs_jval_t jpwm = iotjs_jval_create_object();
  iotjs_jval_set_property_jval(jobj, "PWM", &jpwm);
  unsigned int timer_bit;

// Set PWM pin from configuration bits of nuttx.
// PWM pin name is "TIM(timer).CH(channel)_(n)"
#define SET_GPIO_CONSTANAT(timer, channel, order)                        \
  timer_bit = (GPIO_TIM##timer##_CH##channel##OUT_##order);              \
  timer_bit |= (TIMER_NUM(timer));                                       \
  iotjs_jval_set_property_number(&jtim##timer, "CH" #channel "_" #order, \
                                 timer_bit);

#define SET_GPIO_CONSTANAT_CHANNEL(timer, channel) \
  SET_GPIO_CONSTANAT(timer, channel, 1);           \
  SET_GPIO_CONSTANAT(timer, channel, 2);

#define SET_GPIO_CONSTANAT_TIM(timer)                    \
  iotjs_jval_t jtim##timer = iotjs_jval_create_object(); \
  iotjs_jval_set_property_jval(&jpwm, "TIM" #timer, &jtim##timer);

#define SET_GPIO_CONSTANAT_TIM_1(timer) \
  SET_GPIO_CONSTANAT_TIM(timer);        \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 1); \
  iotjs_jval_destroy(&jtim##timer);

#define SET_GPIO_CONSTANAT_TIM_2(timer) \
  SET_GPIO_CONSTANAT_TIM(timer);        \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 1); \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 2); \
  iotjs_jval_destroy(&jtim##timer);

#define SET_GPIO_CONSTANAT_TIM_4(timer) \
  SET_GPIO_CONSTANAT_TIM(timer);        \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 1); \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 2); \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 3); \
  SET_GPIO_CONSTANAT_CHANNEL(timer, 4); \
  iotjs_jval_destroy(&jtim##timer);

  SET_GPIO_CONSTANAT_TIM_4(1); // PA8, PE9, PA9, PE11, PA10, PE13, PA11, PE14
  SET_GPIO_CONSTANAT_TIM_4(2); // PA0, PA15, PA1, PB3, PA2, PB10, PA3, PB11
  iotjs_jval_set_property_number(&jtim2, "CH1_3", GPIO_TIM2_CH1OUT_3); // PA5
  SET_GPIO_CONSTANAT_TIM_4(3); // PA6, PB4, PA7, PB5, PB0, PC8, PB1, PC9
  iotjs_jval_set_property_number(&jtim3, "CH1_3", GPIO_TIM3_CH1OUT_3); // PC6
  iotjs_jval_set_property_number(&jtim3, "CH2_3", GPIO_TIM3_CH2OUT_3); // PC7
  SET_GPIO_CONSTANAT_TIM_4(4);  // PB6, PD12, PB7, PD13, PB8, PD14, PB9, PD15
  SET_GPIO_CONSTANAT_TIM_4(5);  // PA0, PH10, PA1, PH11, PA2, PH12, PA3, PI0
  SET_GPIO_CONSTANAT_TIM_4(8);  // PC6, PI5, PC7, PI6, PC8, PI7, PC9, PI2
  SET_GPIO_CONSTANAT_TIM_2(9);  // PA2, PE5, PA3, PE6
  SET_GPIO_CONSTANAT_TIM_1(10); // PB8, PF6
  SET_GPIO_CONSTANAT_TIM_1(11); // PB9, PF7
  SET_GPIO_CONSTANAT_TIM_2(12); // PH6, PB14, PB15, PH9
  SET_GPIO_CONSTANAT_TIM_1(13); // PA6, PF8
  SET_GPIO_CONSTANAT_TIM_1(14); // PA7, PF9

#undef SET_GPIO_CONSTANAT_TIM_4
#undef SET_GPIO_CONSTANAT_TIM_2
#undef SET_GPIO_CONSTANAT_TIM_1
#undef SET_GPIO_CONSTANAT_TIM
#undef SET_GPIO_CONSTANAT_CHANNEL
#undef SET_GPIO_CONSTANAT

  iotjs_jval_destroy(&jpwm);
}

#endif /* ENABLE_MODULE_PWM */


void iotjs_pin_initialize(const iotjs_jval_t* jobj) {
#if defined(ENABLE_MODULE_GPIO)
  iotjs_pin_initialize_gpio(jobj);
#endif /* ENABLE_MODULE_GPIO */

#if defined(ENABLE_MODULE_PWM)
  iotjs_pin_initialize_pwm(jobj);
#endif /* ENABLE_MODULE_PWM */
}


#endif // __NUTTX__
