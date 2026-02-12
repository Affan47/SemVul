sync_cookie_isvalid(Sync_Cookie *testcookie, Sync_Cookie *refcookie)
{

    if ((testcookie && refcookie) &&
        (strcmp(testcookie->cookie_client_signature, refcookie->cookie_client_signature) ||
         strcmp(testcookie->cookie_server_signature, refcookie->cookie_server_signature) ||
         testcookie->cookie_change_info == -1 ||
         testcookie->cookie_change_info > refcookie->cookie_change_info)) {
        return (0);
    }


    return (1);
}
