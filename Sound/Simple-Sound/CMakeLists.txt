add_executable(sound_system)

add_picovga(sound_system)

# for vga_config.h include
target_include_directories(sound_system PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_sources(graphics_system PRIVATE src/main.cpp vga16_graphics.c)

# create map/bin/hex file etc.
pico_add_extra_outputs(sound_system)

# Allow stdio to USB
pico_enable_stdio_usb(sound_system 1)