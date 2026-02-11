test_qof_session_swap_data (Fixture *fixture, gconstpointer pData)
{
    QofSession *session2 = NULL;
    QofBackend *be1 = NULL, *be2 = NULL;
    QofBook *book1 = NULL, *book2 = NULL;


    g_assert (fixture->session);
    session2 = qof_session_new ();
    g_assert (session2);
    g_assert (fixture->session != session2);
    be1 = g_new0 (QofBackend, 1);
    g_assert (be1);
    be2 = g_new0 (QofBackend, 1);
    g_assert (be2);
    fixture->session->backend = be1;
    session2->backend = be2;
    book1 = fixture->session->book;
    book2 = session2->book;
    g_assert (book1);
    g_assert (book2);
    qof_book_set_backend (book1, fixture->session->backend);
    qof_book_set_backend (book2, session2->backend);


    g_test_message ("Test book lists are swapped and backend for each book is swapped");
    qof_session_swap_data (fixture->session, session2);
    g_assert (fixture->session->book == book2);
    g_assert (session2->book == book1);

    qof_session_destroy (session2);
}
