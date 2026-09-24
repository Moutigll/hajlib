#!/bin/sh
# scripts/package.sh - build release artifacts for hajlib.
#
# Usage:
#   ./scripts/package.sh <version> <platform=lib>...
#
# Example:
#   ./scripts/package.sh 0.2.0 \
#       linux-x86_64=libhajc.a \
#       linux-aarch64=libhajc-aarch64.a
#
# This script:
#   1. Verifies the git tag vX.Y.Z exists.
#   2. Creates a source tarball from the tag.
#   3. For each platform, creates a binary tarball containing
#      the given library file, the public headers, and the
#      build configuration.
#   4. Computes SHA-256 hashes for all tarballs.
#
# Output is in releases/vX.Y.Z/.

set -e

# Argument parsing
VERSION="$1"
shift

if [ -z "$VERSION" ] || [ "$#" -eq 0 ]; then
    echo "Usage: $0 <version> <platform=lib>..."
    echo "Example: $0 0.2.0 linux-x86_64=libhajc.a linux-aarch64=libhajc-aarch64.a"
    exit 1
fi

case "$VERSION" in
    [0-9]*.[0-9]*.[0-9]*) ;;
    *)
        echo "Error: invalid version '$VERSION' (expected X.Y.Z)"
        exit 1
        ;;
esac

TAG="v$VERSION"
PROJECT="libhajc"
RELEASE_DIR="releases/$TAG"

# Sanity checks
if ! git rev-parse "$TAG" >/dev/null 2>&1; then
    echo "Error: git tag '$TAG' does not exist"
    exit 1
fi

for arg in "$@"; do
    case "$arg" in
        *=*) ;;
        *)
            echo "Error: invalid argument '$arg' (expected platform=libfile)"
            exit 1
            ;;
    esac
    libfile="${arg#*=}"
    if [ ! -f "$libfile" ]; then
        echo "Error: library '$libfile' does not exist"
        exit 1
    fi
done

if [ ! -d include ] || [ ! -d mk ]; then
    echo "Error: must be run from the hajlib source tree"
    exit 1
fi

# Source tarball
echo "=== Creating source tarball ==="
mkdir -p "$RELEASE_DIR"

git archive \
    --format=tar.gz \
    --prefix="$PROJECT-$VERSION/" \
    "$TAG" \
    -o "$RELEASE_DIR/$PROJECT-$VERSION.tar.gz"

# Binary tarballs
for arg in "$@"; do
    platform="${arg%%=*}"
    libfile="${arg#*=}"

    echo "=== Creating binary tarball for $platform ==="

    pkg="$PROJECT-$VERSION-$platform"
    stage="/tmp/$pkg"

    rm -rf "$stage"
    mkdir -p "$stage/lib"
    mkdir -p "$stage/include"

    cp "$libfile" "$stage/lib/libhajc.a"
    cp -r include/* "$stage/include/"
    cp mk/config.mk "$stage/"
    cp mk/hajlib.mk "$stage/"
    cp LICENSE "$stage/" 2>/dev/null || true
    cp README.md "$stage/" 2>/dev/null || true
    cp CHANGELOG.md "$stage/" 2>/dev/null || true

    (cd /tmp && tar czf "$pkg.tar.gz" "$pkg")
    mv "/tmp/$pkg.tar.gz" "$RELEASE_DIR/"
    rm -rf "$stage"
done

# Hashes
echo "=== Computing SHA-256 hashes ==="
(cd "$RELEASE_DIR" && sha256sum *.tar.gz > SHA256SUMS)

# Summary
echo ""
echo "=== Release artifacts for $TAG ==="
ls -lh "$RELEASE_DIR"
echo ""
echo "--- SHA256SUMS ---"
cat "$RELEASE_DIR/SHA256SUMS"
echo ""
echo "=== To sign all artifacts ==="
echo ""
echo "    cd $RELEASE_DIR && for f in *.tar.gz; do gpg --armor --detach-sign \"\$f\"; done"
echo ""
