restore_from_file(VMG_ vm_obj_id_t self,
                                      class CVmFile *fp, CVmObjFixup *fixups)
{
    char buf[VMB_DATAHOLDER];


    if (ext_ == 0)
        ext_ = (char *)G_mem->get_var_heap()
               ->alloc_mem(sizeof(vmobj_pat_ext), this);


    fp->read_bytes(buf, VMB_DATAHOLDER);


    fixups->fix_dh(vmg_ buf);


    vmb_get_dh(buf, &get_ext()->str);


    set_pattern(0);
    G_obj_table->request_post_load_init(self);
}
