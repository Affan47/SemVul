wap_event_destroy(WAPEvent *event) {
	if (event == NULL)
		return;

	wap_event_assert(event);

	switch (event->type) {
	#define WAPEVENT(name, prettyname, fields) \
		case name: \
			{ struct name *p = &event->u.name; fields; } \
			break;
	#define OCTSTR(name) octstr_destroy(p->name);
	#define OPTIONAL_OCTSTR(name) octstr_destroy(p->name);
	#define INTEGER(name) p->name = 0;
    #define WTLSPDUS(name) debug("wap.events",0,"You need to create wtls_pdulist_destroy!");
	#define HTTPHEADER(name) http_destroy_headers(p->name);
	#define ADDRTUPLE(name) wap_addr_tuple_destroy(p->name);
	#define CAPABILITIES(name) wsp_cap_destroy_list(p->name);
	#include "wap_events.def"
	default:
		panic(0, "Unknown WAPEvent type %d", (int) event->type);
	}
	gw_free(event);
}
