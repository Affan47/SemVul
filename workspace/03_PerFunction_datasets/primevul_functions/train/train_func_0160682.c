queue_get_spool_list(int subdiroffset, uschar *subdirs, int *subcount,
  BOOL randomize)
{
int i;
int flags = 0;
int resetflags = -1;
int subptr;
queue_filename *yield = NULL;
queue_filename *last = NULL;
struct dirent *ent;
DIR *dd;
uschar buffer[256];
queue_filename *root[LOG2_MAXNODES];


if (randomize)
  resetflags = time(NULL) & 0xFFFF;
else
   for (i = 0; i < LOG2_MAXNODES; i++)
     root[i] = NULL;


if (subdiroffset <= 0)
  {
  i = 0;
  subdirs[0] = 0;
  *subcount = 0;
  }
else
  i = subdiroffset;


spool_pname_buf(buffer, sizeof(buffer));
buffer[sizeof(buffer) - 3] = 0;
subptr = Ustrlen(buffer);
buffer[subptr+2] = 0;


for (; i <= *subcount; i++)
  {
  int count = 0;
  int subdirchar = subdirs[i];

  if (subdirchar != 0)
    {
    buffer[subptr] = '/';
    buffer[subptr+1] = subdirchar;
    }

  DEBUG(D_queue_run) debug_printf("looking in %s\n", buffer);
  if (!(dd = opendir(CS buffer)))
    continue;


  while ((ent = readdir(dd)))
    {
    uschar *name = US ent->d_name;
    int len = Ustrlen(name);


    count++;


    if (i == 0 && len == 1 && isalnum(*name))
      {
      *subcount = *subcount + 1;
      subdirs[*subcount] = *name;
      continue;
      }


    if (len == SPOOL_NAME_LENGTH &&
        Ustrcmp(name + SPOOL_NAME_LENGTH - 2, "-H") == 0)
      {
      queue_filename *next =
        store_get(sizeof(queue_filename) + Ustrlen(name));
      Ustrcpy(next->text, name);
      next->dir_uschar = subdirchar;


      if (randomize)
        if (!yield)
          {
          next->next = NULL;
          yield = last = next;
          }
        else
          {
          if (flags == 0)
	    flags = resetflags;
          if ((flags & 1) == 0)
            {
            next->next = yield;
            yield = next;
            }
          else
            {
            next->next = NULL;
            last->next = next;
            last = next;
            }
          flags = flags >> 1;
          }


      else
        {
        int j;
        next->next = NULL;
        for (j = 0; j < LOG2_MAXNODES; j++)
          if (root[j])
            {
            next = merge_queue_lists(next, root[j]);
            root[j] = j == LOG2_MAXNODES - 1 ? next : NULL;
            }
          else
            {
            root[j] = next;
            break;
            }
        }
      }
    }


  closedir(dd);


  if (i != 0)
    {
    if (!split_spool_directory && count <= 2)
      {
      uschar subdir[2];

      rmdir(CS buffer);
      subdir[0] = subdirchar; subdir[1] = 0;
      rmdir(CS spool_dname(US"msglog", subdir));
      }
    if (subdiroffset > 0) break;
    }


  else if (subdiroffset == 0)
    break;
  }


if (!randomize)
  for (i = 0; i < LOG2_MAXNODES; ++i)
    yield = merge_queue_lists(yield, root[i]);

return yield;
}
