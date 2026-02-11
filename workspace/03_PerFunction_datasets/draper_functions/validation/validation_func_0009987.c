GXDrawPathStartNew(GWindow w) {
    if ( !((GXWindow) w)->usecairo )
return;
    _GXCDraw_PathStartNew(w);
}
