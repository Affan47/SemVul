remove_edge(int argc, char* argv[]) {
	int V, W;
    int id1, id2;
    MesgOrder message;
    MesgInfo reply;
    if (argc != 4)
        print_usage_info(argv[0]);
	if ((V = myatoi(argv[2])) < 0)
        print_usage_info(argv[0]);
	if ((W = myatoi(argv[3])) < 0)
        print_usage_info(argv[0]);

    message.type = getpid();
    message.command = DEL;
    message.len = 2;
    message.data[0] = V;
    message.data[1] = W;
    id1 = init_queue(MKEY1, 0);
    send_order(id1, &message, 4 * sizeof(int));
    id2 = init_queue(MKEY2, 0);
    receive_info(id2, &reply, getpid());
    return reply.command;
}
