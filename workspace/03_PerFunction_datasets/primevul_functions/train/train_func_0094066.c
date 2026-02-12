QPDFWriter::assignCompressedObjectNumbers(QPDFObjGen const& og)
{
    int objid = og.getObj();
    if ((og.getGen() != 0) ||
        (this->object_stream_to_objects.count(objid) == 0))
    {

	return;
    }


    for (std::set<QPDFObjGen>::iterator iter =
	     this->object_stream_to_objects[objid].begin();
	 iter != this->object_stream_to_objects[objid].end();
	 ++iter)
    {
	obj_renumber[*iter] = next_objid++;
    }
}
