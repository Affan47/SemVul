xmlBufDumpNotationTable(xmlBufPtr buf, xmlNotationTablePtr table) {
    xmlBufferPtr buffer;

    buffer = xmlBufferCreate();
    if (buffer == NULL) {


        return;
    }
    xmlDumpNotationTable(buffer, table);
    xmlBufMergeBuffer(buf, buffer);
}
