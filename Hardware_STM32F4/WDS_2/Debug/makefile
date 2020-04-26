################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
WDS_2.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
WDS_2.list \

OBJCOPY_BIN += \
WDS_2.bin \


# All Target
all: WDS_2.elf secondary-outputs

# Tool invocations
WDS_2.elf: $(OBJS) $(USER_OBJS) C:\Users\Konrad\Desktop\Materialy_studia\AiR_6sem\Wizualizacja_danych_sens\Projekt\Tesciki_proby\QT_Skier_01\Hardware_STM32F4\WDS_2\STM32F411VETX_FLASH.ld
	arm-none-eabi-gcc -o "WDS_2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Konrad\Desktop\Materialy_studia\AiR_6sem\Wizualizacja_danych_sens\Projekt\Tesciki_proby\QT_Skier_01\Hardware_STM32F4\WDS_2\STM32F411VETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="WDS_2.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

WDS_2.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "WDS_2.list"
	@echo 'Finished building: $@'
	@echo ' '

WDS_2.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "WDS_2.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
