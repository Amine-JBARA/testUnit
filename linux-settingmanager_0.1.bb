DESCRIPTION = "A friendly program that prints Hello World!"

SECTION = "examples"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
SRC_URI = "file://main.cpp \
            file://ipc.cpp \
            file://daemon.cpp \
            file://sqlite_interface.cpp \
            file://sqlite_interface.hpp \
            file://enums.hpp \
	    file://daemon.hpp \
	    file://ipc.hpp \
	    file://mu_settings.hpp \
	    file://mu_status.hpp \
	    file://mu_config.cfg \
	    file://log.hpp \
	    file://command-line-parser.hpp \
            file://Makefile"
S = "${WORKDIR}"

DEPENDS = "ti-rpmsg-char sqlite3"
RDEPENDS_${PN} += "bash"

do_compile() {
    oe_runmake -f Makefile all
}

do_install() {
    install -d ${D}${bindir}
    install -d ${D}${ROOT_HOME}
    install -m 0755 SettingManagerDaemon_arm ${D}${bindir}
    install -m 0666 mu_config.cfg ${D}${ROOT_HOME}
}

FILES_${PN} += "${ROOT_HOME}/*"
