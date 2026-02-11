bkn_suspend_tx(bkn_switch_info_t *sinfo)
{
    struct list_head *list;
    bkn_priv_t *priv = netdev_priv(sinfo->dev);


    netif_stop_queue(priv->dev);
    sinfo->tx.suspends++;

    list_for_each(list, &sinfo->ndev_list) {
        priv = (bkn_priv_t *)list;
        netif_stop_queue(priv->dev);
    }
}
