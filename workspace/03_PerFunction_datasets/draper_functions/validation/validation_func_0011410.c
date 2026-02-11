glusterd_brickinfo_delete (glusterd_brickinfo_t *brickinfo)
{
        int32_t         ret = -1;

        GF_ASSERT (brickinfo);

        list_del_init (&brickinfo->brick_list);

        if (brickinfo->logfile)
                GF_FREE (brickinfo->logfile);
        GF_FREE (brickinfo);

        ret = 0;

        return ret;
}
