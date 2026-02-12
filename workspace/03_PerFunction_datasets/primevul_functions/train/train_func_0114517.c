PosibErr<int> Config::commit(Entry * entry, Conv * conv)
  {
    PosibErr<const KeyInfo *> pe = keyinfo(entry->key);
    {
      if (pe.has_err()) goto error;

      const KeyInfo * ki = pe;

      entry->key = ki->name;


      int place_holder = entry->place_holder;

      if (conv && ki->flags & KEYINFO_UTF8)
        entry->value = (*conv)(entry->value);

      if (ki->type != KeyInfoList && list_action(entry->action)) {
        pe = make_err(key_not_list, entry->key);
        goto error;
      }

      assert(ki->def != 0);

      String value(entry->action == Reset ? get_default(ki) : entry->value);

      switch (ki->type) {

      case KeyInfoBool: {

        bool val;

        if  (value.empty() || entry->place_holder != -1) {


          entry->value = "true";
          val = true;
          place_holder = -1;
        } else if (value == "true") {
          val = true;
        } else if (value == "false") {
          val = false;
        } else {
          pe = make_err(bad_value, entry->key, value,


                        _("either \"true\" or \"false\""));
          goto error;
        }

        NOTIFY_ALL(item_updated(ki, val));
        break;

      } case KeyInfoString:

        NOTIFY_ALL(item_updated(ki, value));
        break;

      case KeyInfoInt:
      {
        int num;

        if (sscanf(value.str(), "%i", &num) == 1 && num >= 0) {
          NOTIFY_ALL(item_updated(ki, num));
        } else {
          pe = make_err(bad_value, entry->key, value, _("a positive integer"));
          goto error;
        }

        break;
      }
      case KeyInfoList:

        NOTIFY_ALL(list_updated(ki));
        break;

      }
      return place_holder;
    }
  error:
    entry->action = NoOp;
    if (!entry->file.empty())
      return pe.with_file(entry->file, entry->line_num);
    else
      return (PosibErrBase &)pe;
  }
