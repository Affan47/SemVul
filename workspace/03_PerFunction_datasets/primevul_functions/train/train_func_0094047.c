QPDFWriter::writeStandard()
{
    if (this->deterministic_id)
    {
        pushMD5Pipeline();
    }


    writeHeader();
    writeString(this->extra_header_text);

    if (this->preserve_unreferenced_objects)
    {
        QTC::TC("qpdf", "QPDFWriter preserve unreferenced standard");
        std::vector<QPDFObjectHandle> all = this->pdf.getAllObjects();
        for (std::vector<QPDFObjectHandle>::iterator iter = all.begin();
             iter != all.end(); ++iter)
        {
            enqueueObject(*iter);
        }
    }


    QPDFObjectHandle trailer = getTrimmedTrailer();
    enqueueObject(trailer.getKey("/Root"));


    std::set<std::string> keys = trailer.getKeys();
    for (std::set<std::string>::iterator iter = keys.begin();
	 iter != keys.end(); ++iter)
    {
	enqueueObject(trailer.getKey(*iter));
    }


    while (this->object_queue.size())
    {
	QPDFObjectHandle cur_object = this->object_queue.front();
	this->object_queue.pop_front();
	writeObject(cur_object);
    }


    if (this->encrypted)
    {
	writeEncryptionDictionary();
    }


    qpdf_offset_t xref_offset = this->pipeline->getCount();
    if (this->object_stream_to_objects.empty())
    {

	writeXRefTable(t_normal, 0, this->next_objid - 1, this->next_objid);
    }
    else
    {

	int xref_id = this->next_objid++;
	writeXRefStream(xref_id, xref_id, xref_offset, t_normal,
			0, this->next_objid - 1, this->next_objid);
    }
    writeString("startxref\n");
    writeString(QUtil::int_to_string(xref_offset));
    writeString("\n%%EOF\n");

    if (this->deterministic_id)
    {
	QTC::TC("qpdf", "QPDFWriter standard deterministic ID",
                this->object_stream_to_objects.empty() ? 0 : 1);
        popPipelineStack();
        assert(this->md5_pipeline == 0);
    }
}
