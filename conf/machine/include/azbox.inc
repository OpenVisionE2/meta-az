# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

KERNELVERSION = "3.9.2"

BOX_BRAND = "azbox"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	azbox-compat \
	azbox-dvb-modules-${MACHINE} \
	azbox-mrua-${MACHINE} \
	"

EXTRA_IMAGEDEPENDS += "\
	kmod-native \
	"

DVBPROVIDER = "kernel"

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dtsdownmix"

MACHINE_FEATURES += "azbox alsa usbhost nl80211 switchoff lpcm textlcd 32bpp dvbapi5 dvb-c blindscan-dvbs HDMI"

PREFERRED_PROVIDER_virtual/kernel = "linux-azbox"
PREFERRED_VERSION_linux-azbox = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "azbox-blindscan-dvbs-utils"

GLIBC_EXTRA_OECONF = "--with-tls --with-__thread"

require conf/machine/include/tune-mips32.inc
require conf/machine/include/soc-family.inc

SYSVINIT_ENABLED_GETTYS = ""

BLINDSCAN_BINARY = "avl_azbox_blindscan"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	kernel-module-rt61pci \
	kernel-module-rt2x00pci \
	kernel-module-rt2x00lib \
	kernel-module-mac80211 \
	kernel-module-eeprom-93cx6 \
	rt61-firmware \
	"

do_image_azboxcramfs[depends] += "${MACHINE}-buildimage-native:do_populate_sysroot"

MACHINE_FEATURES += "ci smallflash SCART YUV RCA"

SOC_FAMILY = "smp8634"

KERNEL_MODULE_AUTOLOAD += "\
	rt61pci \
	rt2x00pci \
	rt2x00lib \
	mac80211 \
	eeprom_93cx6 \
	"

IMAGE_FSTYPES = "azboxcramfs"

IMAGE_CMD_azboxcramfs_append = " \
	rm -fR ${IMAGE_ROOTFS}/boot/*; \
	mkfs.cramfs ${IMAGE_ROOTFS} ${DEPLOY_DIR_IMAGE}/azboxhd.cramfs; \
	pack_e2 -t Vision \
	-d Vision \
	-a Enigma2 \
	-v ${VISIONVERSION}-${VISIONREVISION} \
	-i ${DEPLOY_DIR_IMAGE}/azboxhd.cramfs \
	-k ${DEPLOY_DIR_IMAGE}/zbimage-linux-xload -K ULK-${KERNELVERSION} \
	-p ${DEPLOY_DIR_IMAGE}/patch.e2; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tgz; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.cramfs; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.zip; \
	echo ${IMAGE_NAME} > ${DEPLOY_DIR_IMAGE}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${DEPLOY_DIR_IMAGE}/donate.txt; \
	cd ${DEPLOY_DIR_IMAGE}; \
	zip ${IMAGE_NAME}_azup.zip patch.e2 imageversion donate.txt; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.e2; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

# Image fails to boot if kernel exceeds some limit
KERNEL_IMAGE_MAXSIZE = "6815744"

RCNAME = "azboxhd"
