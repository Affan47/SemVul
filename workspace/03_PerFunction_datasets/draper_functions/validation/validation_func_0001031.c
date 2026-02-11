CPAL_I2C_DeInit(CPAL_InitTypeDef* pDevInitStruct)
{
  CPAL_LOG("\n\r\n\rLOG <CPAL_I2C_DeInit> : I2C Device Deinit");


  if ((pDevInitStruct->CPAL_State == CPAL_STATE_READY)
     || (pDevInitStruct->CPAL_State == CPAL_STATE_ERROR)
     || (pDevInitStruct->CPAL_State == CPAL_STATE_DISABLED))
  {


    CPAL_I2C_HAL_GPIODeInit(pDevInitStruct->CPAL_Dev);

    CPAL_LOG("\n\rLOG : I2C Device IOs Deinit");


    __CPAL_I2C_HAL_DISABLE_DEV(pDevInitStruct->CPAL_Dev);

    CPAL_LOG("\n\rLOG : I2C Device Disabled");


    CPAL_I2C_HAL_CLKDeInit(pDevInitStruct->CPAL_Dev);

    CPAL_LOG("\n\rLOG : I2C Device Clock Deinit");

#ifdef CPAL_I2C_DMA_PROGMODEL


    if (pDevInitStruct->CPAL_ProgModel == CPAL_PROGMODEL_DMA)
    {
      CPAL_I2C_HAL_DMADeInit(pDevInitStruct->CPAL_Dev, pDevInitStruct->CPAL_Direction);

      CPAL_LOG("\n\rLOG : I2C Device DMA Deinit");
    }
#endif


    CPAL_I2C_HAL_ITDeInit(pDevInitStruct->CPAL_Dev, pDevInitStruct->wCPAL_Options, pDevInitStruct->CPAL_Direction, pDevInitStruct->CPAL_ProgModel);

    CPAL_LOG("\n\rLOG : I2C Device IT Deinit");


    pDevInitStruct-> CPAL_State     = CPAL_STATE_DISABLED;
    pDevInitStruct-> wCPAL_DevError = CPAL_I2C_ERR_NONE;
    pDevInitStruct-> wCPAL_Timeout  = ((uint32_t)CPAL_I2C_TIMEOUT_DEFAULT);

    CPAL_LOG("\n\rLOG :Set State fields to default");


    _CPAL_TIMEOUT_DEINIT();

    return CPAL_PASS;
  }

  else
  {
    CPAL_LOG("\n\rERROR : I2C Device Busy");

    return CPAL_FAIL;
  }
}
