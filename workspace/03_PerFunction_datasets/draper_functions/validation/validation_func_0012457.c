cyber5k_validate_blitting_cmd( CyberDriverData *cdrv,
                               CyberDeviceData *cdev, CardState *state )
{
     if (cdev->v_blitting_cmd)
          return;

     cdev->blitting_cmd = COP_PXBLT | PAT_FIXFGD | FGD_IS_SRC1;

     if (state->blittingflags & DSBLIT_SRC_COLORKEY)
          cdev->blitting_cmd |= TRANS_ENABLE | TRANS_IS_SRC1 | TRANS_INVERT;

     cdev->v_blitting_cmd = 1;
}
