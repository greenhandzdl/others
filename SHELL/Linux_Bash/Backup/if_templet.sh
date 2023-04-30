#!/bin/bash

read -p "Do you want to install the software? (Y/y/N/n) " answer
if [ "$answer" == "Y" ] || [ "$answer" == "y" ]
then
    echo "Installing software..."
    # Add commands to install software here
elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
then
    echo "Skipping installation..."
else
    echo "Invalid input. Skipping installation..."
fi