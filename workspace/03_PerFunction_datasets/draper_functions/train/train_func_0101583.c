dbslayer_log_request(dbslayer_log_manager_t *manager, apr_pool_t *mpool, apr_socket_t *conn,
		const char *request_line, int response_code, int nbytes_sent, apr_int64_t time_toservice) {

	char dstring[1024];
	apr_int64_t current_time = apr_time_now();
	apr_size_t result_size;
	apr_time_exp_t ltime;
	apr_time_exp_lt(&ltime,current_time);
	apr_strftime (dstring, &result_size, sizeof(dstring), "%d/%b/%Y:%H:%M:%S %z", &ltime );

	apr_sockaddr_t *client_addr;
	char *client_ip;
	apr_socket_addr_get(&client_addr,0,conn);
	apr_sockaddr_ip_get(&client_ip,client_addr);
	if(manager->fhandle){
		char *message = apr_pstrcat(mpool,client_ip," - - ","[",dstring,"] \"",request_line,"\" ",
				apr_itoa(mpool,response_code)," ",apr_itoa(mpool,nbytes_sent), " ",apr_ltoa(mpool,time_toservice), "\n",NULL);
		dbslayer_log_message(manager,message);
	}
	dbslayer_log_add_entry(manager,mpool,client_ip,current_time,request_line,response_code,nbytes_sent,time_toservice);
	return 0;
}
