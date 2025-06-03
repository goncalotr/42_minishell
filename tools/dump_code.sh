#!/bin/bash

# Name of the output file
OUTPUT_FILE="all_code_dump_with_headers.txt"
# Directory to search in
SEARCH_DIR="./../minishell/"

echo "--------------------------------------------------"
echo "Starting code and structure dump..."
echo "Searching in: $(realpath "$SEARCH_DIR")"
echo "Output file: $OUTPUT_FILE"
echo "--------------------------------------------------"

# --- 1. Gather Statistics ---
echo "Gathering statistics..."

# Count .c files
num_c_files=$(find "$SEARCH_DIR" -type f -name "*.c" -print | wc -l)

# Count .h files
num_h_files=$(find "$SEARCH_DIR" -type f -name "*.h" -print | wc -l)

# Count Makefiles (Makefile, makefile, Makefile.*)
num_makefiles=$(find "$SEARCH_DIR" -type f \( -name "Makefile" -o -name "makefile" -o -name "Makefile.*" \) -print | wc -l)

# Total number of files to be dumped
total_matching_files=$((num_c_files + num_h_files + num_makefiles))

# Count total number of directories (including the SEARCH_DIR itself and subdirectories)
# count only subdirectories subdirectories: find "$SEARCH_DIR" -mindepth 1 -type d
num_directories=$(find "$SEARCH_DIR" -type d | wc -l)

# Get current date and time
current_datetime=$(date +"%Y-%m-%d %H:%M:%S %Z")

echo "Statistics gathered:"
echo "  .c files: $num_c_files"
echo "  .h files: $num_h_files"
echo "  Makefiles: $num_makefiles"
echo "  Total source/make files: $total_matching_files"
echo "  Total directories searched (incl. root): $num_directories"

# --- 2. Write Summary Header to Output File ---
# Create/overwrite the output file with the summary
{
  echo "=================================================="
  echo "PROJECT DUMP SUMMARY"
  echo "=================================================="
  echo "Dump generated on: $current_datetime"
  echo "Searched directory: $(realpath "$SEARCH_DIR")"
  echo "--------------------------------------------------"
  echo "File Type Counts:"
  echo "  C source files (.c):      $num_c_files"
  echo "  Header files (.h):        $num_h_files"
  echo "  Makefiles (Makefile*):    $num_makefiles"
  echo "  ------------------------------------------------"
  echo "  TOTAL files to be dumped: $total_matching_files"
  echo "--------------------------------------------------"
  echo "Structure:"
  echo "  Total directories scanned: $num_directories"
  echo "=================================================="
  echo # Add a blank line before file contents start
  echo # Add another for more space
} > "$OUTPUT_FILE" # Use > to overwrite/create the file with the header


# --- 3. Append File Contents ---
echo "Appending file contents..."

# Find all relevant files and append their content.
# -print0: prints filenames separated by a null character (safer for filenames with spaces/newlines).
# while IFS= read -r -d $'\0' file_path: reads null-delimited filenames robustly.
find "$SEARCH_DIR" -type f \( \
    -name "*.c" -o \
    -name "*.h" -o \
    -name "Makefile" -o \
    -name "makefile" -o \
    -name "Makefile.*" \
\) -print0 | while IFS= read -r -d $'\0' file_path; do
    echo "Processing: $file_path"
    # Append to the output file
    echo "--------------------------------------------------" >> "$OUTPUT_FILE"
    echo "FILE: $file_path" >> "$OUTPUT_FILE"
    echo "--------------------------------------------------" >> "$OUTPUT_FILE"
    cat "$file_path" >> "$OUTPUT_FILE"
    echo "" >> "$OUTPUT_FILE" # Add a blank line for separation
    echo "" >> "$OUTPUT_FILE" # Add another for more space after file content
done

echo "--------------------------------------------------"
if [ "$total_matching_files" -eq 0 ]; then
    echo "No matching .c, .h, or Makefile files were found to dump."
    echo "The output file '$OUTPUT_FILE' contains only the summary header."
else
    echo "All found files (with headers) have been concatenated into '$OUTPUT_FILE'."
fi
echo "Dump process complete."
