static void terminate(int sig)
{

    unlink(socket_file);
    exit(0);

}
