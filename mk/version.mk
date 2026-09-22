# version.mk - extract version info from include/haj/version.h
#
# This file reads the version numbers directly from the C header so
# there is exactly ONE place to edit when releasing.
#
# Variables defined:
#   HAJ_VERSION_MAJOR   (int)
#   HAJ_VERSION_MINOR   (int)
#   HAJ_VERSION_PATCH   (int)
#   HAJ_VERSION         (e.g. "0.1.0")
#   HAJ_VERSION_TAG     (e.g. "v0.1.0")

VERSION_HEADER := include/haj/version.h

# Extract the three integers from the C header.
# The pattern matches lines like:
#   # define HAJ_VERSION_MAJOR	0
# where the separator between the macro name and the value is one
# or more spaces/tabs.
HAJ_VERSION_MAJOR := $(shell sed -n 's/^# define HAJ_VERSION_MAJOR[ \t][ \t]*//p' $(VERSION_HEADER))
HAJ_VERSION_MINOR := $(shell sed -n 's/^# define HAJ_VERSION_MINOR[ \t][ \t]*//p' $(VERSION_HEADER))
HAJ_VERSION_PATCH := $(shell sed -n 's/^# define HAJ_VERSION_PATCH[ \t][ \t]*//p' $(VERSION_HEADER))

# Composed version strings.
HAJ_VERSION		:= $(HAJ_VERSION_MAJOR).$(HAJ_VERSION_MINOR).$(HAJ_VERSION_PATCH)
HAJ_VERSION_TAG	:= v$(HAJ_VERSION)

# Export so sub-makefiles can use them.
export HAJ_VERSION_MAJOR
export HAJ_VERSION_MINOR
export HAJ_VERSION_PATCH
export HAJ_VERSION
export HAJ_VERSION_TAG
