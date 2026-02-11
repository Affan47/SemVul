new_ExpandFile(void)
{
  ExpandFile *ef;


  ef = (ExpandFile *) malloc(sizeof(ExpandFile));
  if(!ef) {
    errno = ENOMEM;
    return NULL;
  };


  ef->err = NULL;
  ef->sg = NULL;
  ef->cache.mem = NULL;
  ef->cache.head = NULL;
  ef->cache.next = NULL;
  ef->cache.tail = NULL;
  ef->path = NULL;
  ef->home = NULL;
  ef->result.files = NULL;
  ef->result.nfile = 0;
  ef->usrnam[0] = '\0';
  ef->envnam[0] = '\0';


  ef->err = _new_ErrMsg();
  if(!ef->err)
    return del_ExpandFile(ef);


  ef->sg = _new_StringGroup(_pu_pathname_dim());
  if(!ef->sg)
    return del_ExpandFile(ef);


  ef->cache.mem = _new_FreeList(sizeof(DirNode), DIR_CACHE_BLK);
  if(!ef->cache.mem)
    return del_ExpandFile(ef);


  ef->path = _new_PathName();
  if(!ef->path)
    return del_ExpandFile(ef);


  ef->home = _new_HomeDir();
  if(!ef->home)
    return del_ExpandFile(ef);


  ef->files_dim = MATCH_BLK_FACT;
  ef->result.files = (char **) malloc(sizeof(ef->result.files[0]) *
				      ef->files_dim);
  if(!ef->result.files) {
    errno = ENOMEM;
    return del_ExpandFile(ef);
  };
  return ef;
}
