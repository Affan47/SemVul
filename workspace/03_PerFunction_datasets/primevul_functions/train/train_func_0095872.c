static int checkGrafana(const struct mg_connection *conn,
			const struct mg_request_info *request_info) {

  if(!strcmp(request_info->request_method, "OPTIONS")
    && !strncmp(request_info->uri, GRAFANA_URL, strlen(GRAFANA_URL)))

    return(1);

  return(0);
}
