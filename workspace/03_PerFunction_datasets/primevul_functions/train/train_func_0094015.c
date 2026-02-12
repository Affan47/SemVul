QPDFWriter::generateObjectStreams()
{


    std::vector<QPDFObjGen> const& eligible =
        QPDF::Writer::getCompressibleObjGens(this->pdf);
    unsigned int n_object_streams = (eligible.size() + 99) / 100;
    if (n_object_streams == 0)
    {
        throw std::logic_error("n_object_streams == 0");
    }
    unsigned int n_per = eligible.size() / n_object_streams;
    if (n_per * n_object_streams < eligible.size())
    {
	++n_per;
    }
    unsigned int n = 0;
    int cur_ostream = 0;
    for (std::vector<QPDFObjGen>::const_iterator iter = eligible.begin();
	 iter != eligible.end(); ++iter)
    {
	if ((n % n_per) == 0)
	{
	    if (n > 0)
	    {
		QTC::TC("qpdf", "QPDFWriter generate >1 ostream");
	    }
	    n = 0;
	}
	if (n == 0)
	{


	    cur_ostream = this->pdf.makeIndirectObject(
		QPDFObjectHandle::newNull()).getObjectID();
	}
	this->object_to_object_stream[*iter] = cur_ostream;
	++n;
    }
}
