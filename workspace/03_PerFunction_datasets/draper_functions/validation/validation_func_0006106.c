attribute_flush(void)
{
  struct player *pplayer = client_player();

  if (!pplayer || client_is_observer() || !pplayer->is_alive) {
    return;
  }

  fc_assert_ret(NULL != attribute_hash);

  if (0 == attribute_hash_size(attribute_hash))
    return;

  if (pplayer->attribute_block.data) {
    free(pplayer->attribute_block.data);
    pplayer->attribute_block.data = NULL;
  }

  serialize_hash(attribute_hash, &pplayer->attribute_block.data,
                 &pplayer->attribute_block.length);
  send_attribute_block(pplayer, &client.conn);
}
