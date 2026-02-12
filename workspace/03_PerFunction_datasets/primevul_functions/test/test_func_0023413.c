void set_param_func(uchar **pos, ulong len)
  {


    const Type_handler *h= Item_param::type_handler();
    value.set_handler(h);
    h->Item_param_set_param_func(this, pos, len);
  }
