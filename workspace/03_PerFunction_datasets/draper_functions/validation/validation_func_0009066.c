unlink_dyn(CVmPoolDynObj *obj)
{


    if (obj->get_prev() != 0)
        obj->get_prev()->set_next(obj->get_next());
    else
        dyn_head_ = obj->get_next();


    if (obj->get_next() != 0)
        obj->get_next()->set_prev(obj);
    else
        dyn_tail_ = obj->get_prev();
}
