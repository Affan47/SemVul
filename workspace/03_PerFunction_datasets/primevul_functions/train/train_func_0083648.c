QPDF::read_xref(qpdf_offset_t xref_offset)
{
    std::map<int, int> free_table;
    while (xref_offset)
    {
        char buf[7];
        memset(buf, 0, sizeof(buf));
	this->m->file->seek(xref_offset, SEEK_SET);
	this->m->file->read(buf, sizeof(buf) - 1);


        if ((strncmp(buf, "xref", 4) == 0) &&
            QUtil::is_space(buf[4]))
	{
            QTC::TC("qpdf", "QPDF xref space",
                    ((buf[4] == '\n') ? 0 :
                     (buf[4] == '\r') ? 1 :
                     (buf[4] == ' ') ? 2 : 9999));
            int skip = 4;


            while (QUtil::is_space(buf[skip]))
            {
                ++skip;
            }
            xref_offset = read_xrefTable(xref_offset + skip);
	}
	else
	{
	    xref_offset = read_xrefStream(xref_offset);
	}
    }

    if (! this->m->trailer.isInitialized())
    {
        throw QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(), "", 0,
                      "unable to find trailer while reading xref");
    }
    int size = this->m->trailer.getKey("/Size").getIntValue();
    int max_obj = 0;
    if (! this->m->xref_table.empty())
    {
	max_obj = (*(this->m->xref_table.rbegin())).first.getObj();
    }
    if (! this->m->deleted_objects.empty())
    {
	max_obj = std::max(max_obj, *(this->m->deleted_objects.rbegin()));
    }
    if (size != max_obj + 1)
    {
	QTC::TC("qpdf", "QPDF xref size mismatch");
	warn(QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(), "", 0,
		     std::string("reported number of objects (") +
		     QUtil::int_to_string(size) +
		     ") inconsistent with actual number of objects (" +
		     QUtil::int_to_string(max_obj + 1) + ")"));
    }


    this->m->deleted_objects.clear();
}
