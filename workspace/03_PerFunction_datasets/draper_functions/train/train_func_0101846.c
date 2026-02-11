sdecoder_msg_end_handler(struct lwpb_decoder *decoder,
                                  const struct lwpb_msg_desc *msg_desc,
                                  void *arg)
{
    struct lwpb_struct_decoder *sdecoder = arg;
    struct lwpb_struct_decoder_stack_frame *frame;

    LWPB_DIAG_PRINTF("msg end\n");

    sdecoder->depth--;
    frame = &sdecoder->stack[sdecoder->depth];

    if (sdecoder->msg_end_handler)
        sdecoder->msg_end_handler(sdecoder, msg_desc, sdecoder->arg);
}
