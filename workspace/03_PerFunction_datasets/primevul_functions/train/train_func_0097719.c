int avpriv_bprint_to_extradata(AVCodecContext *avctx, struct AVBPrint *buf)
{
    int ret;
    char *str;

    ret = av_bprint_finalize(buf, &str);
    if (ret < 0)
        return ret;
    avctx->extradata = str;


    avctx->extradata_size = buf->len;
    return 0;
}
