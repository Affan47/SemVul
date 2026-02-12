xmlSwitchInputEncodingInt(xmlParserCtxtPtr ctxt, xmlParserInputPtr input,
                          xmlCharEncodingHandlerPtr handler, int len)
{
    int nbchars;

    if (handler == NULL)
        return (-1);
    if (input == NULL)
        return (-1);
    if (input->buf != NULL) {
        if (input->buf->encoder != NULL) {


            if (input->buf->encoder == handler)
                return (0);


            xmlCharEncCloseFunc(input->buf->encoder);
            input->buf->encoder = handler;
            return (0);
        }
        input->buf->encoder = handler;


        if (xmlBufIsEmpty(input->buf->buffer) == 0) {
            int processed;
	    unsigned int use;


            if ((handler->name != NULL) &&
                (!strcmp(handler->name, "UTF-16LE") ||
                 !strcmp(handler->name, "UTF-16")) &&
                (input->cur[0] == 0xFF) && (input->cur[1] == 0xFE)) {
                input->cur += 2;
            }
            if ((handler->name != NULL) &&
                (!strcmp(handler->name, "UTF-16BE")) &&
                (input->cur[0] == 0xFE) && (input->cur[1] == 0xFF)) {
                input->cur += 2;
            }


            if ((handler->name != NULL) &&
                (!strcmp(handler->name, "UTF-8")) &&
                (input->cur[0] == 0xEF) &&
                (input->cur[1] == 0xBB) && (input->cur[2] == 0xBF)) {
                input->cur += 3;
            }


            processed = input->cur - input->base;
            xmlBufShrink(input->buf->buffer, processed);
            input->buf->raw = input->buf->buffer;
            input->buf->buffer = xmlBufCreate();
	    input->buf->rawconsumed = processed;
	    use = xmlBufUse(input->buf->raw);

            if (ctxt->html) {


                nbchars = xmlCharEncInput(input->buf, 1);
            } else {


                nbchars = xmlCharEncFirstLineInput(input->buf, len);
            }
            if (nbchars < 0) {
                xmlErrInternal(ctxt,
                               "switching encoding: encoder error\n",
                               NULL);
                return (-1);
            }
	    input->buf->rawconsumed += use - xmlBufUse(input->buf->raw);
            xmlBufResetInput(input->buf->buffer, input);
        }
        return (0);
    } else if (input->length == 0) {


	xmlErrInternal(ctxt, "switching encoding : no input\n", NULL);
	return (-1);
    }
    return (0);
}
