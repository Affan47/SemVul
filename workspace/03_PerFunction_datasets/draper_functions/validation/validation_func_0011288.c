oxygen_write_eeprom(struct oxygen *chip, unsigned int index, u16 value)
{
	unsigned int timeout;

	oxygen_write16(chip, OXYGEN_EEPROM_DATA, value);
	oxygen_write8(chip, OXYGEN_EEPROM_CONTROL,
		      index | OXYGEN_EEPROM_DIR_WRITE);
	for (timeout = 0; timeout < 10; ++timeout) {
		msleep(1);
		if (!(oxygen_read8(chip, OXYGEN_EEPROM_STATUS)
		      & OXYGEN_EEPROM_BUSY))
			return;
	}
	dev_err(chip->card->dev, "EEPROM write timeout\n");
}
