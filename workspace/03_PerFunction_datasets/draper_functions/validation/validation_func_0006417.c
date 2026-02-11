finalise_command ()
{


    if (shutting_down && processed_seqnum == sent_seqnum.get ()) {
        process_unplug ();
        send_term_ack (owner);
        delete this;
    }
}
