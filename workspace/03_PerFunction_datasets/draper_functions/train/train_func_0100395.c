_dxf_BUFFER_RESTORE_CONFIG (void *ctx,
					int OrigDisplayMode,
					int OrigBufferMode,
					tdmInteractorRedrawMode redrawMode)
{


  ENTRY(("_dxf_BUFFER_RESTORE_CONFIG (0x%x, %d, %d, %d)",
	 ctx, OrigDisplayMode, OrigBufferMode, redrawMode));

  if (redrawMode == tdmBothBufferDraw ||
      redrawMode == tdmFrontBufferDraw) {

    PRINT(("current interactor redraw mode is \"%s\"",
	   (redrawMode == tdmFrontBufferDraw) ?
	   "tdmFrontBufferDraw" : "tdmBothBufferDraw"));


    glFlush() ;

    if (OrigBufferMode == GL_BACK ||
	OrigBufferMode == GL_BACK_LEFT) {
      PRINT(("restoring to original back buffer draw"));
      glDrawBuffer(GL_BACK) ;
    } else {
      PRINT(("remaining in original front buffer draw"));
    }
  } else if (redrawMode == tdmBackBufferDraw ||
	     redrawMode == tdmViewEchoMode) {

    PRINT(("current interactor redraw mode is \"%s\"",
	   (redrawMode == tdmViewEchoMode) ?
	   "tdmViewEchoMode" : "tdmBackBufferDraw"));

    if (OrigBufferMode == GL_FRONT ||
	OrigBufferMode == GL_FRONT_LEFT) {
      PRINT(("restoring to original front buffer draw"));
      glDrawBuffer(GL_FRONT) ;
    } else {
      PRINT(("remaining in original back buffer draw"));
    }
  } else {
    PRINT(("ignoring redraw mode"));
  }

  EXIT((""));
}
