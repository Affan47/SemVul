nau8825_interrupt(int irq, void *data)
{
	struct nau8825 *nau8825 = (struct nau8825 *)data;
	struct regmap *regmap = nau8825->regmap;
	int active_irq, clear_irq = 0, event = 0, event_mask = 0;

	regmap_read(regmap, NAU8825_REG_IRQ_STATUS, &active_irq);

	if ((active_irq & NAU8825_JACK_EJECTION_IRQ_MASK) ==
		NAU8825_JACK_EJECTION_DETECTED) {

		nau8825_eject_jack(nau8825);
		event_mask |= SND_JACK_HEADSET;
		clear_irq = NAU8825_JACK_EJECTION_IRQ_MASK;
	} else if (active_irq & NAU8825_KEY_SHORT_PRESS_IRQ) {
		int key_status;

		regmap_read(regmap, NAU8825_REG_INT_CLR_KEY_STATUS,
			&key_status);


		nau8825->button_pressed = nau8825_button_decode(
			key_status >> 8);

		event |= nau8825->button_pressed;
		event_mask |= NAU8825_BUTTONS;
		clear_irq = NAU8825_KEY_SHORT_PRESS_IRQ;
	} else if (active_irq & NAU8825_KEY_RELEASE_IRQ) {
		event_mask = NAU8825_BUTTONS;
		clear_irq = NAU8825_KEY_RELEASE_IRQ;
	} else if (active_irq & NAU8825_HEADSET_COMPLETION_IRQ) {
		if (nau8825_is_jack_inserted(regmap)) {
			event |= nau8825_jack_insert(nau8825);
		} else {
			dev_warn(nau8825->dev, "Headset completion IRQ fired but no headset connected\n");
			nau8825_eject_jack(nau8825);
		}

		event_mask |= SND_JACK_HEADSET;
		clear_irq = NAU8825_HEADSET_COMPLETION_IRQ;
	}

	if (!clear_irq)
		clear_irq = active_irq;

	regmap_write(regmap, NAU8825_REG_INT_CLR_KEY_STATUS, clear_irq);

	if (event_mask)
		snd_soc_jack_report(nau8825->jack, event, event_mask);

	return IRQ_HANDLED;
}
