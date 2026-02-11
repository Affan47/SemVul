TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct)
{
  uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;


  assert_param(IS_TIM_LIST3_PERIPH(TIMx));
  assert_param(IS_TIM_OC_MODE(TIM_OCInitStruct->TIM_OCMode));
  assert_param(IS_TIM_OUTPUT_STATE(TIM_OCInitStruct->TIM_OutputState));
  assert_param(IS_TIM_OC_POLARITY(TIM_OCInitStruct->TIM_OCPolarity));


  TIMx->CCER &= (uint16_t)~TIM_CCER_CC4E;


  tmpccer = TIMx->CCER;

  tmpcr2 =  TIMx->CR2;


  tmpccmrx = TIMx->CCMR2;


  tmpccmrx &= (uint16_t)~TIM_CCMR2_OC4M;
  tmpccmrx &= (uint16_t)~TIM_CCMR2_CC4S;


  tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);


  tmpccer &= (uint16_t)~TIM_CCER_CC4P;

  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);


  tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);

  if((TIMx == TIM1) || (TIMx == TIM8))
  {
    assert_param(IS_TIM_OCIDLE_STATE(TIM_OCInitStruct->TIM_OCIdleState));

    tmpcr2 &=(uint16_t) ~TIM_CR2_OIS4;

    tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
  }

  TIMx->CR2 = tmpcr2;


  TIMx->CCMR2 = tmpccmrx;


  TIMx->CCR4 = TIM_OCInitStruct->TIM_Pulse;


  TIMx->CCER = tmpccer;
}
