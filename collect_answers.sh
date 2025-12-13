#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
OUT_DIR="$ROOT_DIR/submission/answers"

echo "▶ Preparing scripts output directory"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

echo "▶ Collecting scripts and documentation per exercise"

find "$ROOT_DIR" -maxdepth 1 -type d -name "exercise*" | while read -r ex_dir; do
    ex_name="$(basename "$ex_dir")"

    echo "  ▶ $ex_name"
    mkdir -p "$OUT_DIR/$ex_name"

    find "$ex_dir" -maxdepth 1 -type f \( \
        -name "*.cpp" -o \
        -name "*.txt" -o \
        -name "*.png" -o \
        -name "*.pdf" \
    \) ! -name "CMakeLists.txt" ! -name "CMakeCache.txt" | while read -r f; do
        echo "    ✔ $(basename "$f")"
        cp "$f" "$OUT_DIR/$ex_name/"
    done
done

echo "✅ Done. Scripts and documentation copied to submission/scripts/"
