send_request(int fd, char *buff, char *lec_addr, char *elan_name)
{
        char *tmp;
        int retval;
        struct le_config_frame *frame;

        frame = (struct le_config_frame *)buff;
        frame->marker   = htons(0xff00);
        frame->protocol = 0x01;
        frame->version  = 0x01;
        frame->opcode   = htons(0x0001);
        frame->tran_id  = htonl(42);
        frame->flags    = htons(0x002);
        memcpy(frame->src_atm_addr, lec_addr, ATM_ESA_LEN);
        frame->num_tlvs = 1;
        if (elan_name != NULL) {
                strcpy(frame->elan_name, elan_name);
                frame->elan_name_size = strlen(elan_name);
        }


        tmp = buff + sizeof(struct le_config_frame);
        *(uint32_t *)tmp = htonl(TLV_MPOA_DEVICE_TYPE);
        tmp += 4;

        *tmp++ = 22;
        *tmp++ = MPC;
        *tmp++ = 0;
        memcpy(tmp, lec_addr, ATM_ESA_LEN); tmp += ATM_ESA_LEN;

        retval = write(fd, buff, tmp - buff);
        if (retval < 0 || retval != (tmp - buff)) return -1;

        return 0;
}
