cmake_minimum_required(VERSION 3.22)

# Force arm64 for Apple Silicon
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for macOS")

project(Program-Changer VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Reference JUCE from environment variable
if(DEFINED ENV{JUCE_DIR})
    add_subdirectory($ENV{JUCE_DIR} "${CMAKE_BINARY_DIR}/JUCE")
else()
    message(FATAL_ERROR "JUCE_DIR environment variable not set. Please set it to your JUCE installation path.")
endif()

# ============================================================================
# SOURCE FILES
# Add your new .cpp files here (keep them sorted alphabetically for clarity)
# ============================================================================

set(PLUGIN_SOURCES
    # Core
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
    Source/PluginFactory.cpp
    
    # Add your new source files below
)

# ============================================================================
# PLUGIN CONFIGURATION
# ============================================================================

juce_add_plugin(Program-Changer
    COMPANY_NAME "Ten Square Software"
    BUNDLE_ID "com.TenSquareSoftware.Program-Changer"
    PLUGIN_MANUFACTURER_CODE Tssf
    PLUGIN_CODE Tspc
    FORMATS AU VST3 Standalone
    PRODUCT_NAME "Program-Changer"
	PLUGIN_NAME "Program Changer"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT TRUE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    VST3_CATEGORIES Fx
    AU_MAIN_TYPE kAudioUnitType_Effect
)

target_sources(Program-Changer PRIVATE ${PLUGIN_SOURCES})

target_link_libraries(Program-Changer
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(Program-Changer
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
)