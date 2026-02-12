xmlBufDumpEntityDecl(xmlBufPtr buf, xmlEntityPtr ent) {
    xmlBufferPtr buffer;

    buffer = xmlBufferCreate();
    if (buffer == NULL) {


        return;
    }
    xmlDumpEntityDecl(buffer, ent);
    xmlBufMergeBuffer(buf, buffer);
}
