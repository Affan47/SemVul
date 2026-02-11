nv4SetState( void *drv, void *dev,
                         GraphicsDeviceFuncs *funcs,
                         CardState *state, DFBAccelerationMask accel )
{
     NVidiaDriverData *nvdrv  = (NVidiaDriverData*) drv;
     NVidiaDeviceData *nvdev  = (NVidiaDeviceData*) dev;

     nvdev->set &= ~state->mod_hw;
     if (state->mod_hw & SMF_COLOR)
          nvdev->set &= ~(SMF_DRAWING_COLOR | SMF_BLITTING_COLOR);

     nv_set_destination( nvdrv, nvdev, state );
     nv_set_clip( nvdrv, nvdev, state );

     if (state->render_options & DSRO_MATRIX && !M_IDENTITY(state->matrix))
          nvdev->matrix = state->matrix;
     else
          nvdev->matrix = NULL;

     switch (accel) {
          case DFXL_FILLRECTANGLE:
          case DFXL_FILLTRIANGLE:
          case DFXL_DRAWRECTANGLE:
          case DFXL_DRAWLINE:
               nv_set_drawing_color( nvdrv, nvdev, state );
               if (state->drawingflags & DSDRAW_BLEND)
                    nv_set_blend_function( nvdrv, nvdev, state );
               nv_set_drawingflags( nvdrv, nvdev, state );

               if ((state->drawingflags & DSDRAW_BLEND || nvdev->matrix) && nvdev->enabled_3d) {
                    nvdev->state3d[0].modified = true;

                    funcs->FillRectangle = nvFillRectangle3D;
                    funcs->FillTriangle  = nvFillTriangle3D;
                    funcs->DrawRectangle = nvDrawRectangle3D;
                    funcs->DrawLine      = nvDrawLine3D;
               } else {
                    funcs->FillRectangle = nvFillRectangle2D;
                    funcs->FillTriangle  = nvFillTriangle2D;
                    funcs->DrawRectangle = nvDrawRectangle2D;
                    funcs->DrawLine      = nvDrawLine2D;
               }

               state->set = DFXL_FILLRECTANGLE |
                            DFXL_FILLTRIANGLE  |
                            DFXL_DRAWRECTANGLE |
                            DFXL_DRAWLINE;
               break;

          case DFXL_BLIT:
          case DFXL_STRETCHBLIT:
          case DFXL_TEXTRIANGLES:
               nv_set_source( nvdrv, nvdev, state );

               if (state->blittingflags & DSBLIT_MODULATE_ALPHA) {
                    nv_set_blend_function( nvdrv, nvdev, state );
                    nv_set_blitting_color( nvdrv, nvdev, state );
               }

               nv_set_blittingflags( nvdrv, nvdev, state );

               if (accel == DFXL_TEXTRIANGLES) {
                    if (nvdev->src_texture != state->src.buffer)
                         nvdev->set &= ~SMF_SOURCE_TEXTURE;

                    nvdev->src_texture = state->src.buffer;
                    nvdev->state3d[1].modified = true;

                    state->set = DFXL_TEXTRIANGLES;
               } else {
                    state->set = DFXL_BLIT |
                                 DFXL_STRETCHBLIT;
               }
               break;

          default:
               D_BUG( "unexpected drawing/blitting function" );
               break;
     }

     state->mod_hw = 0;
}
