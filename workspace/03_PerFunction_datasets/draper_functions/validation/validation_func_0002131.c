printEnv(char **envp)
{
#if !VXWORKS && !WINCE
    printf("<H2>Environment Variables</H2>\r\n");
    printf("<P>AUTH_TYPE=%s</P>\r\n", safeGetenv("AUTH_TYPE"));
    printf("<P>CONTENT_LENGTH=%s</P>\r\n", safeGetenv("CONTENT_LENGTH"));
    printf("<P>CONTENT_TYPE=%s</P>\r\n", safeGetenv("CONTENT_TYPE"));
    printf("<P>DOCUMENT_ROOT=%s</P>\r\n", safeGetenv("DOCUMENT_ROOT"));
    printf("<P>GATEWAY_INTERFACE=%s</P>\r\n", safeGetenv("GATEWAY_INTERFACE"));
    printf("<P>HTTP_ACCEPT=%s</P>\r\n", safeGetenv("HTTP_ACCEPT"));
    printf("<P>HTTP_CONNECTION=%s</P>\r\n", safeGetenv("HTTP_CONNECTION"));
    printf("<P>HTTP_HOST=%s</P>\r\n", safeGetenv("HTTP_HOST"));
    printf("<P>HTTP_USER_AGENT=%s</P>\r\n", safeGetenv("HTTP_USER_AGENT"));
    printf("<P>PATH_INFO=%s</P>\r\n", safeGetenv("PATH_INFO"));
    printf("<P>PATH_TRANSLATED=%s</P>\r\n", safeGetenv("PATH_TRANSLATED"));
    printf("<P>QUERY_STRING=%s</P>\r\n", safeGetenv("QUERY_STRING"));
    printf("<P>REMOTE_ADDR=%s</P>\r\n", safeGetenv("REMOTE_ADDR"));
    printf("<P>REQUEST_METHOD=%s</P>\r\n", safeGetenv("REQUEST_METHOD"));
    printf("<P>REQUEST_URI=%s</P>\r\n", safeGetenv("REQUEST_URI"));
    printf("<P>REMOTE_USER=%s</P>\r\n", safeGetenv("REMOTE_USER"));
    printf("<P>SCRIPT_NAME=%s</P>\r\n", safeGetenv("SCRIPT_NAME"));
    printf("<P>SERVER_ADDR=%s</P>\r\n", safeGetenv("SERVER_ADDR"));
    printf("<P>SERVER_NAME=%s</P>\r\n", safeGetenv("SERVER_NAME"));
    printf("<P>SERVER_PORT=%s</P>\r\n", safeGetenv("SERVER_PORT"));
    printf("<P>SERVER_PROTOCOL=%s</P>\r\n", safeGetenv("SERVER_PROTOCOL"));
    printf("<P>SERVER_SOFTWARE=%s</P>\r\n", safeGetenv("SERVER_SOFTWARE"));

    printf("\r\n<H2>All Defined Environment Variables</H2>\r\n");
    if (envp) {
        char    *p;
        int     i;
        for (i = 0, p = envp[0]; envp[i]; i++) {
            p = envp[i];
            printf("<P>%s</P>\r\n", p);
        }
    }
    printf("\r\n");
#endif
}
