GDrawGetBiTextBounds(GWindow gw,const unichar_t *text, int32 cnt, FontMods *mods, GTextBounds *bounds) {
    int ret;
    struct tf_arg arg;

    memset(&arg,'\0',sizeof(arg));
    arg.first = true;
#ifndef _NO_LIBPANGO
    if ( gw->usepango )
	ret = _GXPDraw_DoText(gw,0,0,text,cnt,mods,0x0,tf_rect,&arg);
    else
#endif
	ret = _GDraw_DoText(gw,0,0,(unichar_t *) text,cnt,mods,0,tf_rect,&arg);
    *bounds = arg.size;
return( ret );
}
