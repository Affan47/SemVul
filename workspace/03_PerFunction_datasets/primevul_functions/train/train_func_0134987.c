static void cmd_test_unit_ready(IDEState *s, uint8_t *buf)
{


    ide_atapi_cmd_ok(s);
}
