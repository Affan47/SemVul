dbpool_conn_destroy(DBPoolConn *conn)
{
    gw_assert(conn != NULL);

    if (conn->conn != NULL)
        conn->pool->db_ops->close(conn->conn);

    gw_free(conn);
}
