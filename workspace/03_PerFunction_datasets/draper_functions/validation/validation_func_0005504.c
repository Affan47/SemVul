wm8994_gpio_fn(u16 fn)
{
	switch (fn) {
	case WM8994_GP_FN_PIN_SPECIFIC:
		return "pin-specific";
	case WM8994_GP_FN_GPIO:
		return "GPIO";
	case WM8994_GP_FN_SDOUT:
		return "SDOUT";
	case WM8994_GP_FN_IRQ:
		return "IRQ";
	case WM8994_GP_FN_TEMPERATURE:
		return "Temperature";
	case WM8994_GP_FN_MICBIAS1_DET:
		return "MICBIAS1 detect";
	case WM8994_GP_FN_MICBIAS1_SHORT:
		return "MICBIAS1 short";
	case WM8994_GP_FN_MICBIAS2_DET:
		return "MICBIAS2 detect";
	case WM8994_GP_FN_MICBIAS2_SHORT:
		return "MICBIAS2 short";
	case WM8994_GP_FN_FLL1_LOCK:
		return "FLL1 lock";
	case WM8994_GP_FN_FLL2_LOCK:
		return "FLL2 lock";
	case WM8994_GP_FN_SRC1_LOCK:
		return "SRC1 lock";
	case WM8994_GP_FN_SRC2_LOCK:
		return "SRC2 lock";
	case WM8994_GP_FN_DRC1_ACT:
		return "DRC1 activity";
	case WM8994_GP_FN_DRC2_ACT:
		return "DRC2 activity";
	case WM8994_GP_FN_DRC3_ACT:
		return "DRC3 activity";
	case WM8994_GP_FN_WSEQ_STATUS:
		return "Write sequencer";
	case WM8994_GP_FN_FIFO_ERROR:
		return "FIFO error";
	case WM8994_GP_FN_OPCLK:
		return "OPCLK";
	case WM8994_GP_FN_THW:
		return "Thermal warning";
	case WM8994_GP_FN_DCS_DONE:
		return "DC servo";
	case WM8994_GP_FN_FLL1_OUT:
		return "FLL1 output";
	case WM8994_GP_FN_FLL2_OUT:
		return "FLL1 output";
	default:
		return "Unknown";
	}
}
