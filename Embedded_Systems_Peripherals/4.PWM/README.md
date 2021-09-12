# PWM - Pulse Width Modulation

controlling a **PWM** through timer is a function specific mode in Timer Peripheral where we can program a timer channel connected to a certain pin to reset it's value at a certain counter value(**CNT**) generating a pwm controlled signal via **CCR** capture compare register

now to generate a PWM signal we need to know

## datasheet procedure

- select PWM mode1(110) or mode 2(111) in CCMRx register bit OCxM
- enable the coressponding preload register from CCMRx register bit OCxPE
- enable the auto reload preload register from CR1 register bit ARPE
- initialize all the registers from EGR register bit UG
- OCx polarity is software programmable using CCER register bit CCxP. It can be programmed as active high or active low.
- OCx output is enabled by CCER register bit CCxE.

**notice :** x is a number depending on timer used

now the procedure i used in my driver library

## operational Procedures

- **First** we need to enable the selected pin as an alternate output function, push-pull, and output 50Mhz control signal frequency

- **Second** enable the timer clock of this pin channel

- **Third** enable the output channel of the capture/compare PWM module

- **Fourth** Set **ARPE** bit which make ARR register is buffered

- **Fifth**  Set **OC4PE** bit : Output compare 4 preload enable and set bit 13,14 for **OC4M** :Output compare 4 mode according to channel selected

- **Sixth** Set the frequency Divider **PSC** register value and **ARR** regisgter

    here we need to notice that  
    **PWM frequency** = Fclk / PSC * ARR  
    **PWM Duty** = CCR4 / ARR

- **Seventh** Set the capture/compare register channel **CCR1** which will set the channel state when reaches this register value from the ARR register as amaximum value

- **Eighth** start the counting with **EGR** and **CR1** registers

now we can configure the CCR register to control the pulse width and use the CNT register to measure the delay function value so you can use both delay and PWM with the same peripheral but don't do that because of shared resources problems on application conflicts

```C
    //enable clock for this peripheral and configure the pin mode as ALT_FUNC_OUT_50_mhz,OUTPUT mode
    init_GP(port,pin,OUT50, O_AF_PP);
    
    //enable clock for timer x peripheral
    RCC->APB1ENR |= bit(timerIndex);

    //Enable CC4E bit which enable capture compare on output channel
    TIMx[(int)timerIndex]->CCER |= bit(channel*4); 
    
    //Set ARPE bit which make ARR register is buffered
    TIMx[(int)timerIndex]->CR1 |= bit(7);

    //set OC4PE bit : Output compare 4 preload enable
    //set bit 13,14 for OC4M :Output compare 4 mode
    //according to channel selected
    TIMx[(int)timerIndex]->CCMR1 |= ( bit(3) | bit(5) |bit(6) );

    //PWM frequency = Fclk / PSC * ARR
    //PWM Duty = CCR4 / ARR

    TIMx[(int)timerIndex]->PSC = 8000000/(frequency * resolution);//configure the prescaler for this timer from the main clock prescaller means (clock divider )

    TIMx[(int)timerIndex]->ARR = resolution;

    //reset all channels while configuration of PWM signals
    TIMx[(int)timerIndex]->CCR1 = 0;

    //start counting
    TIMx[(int)timerIndex]->EGR |= bit(0);
    TIMx[(int)timerIndex]->CR1 |= bit(0);//enable counter
```
