xmlBufDumpElementDecl(xmlBufPtr buf, xmlElementPtr elem) {
    xmlBufferPtr buffer;

    buffer = xmlBufferCreate();
    if (buffer == NULL) {


        return;
    }
    xmlDumpElementDecl(buffer, elem);
    xmlBufMergeBuffer(buf, buffer);
}
