_e_border_pri_norm(E_Border *bd)
{
   if (bd->client.netwm.pid <= 0) return;
   if (bd->client.netwm.pid == getpid()) return;
   _pri_adj(bd->client.netwm.pid,
            e_config->priority, 1, EINA_FALSE,

            EINA_TRUE, EINA_FALSE);


}
