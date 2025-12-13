#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
OUT_DIR="$ROOT_DIR/submission"
PYTHON_PKG="uh_numerical"

echo "▶ Preparing submission directory"
rm -rf "$OUT_DIR"
mkdir -p "$OUT_DIR"/{bin,python/$PYTHON_PKG,scripts}
touch "$OUT_DIR/python/$PYTHON_PKG/__init__.py"

echo "▶ Scanning build directory"

find "$BUILD_DIR" -maxdepth 1 -type d -name "exercise*" | while read -r ex_dir; do
    ex_name="$(basename "$ex_dir")"

    echo "  ▶ $ex_name"

    mkdir -p "$OUT_DIR/python/$PYTHON_PKG/$ex_name"

    # --- CLI executables ---
    find "$ex_dir" -maxdepth 1 -type f ! -name "*.so" ! -name "*.a" ! -name "*.o" \
        -exec file {} \; | grep "ELF.*executable" | cut -d: -f1 | while read -r exe; do
            echo "    CLI → $(basename "$exe")"
            cp "$exe" "$OUT_DIR/bin/"
    done

    # --- Python extension modules ---
    find "$ex_dir" -maxdepth 1 -type f -name "*.so" | while read -r so; do
        echo "    PY  → $(basename "$so")"
        cp "$so" "$OUT_DIR/python/$PYTHON_PKG/$ex_name/"
    done
done

echo "▶ Collecting Python scripts"

find "$ROOT_DIR" -maxdepth 2 -type f -name "*.py" ! -path "*/build/*" | while read -r py; do
    ex_name="$(basename "$(dirname "$py")")"
    out_name="${ex_name}_$(basename "$py")"
    echo "  SCRIPT → $out_name"
    cp "$py" "$OUT_DIR/scripts/$out_name"
done

echo "▶ Writing README"

cat > "$OUT_DIR/README.txt" <<EOF
UH Numerical Methods — Submission

Requirements:
- Ubuntu
- Python 3.10+
- numpy, matplotlib installed

How to run CLI executables:
  ./bin/<executable>

How to run Python versions:
  export PYTHONPATH=\$PWD/python:\$PYTHONPATH
  python scripts/exercise01_plotFunks.py

Contents:
- bin/      : CLI executables
- python/   : eigenpy-based Python modules
- scripts/  : plotting scripts

No installation required.
EOF

echo "▶ Creating archive"
tar czf submission.tar.gz submission

echo "✅ submission.tar.gz created successfully"

