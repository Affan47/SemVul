pinMode(uint32_t pin, uint32_t mode)
{
  if (pin > 13) {
    return;
  }

  RCC_AHB1PeriphClockCmd(deckGPIOMapping[pin-1].periph, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure = {0};

  GPIO_InitStructure.GPIO_Pin = deckGPIOMapping[pin-1].pin;
  GPIO_InitStructure.GPIO_Mode = (mode == OUTPUT) ? GPIO_Mode_OUT:GPIO_Mode_IN;
  if (mode == OUTPUT) GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  if (mode == INPUT_PULLUP) GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  if (mode == INPUT_PULLDOWN) GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Init(deckGPIOMapping[pin-1].port, &GPIO_InitStructure);
}
