#!/bin/bash
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    rm -rf "$HOME/.cxoffice/*/drive_c/windows/system32/spool/drivers/color/*"
    echo "The timer for Crossover software containers has been cleared."
elif [[ "$OSTYPE" == "darwin"* ]]; then
    rm -rf "$HOME/Library/Application Support/CrossOver/Bottles/*/Contents/Resources/Drive_C/windows/system32/spool/drivers/color/*"
    echo "The timer for Crossover software containers has been cleared."
else
    echo "Unsupported operating system. This script only supports Linux and macOS."
fi