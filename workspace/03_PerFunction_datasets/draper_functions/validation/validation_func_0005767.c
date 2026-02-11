cleanreturn(int retval, freelist_t *freelist)
{
    int index;

    if (retval == 0) {


      for (index = 0; index < freelist->first_available; ++index) {
          freelist->entries[index].destructor(NULL,
                                              freelist->entries[index].item);
      }
    }
    if (freelist->entries_malloced)
        PyMem_FREE(freelist->entries);
    return retval;
}
