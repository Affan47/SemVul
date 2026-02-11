get(const nstring &filename)
{
    trace(("project_file_roll_forward::get(\"%s\")\n{\n", filename.c_str()));
    assert(!filename_to_uuid.empty());
    nstring uuid(filename_to_uuid.query(filename));
    if (!uuid)
    {
	trace(("return NULL;\n"));
	trace(("}\n"));
	return file_event_list::pointer();
    }
    assert(!uuid_to_felp.empty());
    file_event_list::pointer result = uuid_to_felp.get(uuid);


    if (result)
    {
        bool file_action_create_missing = true;
        for (size_t j = 0; j < result->size(); ++j)
        {
            file_event *fep = result->get(j);
            assert(fep);
            fstate_src_ty *fstate_src = fep->get_src();
            assert(fstate_src);
            if (fstate_src->action == file_action_create)
            {
                file_action_create_missing = false;
                break;
            }
        }

        if (!result->empty() && file_action_create_missing)
        {


            assert(uuid);
            if (universal_unique_identifier_valid(uuid))
            {


                file_event_list::pointer felp2 =
                    uuid_to_felp.get(nstring(filename));
                if (felp2)
                {
                    felp2->push_back(*result);


                    uuid_to_felp.assign(uuid, felp2);
                    result = uuid_to_felp.get(uuid);
                    assert(result);
                    assert(result == felp2);
                }
            }
        }

#ifdef DEBUG
	for (size_t j = 0; j < result->size(); ++j)
	{
	    file_event *fep = result->get(j);
	    change::pointer cp = fep->get_change();
            time_t when = fep->get_when();
	    trace(("%s, %ld, %.24s\n", project_name_get(cp->pp)->str_text,
		cp->number, ctime(&when)));
	}
#endif
    }

    trace(("return %08lX\n", (long)result.get()));
    trace(("}\n"));
    return result;
}
