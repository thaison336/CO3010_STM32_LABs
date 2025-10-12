################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
BUILD_ARTIFACT_NAME := lab1_ex2
========
BUILD_ARTIFACT_NAME := lab1_ex1
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
lab1_ex2.elf \

MAP_FILES += \
lab1_ex2.map \
========
lab1_ex1.elf \

MAP_FILES += \
lab1_ex1.map \
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
lab1_ex2.list \

OBJCOPY_HEX += \
lab1_ex2.hex \
========
lab1_ex1.list \

OBJCOPY_HEX += \
lab1_ex1.hex \
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile


# All Target
all: main-build

# Main-build Target
<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
main-build: lab1_ex2.elf secondary-outputs

# Tool invocations
lab1_ex2.elf lab1_ex2.map: $(OBJS) $(USER_OBJS) C:\Users\DELL\Documents\_PROJECTS\GitHub\CO3010_STM32_LABs\CO3010_STM32_Lab_1\Ex2\STM32\STM32F103C6UX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "lab1_ex2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\DELL\Documents\_PROJECTS\GitHub\CO3010_STM32_LABs\CO3010_STM32_Lab_1\Ex2\STM32\STM32F103C6UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lab1_ex2.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
========
main-build: lab1_ex1.elf secondary-outputs

# Tool invocations
lab1_ex1.elf lab1_ex1.map: $(OBJS) $(USER_OBJS) C:\Users\DELL\Documents\_PROJECTS\GitHub\CO3010_STM32_LABs\CO3010_STM32_Lab_1\Ex1\STM32\STM32F103C6UX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "lab1_ex1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\DELL\Documents\_PROJECTS\GitHub\CO3010_STM32_LABs\CO3010_STM32_Lab_1\Ex1\STM32\STM32F103C6UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="lab1_ex1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
lab1_ex2.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lab1_ex2.list"
	@echo 'Finished building: $@'
	@echo ' '

lab1_ex2.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "lab1_ex2.hex"
========
lab1_ex1.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "lab1_ex1.list"
	@echo 'Finished building: $@'
	@echo ' '

lab1_ex1.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "lab1_ex1.hex"
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
<<<<<<<< HEAD:CO3010_STM32_Lab_1/Ex2/STM32/Debug/makefile
	-$(RM) default.size.stdout lab1_ex2.elf lab1_ex2.hex lab1_ex2.list lab1_ex2.map
========
	-$(RM) default.size.stdout lab1_ex1.elf lab1_ex1.hex lab1_ex1.list lab1_ex1.map
>>>>>>>> Ex1:CO3010_STM32_Lab_1/Ex1/STM32/Debug/makefile
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
