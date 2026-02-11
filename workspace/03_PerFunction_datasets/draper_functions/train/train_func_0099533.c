run(Workqueue* workqueue)
{
  Read_relocs_data* rd = new Read_relocs_data;
  this->object_->read_relocs(rd);
  this->object_->set_relocs_data(rd);
  this->object_->release();


  if (parameters->options().gc_sections()
      || parameters->options().icf_enabled())
    {
      workqueue->queue_next(new Gc_process_relocs(this->symtab_,
                                                  this->layout_,
                                                  this->object_, rd,
                                                  this->this_blocker_,
						  this->next_blocker_));
    }
  else
    {
      workqueue->queue_next(new Scan_relocs(this->symtab_, this->layout_,
					    this->object_, rd,
                                            this->this_blocker_,
					    this->next_blocker_));
    }
}
