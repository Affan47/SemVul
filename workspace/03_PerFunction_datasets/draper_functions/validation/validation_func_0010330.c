make_data_cont()
{
  succDataContainer* s = NULL;


  if (reused_entry_value_ != NULL)
    {
      s = reused_entry_value_;
      reused_entry_value_ = NULL;
      return s;
    }


  if (!expansion_stopped_)
    {
      s = new succDataContainer();
      gpt::mem_successor_hash += gpt::heap_overhead + sizeof(succDataContainer);
      s->set_owned_by_hash(true);
      return s;
    }


  if (!table_emptied_)
    {
      advance_to_deletable_entry();
    }


  if (remove_ptr_ == NULL)
    {
      s = new succDataContainer();
      s->set_owned_by_hash(false);
      return s;
    }


  hashEntry_t<succDataContainer*>* ptr_helper = remove_ptr_;
  remove_ptr_ = remove_ptr_->prev_;
  remove_ptr_->next_ = ptr_helper->next_;

  if (ptr_helper->next_ == NULL)
    {
      table_oldest_entries_[remove_idx_] = remove_ptr_;
    }

  s = ptr_helper->value();
  s->reset();
  ptr_helper->prev_ = NULL;
  ptr_helper->next_ = NULL;
  ptr_helper->state_ = NULL;
  ptr_helper->value_ = NULL;
  ptr_helper->reset_bits(0xffffffff);
  reused_entry_ = ptr_helper;
  return s;
}
