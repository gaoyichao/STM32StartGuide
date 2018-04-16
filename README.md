
系统时钟计算方法：
f(VCO clock) = f(PLL clock input) * PLLN / PLLM
f(PLL general clock output) = f(VCO clock) / PLLP
f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ

PLLI2S时钟计算方法：
f(VCO clock) = f(PLLI2S clock input) * PLLI2SN / PLLM
f(PLLI2S clock output) = f(VCO clock) / PLLI2SR

