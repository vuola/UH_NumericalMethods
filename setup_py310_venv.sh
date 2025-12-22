#!/usr/bin/env bash
set -eo pipefail

VENV_DIR=".venv"
PYTHON_VERSION="3.10"
PYTHON_BIN="python${PYTHON_VERSION}"
REQUIREMENTS_FILE="requirements.txt"

echo ">>> Detecting OS..."
if [[ ! -f /etc/os-release ]]; then
    echo "ERROR: Cannot detect OS (missing /etc/os-release)"
    return 1
fi

. /etc/os-release

if [[ "${ID:-}" != "ubuntu" ]]; then
    echo "ERROR: This script supports Ubuntu only."
    return 1
fi

echo ">>> Ubuntu ${VERSION_ID} detected"

echo ">>> Checking for ${PYTHON_BIN}..."
if ! command -v "${PYTHON_BIN}" >/dev/null 2>&1; then
    echo ">>> ${PYTHON_BIN} not found, installing..."

    sudo apt update
    sudo apt install -y software-properties-common

    UBUNTU_MAJOR="${VERSION_ID%%.*}"

    if (( UBUNTU_MAJOR >= 24 )); then
        echo ">>> Ubuntu ${VERSION_ID} detected — adding deadsnakes PPA"
        sudo add-apt-repository -y ppa:deadsnakes/ppa
        sudo apt update
    fi

    sudo apt install -y \
        "python${PYTHON_VERSION}" \
        "python${PYTHON_VERSION}-venv" \
        "python${PYTHON_VERSION}-dev"
else
    echo ">>> ${PYTHON_BIN} already installed"
fi

echo ">>> Creating virtual environment (${VENV_DIR})"
"${PYTHON_BIN}" -m venv "${VENV_DIR}"

echo ">>> Activating virtual environment"
# shellcheck disable=SC1091
source "${VENV_DIR}/bin/activate"

echo ">>> Verifying interpreter"
python --version

if [[ "$(python -c 'import sys; print(sys.version_info[:2])')" != "(3, 10)" ]]; then
    echo "ERROR: Virtual environment is not using Python 3.10"
    return 1
fi

echo ">>> Upgrading pip/setuptools/wheel"
python -m pip install --upgrade pip setuptools wheel

if [[ -f "${REQUIREMENTS_FILE}" ]]; then
    echo ">>> Installing Python dependencies from ${REQUIREMENTS_FILE}"
    pip install -r "${REQUIREMENTS_FILE}"
else
    echo "WARNING: ${REQUIREMENTS_FILE} not found, skipping dependency installation"
fi

echo ">>> SUCCESS"
echo ">>> Python executable: $(which python)"
echo ">>> Python version:    $(python --version)"
echo ">>> Virtual env path:  ${VENV_DIR}"
