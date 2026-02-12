repodata_add_array(Repodata *data, Id handle, Id keyname, Id keytype, int entrysize)
{
  int oldsize;
  Id *ida, *pp, **ppp;


  if (handle == data->lasthandle && data->keys[data->lastkey].name == keyname && data->keys[data->lastkey].type == keytype && data->attriddatalen == data->lastdatalen)
    {

      data->attriddata = solv_extend(data->attriddata, data->attriddatalen, entrysize, sizeof(Id), REPODATA_ATTRIDDATA_BLOCK);
      data->attriddatalen--;
      data->lastdatalen += entrysize;
      return;
    }

  ppp = repodata_get_attrp(data, handle);
  pp = *ppp;
  if (pp)
    {
      for (; *pp; pp += 2)
        if (data->keys[*pp].name == keyname)
          break;
    }
  if (!pp || !*pp || data->keys[*pp].type != keytype)
    {

      Repokey key;
      Id keyid;
      key.name = keyname;
      key.type = keytype;
      key.size = 0;
      key.storage = KEY_STORAGE_INCORE;
      data->attriddata = solv_extend(data->attriddata, data->attriddatalen, entrysize + 1, sizeof(Id), REPODATA_ATTRIDDATA_BLOCK);
      keyid = repodata_key2id(data, &key, 1);
      repodata_insert_keyid(data, handle, keyid, data->attriddatalen, 1);
      data->lasthandle = handle;
      data->lastkey = keyid;
      data->lastdatalen = data->attriddatalen + entrysize + 1;
      return;
    }
  oldsize = 0;
  for (ida = data->attriddata + pp[1]; *ida; ida += entrysize)
    oldsize += entrysize;
  if (ida + 1 == data->attriddata + data->attriddatalen)
    {

      data->attriddata = solv_extend(data->attriddata, data->attriddatalen, entrysize, sizeof(Id), REPODATA_ATTRIDDATA_BLOCK);
      data->attriddatalen--;
    }
  else
    {

      data->attriddata = solv_extend(data->attriddata, data->attriddatalen,  oldsize + entrysize + 1, sizeof(Id), REPODATA_ATTRIDDATA_BLOCK);
      memcpy(data->attriddata + data->attriddatalen, data->attriddata + pp[1], oldsize * sizeof(Id));
      pp[1] = data->attriddatalen;
      data->attriddatalen += oldsize;
    }
  data->lasthandle = handle;
  data->lastkey = *pp;
  data->lastdatalen = data->attriddatalen + entrysize + 1;
}
