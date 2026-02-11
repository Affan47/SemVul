remove_proc (size_t i)
{
  ACE_TRACE ("ACE_Process_Manager::remove_proc");


  if (this->process_table_[i].exit_notify_ != 0)
    {
      this->process_table_[i].exit_notify_->handle_close
        (this->process_table_[i].process_->gethandle(),
         0);
      this->process_table_[i].exit_notify_ = 0;
    }

#if defined (ACE_WIN32)
  ACE_Reactor * const r = this->reactor ();
  if (r != 0)
    r->remove_handler (this->process_table_[i].process_->gethandle (),
                       ACE_Event_Handler::DONT_CALL);
#endif

  this->process_table_[i].process_->unmanage ();

  this->process_table_[i].process_ = 0;

  this->current_count_--;

  if (this->current_count_ > 0)


    this->process_table_[i] =
      this->process_table_[this->current_count_];

  return 0;
}
