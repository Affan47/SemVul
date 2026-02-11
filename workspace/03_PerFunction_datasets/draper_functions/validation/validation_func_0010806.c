add_to_email_slist(ItemPerson *person, const gchar *bookname)
{
  PerlPluginEmailEntry *ee;
  GList *nodeM;


  nodeM = person->listEMail;
  while(nodeM) {
    ItemEMail *email = nodeM->data;
    ee = g_new0(PerlPluginEmailEntry,1);
    g_return_val_if_fail(ee != NULL, -1);

    if(email->address != NULL) ee->address  = g_strdup(email->address);
    else                       ee->address  = NULL;
    if(bookname != NULL)       ee->bookname = g_strdup(bookname);
    else                       ee->bookname = NULL;

    email_slist->g_slist = g_slist_prepend(email_slist->g_slist,ee);
    nodeM = g_list_next(nodeM);
  }
  return 0;
}
