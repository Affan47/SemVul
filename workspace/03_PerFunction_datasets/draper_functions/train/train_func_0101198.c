_ecore_con_socks_svr_init_v4(Ecore_Con_Server *svr, Ecore_Con_Socks_v4 *v4)
{
   size_t addrlen, buflen, ulen = 1;
   unsigned char *sbuf;

   addrlen = v4->lookup ? strlen(svr->name) + 1 : 0;
   if (v4->username) ulen += v4->ulen;
   buflen = sizeof(char) * (8  + ulen + addrlen);
   sbuf = malloc(buflen);
   if (!sbuf)
     {
        ecore_con_event_server_error(svr, "Memory allocation failure!");
        _ecore_con_server_kill(svr);
        return EINA_FALSE;
     }

   sbuf[0] = 4;
   sbuf[1] = v4->bind ? 2 : 1;
   sbuf[2] = svr->port >> 8;
   sbuf[3] = svr->port & 0xff;
   if (addrlen)
     {
        sbuf[4] = sbuf[5] = sbuf[6] = 0;
        sbuf[7] = 1;
     }
   else

     memcpy(sbuf + 4, svr->ecs_addr, 4);
   if (v4->username)
     memcpy(sbuf + 8, v4->username, ulen);
   else
     sbuf[8] = 0;
   if (addrlen) memcpy(sbuf + 8 + ulen, svr->name, addrlen);

   svr->ecs_buf = eina_binbuf_manage_new_length(sbuf, buflen);
   return EINA_TRUE;
}
