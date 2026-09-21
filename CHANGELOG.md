# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Initial project structure: `include/`, `src/`, `test/`
- Makefile infrastructure: `Makefile`, `build.mk`, `sources.mk`, `cross.mk`, `syscall.mk`
- Versioning: `version.mk`, `include/haj/version.h`
- Release script: `scripts/release.sh`
- Development tooling: `.editorconfig`, `.clangd`, `.clang-tidy`, `.gitignore`
- OS detection: `include/bits/os.h` (`HAJ_OS_LINUX`, `HAJ_OS_FREEBSD`, `HAJ_OS_DARWIN`, `HAJ_OS_WINDOWS`)
- Architecture detection: `include/bits/arch.h` (`HAJ_ARCH_X86_64`, `HAJ_ARCH_AARCH64`, `HAJ_ARCH_I386`, `HAJ_ARCH_ARM`)
- Word size detection: `include/bits/wordsize.h` (`__HAJ_WORDSIZE`, `__HAJ_BYTE_ORDER`, `__HAJ_SIZEOF_*`)
- POSIX types: `include/bits/types.h` (internal `__haj_*` typedefs) and `include/sys/types.h` (public POSIX aliases)
- Fixed-width integers, pointer-sized types (`intptr`/`uintptr`), and max-width integers (`intmax`/`uintmax`)
- POSIX type aliases: `size_t`, `ssize_t`, `ptrdiff_t`, `mode_t`, `off_t`, `pid_t`, `uid_t`, `gid_t`, `dev_t`, `ino_t`, `nlink_t`, `blksize_t`, `blkcnt_t`, `time_t`, `suseconds_t`, `clock_t`, `clockid_t`
- OS-specific ABI matching: `mode_t` (unsigned int on Linux, unsigned short on BSD/Darwin), `dev_t` (signed 32-bit on Darwin), `nlink_t` (16-bit on Darwin, 64-bit elsewhere)
- `stddef.h`: size_t, ptrdiff_t, wchar_t, NULL, offsetof, max_align_t
- `stdint.h`: fixed-width integer types, limits, printf format macros
- `stdbool.h`: bool, true, false

### Changed

- Rewrote the library from a libft-based structure to a POSIX-like libc structure

### Removed

- All `ft_*` sources and headers from the old libft structure

[Unreleased]: https://github.com/moutigll/hajlib/compare/v0.1.0...HEAD
