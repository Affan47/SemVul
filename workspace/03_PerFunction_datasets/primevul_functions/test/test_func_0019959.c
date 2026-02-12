static void vnc_zlib_start(VncState *vs)
{
    buffer_reset(&vs->zlib.zlib);


    vs->zlib.tmp = vs->output;
    vs->output = vs->zlib.zlib;
}
