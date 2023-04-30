#!/bin/bash
if ! command -v you-get &> /dev/null
then
    echo "you-get could not be found. Please install it before running this script."
    exit
fi

echo "Please enter the URL of the content you want to download:"
read url

echo "Available formats and qualities:"
you-get -i $url

echo "Please enter the stream ID of the format and quality you want to download (e.g. 'hd'):"
read stream_id

you-get --itag="$stream_id" $url