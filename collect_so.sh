#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
OUT_DIR="$ROOT_DIR/submission/python"

echo "▶ Preparing output directory"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

echo "▶ Searching for Python extension modules (*.so)..."

find "$BUILD_DIR" -type f -name "*.so" | while read -r so; do
    # Ensure this is a Python extension module (not a random shared lib)
    if file "$so" | grep -q "ELF.*shared object"; then
        echo "  ✔ Found .so: $so"
        cp "$so" "$OUT_DIR/"
    fi
done

echo "✅ Done. Python modules copied to submission/python/"
