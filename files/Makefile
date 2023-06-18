all: build_arm

HOME=../../../../..

INCLUDE_X86= \
		-I./include

INCLUDE_ARM= \
		-I./include -I$(HOME)/build/arago-tmp-external-arm-glibc/sysroots-components/aarch64/ti-rpmsg-char/usr/include \
		-I$(HOME)/build/arago-tmp-external-arm-glibc/work-shared/am64xx-evm/kernel-source/arch/alpha/include \
		-I$(HOME)/build/arago-tmp-external-arm-glibc/work/aarch64-linux/sqlite3/3_3.31.1-r0/image/usr/include
#		-I$(HOME)/build/arago-tmp-external-arm-glibc/work-shared/am64xx-evm/kernel-source/include \
#		-I$(HOME)/build/arago-tmp-external-arm-glibc/work-shared/am64xx-evm/kernel-source/arch/arm64/include \


#LIB_ARM=-L/media/user/DDD/MU/TI-SDK/build/arago-tmp-external-arm-glibc/sysroots-components/aarch64/ti-rpmsg-char/usr/lib -lpthread -lti_rpmsg_char -lstdc++ 
LIB_ARM= \
		-L$(HOME)/build/arago-tmp-external-arm-glibc/work/aarch64-linux/sqlite3/3_3.31.1-r0/image/usr/lib \
		-L$(HOME)/build/arago-tmp-external-arm-glibc/sysroots-components/aarch64/ti-rpmsg-char/usr/lib \
		-L$(HOME)/build/arago-tmp-external-arm-glibc/work/aarch64-linux/sqlite3/3_3.31.1-r0/image/usr/lib \
		-lpthread \
		-lstdc++ \
		-lti_rpmsg_char \
		-lsqlite3 \
		-lm

LIB_X86= \
		-lstdc++ \
		-pthread \
		-lm \
		-lsqlite3

CFLAGS=-Wall -Wextra -O2 -g 
#LIB_EXTRA=/media/user/DDD/MU/TI-SDK/build/arago-tmp-external-arm-glibc/sysroots-components/aarch64/ti-rpmsg-char/usr/lib/libti_rpmsg_char.a
CC=$(HOME)/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc

build_arm_test_ti:
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -c example_ti.c
	$(CC) example_ti.o $(LIB_ARM) $(LIB_EXTRA) -o ti-test

build_arm:
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c main.cpp
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c ipc.cpp
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c daemon.cpp
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c config.cpp
	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c sig_proc.cpp

	$(CC) $(CFLAGS) $(INCLUDE_ARM) -DTARGET_ARM -c sqlite_interface.cpp
	$(CC) -DTARGET_ARM main.o daemon.o config.o sig_proc.o ipc.o sqlite_interface.o $(LIB_ARM) $(LIB_EXTRA) -o SettingManagerDaemon_arm


build_x86:
	g++ $(CFLAGS) $(INCLUDE_X86) -c main.cpp
	g++ $(CFLAGS) $(INCLUDE_X86) -c daemon.cpp
	g++ $(CFLAGS) $(INCLUDE_X86) -c config.cpp
	g++ $(CFLAGS) $(INCLUDE_X86) -c sig_proc.cpp

	g++ $(CFLAGS) $(INCLUDE_X86) -c ipc.cpp
	g++ $(CFLAGS) $(INCLUDE_X86) -c sqlite_interface.cpp
	g++ main.o daemon.o ipc.o sqlite_interface.o $(LIB_X86) -o SettingManagerDaemon_arm


clean:
	rm *.o
	rm SettingManagerDaemon_arm
	rm SettingManagerDaemon_x86
