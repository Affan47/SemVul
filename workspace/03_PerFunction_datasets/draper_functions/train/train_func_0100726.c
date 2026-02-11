example_contact_list_unblock_contacts_async (TpBaseContactList *contact_list,
    TpHandleSet *contacts,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  ExampleContactList *self = EXAMPLE_CONTACT_LIST (contact_list);
  TpIntsetFastIter iter;
  TpHandleSet *changed = tp_handle_set_new (self->priv->contact_repo);
  TpHandle member;

  tp_intset_fast_iter_init (&iter, tp_handle_set_peek (contacts));

  while (tp_intset_fast_iter_next (&iter, &member))
    {
      if (tp_handle_set_remove (self->priv->blocked_contacts, member))
        {
          g_message ("Removing contact %s from blocked list",
              tp_handle_inspect (self->priv->contact_repo, member));
          tp_handle_set_add (changed, member);
        }
    }

  tp_base_contact_list_contact_blocking_changed (contact_list, changed);
  tp_handle_set_destroy (changed);
  tp_simple_async_report_success_in_idle ((GObject *) self, callback,
      user_data, example_contact_list_unblock_contacts_async);
}
