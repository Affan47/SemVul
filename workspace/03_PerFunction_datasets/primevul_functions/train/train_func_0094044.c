QPDFWriter::writeObjectStream(QPDFObjectHandle object)
{


    QPDFObjGen old_og = object.getObjGen();
    assert(old_og.getGen() == 0);
    int old_id = old_og.getObj();
    int new_id = obj_renumber[old_og];

    std::vector<qpdf_offset_t> offsets;
    qpdf_offset_t first = 0;


    PointerHolder<Buffer> stream_buffer;
    int first_obj = -1;
    bool compressed = false;
    for (int pass = 1; pass <= 2; ++pass)
    {
	if (pass == 1)
	{
	    pushDiscardFilter();
	}
	else
	{


	    first = offsets.at(0);
	    for (std::vector<qpdf_offset_t>::iterator iter = offsets.begin();
		 iter != offsets.end(); ++iter)
	    {
		*iter -= first;
	    }


	    pushDiscardFilter();
	    writeObjectStreamOffsets(offsets, first_obj);
	    first += this->pipeline->getCount();
	    popPipelineStack();


	    Pipeline* next = pushPipeline(new Pl_Buffer("object stream"));
	    if (! ((this->stream_data_mode == qpdf_s_uncompress) ||
		   this->qdf_mode))
	    {
		compressed = true;
		next = pushPipeline(
		    new Pl_Flate("compress object stream", next,
				 Pl_Flate::a_deflate));
	    }
	    activatePipelineStack();
	    writeObjectStreamOffsets(offsets, first_obj);
	}

	int count = 0;
	for (std::set<QPDFObjGen>::iterator iter =
		 this->object_stream_to_objects[old_id].begin();
	     iter != this->object_stream_to_objects[old_id].end();
	     ++iter, ++count)
	{
	    QPDFObjGen obj = *iter;
	    int new_obj = this->obj_renumber[obj];
	    if (first_obj == -1)
	    {
		first_obj = new_obj;
	    }
	    if (this->qdf_mode)
	    {
		writeString("%% Object stream: object " +
			    QUtil::int_to_string(new_obj) + ", index " +
			    QUtil::int_to_string(count));
		if (! this->suppress_original_object_ids)
		{
		    writeString("; original object ID: " +
				QUtil::int_to_string(obj.getObj()));


                    if (obj.getGen() != 0)
                    {
                        QTC::TC("qpdf", "QPDFWriter original obj non-zero gen");
                        writeString(" " + QUtil::int_to_string(obj.getGen()));
                    }
		}
		writeString("\n");
	    }
	    if (pass == 1)
	    {
		offsets.push_back(this->pipeline->getCount());
	    }
	    writeObject(this->pdf.getObjectByObjGen(obj), count);

	    this->xref[new_obj] = QPDFXRefEntry(2, new_id, count);
	}


	popPipelineStack(&stream_buffer);
    }


    openObject(new_id);
    setDataKey(new_id);
    writeString("<<");
    writeStringQDF("\n ");
    writeString(" /Type /ObjStm");
    writeStringQDF("\n ");
    size_t length = stream_buffer->getSize();
    adjustAESStreamLength(length);
    writeString(" /Length " + QUtil::int_to_string(length));
    writeStringQDF("\n ");
    if (compressed)
    {
	writeString(" /Filter /FlateDecode");
    }
    writeString(" /N " + QUtil::int_to_string(offsets.size()));
    writeStringQDF("\n ");
    writeString(" /First " + QUtil::int_to_string(first));
    if (! object.isNull())
    {

	QPDFObjectHandle dict = object.getDict();
	QPDFObjectHandle extends = dict.getKey("/Extends");
	if (extends.isIndirect())
	{
	    QTC::TC("qpdf", "QPDFWriter copy Extends");
	    writeStringQDF("\n ");
	    writeString(" /Extends ");
	    unparseChild(extends, 1, f_in_ostream);
	}
    }
    writeStringQDF("\n");
    writeStringNoQDF(" ");
    writeString(">>\nstream\n");
    if (this->encrypted)
    {
	QTC::TC("qpdf", "QPDFWriter encrypt object stream");
    }
    pushEncryptionFilter();
    writeBuffer(stream_buffer);
    popPipelineStack();
    writeString("endstream");
    this->cur_data_key.clear();
    closeObject(new_id);
}
