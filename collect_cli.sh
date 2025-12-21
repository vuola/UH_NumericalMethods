#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
OUT_DIR="$ROOT_DIR/submission/bin"

echo "▶ Preparing output directory"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"

echo "▶ Searching for CLI executables in build/exercise*"

find "$BUILD_DIR" -maxdepth 1 -type d -name "exercise*" | while read -r ex_dir; do
    echo "  ▶ Scanning $ex_dir"

    find "$ex_dir" -type f | while read -r f; do
        # Skip obvious non-candidates
        [[ "$f" == *.so ]] && continue
        [[ "$f" == *.a  ]] && continue
        [[ "$f" == *.o  ]] && continue

        # Check if file is an ELF executable
        if file "$f" | grep -q "ELF.*executable"; then
            echo "    ✔ Found executable: $(basename "$f")"
            cp "$f" "$OUT_DIR/"
        fi

    done
done

echo "▶ Collecting known input files per exercise"

find "$ROOT_DIR" -maxdepth 1 -type d -name "exercise*" | while read -r ex_dir; do
    ex_name="$(basename "$ex_dir")"

    echo "  ▶ $ex_name"

    find "$ex_dir" -maxdepth 1 -type f \( \
        -name "matrix6.txt" -o \
        -name "matrix100.txt" -o \
        -name "matrix6singular1.txt" -o \
        -name "matrix6singular2.txt" \
    \) ! -name "CMakeLists.txt" ! -name "CMakeCache.txt" | while read -r f; do
        echo "    ✔ $(basename "$f")"
        cp "$f" "$OUT_DIR/"
    done
done




echo "✅ Done. Executables copied to submission/bin/"

