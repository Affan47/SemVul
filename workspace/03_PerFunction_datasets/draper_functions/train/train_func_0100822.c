wake()
{
    m_sleeping = false;
    Dprintf(("TMRL::wake\n"));
    if (  t1con->get_tmr1on() && t1con->get_tmr1cs() < 2)
    {
	update();
    }
}
