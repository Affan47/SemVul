matroxEngineReset( void *drv, void *dev )
{
     MatroxDriverData *mdrv = (MatroxDriverData*) drv;
     MatroxDeviceData *mdev = (MatroxDeviceData*) dev;
     volatile u8      *mmio = mdrv->mmio_base;

     mga_waitidle( mdrv, mdev );

     mga_waitfifo( mdrv, mdev, 11 );
     mga_out32( mmio, 0, TDUALSTAGE0 );
     mga_out32( mmio, 0, TDUALSTAGE1 );
     mga_out32( mmio, 0, ALPHAXINC );
     mga_out32( mmio, 0, ALPHAYINC );
     mga_out32( mmio, 0, DR6 );
     mga_out32( mmio, 0, DR7 );
     mga_out32( mmio, 0, DR10 );
     mga_out32( mmio, 0, DR11 );
     mga_out32( mmio, 0, DR14 );
     mga_out32( mmio, 0, DR15 );
     mga_out32( mmio, 0, BCOL );

     mga_waitfifo( mdrv, mdev, 5 );
     mga_out32( mmio, 0, TMR1 );
     mga_out32( mmio, 0, TMR2 );
     mga_out32( mmio, 0, TMR4 );
     mga_out32( mmio, 0, TMR5 );
     mga_out32( mmio, 0x100000, TMR8 );


     if (mdrv->accelerator != FB_ACCEL_MATROX_MGAG100) {
          mga_waitfifo( mdrv, mdev, 1 );
          mga_out32( mmio, 0xFFFFFFFF, PLNWT );
     }
}
