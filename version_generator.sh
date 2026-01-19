#!/bin/bash

TIMESTAMP=$(date +%Y%m%d_%H%M)
GIT_HASH=$(git rev-parse --short HEAD 2>/dev/null || echo "unknown")
# Output the final version string
echo "${TIMESTAMP}_${GIT_HASH}" > ./version.txt
echo Generated version to version.txt "${TIMESTAMP}_${GIT_HASH}"
