istrport_get_byte(ScmInputStrPort *port)
{
    return (*port->cur) ? *port->cur++ : SCM_ICHAR_EOF;
}
