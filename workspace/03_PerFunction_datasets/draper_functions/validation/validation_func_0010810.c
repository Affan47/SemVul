store_server_fields(TABLE *table, FOREIGN_SERVER *server)
{

  table->use_all_columns();


  if (server->host)
    table->field[1]->store(server->host,
                           (uint) strlen(server->host), system_charset_info);
  if (server->db)
    table->field[2]->store(server->db,
                           (uint) strlen(server->db), system_charset_info);
  if (server->username)
    table->field[3]->store(server->username,
                           (uint) strlen(server->username), system_charset_info);
  if (server->password)
    table->field[4]->store(server->password,
                           (uint) strlen(server->password), system_charset_info);
  if (server->port > -1)
    table->field[5]->store(server->port);

  if (server->socket)
    table->field[6]->store(server->socket,
                           (uint) strlen(server->socket), system_charset_info);
  if (server->scheme)
    table->field[7]->store(server->scheme,
                           (uint) strlen(server->scheme), system_charset_info);
  if (server->owner)
    table->field[8]->store(server->owner,
                           (uint) strlen(server->owner), system_charset_info);
}
