#!/bin/bash

# Path to the folder containing files
FOLDER="./maps/bad/"

# Loop through each file in the folder
for filepath in "$FOLDER"/*; do
    # Get just the file name (not the full path)
    filename=$(basename "$filepath")
    
    # Example command using the file name
    echo "Processing file: $filename"
    
    # Replace the line below with your actual command
    ./cub3D "$FOLDER$filename"
done
