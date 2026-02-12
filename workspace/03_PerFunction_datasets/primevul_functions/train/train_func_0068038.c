void CallbackAndDie(bool succeeded) {


    base::MessageLoop::current()->PostTask(FROM_HERE,
                                           base::Bind(callback_, false));
     delete this;
   }
