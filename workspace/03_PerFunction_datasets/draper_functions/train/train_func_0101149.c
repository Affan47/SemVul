xaccInitTransaction (Transaction * trans, QofBook *book)
{
    ENTER ("trans=%p", trans);
    qof_instance_init_data (&trans->inst, GNC_ID_TRANS, book);
    LEAVE (" ");
}
