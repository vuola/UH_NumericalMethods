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


        # Copy all .txt files
        if [[ "$f" == *.txt ]]; then
            echo "    ✔ Found text file: $(basename "$f")"
            cp "$f" "$OUT_DIR/"
            continue
        fi

        # Check if file is an ELF executable
        if file "$f" | grep -q "ELF.*executable"; then
            echo "    ✔ Found executable: $(basename "$f")"
            cp "$f" "$OUT_DIR/"
        fi

    done
done

echo "✅ Done. Executables copied to submission/bin/"

