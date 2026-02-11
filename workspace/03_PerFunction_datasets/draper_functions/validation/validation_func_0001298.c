remove_stale_undo_weak_ref(VMG_ CVmUndoRecord *undo_rec)
{

    if (undo_rec->id.ptrval != 0)
    {
        dict_undo_rec *rec;


        rec = (dict_undo_rec *)undo_rec->id.ptrval;


        switch(rec->action)
        {
        case DICT_UNDO_ADD:
        case DICT_UNDO_DEL:

            if (rec->obj != VM_INVALID_OBJ
                && G_obj_table->is_obj_deletable(rec->obj))
            {


                t3free(rec);
                undo_rec->id.ptrval = 0;
            }
            break;

        case DICT_UNDO_COMPARATOR:

            break;
        }
    }
}
