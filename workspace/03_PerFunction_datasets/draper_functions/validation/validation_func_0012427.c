timer16Init(uint8_t timerNum, uint16_t timerInterval)
{

  if (timerInterval < 1)
  {
    timerInterval = TIMER16_DEFAULTINTERVAL;
  }

  if ( timerNum == 0 )
  {

    SCB_SYSAHBCLKCTRL |= (SCB_SYSAHBCLKCTRL_CT16B0);


    timer16_0_counter = 0;
    TMR_TMR16B0MR0 = timerInterval;


    TMR_TMR16B0MCR = (TMR_TMR16B0MCR_MR0_INT_ENABLED | TMR_TMR16B0MCR_MR0_RESET_ENABLED);


    NVIC_EnableIRQ(TIMER_16_0_IRQn);
  }

  else if ( timerNum == 1 )
  {

    SCB_SYSAHBCLKCTRL |= (SCB_SYSAHBCLKCTRL_CT16B1);


    timer16_1_counter = 0;
    TMR_TMR16B1MR0 = timerInterval;


    TMR_TMR16B1MCR = (TMR_TMR16B1MCR_MR0_INT_ENABLED | TMR_TMR16B1MCR_MR0_RESET_ENABLED);


    NVIC_EnableIRQ(TIMER_16_1_IRQn);
  }
  return;
}
