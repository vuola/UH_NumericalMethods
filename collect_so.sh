#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
OUT_DIR="$ROOT_DIR/submission/python"

echo "▶ Preparing output directory"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

cp -a "$ROOT_DIR/build/runtime/." "$ROOT_DIR/submission/python/"

echo "✅ Done. Python modules copied to submission/python/"
