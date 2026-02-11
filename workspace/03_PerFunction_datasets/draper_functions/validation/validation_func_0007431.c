explain_buffer_ebadf(explain_string_buffer_t *sb, int fildes,
    const char *caption)
{
    if (explain_buffer_check_fildes_range(sb, fildes, caption) >= 0)
        explain_string_buffer_puts(sb, ", ");
    explain_string_buffer_printf_gettext
    (
        sb,


        i18n("%s does not refer to an open file"),
        caption
    );
    explain_buffer_software_error(sb);
}
