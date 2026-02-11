explain_buffer_errno_shmctl_system_call(explain_string_buffer_t *sb, int errnum,
    int shmid, int command, struct shmid_ds *data)
{
    (void)errnum;
    explain_string_buffer_puts(sb, "shmctl(shmid = ");
    explain_buffer_int(sb, shmid);
    explain_string_buffer_puts(sb, ", command = ");
    explain_buffer_shmctl_command(sb, command);
    explain_string_buffer_puts(sb, ", data = ");
    switch (command)
    {
#ifdef IPC_SET
    case IPC_SET:
        explain_buffer_shmid_ds(sb, data, 0);
        break;
#endif

#ifdef IPC_INFO
    case IPC_INFO:
#endif
#ifdef IPC_RMID
    case IPC_RMID:
#endif
#ifdef IPC_STAT
    case IPC_STAT:
#endif
#ifdef SHM_INFO
    case SHM_INFO:
#endif
#ifdef SHM_LOCK
    case SHM_LOCK:
#endif
#ifdef SHM_STAT
    case SHM_STAT:
#endif
#ifdef SHM_UNLOCK
    case SHM_UNLOCK:
#endif
    default:
        explain_buffer_pointer(sb, data);
        break;
    }
    explain_string_buffer_putc(sb, ')');
}
