ipmi_get_oem_sensor_type_message (uint32_t manufacturer_id,
                                  uint16_t product_id,
                                  uint8_t sensor_type,
                                  unsigned int offset,
                                  char *buf,
                                  unsigned int buflen)
{
  if (!buf || !buflen)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }


  if (manufacturer_id == IPMI_IANA_ENTERPRISE_ID_DELL
      && (product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_R610
          || product_id == IPMI_DELL_PRODUCT_ID_POWEREDGE_R710))
    {
      switch (sensor_type)
        {
        case IPMI_SENSOR_TYPE_OEM_DELL_SYSTEM_PERFORMANCE_DEGRADATION_STATUS:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_dell_system_performance_degradation_status_max_index,
                                      ipmi_sensor_type_oem_dell_system_performance_degradation_status));
        case IPMI_SENSOR_TYPE_OEM_DELL_LINK_TUNING:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_dell_link_tuning_max_index,
                                      ipmi_sensor_type_oem_dell_link_tuning));
        case IPMI_SENSOR_TYPE_OEM_DELL_NON_FATAL_ERROR:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_dell_non_fatal_error_max_index,
                                      ipmi_sensor_type_oem_dell_non_fatal_error));
        case IPMI_SENSOR_TYPE_OEM_DELL_FATAL_IO_ERROR:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_dell_fatal_io_error_max_index,
                                      ipmi_sensor_type_oem_dell_fatal_io_error));
        case IPMI_SENSOR_TYPE_OEM_DELL_UPGRADE:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_dell_upgrade_max_index,
                                      ipmi_sensor_type_oem_dell_upgrade));
        }
    }


  if (manufacturer_id == IPMI_IANA_ENTERPRISE_ID_FUJITSU
      && (product_id >= IPMI_FUJITSU_PRODUCT_ID_MIN
          && product_id <= IPMI_FUJITSU_PRODUCT_ID_MAX))
    {
      switch (sensor_type)
        {
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_I2C_BUS:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_i2c_bus_max_index,
                                      ipmi_sensor_type_oem_fujitsu_i2c_bus));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_SYSTEM_POWER_CONSUMPTION:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_system_power_consumption_max_index,
                                      ipmi_sensor_type_oem_fujitsu_system_power_consumption));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_STATUS:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_memory_status_max_index,
                                      ipmi_sensor_type_oem_fujitsu_memory_status));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY_CONFIG:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_memory_config_max_index,
                                      ipmi_sensor_type_oem_fujitsu_memory_config));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_MEMORY:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_memory_max_index,
                                      ipmi_sensor_type_oem_fujitsu_memory));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_HW_ERROR:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_hw_error_max_index,
                                      ipmi_sensor_type_oem_fujitsu_hw_error));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_SYS_ERROR:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_sys_error_max_index,
                                      ipmi_sensor_type_oem_fujitsu_sys_error));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_FAN_STATUS:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_fan_status_max_index,
                                      ipmi_sensor_type_oem_fujitsu_fan_status));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_STATUS:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_psu_status_max_index,
                                      ipmi_sensor_type_oem_fujitsu_psu_status));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_PSU_REDUNDANCY:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_psu_redundancy_max_index,
                                      ipmi_sensor_type_oem_fujitsu_psu_redundancy));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_FLASH:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_flash_max_index,
                                      ipmi_sensor_type_oem_fujitsu_flash));
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_CONFIG_BACKUP:
          return (_get_event_message (offset,
                                      buf,
                                      buflen,
                                      ipmi_sensor_type_oem_fujitsu_config_backup_max_index,
                                      ipmi_sensor_type_oem_fujitsu_config_backup));

        case IPMI_SENSOR_TYPE_OEM_FUJITSU_COMMUNICATION:
        case IPMI_SENSOR_TYPE_OEM_FUJITSU_EVENT:
        default:
          break;
        }
    }

  SET_ERRNO (EINVAL);
  return (-1);
}
