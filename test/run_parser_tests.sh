#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color
PASS="✅"
FAIL="❌"

TESTER="$(dirname "$0")/test_parser"

run_tests() {
    local dir="$1"
    local label="$2"
    for file in "$dir"/*; do
        if [ -f "$file" ]; then
            "$TESTER" "$file" > /dev/null 2>&1
            result=$?
            if [ $result -eq 0 ]; then
                echo -e "${GREEN}$PASS${NC} $label: $(basename "$file")"
            else
                echo -e "${RED}$FAIL${NC} $label: $(basename "$file")"
            fi
            echo "----------------------------------------"
        fi
    done
}

run_tests "../maps/good" "GOOD"
run_tests "../maps/bad" "BAD" 