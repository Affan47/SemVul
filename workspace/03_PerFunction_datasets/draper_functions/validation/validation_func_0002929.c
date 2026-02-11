icalclassify_request_new(struct icalclassify_parts *comp,
				    struct icalclassify_parts *match,
				    const char* user)
{


    icalclassify_pre
    (void)user;

    if(match->c==0 && comp->method == ICAL_METHOD_REQUEST){
	rtrn = 1;
    }

    icalclassify_post

}
