# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- OS detection: `include/bits/os.h` (`HAJ_OS_LINUX`, `HAJ_OS_FREEBSD`, `HAJ_OS_DARWIN`, `HAJ_OS_WINDOWS`)
- Architecture detection: `include/bits/arch.h` (`HAJ_ARCH_X86_64`, `HAJ_ARCH_AARCH64`, `HAJ_ARCH_I386`, `HAJ_ARCH_ARM`)
- Word size detection: `include/bits/wordsize.h` (`__HAJ_WORDSIZE`, `__HAJ_BYTE_ORDER`, `__HAJ_SIZEOF_*`)
- Internal types: `include/bits/types.h` (`__haj_size`, `__haj_ssize`, `__haj_mode`, `__haj_off`, ...)
- POSIX types: `include/sys/types.h` (`size_t`, `ssize_t`, `off_t`, `mode_t`, `pid_t`, ...)
  - ABI-matched per OS (`mode_t` is 32-bit on Linux, 16-bit on BSD/Darwin)
- Standard definitions: `include/stddef.h` (`size_t`, `ptrdiff_t`, `wchar_t`, `NULL`, `offsetof`, `max_align_t`)
- Fixed-width integers: `include/stdint.h` (`int8_t`..`int64_t`, limits, printf format macros)
- Boolean type: `include/stdbool.h` (`bool`, `true`, `false`)
- POSIX limits: `include/bits/limits.h` (`HAJ_PATH_MAX`, `HAJ_NAME_MAX`, `HAJ_ARG_MAX`, `HAJ_OPEN_MAX`, `HAJ_PIPE_BUF` per OS)
- Implementation limits: `include/limits.h` (`CHAR_BIT`, `INT_MAX`, `LONG_MAX`, `LLONG_MAX`, ... and POSIX aliases `PATH_MAX`, `NAME_MAX`, `ARG_MAX`, `OPEN_MAX`)
- Variable arguments: `include/stdarg.h` (`va_list`, `va_start`, `va_arg`, `va_end`, `va_copy`, `__gnuc_va_list`)
- Error codes: `include/bits/errno.h` (per-OS values for Linux, FreeBSD, Darwin, Windows)
- Error reporting: `include/errno.h` (thread-local `errno`, `__haj_errno`), `src/errno/errno.c`, `src/errno/strerror.c`
  - `strerror()` with per-OS message tables (common, networking, POSIX realtime, OS-specific)
  - Thread-local buffer for unknown error codes
- CRT internals: `include/bits/crt.h` (`__haj_run_atexit`, `__cxa_atexit`, `__cxa_finalize`, `__dso_handle`)
- Program termination: `src/crt/exit.c`, `src/crt/_exit.c`, `src/crt/abort.c`
- Exit handlers: `src/crt/atexit.c`, `src/crt/cxa_atexit.c`, `src/crt/cxa_finalize.c`, `src/crt/dso_handle.c`
- Startup code: per-OS and per-arch entry points
  - Linux x86_64 / aarch64, FreeBSD x86_64 / aarch64, Darwin x86_64 / arm64
  - Reads `argc`/`argv`/`envp` (from stack on Linux/FreeBSD, from registers on Darwin), calls `main` then `exit`
- Raw syscall interface: `include/bits/syscall.h` (`__haj_syscall6`, `HAJ_AT_FDCWD`, `HAJ_AT_*` flags)
- Syscall numbers per OS/arch: `include/bits/syscall/{linux/x86_64,linux/aarch64,freebsd,darwin,windows}.h`
- Syscall implementations per OS/arch:
  - Linux x86_64 / aarch64 (raw Linux convention, negative = `-errno`)
  - FreeBSD x86_64 / aarch64 (normalizes carry-flag error to `-errno`)
  - Darwin x86_64 / arm64 (same as FreeBSD)
  - Windows (C shim dispatching to the mingw CRT, normalizes `errno`)

### Changed

- Nothing yet

### Fixed

- Nothing yet

### Removed

- Removed `syscall.mk`

### Deprecated

- Nothing yet

## [0.1.0] - 2026-09-21

### Added

- Initial project structure: `include/`, `src/`, `test/`
- Build infrastructure: `Makefile`, `build.mk`, `sources.mk`, `cross.mk`, `syscall.mk`
- Versioning: `version.mk`, `include/haj/version.h`
- Release script: `scripts/release.sh`
- Development tooling: `.editorconfig`, `.clangd`, `.clang-tidy`, `.gitignore`, `.gitattributes`

### Changed

- Rewrote the library from a libft-based structure to a POSIX-like libc structure

### Removed

- All `ft_*` sources and headers from the old libft structure

[Unreleased]: https://github.com/moutigll/hajlib/compare/v0.1.0...HEAD
[0.1.0]: https://github.com/moutigll/hajlib/releases/tag/v0.1.0
