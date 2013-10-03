# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := libsynthax.a
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode
  TARGET := libsynthax.a
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

OBJECTS := \
  $(OBJDIR)/audio_util_1e6dca20.o \
  $(OBJDIR)/juce_file_io_23efa0cc.o \
  $(OBJDIR)/logger_f86ce265.o \
  $(OBJDIR)/kiss_fft_5150b3c.o \
  $(OBJDIR)/kiss_fftr_9d8d5580.o \
  $(OBJDIR)/WaveTableOsc_3abb7d69.o \
  $(OBJDIR)/adsr_139b05cc.o \
  $(OBJDIR)/lfo_c5789d75.o \
  $(OBJDIR)/piecewise_linear_aff4c7fc.o \
  $(OBJDIR)/wave_table_dcbad452.o \
  $(OBJDIR)/adsr_cea0a9de.o \
  $(OBJDIR)/gain_8dec311b.o \
  $(OBJDIR)/lfo_dc052f23.o \
  $(OBJDIR)/piecewise_linear_c0dae10e.o \
  $(OBJDIR)/add_ff08cb97.o \
  $(OBJDIR)/cosine_4156b6cd.o \
  $(OBJDIR)/multiply_6b228eb8.o \
  $(OBJDIR)/sine_4c643221.o \
  $(OBJDIR)/subtract_8c390ba8.o \
  $(OBJDIR)/mixer_99b9d5.o \
  $(OBJDIR)/switcher_7d022e1f.o \
  $(OBJDIR)/sine_amp_mod_2ed81fc5.o \
  $(OBJDIR)/sine_phase_mod_33978a3c.o \
  $(OBJDIR)/saw_f6196e2a.o \
  $(OBJDIR)/sine_67d95836.o \
  $(OBJDIR)/square_f09e7dc6.o \
  $(OBJDIR)/triangle_a02d7431.o \
  $(OBJDIR)/wave_table_57477db8.o \
  $(OBJDIR)/saw_f8c632a.o \
  $(OBJDIR)/sine_7cc50336.o \
  $(OBJDIR)/square_794b68c6.o \
  $(OBJDIR)/triangle_b14b9f31.o \
  $(OBJDIR)/adsr_635568b2.o \
  $(OBJDIR)/constant_b2e4d814.o \
  $(OBJDIR)/input_static_da5d13f3.o \
  $(OBJDIR)/lfo_e91345cf.o \
  $(OBJDIR)/noise_f9238af4.o \
  $(OBJDIR)/piecewise_linear_aae401e2.o \
  $(OBJDIR)/silence_b22f47bb.o \
  $(OBJDIR)/time_1696a03d.o \
  $(OBJDIR)/wave_table_a27cf2b8.o \
  $(OBJDIR)/algorithm_267fb119.o \
  $(OBJDIR)/gp_population_8c49608d.o \
  $(OBJDIR)/parser_f3a199ff.o \
  $(OBJDIR)/random_33fc50a3.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_core_aff681cc.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking synthax
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning synthax
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

strip:
	@echo Stripping synthax
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/audio_util_1e6dca20.o: ../../src/auxilliary/audio_util.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling audio_util.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_file_io_23efa0cc.o: ../../src/auxilliary/juce_file_io.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_file_io.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/logger_f86ce265.o: ../../src/auxilliary/logger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling logger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/kiss_fft_5150b3c.o: ../../src/dependencies/kissfft/kiss_fft.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling kiss_fft.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/kiss_fftr_9d8d5580.o: ../../src/dependencies/kissfft/kiss_fftr.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling kiss_fftr.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/WaveTableOsc_3abb7d69.o: ../../src/dependencies/WaveTableOsc/WaveTableOsc.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling WaveTableOsc.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_139b05cc.o: ../../src/primitives/abstract/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_c5789d75.o: ../../src/primitives/abstract/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_aff4c7fc.o: ../../src/primitives/abstract/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_dcbad452.o: ../../src/primitives/abstract/wave_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_cea0a9de.o: ../../src/primitives/envelope/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/gain_8dec311b.o: ../../src/primitives/envelope/gain.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gain.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_dc052f23.o: ../../src/primitives/envelope/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_c0dae10e.o: ../../src/primitives/envelope/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/add_ff08cb97.o: ../../src/primitives/function/add.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling add.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cosine_4156b6cd.o: ../../src/primitives/function/cosine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cosine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/multiply_6b228eb8.o: ../../src/primitives/function/multiply.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling multiply.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_4c643221.o: ../../src/primitives/function/sine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/subtract_8c390ba8.o: ../../src/primitives/function/subtract.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling subtract.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/mixer_99b9d5.o: ../../src/primitives/logic/mixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling mixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/switcher_7d022e1f.o: ../../src/primitives/logic/switcher.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling switcher.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_amp_mod_2ed81fc5.o: ../../src/primitives/modulation/sine_amp_mod.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine_amp_mod.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_phase_mod_33978a3c.o: ../../src/primitives/modulation/sine_phase_mod.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine_phase_mod.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/saw_f6196e2a.o: ../../src/primitives/modulation/oscillator/saw.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_67d95836.o: ../../src/primitives/modulation/oscillator/sine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/square_f09e7dc6.o: ../../src/primitives/modulation/oscillator/square.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling square.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/triangle_a02d7431.o: ../../src/primitives/modulation/oscillator/triangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling triangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_57477db8.o: ../../src/primitives/modulation/wave_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/saw_f8c632a.o: ../../src/primitives/terminal/oscillator/saw.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_7cc50336.o: ../../src/primitives/terminal/oscillator/sine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/square_794b68c6.o: ../../src/primitives/terminal/oscillator/square.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling square.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/triangle_b14b9f31.o: ../../src/primitives/terminal/oscillator/triangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling triangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_635568b2.o: ../../src/primitives/terminal/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/constant_b2e4d814.o: ../../src/primitives/terminal/constant.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling constant.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/input_static_da5d13f3.o: ../../src/primitives/terminal/input_static.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling input_static.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_e91345cf.o: ../../src/primitives/terminal/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/noise_f9238af4.o: ../../src/primitives/terminal/noise.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling noise.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_aae401e2.o: ../../src/primitives/terminal/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/silence_b22f47bb.o: ../../src/primitives/terminal/silence.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling silence.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/time_1696a03d.o: ../../src/primitives/terminal/time.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling time.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_a27cf2b8.o: ../../src/primitives/terminal/wave_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/algorithm_267fb119.o: ../../src/algorithm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling algorithm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/gp_population_8c49608d.o: ../../src/gp_population.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gp_population.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/parser_f3a199ff.o: ../../src/parser.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling parser.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/random_33fc50a3.o: ../../src/random.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling random.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
