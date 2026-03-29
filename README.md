# STM32CubeMX-STM32L151C8T6

基于 STM32CubeMX V6.0.0 生成的 STM32L151C8T6 示例工程集合，包含 GPIO、中断、串口、IIC、定时器、PWM、输入捕获、低功耗和 ADC 等常见外设练习，适合作为 STM32L1 系列入门和功能验证工程。

## 仓库内容

- `01_LED`：GPIO/LED 基础实验
- `02_EXTI`：外部中断实验
- `03_USART`：串口通信实验
- `04_IIC`：IIC 通信实验
- `05_TIM_Interrupt`：定时器中断实验
- `06_TIM_PWM`：PWM 输出实验
- `07_TIM_InputCaputer`：定时器输入捕获实验
- `08_LowPowerMode`：低功耗模式实验
- `09_ADC`：ADC 采样实验

## 工程结构

每个实验目录通常包含以下内容：

- `.ioc`：STM32CubeMX 工程配置文件
- `Core`：应用层源码
- `Drivers`：HAL 与 CMSIS 驱动
- `MDK-ARM`：Keil MDK 工程文件和生成产物

## 开发环境

- 芯片：STM32L151C8T6
- 工具：STM32CubeMX V6.0.0、Keil MDK
- 框架：STM32 HAL / CMSIS

## 使用方式

1. 选择一个实验目录。
2. 如需修改外设配置，可先打开对应 `.ioc` 文件。
3. 如需直接编译，可使用 Keil 打开 `MDK-ARM` 下的 `.uvprojx` 工程。
4. 下载到开发板后进行功能验证。

## 说明

- 仓库是按实验拆分的多工程集合，不是单一应用。
- 某些目录中包含编译产物、调试配置和 HEX 文件，便于直接验证。

## License

本仓库采用 [MIT License](LICENSE)。
