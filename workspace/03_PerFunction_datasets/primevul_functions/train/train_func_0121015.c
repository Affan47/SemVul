QPDF::resolve(int objid, int generation)
{


    QPDFObjGen og(objid, generation);
    if (this->resolving.count(og))
    {


	QTC::TC("qpdf", "QPDF recursion loop in resolve");
	warn(QPDFExc(qpdf_e_damaged_pdf, this->file->getName(),
		     "", this->file->getLastOffset(),
		     "loop detected resolving object " +
		     QUtil::int_to_string(objid) + " " +
		     QUtil::int_to_string(generation)));
        return new QPDF_Null;
    }
    ResolveRecorder rr(this, og);

    if (! this->obj_cache.count(og))
    {
	if (! this->xref_table.count(og))
	{

	    return new QPDF_Null;
	}

	QPDFXRefEntry const& entry = this->xref_table[og];
	switch (entry.getType())
	{
	  case 1:
	    {
		qpdf_offset_t offset = entry.getOffset();

		int aobjid;
		int ageneration;
		QPDFObjectHandle oh =
		    readObjectAtOffset(true, offset, "", objid, generation,
				       aobjid, ageneration);
	    }
	    break;

	  case 2:
	    resolveObjectsInStream(entry.getObjStreamNumber());
	    break;

	  default:
	    throw QPDFExc(qpdf_e_damaged_pdf, this->file->getName(), "", 0,
			  "object " +
			  QUtil::int_to_string(objid) + "/" +
			  QUtil::int_to_string(generation) +
			  " has unexpected xref entry type");
	}
    }

    return this->obj_cache[og].object;
}
