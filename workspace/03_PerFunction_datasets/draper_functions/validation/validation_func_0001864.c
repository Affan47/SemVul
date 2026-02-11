key_register() const{
    if(NULL == get_key())
        return;
    singleton<detail::ktmap>::get_mutable_instance().insert(this);
}
