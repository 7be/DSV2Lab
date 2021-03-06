# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     dsv1_3_Debug
#     dsv1_3_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files (x86)\Analog Devices\VisualDSP 5.1.1


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "dsv1_3_Debug" configuration
#

ifeq ($(MAKECMDGOALS),dsv1_3_Debug)

dsv1_3_Debug : ./Debug/dsv1_3.dxe 

./Debug/isr_s.doj :./isr_s.asm $(VDSP)/Blackfin/include/defBF561.h $(VDSP)/Blackfin/include/def_LPBlackfin.h 
	@echo ".\isr_s.asm"
	$(VDSP)/easmblkfn.exe .\isr_s.asm -proc ADSP-BF561 -file-attr ProjectName=dsv1_3 -g -si-revision 0.5 -o .\Debug\isr_s.doj -MM

Debug/main.doj :main.c $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/cdefBF561.h $(VDSP)/Blackfin/include/defBF561.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h isr.h $(VDSP)/Blackfin/include/sys/exception.h codeclib.h process_data.h 
	@echo ".\main.c"
	$(VDSP)/ccblkfn.exe -c .\main.c -file-attr ProjectName=dsv1_3 -g -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -warn-protos -si-revision 0.5 -proc ADSP-BF561 -o .\Debug\main.doj -MM

./Debug/process_data_s.doj :./process_data_s.asm 
	@echo ".\process_data_s.asm"
	$(VDSP)/easmblkfn.exe .\process_data_s.asm -proc ADSP-BF561 -file-attr ProjectName=dsv1_3 -g -si-revision 0.5 -o .\Debug\process_data_s.doj -MM

./Debug/dsv1_3.dxe :./adsp-BF561-codec.ldf $(VDSP)/Blackfin/lib/bf561_rev_0.5/crtsf561y.doj ./Debug/isr_s.doj ./Debug/main.doj ./Debug/process_data_s.doj $(VDSP)/Blackfin/lib/cplbtab561a.doj $(VDSP)/Blackfin/lib/bf561_rev_0.5/libsmall561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/__initsbsz561.doj $(VDSP)/Blackfin/lib/bf561_rev_0.5/libio561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libc561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libm3free561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libevent561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libx561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libcpp561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libcpprt561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libf64ieee561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libdsp561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libsftflt561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/libetsi561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/Debug/libssl561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/Debug/libdrv561y.dlb $(VDSP)/Blackfin/lib/bf561_rev_0.5/idle561y.doj $(VDSP)/Blackfin/lib/bf561_rev_0.5/librt_fileio561y.dlb ./codeclib.dlb 
	@echo "Linking..."
	$(VDSP)/ccblkfn.exe .\Debug\isr_s.doj .\Debug\main.doj .\Debug\process_data_s.doj -T .\adsp-BF561-codec.ldf -L .\Debug -add-debug-libpaths -flags-link -od,.\Debug -o .\Debug\dsv1_3.dxe -proc ADSP-BF561 -si-revision 0.5 -flags-link -MM

endif

ifeq ($(MAKECMDGOALS),dsv1_3_Debug_clean)

dsv1_3_Debug_clean:
	-$(RM) ".\Debug\isr_s.doj"
	-$(RM) "Debug\main.doj"
	-$(RM) ".\Debug\process_data_s.doj"
	-$(RM) ".\Debug\dsv1_3.dxe"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


