query=$(rofi -dmenu -window-title "Search:  " -lines 0 -hide-scrollbar -theme $HOME/.config/rofi/themes/dracula/youtube-applet.rasi)
if [ -z "$query" ]
then
    exit
fi
query=$(sed -e 's|+|%2B|g' -e 's|#|%23|g' -e 's|&|%26|g' -e 's| |+|g' <<< "$query")
videoIDs=$(curl -s "https://www.youtube.com/results?search_query=$query" | grep -oP '"videoRenderer":{"videoId":".{11}".+?"text":".+?[^\\](?=")' | sed 's|\\\"|“|g' | awk -F\" '{ print $6 " " $NF}')
play=$(rofi -dmenu -window-title "Filter:   " -sep "\n" <<< "$videoIDs" -columns 1 -hide-scrollbar -theme $HOME/.config/rofi/themes/dracula/youtube-applet.rasi)
if [ -z "$play" ]
then
    exit
fi
echo $(echo $play | cut -d ' ' -f1)
celluloid "https://youtu.be/$(echo $play | cut -d ' ' -f1)"
