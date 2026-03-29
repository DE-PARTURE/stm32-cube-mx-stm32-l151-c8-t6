# STM32CubeMX-STM32L151C8T6

This repository contains STM32L151C8T6 demo projects generated with STM32CubeMX v6.0.0. It includes basic peripheral examples for GPIO, EXTI, USART, I2C, timer interrupt, PWM, input capture, low-power mode, and ADC.

## Contents

- `01_LED`: GPIO / LED example
- `02_EXTI`: external interrupt example
- `03_USART`: USART communication example
- `04_IIC`: I2C communication example
- `05_TIM_Interrupt`: timer interrupt example
- `06_TIM_PWM`: PWM example
- `07_TIM_InputCaputer`: timer input capture example
- `08_LowPowerMode`: low-power mode example
- `09_ADC`: ADC example

## Toolchain

- MCU: STM32L151C8T6
- Tools: STM32CubeMX v6.0.0, Keil MDK
- Framework: STM32 HAL / CMSIS

## Usage

1. Open the corresponding `.ioc` file if you want to adjust peripheral settings in STM32CubeMX.
2. Open the `.uvprojx` project under `MDK-ARM` if you want to build directly in Keil.
3. Flash the generated binary to the board and verify the target function.

## License

This repository is licensed under the [MIT License](LICENSE).
