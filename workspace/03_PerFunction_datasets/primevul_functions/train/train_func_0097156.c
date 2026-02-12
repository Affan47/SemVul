sds createStreamIDString(streamID *id) {

    sds str = sdsnewlen(SDS_NOINIT, STREAM_ID_STR_LEN);
    sdssetlen(str, 0);
    return sdscatfmt(str,"%U-%U", id->ms,id->seq);
}
