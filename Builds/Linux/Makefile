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
  $(OBJDIR)/algorithm_e540ed39.o \
  $(OBJDIR)/gp_population_51cf8cad.o \
  $(OBJDIR)/adsr_f7fba9be.o \
  $(OBJDIR)/gain_b74730fb.o \
  $(OBJDIR)/lfo_dd5ab343.o \
  $(OBJDIR)/piecewise_linear_e95510ee.o \
  $(OBJDIR)/add_5e4fb7.o \
  $(OBJDIR)/cosine_7ff13ead.o \
  $(OBJDIR)/multiply_6d3a9e98.o \
  $(OBJDIR)/sine_75bf3201.o \
  $(OBJDIR)/subtract_8e511b88.o \
  $(OBJDIR)/switcher_7f072a3f.o \
  $(OBJDIR)/mixer_3a7331b5.o \
  $(OBJDIR)/saw_1e939e0a.o \
  $(OBJDIR)/sine_4ea52456.o \
  $(OBJDIR)/square_53a7c1e6.o \
  $(OBJDIR)/triangle_65f63051.o \
  $(OBJDIR)/am_sin_d65f8bd5.o \
  $(OBJDIR)/pm_sin_26ad2ca6.o \
  $(OBJDIR)/wave_table_6d149d98.o \
  $(OBJDIR)/adsr_4a8ef5a3.o \
  $(OBJDIR)/function_1078dab9.o \
  $(OBJDIR)/lfo_7cebd6be.o \
  $(OBJDIR)/piecewise_linear_b584ad53.o \
  $(OBJDIR)/saw_e6910b0a.o \
  $(OBJDIR)/sin_f3b8fc79.o \
  $(OBJDIR)/square_601734e6.o \
  $(OBJDIR)/triangle_1454e351.o \
  $(OBJDIR)/adsr_8cb06892.o \
  $(OBJDIR)/constant_b4fce7f4.o \
  $(OBJDIR)/input_static_f02a33d3.o \
  $(OBJDIR)/lfo_ea68c9ef.o \
  $(OBJDIR)/noise_fb288714.o \
  $(OBJDIR)/piecewise_linear_d35e31c2.o \
  $(OBJDIR)/silence_46e5bbdb.o \
  $(OBJDIR)/time_3ff1a01d.o \
  $(OBJDIR)/wave_table_7ed08a98.o \
  $(OBJDIR)/audio_util_1c111119.o \
  $(OBJDIR)/juce_file_io_45dd0d85.o \
  $(OBJDIR)/logger_41348dde.o \
  $(OBJDIR)/parser_e813f4ed.o \
  $(OBJDIR)/random_286eab91.o \
  $(OBJDIR)/kiss_fft_5150b3c.o \
  $(OBJDIR)/kiss_fftr_9d8d5580.o \
  $(OBJDIR)/WaveTableOsc_3abb7d69.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
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

$(OBJDIR)/algorithm_e540ed39.o: ../../src/algorithm/algorithm.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling algorithm.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/gp_population_51cf8cad.o: ../../src/algorithm/gp_population.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gp_population.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_f7fba9be.o: ../../src/algorithm/primitives/envelope/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/gain_b74730fb.o: ../../src/algorithm/primitives/envelope/gain.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling gain.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_dd5ab343.o: ../../src/algorithm/primitives/envelope/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_e95510ee.o: ../../src/algorithm/primitives/envelope/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/add_5e4fb7.o: ../../src/algorithm/primitives/function/add.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling add.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cosine_7ff13ead.o: ../../src/algorithm/primitives/function/cosine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cosine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/multiply_6d3a9e98.o: ../../src/algorithm/primitives/function/multiply.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling multiply.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_75bf3201.o: ../../src/algorithm/primitives/function/sine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/subtract_8e511b88.o: ../../src/algorithm/primitives/function/subtract.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling subtract.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/switcher_7f072a3f.o: ../../src/algorithm/primitives/logic/switcher.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling switcher.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/mixer_3a7331b5.o: ../../src/algorithm/primitives/logic/mixer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling mixer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/saw_1e939e0a.o: ../../src/algorithm/primitives/modulation/oscillator/saw.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sine_4ea52456.o: ../../src/algorithm/primitives/modulation/oscillator/sine.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sine.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/square_53a7c1e6.o: ../../src/algorithm/primitives/modulation/oscillator/square.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling square.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/triangle_65f63051.o: ../../src/algorithm/primitives/modulation/oscillator/triangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling triangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/am_sin_d65f8bd5.o: ../../src/algorithm/primitives/modulation/am_sin.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling am_sin.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pm_sin_26ad2ca6.o: ../../src/algorithm/primitives/modulation/pm_sin.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pm_sin.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_6d149d98.o: ../../src/algorithm/primitives/modulation/wave_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_4a8ef5a3.o: ../../src/algorithm/primitives/super/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/function_1078dab9.o: ../../src/algorithm/primitives/super/function.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling function.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_7cebd6be.o: ../../src/algorithm/primitives/super/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_b584ad53.o: ../../src/algorithm/primitives/super/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/saw_e6910b0a.o: ../../src/algorithm/primitives/terminal/oscillator/saw.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling saw.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sin_f3b8fc79.o: ../../src/algorithm/primitives/terminal/oscillator/sin.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sin.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/square_601734e6.o: ../../src/algorithm/primitives/terminal/oscillator/square.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling square.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/triangle_1454e351.o: ../../src/algorithm/primitives/terminal/oscillator/triangle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling triangle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_8cb06892.o: ../../src/algorithm/primitives/terminal/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/constant_b4fce7f4.o: ../../src/algorithm/primitives/terminal/constant.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling constant.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/input_static_f02a33d3.o: ../../src/algorithm/primitives/terminal/input_static.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling input_static.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lfo_ea68c9ef.o: ../../src/algorithm/primitives/terminal/lfo.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lfo.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/noise_fb288714.o: ../../src/algorithm/primitives/terminal/noise.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling noise.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/piecewise_linear_d35e31c2.o: ../../src/algorithm/primitives/terminal/piecewise_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling piecewise_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/silence_46e5bbdb.o: ../../src/algorithm/primitives/terminal/silence.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling silence.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/time_3ff1a01d.o: ../../src/algorithm/primitives/terminal/time.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling time.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/wave_table_7ed08a98.o: ../../src/algorithm/primitives/terminal/wave_table.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling wave_table.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/audio_util_1c111119.o: ../../src/common/audio_util.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling audio_util.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_file_io_45dd0d85.o: ../../src/common/juce_file_io.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_file_io.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/logger_41348dde.o: ../../src/common/logger.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling logger.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/parser_e813f4ed.o: ../../src/common/parser.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling parser.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/random_286eab91.o: ../../src/common/random.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling random.cpp"
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

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
