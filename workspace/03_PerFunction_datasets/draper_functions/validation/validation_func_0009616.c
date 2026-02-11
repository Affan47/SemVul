isert_cma_handler(struct rdma_cm_id *cma_id, struct rdma_cm_event *event)
{
	struct isert_np *isert_np = cma_id->context;
	int ret = 0;

	isert_info("%s (%d): status %d id %p np %p\n",
		   rdma_event_msg(event->event), event->event,
		   event->status, cma_id, cma_id->context);

	if (isert_np->cm_id == cma_id)
		return isert_np_cma_handler(cma_id->context, event->event);

	switch (event->event) {
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		ret = isert_connect_request(cma_id, event);
		if (ret)
			isert_err("failed handle connect request %d\n", ret);
		break;
	case RDMA_CM_EVENT_ESTABLISHED:
		isert_connected_handler(cma_id);
		break;
	case RDMA_CM_EVENT_ADDR_CHANGE:
	case RDMA_CM_EVENT_DISCONNECTED:
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
	case RDMA_CM_EVENT_TIMEWAIT_EXIT:
		ret = isert_disconnected_handler(cma_id, event->event);
		break;
	case RDMA_CM_EVENT_REJECTED:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_CONNECT_ERROR:
		ret = isert_connect_error(cma_id);
		break;
	default:
		isert_err("Unhandled RDMA CMA event: %d\n", event->event);
		break;
	}

	return ret;
}
