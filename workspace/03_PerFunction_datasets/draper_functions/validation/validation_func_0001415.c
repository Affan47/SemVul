uc_ovl_remove(CoreLayer *layer,
              void      *driver_data,
              void      *layer_data,
              void      *region_data)
{
    UcDriverData*  ucdrv = (UcDriverData*) driver_data;
    UcOverlayData* ucovl = (UcOverlayData*) layer_data;
    volatile u8*   vio = ucdrv->hwregs;

    ucovl->v1.isenabled = false;

    uc_ovl_vcmd_wait(vio);

    VIDEO_OUT(vio, V_FIFO_CONTROL, UC_MAP_V1_FIFO_CONTROL(16,12,8));


    if (ucovl->hwrev >= 0x10) {
        VIDEO_OUT(vio, V1_ColorSpaceReg_1, ColorSpaceValue_1_3123C0);
        VIDEO_OUT(vio, V1_ColorSpaceReg_2, ColorSpaceValue_2_3123C0);
    }
    else {
        VIDEO_OUT(vio, V1_ColorSpaceReg_1, ColorSpaceValue_1);
        VIDEO_OUT(vio, V1_ColorSpaceReg_2, ColorSpaceValue_2);
    }

    VIDEO_OUT(vio, HQV_CONTROL, VIDEO_IN(vio, HQV_CONTROL) & ~HQV_ENABLE);
    VIDEO_OUT(vio, V1_CONTROL, VIDEO_IN(vio, V1_CONTROL) & ~V1_ENABLE);


    VIDEO_OUT(vio, V_COMPOSE_MODE,
        (VIDEO_IN(vio, V_COMPOSE_MODE) & ~ENABLE_COLOR_KEYING) | V1_COMMAND_FIRE);

    ucovl->surface = NULL;

    return DFB_OK;
}
