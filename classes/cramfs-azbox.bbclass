inherit image_types

IMAGE_CMD_cramfs = "mkfs.cramfs ${IMAGE_ROOTFS} ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.cramfs;"

do_image_cramfs[depends] += "${MACHINE}-buildimage-native:do_populate_sysroot"
