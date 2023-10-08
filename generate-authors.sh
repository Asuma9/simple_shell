#!/bin/bash

# File path to write contributors to
AUTHORS_FILE="AUTHORS"

# Add header to the AUTHORS file
echo "# This file lists all contributors to the repository." > $AUTHORS_FILE
echo "# It is auto-generated using the generate-authors.sh script. DO NOT EDIT directly." >> $AUTHORS_FILE
echo "" >> $AUTHORS_FILE

# Extract contributors from Git commit history, sort them, and remove duplicates
git log --format='%aN <%aE>' | sort -u >> $AUTHORS_FILE

# Notify user
echo "AUTHORS file has been generated/updated."
