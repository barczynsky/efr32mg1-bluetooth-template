cmake_minimum_required(VERSION 3.1)

set(GECKO_MCU_ID "EFR32MG1P232F256GM48")
# set(GECKO_MCU_CPU "cortex-m4")
# set(GECKO_MCU_ARCH "armv7e-m")
set(GECKO_LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/efr32mg1p.ld")

set(GECKO_SDK_ROOT "/opt/simplicity/developer/stacks/ble/v2.1.1.0")
set(GECKO_BLE_STACK_ROOT "${GECKO_SDK_ROOT}/protocol/bluetooth_2.1")

set(GECKO_TOOLCHAIN "arm-none-eabi")
# set(GECKO_TOOLCHAIN_DIR "/opt/cross/gcc-arm-none-eabi-5_4-2016q3")
# set(GECKO_TOOLCHAIN_DIR "/opt/cross/gcc-arm-none-eabi-6_2-2016q4")
set(GECKO_TOOLCHAIN_DIR "/opt/cross/gcc-arm-none-eabi-6-2017-q1-update")
set(GECKO_JLINK_EXE "JLinkExe")

# ----------------------------------------------------------------------------

set(CMAKE_SYSTEM_NAME Generic)
# set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
# set(CMAKE_SYSROOT ${GECKO_TOOLCHAIN_DIR})

set(CMAKE_ASM_COMPILER ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc)
set(CMAKE_C_COMPILER ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc)
set(CMAKE_CXX_COMPILER ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-g++)
set(CMAKE_LINKER ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc)
set(CMAKE_STRIP ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-strip)
set(CMAKE_NM ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc-nm)
set(CMAKE_AR ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc-ar)
set(CMAKE_RANLIB ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-gcc-ranlib)
set(CMAKE_OBJCOPY ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-objcopy)
set(CMAKE_OBJDUMP ${GECKO_TOOLCHAIN_DIR}/bin/${GECKO_TOOLCHAIN}-objdump)

# set(CMAKE_FIND_ROOT_PATH "${GECKO_TOOLCHAIN_DIR}/${GECKO_TOOLCHAIN}")
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# ----------------------------------------------------------------------------

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
# warnings suppression
	# set(AUX_ARM_FLAGS "-Wno-unused-parameter ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-Wno-unused-variable ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-Wno-keyword-macro ${AUX_ARM_FLAGS}") # What the hell?
# coding directives
	# set(AUX_ARM_FLAGS "-fshort-wchar ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-fshort-enums ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-Wall ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-Wextra ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-pedantic ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-fdiagnostics-color ${AUX_ARM_FLAGS}")
# common options
	# set(AUX_ARM_FLAGS "-nostartfiles ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-nostdlib ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-flto ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-v ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-nodefaultlibs ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-mlong-calls ${AUX_ARM_FLAGS}")
	# set(AUX_ARM_FLAGS "-flto ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-ffunction-sections ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-fdata-sections ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-fno-builtin ${AUX_ARM_FLAGS}")
# common linker options
	set(AUX_ARM_FLAGS "-T ${GECKO_LINKER_SCRIPT} ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-specs=nano.specs ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-specs=nosys.specs ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-mthumb -mthumb-interwork ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-mtune=cortex-m4 ${AUX_ARM_FLAGS}")
	set(AUX_ARM_FLAGS "-march=armv7e-m ${AUX_ARM_FLAGS}")
# extra C++ options
	set(AUX_CXX_FLAGS "-fno-rtti ${AUX_CXX_FLAGS}")
	set(AUX_CXX_FLAGS "-fno-exceptions ${AUX_CXX_FLAGS}")
	set(AUX_CXX_FLAGS "-fno-unwind-tables ${AUX_CXX_FLAGS}")
	set(AUX_CXX_FLAGS "-fno-threadsafe-statics ${AUX_CXX_FLAGS}")
# grand total flags
	set(AUX_C_FLAGS "${AUX_ARM_FLAGS} ${AUX_C_FLAGS}")
	set(AUX_CXX_FLAGS "${AUX_ARM_FLAGS} ${AUX_CXX_FLAGS}")
	set(AUX_LINKER_FLAGS "${AUX_ARM_FLAGS} ${AUX_LINKER_FLAGS}")
	# set(AUX_LINKER_FLAGS "-Wl,--verbose ${AUX_LINKER_FLAGS}")
endif()
set(CMAKE_C_FLAGS "${AUX_C_FLAGS} ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${AUX_CXX_FLAGS} ${CMAKE_CXX_FLAGS}")
set(CMAKE_LINKER_FLAGS "${AUX_LINKER_FLAGS} ${CMAKE_LINKER_FLAGS}")

# set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "MinSizeRel")
set(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_BUILD_TYPE "RelWithDebInfo")

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 14)

# ----------------------------------------------------------------------------

include_directories("${GECKO_BLE_STACK_ROOT}/ble_stack/inc")
include_directories("${GECKO_BLE_STACK_ROOT}/ble_stack/inc/common")
include_directories("${GECKO_BLE_STACK_ROOT}/ble_stack/inc/soc")
include_directories("${GECKO_SDK_ROOT}/platform/CMSIS/Include")
include_directories("${GECKO_SDK_ROOT}/platform/Device/SiliconLabs/EFR32MG1P/Include")
include_directories("${GECKO_SDK_ROOT}/platform/emdrv/common/inc")
include_directories("${GECKO_SDK_ROOT}/platform/emlib/inc")
include_directories("${GECKO_SDK_ROOT}/platform/emlib/src")

set(LIBS ${LIBS} gcc)
# set(LIBS ${LIBS} gcov)
set(LIBS ${LIBS} c_nano)
# set(LIBS ${LIBS} g_nano)
# set(LIBS ${LIBS} stdc++_nano)
set(LIBS ${LIBS} nosys)

set(LIBS ${LIBS} "${GECKO_BLE_STACK_ROOT}/lib/binbootloader.o")
set(LIBS ${LIBS} "${GECKO_BLE_STACK_ROOT}/lib/binstack.o")
set(LIBS ${LIBS} "${GECKO_BLE_STACK_ROOT}/lib/stack.a")

# ----------------------------------------------------------------------------

set(GATT "GATT")

include_directories("${CMAKE_SOURCE_DIR}/bgbuild")

set(GATT_SRC ${GATT_SRC} "${CMAKE_SOURCE_DIR}/bgbuild/gatt.xml")
set(GATTDB_INC ${GATTDB_INC} "${CMAKE_SOURCE_DIR}/bgbuild/gatt_db.h")
set(GATTDB_SRC ${GATTDB_SRC} "${CMAKE_SOURCE_DIR}/bgbuild/gatt_db.c")

# ----------------------------------------------------------------------------

set(APP "gniazdko")
set(APP_OUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP}.elf")
set(APP_BIN "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP}.bin")
set(APP_DIS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${APP}.diS")

include_directories("${CMAKE_SOURCE_DIR}/common")
include_directories("${CMAKE_SOURCE_DIR}/common/emlib")
include_directories("${CMAKE_SOURCE_DIR}/src")

set(APP_SRC ${APP_SRC} "${GECKO_SDK_ROOT}/platform/Device/SiliconLabs/EFR32MG1P/Source/GCC/startup_efr32mg1p.c")

set(APP_SRC ${APP_SRC} "${GECKO_SDK_ROOT}/platform/emlib/src/em_gpio.c")
set(APP_SRC ${APP_SRC} "${GECKO_SDK_ROOT}/platform/emlib/src/em_rtcc.c")
set(APP_SRC ${APP_SRC} "${GECKO_SDK_ROOT}/platform/emlib/src/em_timer.c")

set(APP_SRC ${APP_SRC} "${CMAKE_SOURCE_DIR}/src/main.cpp")
set(APP_SRC ${APP_SRC} "${CMAKE_SOURCE_DIR}/src/InitDevice.c")
set(APP_SRC ${APP_SRC} "${CMAKE_SOURCE_DIR}/src/GeckoConfiguration.c")

# ----------------------------------------------------------------------------

message("** New executable: ${APP}")
message("-- (${GATT}) GATT_SRC = ${GATT_SRC}")
message("-- (${GATT}) GATTDB_SRC = ${GATTDB_SRC}")
message("-- (${APP}) APP_SRC = ${APP_SRC}")

add_executable(${APP} ${APP_SRC} ${GATTDB_SRC})
set_target_properties(${APP} PROPERTIES SUFFIX ".elf")
set_source_files_properties(${GATTDB_SRC} PROPERTIES GENERATED TRUE)
target_compile_definitions(${APP} PRIVATE "-D__NO_SYSTEM_INIT -D${GECKO_MCU_ID}")
target_link_libraries(${APP} ${LIBS})

add_custom_target(${GATT} ${GECKO_BLE_STACK_ROOT}/bin/bgbuild -gn -c ${GECKO_TOOLCHAIN_DIR} ${GATT_SRC})
add_dependencies(${APP} ${GATT})

set(SizeTarget "size")
set(BinaryTarget "${APP}.bin")
set(FlashTarget "flash")
set(ResetTarget "reset")
set(DisasmTarget "disasm")

add_custom_target(${BinaryTarget} ${GECKO_TOOLCHAIN}-objcopy -v -S --gap-fill 255 -O binary ${APP_OUT} ${APP_BIN} DEPENDS ${APP})
add_custom_target(${SizeTarget} ${GECKO_TOOLCHAIN}-size ${APP_OUT} DEPENDS ${APP} ${BinaryTarget})
# add_custom_target(${FlashTarget} ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=." "./commander/commander" flash ${APP_BIN} WORKING_DIRECTORY "${GECKO_BLE_STACK_ROOT}/bin/" DEPENDS ${BinaryTarget} ${SizeTarget})
add_custom_target(${FlashTarget} ${GECKO_JLINK_EXE} <"${CMAKE_SOURCE_DIR}/flash.jlink" DEPENDS ${BinaryTarget} ${SizeTarget})
add_custom_target(${ResetTarget} ${GECKO_JLINK_EXE} <"${CMAKE_SOURCE_DIR}/reset.jlink")
add_custom_target(${DisasmTarget} ${GECKO_TOOLCHAIN}-objdump -C -d -S -l ${APP_OUT} >${APP_DIS} DEPENDS ${APP})

message("** (${APP}) Done.")

# ----------------------------------------------------------------------------

message("** (global) LIBS = ${LIBS}")
message("** (global) C_FLAGS = ${CMAKE_C_FLAGS}")
message("** (global) CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message("** (global) LD_FLAGS = ${CMAKE_LINKER_FLAGS}")
message("** (global) Done.")
