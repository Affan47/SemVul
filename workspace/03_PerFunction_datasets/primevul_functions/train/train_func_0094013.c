QPDFWriter::write()
{


    if (this->linearized)
    {
	this->qdf_mode = false;
    }

    if (this->qdf_mode)
    {
	if (! this->normalize_content_set)
	{
	    this->normalize_content = true;
	}
	if (! this->stream_data_mode_set)
	{
	    this->stream_data_mode = qpdf_s_uncompress;
	}
    }

    if (this->encrypted)
    {

	this->preserve_encryption = false;
    }
    else if (this->normalize_content ||
	     (this->stream_data_mode == qpdf_s_uncompress) ||
	     this->qdf_mode)
    {


	this->preserve_encryption = false;
    }

    if (preserve_encryption)
    {
	copyEncryptionParameters(this->pdf);
    }

    if (! this->forced_pdf_version.empty())
    {
	int major = 0;
	int minor = 0;
	parseVersion(this->forced_pdf_version, major, minor);
	disableIncompatibleEncryption(major, minor,
                                      this->forced_extension_level);
	if (compareVersions(major, minor, 1, 5) < 0)
	{
	    QTC::TC("qpdf", "QPDFWriter forcing object stream disable");
	    this->object_stream_mode = qpdf_o_disable;
	}
    }

    if (this->qdf_mode || this->normalize_content ||
	(this->stream_data_mode == qpdf_s_uncompress))
    {
	initializeSpecialStreams();
    }

    if (this->qdf_mode)
    {


	this->direct_stream_lengths = false;
    }

    switch (this->object_stream_mode)
    {
      case qpdf_o_disable:

	break;

      case qpdf_o_preserve:
	preserveObjectStreams();
	break;

      case qpdf_o_generate:
	generateObjectStreams();
	break;


    }

    if (this->linearized)
    {

	std::vector<QPDFObjectHandle> pages = pdf.getAllPages();
	for (std::vector<QPDFObjectHandle>::iterator iter = pages.begin();
	     iter != pages.end(); ++iter)
	{
	    QPDFObjectHandle& page = *iter;
	    QPDFObjGen og = page.getObjGen();
	    if (this->object_to_object_stream.count(og))
	    {
		QTC::TC("qpdf", "QPDFWriter uncompressing page dictionary");
		this->object_to_object_stream.erase(og);
	    }
	}
    }

    if (this->linearized || this->encrypted)
    {


	QPDFObjGen og = pdf.getRoot().getObjGen();
	if (this->object_to_object_stream.count(og))
	{
	    QTC::TC("qpdf", "QPDFWriter uncompressing root");
	    this->object_to_object_stream.erase(og);
	}
    }


    for (std::map<QPDFObjGen, int>::iterator iter =
	     this->object_to_object_stream.begin();
	 iter != this->object_to_object_stream.end(); ++iter)
    {
	QPDFObjGen obj = (*iter).first;
	int stream = (*iter).second;
	this->object_stream_to_objects[stream].insert(obj);
	this->max_ostream_index =
	    std::max(this->max_ostream_index,
		     static_cast<int>(
                         this->object_stream_to_objects[stream].size()) - 1);
    }

    if (! this->object_stream_to_objects.empty())
    {
	setMinimumPDFVersion("1.5");
    }

    prepareFileForWrite();

    if (this->linearized)
    {
	writeLinearized();
    }
    else
    {
	writeStandard();
    }

    this->pipeline->finish();
    if (this->close_file)
    {
	fclose(this->file);
    }
    this->file = 0;
    if (this->buffer_pipeline)
    {
	this->output_buffer = this->buffer_pipeline->getBuffer();
	this->buffer_pipeline = 0;
    }
}
