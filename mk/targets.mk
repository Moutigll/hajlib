# targets.mk - select OS/arch-specific source files.
#
# Must be included AFTER cross.mk (which sets TARGET_OS and
# TARGET_ARCH).
#
# Defines:
#   CRT_START_SRCS    startup assembly file
#   SYSCALL_SRCS      syscall primitive
#   SETJMP_SRCS       setjmp/longjmp assembly files
#
# These files are specific to one OS and one architecture. They
# are selected based on TARGET_OS and TARGET_ARCH, both set by
# cross.mk.
#
# To add support for a new OS or arch:
#   1. Add the appropriate block below.
#   2. Add the corresponding source files in src/.

# Validate target
ifeq ($(TARGET_OS),)
  $(error targets.mk: TARGET_OS is not defined, include cross.mk first)
endif
ifeq ($(TARGET_ARCH),)
  $(error targets.mk: TARGET_ARCH is not defined, include cross.mk first)
endif

# Linux
ifeq ($(TARGET_OS),Linux)

  ifeq ($(TARGET_ARCH),x86_64)
    CRT_START_SRCS	:= src/crt/linux/x86_64/start.S
    SYSCALL_SRCS	:= src/syscall/linux/x86_64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/x86_64/setjmp.S \
			   src/setjmp/x86_64/longjmp.S
    CPU_SRCS		:= src/cpu/x86/cpuFeatures.c

  else ifeq ($(TARGET_ARCH),aarch64)
    CRT_START_SRCS	:= src/crt/linux/aarch64/start.S
    SYSCALL_SRCS	:= src/syscall/linux/aarch64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/aarch64/setjmp.S \
			   src/setjmp/aarch64/longjmp.S

  else
    $(error targets.mk: unsupported Linux arch '$(TARGET_ARCH)')
  endif

# FreeBSD
else ifeq ($(TARGET_OS),FreeBSD)

  ifeq ($(TARGET_ARCH),x86_64)
    CRT_START_SRCS	:= src/crt/freebsd/x86_64/start.S
    SYSCALL_SRCS	:= src/syscall/freebsd/x86_64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/x86_64/setjmp.S \
			   src/setjmp/x86_64/longjmp.S
	CPU_SRCS		:= src/cpu/x86/cpuFeatures.c

  else ifeq ($(TARGET_ARCH),aarch64)
    CRT_START_SRCS	:= src/crt/freebsd/aarch64/start.S
    SYSCALL_SRCS	:= src/syscall/freebsd/aarch64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/aarch64/setjmp.S \
			   src/setjmp/aarch64/longjmp.S

  else
    $(error targets.mk: unsupported FreeBSD arch '$(TARGET_ARCH)')
  endif

# Darwin (macOS, iOS)
else ifeq ($(TARGET_OS),Darwin)

  ifeq ($(TARGET_ARCH),x86_64)
    CRT_START_SRCS	:= src/crt/darwin/x86_64/start.S
    SYSCALL_SRCS	:= src/syscall/darwin/x86_64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/x86_64/setjmp.S \
			   src/setjmp/x86_64/longjmp.S
	CPU_SRCS		:= src/cpu/x86/cpuFeatures.c

  else ifeq ($(TARGET_ARCH),arm64)
    CRT_START_SRCS	:= src/crt/darwin/arm64/start.S
    SYSCALL_SRCS	:= src/syscall/darwin/arm64/__haj_syscall6.S
    SETJMP_SRCS		:= src/setjmp/aarch64/setjmp.S \
			   src/setjmp/aarch64/longjmp.S

  else
    $(error targets.mk: unsupported Darwin arch '$(TARGET_ARCH)')
  endif

# Windows (mingw)
else ifeq ($(TARGET_OS),Windows)

  # Windows uses the mingw CRT startup and setjmp/longjmp.
  # We only provide the syscall shim.
  CRT_START_SRCS	:=
  SYSCALL_SRCS		:= src/syscall/windows/__haj_syscall6.c
  SETJMP_SRCS		:=

# Unknown OS
else
  $(error targets.mk: unsupported OS '$(TARGET_OS)')
endif
