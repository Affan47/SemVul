r200SetState( void *drv, void *dev,
                          GraphicsDeviceFuncs *funcs,
                          CardState *state, DFBAccelerationMask accel )
{
     RadeonDriverData *rdrv = (RadeonDriverData*) drv;
     RadeonDeviceData *rdev = (RadeonDeviceData*) dev;

     rdev->set &= ~state->mod_hw;
     if (DFB_BLITTING_FUNCTION( accel )) {
          if ((rdev->accel ^ accel) & DFXL_TEXTRIANGLES)
               rdev->set &= ~SMF_BLITTING_FLAGS;
     }

     rdev->accel = accel;

     r200_set_destination( rdrv, rdev, state );
     r200_set_clip( rdrv, rdev, state );
     r200_set_render_options( rdrv, rdev, state );

     switch (accel) {
          case DFXL_FILLRECTANGLE:
          case DFXL_FILLTRIANGLE:
          case DFXL_DRAWRECTANGLE:
          case DFXL_DRAWLINE:
               r200_set_drawing_color( rdrv, rdev, state );

               if (state->drawingflags & DSDRAW_BLEND)
                    r200_set_blend_function( rdrv, rdev, state );

               r200_set_drawingflags( rdrv, rdev, state );

               if (RADEON_DRAW_3D()) {
                    funcs->FillRectangle = r200FillRectangle3D;
                    funcs->FillTriangle  = r200FillTriangle;
                    funcs->DrawRectangle = r200DrawRectangle3D;
                    funcs->DrawLine      = r200DrawLine3D;
                    funcs->EmitCommands  = r200EmitCommands3D;
               } else {
                    funcs->FillRectangle = RADEON_FUNC(radeonFillRectangle2D);
                    funcs->FillTriangle  = NULL;
                    funcs->DrawRectangle = RADEON_FUNC(radeonDrawRectangle2D);
                    funcs->DrawLine      = RADEON_FUNC(radeonDrawLine2D);
                    funcs->EmitCommands  = NULL;
               }

               state->set = rdev->drawing_mask;
               break;

          case DFXL_BLIT:
          case DFXL_STRETCHBLIT:
          case DFXL_TEXTRIANGLES:
               r200_set_source( rdrv, rdev, state );

               if (state->blittingflags & DSBLIT_MASK)
                    r200_set_source_mask( rdrv, rdev, state );

               if (state->blittingflags & DSBLIT_MODULATE_ALPHA)
                    r200_set_blend_function( rdrv, rdev, state );

               if (state->blittingflags & DSBLIT_MODULATE_COLOR)
                    r200_set_blitting_color( rdrv, rdev, state );

               if (state->blittingflags & DSBLIT_SRC_COLORKEY)
                    r200_set_src_colorkey( rdrv, rdev, state );

               r200_set_blittingflags( rdrv, rdev, state );

               if (RADEON_BLIT_3D()) {
                    funcs->Blit             = r200Blit3D;
                    funcs->StretchBlit      = r200StretchBlit;
                    funcs->TextureTriangles = r200TextureTriangles;
                    funcs->EmitCommands     = r200EmitCommands3D;
               } else {
                    funcs->Blit             = RADEON_FUNC(radeonBlit2D);
                    funcs->StretchBlit      = NULL;
                    funcs->TextureTriangles = NULL;
                    funcs->EmitCommands     = NULL;
               }

               state->set = (accel & DFXL_TEXTRIANGLES)
                            ? : (rdev->blitting_mask & ~DFXL_TEXTRIANGLES);
               break;

          default:
               D_BUG( "unexpected drawing/blitting function" );
               break;
     }

     state->mod_hw = 0;
}
