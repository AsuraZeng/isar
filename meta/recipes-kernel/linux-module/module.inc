# Custom kernel module recipe include
#
# This software is a part of ISAR.
# Copyright (c) Siemens AG, 2018
#
# SPDX-License-Identifier: MIT

FILESPATH =. "${LAYERDIR_core}/recipes-kernel/linux-module/files:"

DESCRIPTION ?= "Custom kernel module ${PN}"

DEPENDS += "linux-headers-${KERNEL_NAME}"

SRC_URI += "file://debian/"

AUTOLOAD ?= ""

inherit dpkg

do_prepare_build() {
    cp -r ${WORKDIR}/debian ${S}/
    sed -i -e 's/@PN@/${PN}/g' -e 's/@PV@/${PV}/g' \
           -e 's/@KERNEL_NAME@/${KERNEL_NAME}/g' \
           -e 's/@DESCRIPTION@/${DESCRIPTION}/g' \
        ${S}/debian/changelog ${S}/debian/control

    for module in "${AUTOLOAD}"; do
        echo "echo $module >> /etc/modules" >> ${S}/debian/postinst
    done
}
