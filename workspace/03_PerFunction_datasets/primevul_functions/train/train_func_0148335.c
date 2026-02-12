static bool vmxnet3_validate_queues(VMXNET3State *s)
{


    if (s->txq_num > VMXNET3_DEVICE_MAX_TX_QUEUES) {
        qemu_log_mask(LOG_GUEST_ERROR, "vmxnet3: Bad TX queues number: %d\n",
                      s->txq_num);
        return false;
    }

    if (s->rxq_num > VMXNET3_DEVICE_MAX_RX_QUEUES) {
        qemu_log_mask(LOG_GUEST_ERROR, "vmxnet3: Bad RX queues number: %d\n",
                      s->rxq_num);
        return false;
    }

    return true;
}
