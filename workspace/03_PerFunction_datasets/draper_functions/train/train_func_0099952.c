tdfx_waitidle( TDFXDriverData *tdrv,
                                  TDFXDeviceData *tdev )
{
     int i = 0;
     int timeout = 1000000;


     while (timeout--) {
          tdev->idle_waitcycles++;

          i = (tdrv->voodoo2D->status & (0xF << 7))  ?  0 : i + 1;
          if (i == 3)
               return;

     }

     D_BUG( "timeout during waitidle!\n");
}
