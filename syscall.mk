# syscall.mk - select the correct syscall primitive for the target.
#
# Must be included AFTER cross.mk, because it uses TARGET_OS and
# TARGET_ARCH which cross.mk defines.
#
# Defines:
#   SYSCALL_SRCS  list of syscall source files for the target
#   SYSCALL_OBJS  corresponding object files

SYSCALL_DIR := src/syscall

ifeq ($(TARGET_OS),Linux)
  ifeq ($(TARGET_ARCH),x86_64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/linux/x86_64/__haj_syscall6.S
  else ifeq ($(TARGET_ARCH),aarch64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/linux/aarch64/__haj_syscall6.S
  else
    $(error hajlib: unsupported Linux arch '$(TARGET_ARCH)')
  endif
else ifeq ($(TARGET_OS),FreeBSD)
  ifeq ($(TARGET_ARCH),x86_64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/freebsd/x86_64/__haj_syscall6.S
  else ifeq ($(TARGET_ARCH),aarch64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/freebsd/aarch64/__haj_syscall6.S
  else
    $(error hajlib: unsupported FreeBSD arch '$(TARGET_ARCH)')
  endif
else ifeq ($(TARGET_OS),Darwin)
  ifeq ($(TARGET_ARCH),x86_64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/darwin/x86_64/__haj_syscall6.S
  else ifeq ($(TARGET_ARCH),arm64)
    SYSCALL_SRCS := $(SYSCALL_DIR)/darwin/arm64/__haj_syscall6.S
  else
    $(error hajlib: unsupported Darwin arch '$(TARGET_ARCH)')
  endif
else ifeq ($(TARGET_OS),Windows)
  SYSCALL_SRCS := $(SYSCALL_DIR)/windows/__haj_syscall6.c
else
  $(error hajlib: unsupported OS '$(TARGET_OS)')
endif
