xmlBufDumpAttributeDecl(xmlBufPtr buf, xmlAttributePtr attr) {
    xmlBufferPtr buffer;

    buffer = xmlBufferCreate();
    if (buffer == NULL) {


        return;
    }
    xmlDumpAttributeDecl(buffer, attr);
    xmlBufMergeBuffer(buf, buffer);
}
