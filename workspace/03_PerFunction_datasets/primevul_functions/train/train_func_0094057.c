QPDFWriter::closeObject(int objid)
{


    writeString("\nendobj\n");
    writeStringQDF("\n");
    this->lengths[objid] = pipeline->getCount() - this->xref[objid].getOffset();
}
