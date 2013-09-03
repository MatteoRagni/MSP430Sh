################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
adc.obj: ../adc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="adc.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

help.obj: ../help.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="help.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

isr_hdl.obj: ../isr_hdl.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="isr_hdl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

parser.obj: ../parser.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="parser.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

timer.obj: ../timer.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="timer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

uart.obj: ../uart.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmsp --abi=eabi -g --include_path="C:/CodeComposer/ccsv5/ccs_base/msp430/include" --include_path="C:/CodeComposer/ccsv5/tools/compiler/msp430_4.1.1/include" --advice:power="all" --define=__MSP430G2553__ --define=__DEBUG --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="uart.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


