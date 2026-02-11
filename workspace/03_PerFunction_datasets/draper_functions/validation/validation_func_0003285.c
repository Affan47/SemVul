copy_DigestInit(const DigestInit *from, DigestInit *to)
{
memset(to, 0, sizeof(*to));
if(der_copy_utf8string(&(from)->type, &(to)->type)) goto fail;
if((from)->channel) {
(to)->channel = malloc(sizeof(*(to)->channel));
if((to)->channel == NULL) goto fail;
if(der_copy_utf8string(&((from)->channel)->cb_type, &((to)->channel)->cb_type)) goto fail;
if(der_copy_utf8string(&((from)->channel)->cb_binding, &((to)->channel)->cb_binding)) goto fail;
}else
(to)->channel = NULL;
if((from)->hostname) {
(to)->hostname = malloc(sizeof(*(to)->hostname));
if((to)->hostname == NULL) goto fail;
if(der_copy_utf8string((from)->hostname, (to)->hostname)) goto fail;
}else
(to)->hostname = NULL;
return 0;
fail:
free_DigestInit(to);
return ENOMEM;
}
