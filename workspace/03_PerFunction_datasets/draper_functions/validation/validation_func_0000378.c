s5k4ecgx_gpio_set_value(struct s5k4ecgx *priv, int id, u32 val)
{
	if (!gpio_is_valid(priv->gpio[id].gpio))
		return 0;
	gpio_set_value(priv->gpio[id].gpio, val);

	return 1;
}
