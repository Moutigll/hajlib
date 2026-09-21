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

### Changed

- Nothing yet

### Fixed

- Nothing yet

### Removed

- Nothing yet

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
