#!/bin/bash
if ! command -v flatpak &> /dev/null
then
    echo "Flatpak could not be found. Please install it before running this script."
    exit
fi

for app in $(flatpak list --app --columns=application)
do
    desktop_file=$(flatpak info --show-location $app)/export/share/applications/*.desktop
    if [ -f "$desktop_file" ]; then
        sudo cp "$desktop_file" /usr/share/applications/
    fi
done

for file in /usr/share/applications/*.desktop
do
    app_id=$(grep -E "^X-Flatpak=" "$file" | cut -d "=" -f 2)
    if [ ! -z "$app_id" ] && ! flatpak info $app_id &> /dev/null; then
        sudo rm "$file"
    fi
done

echo "Flatpak application desktop files have been updated in /usr/share/applications."