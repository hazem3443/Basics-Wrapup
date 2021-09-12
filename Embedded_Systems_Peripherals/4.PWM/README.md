# PWM - Pulse Width Modulation

x is a number depending on timer used

- select PWM mode1(110) or mode 2(111) in CCMRx register bit OCxM
- enable the coressponding preload register from CCMRx register bit OCxPE
- enable the auto reload preload register from CR1 register bit ARPE
- initialize all the registers from EGR register bit UG
- OCx polarity is software programmable using CCER register bit CCxP. It can be programmed as active high or active low.
- OCx output is enabled by CCER register bit CCxE.
