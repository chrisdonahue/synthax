# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

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

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := libsynthax.a
  BLDCMD = ar -rcs $(OUTDIR)/$(TARGET) $(OBJECTS)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -ldl -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules
  TARGET := libsynthax.a
  BLDCMD = ar -rcs $(OUTDIR)/$(TARGET) $(OBJECTS)
endif

OBJECTS := \
  $(OBJDIR)/adsr_x_e596686d.o \
  $(OBJDIR)/env_lin_x_a2b11410.o \
  $(OBJDIR)/gain_e9890bf1.o \
  $(OBJDIR)/lfo_x_5c1bb306.o \
  $(OBJDIR)/adsr_b_3b07f860.o \
  $(OBJDIR)/env_lin_b_b9337151.o \
  $(OBJDIR)/lfo_b_23e2d3c7.o \
  $(OBJDIR)/wave_table_b_a80d44a6.o \
  $(OBJDIR)/add_ff08cb97.o \
  $(OBJDIR)/cosine_4156b6cd.o \
  $(OBJDIR)/multiply_6b228eb8.o \
  $(OBJDIR)/sine_4c643221.o \
  $(OBJDIR)/subtract_8c390ba8.o \
  $(OBJDIR)/mixer_99b9d5.o \
  $(OBJDIR)/switcher_7d022e1f.o \
  $(OBJDIR)/saw_fm_fe440586.o \
  $(OBJDIR)/sin_fm_f97ce9b7.o \
  $(OBJDIR)/sqr_fm_3b25153b.o \
  $(OBJDIR)/tri_fm_1cc86184.o \
  $(OBJDIR)/sin_am_96dfd7a3.o \
  $(OBJDIR)/sin_pm_b07888f4.o \
  $(OBJDIR)/wave_table_fm_ed682338.o \
  $(OBJDIR)/adsr_635568b2.o \
  $(OBJDIR)/constant_b2e4d814.o \
  $(OBJDIR)/env_lin_4f717059.o \
  $(OBJDIR)/input_s_ad2b55d8.o \
  $(OBJDIR)/lfo_e91345cf.o \
  $(OBJDIR)/noise_f9238af4.o \
  $(OBJDIR)/saw_s_gen_e4035d6f.o \
  $(OBJDIR)/sin_s_gen_e5863f9e.o \
  $(OBJDIR)/sqr_s_gen_76a6359a.o \
  $(OBJDIR)/tri_s_gen_30d098b1.o \
  $(OBJDIR)/silence_b22f47bb.o \
  $(OBJDIR)/time_1696a03d.o \
  $(OBJDIR)/wave_table_a27cf2b8.o \
  $(OBJDIR)/audio_util_1e6dca20.o \
  $(OBJDIR)/juce_file_io_23efa0cc.o \
  $(OBJDIR)/logger_f86ce265.o \
  $(OBJDIR)/kiss_fft_5150b3c.o \
  $(OBJDIR)/kiss_fftr_9d8d5580.o \
  $(OBJDIR)/WaveTableOsc_3abb7d69.o \
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

$(OBJDIR)/adsr_x_e596686d.o: ../../src/primitives/attenuation/adsr_x.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr_x.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/env_lin_x_a2b11410.o: ../../src/primitives/attenuation/env_lin_x.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling env_lin_x.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/gain_e9890bf1.o: ../../src/primitives/attenuation/gain.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gain.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_x_5c1bb306.o: ../../src/primitives/attenuation/lfo_x.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo_x.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_b_3b07f860.o: ../../src/primitives/base/adsr_b.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr_b.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/env_lin_b_b9337151.o: ../../src/primitives/base/env_lin_b.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling env_lin_b.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_b_23e2d3c7.o: ../../src/primitives/base/lfo_b.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo_b.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_b_a80d44a6.o: ../../src/primitives/base/wave_table_b.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table_b.cpp"
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

$(OBJDIR)/saw_fm_fe440586.o: ../../src/primitives/modulation/oscillator/saw_fm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw_fm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sin_fm_f97ce9b7.o: ../../src/primitives/modulation/oscillator/sin_fm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sin_fm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqr_fm_3b25153b.o: ../../src/primitives/modulation/oscillator/sqr_fm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqr_fm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tri_fm_1cc86184.o: ../../src/primitives/modulation/oscillator/tri_fm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tri_fm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sin_am_96dfd7a3.o: ../../src/primitives/modulation/sin_am.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sin_am.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sin_pm_b07888f4.o: ../../src/primitives/modulation/sin_pm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sin_pm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_fm_ed682338.o: ../../src/primitives/modulation/wave_table_fm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table_fm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_635568b2.o: ../../src/primitives/terminal/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/constant_b2e4d814.o: ../../src/primitives/terminal/constant.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling constant.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/env_lin_4f717059.o: ../../src/primitives/terminal/env_lin.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling env_lin.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/input_s_ad2b55d8.o: ../../src/primitives/terminal/input_s.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling input_s.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_e91345cf.o: ../../src/primitives/terminal/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/noise_f9238af4.o: ../../src/primitives/terminal/noise.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling noise.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/saw_s_gen_e4035d6f.o: ../../src/primitives/terminal/oscillator/saw_s_gen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw_s_gen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sin_s_gen_e5863f9e.o: ../../src/primitives/terminal/oscillator/sin_s_gen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sin_s_gen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqr_s_gen_76a6359a.o: ../../src/primitives/terminal/oscillator/sqr_s_gen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqr_s_gen.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tri_s_gen_30d098b1.o: ../../src/primitives/terminal/oscillator/tri_s_gen.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tri_s_gen.cpp"
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
