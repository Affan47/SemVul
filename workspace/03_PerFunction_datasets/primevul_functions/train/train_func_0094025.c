QPDFWriter::preserveObjectStreams()
{


    std::map<int, int> omap;
    QPDF::Writer::getObjectStreamData(this->pdf, omap);
    for (std::map<int, int>::iterator iter = omap.begin();
         iter != omap.end(); ++iter)
    {
        this->object_to_object_stream[QPDFObjGen((*iter).first, 0)] =
            (*iter).second;
    }
}
