#!/bin/sh
#Az : A live wallpaper selector that run "livewallpaper" command on the selected preview (livewallpaper works with xwinwrap and mpv)

CACHE_DIR="$HOME/.cache/sxivlivewall/"
TMP_DIR="/tmp/sxivlivewall/"
WALLPAPE_DIR="$HOME/Videos/LiveWallpapers/"
# NOTIFIER="dunstify -a LiveWallpaper"
SXIVINPUT=""
[ -d "$CACHE_DIR" ] || mkdir $CACHE_DIR
[ -d "$TMP_DIR" ] || mkdir $TMP_DIR
declare -A hashdico    #Hash
for file in $WALLPAPE_DIR*; do
    filehash=$(sha1sum $file | sed 's/  .*//')    #Hash so we wont regenerate a preview when a file has been renamed but it can slow things a bit
    hashdico[$filehash]=$file    #Hash
    OUT="$CACHE_DIR${filehash}.gif"    #Hash
    #OUT="$CACHE_DIR${file: ${#WALLPAPE_DIR}:-4}.gif"     #NoHash mostly usefull if it is to slow. If used comment the #Hash lines uncomment #NoHash lines

    #[ -f $OUT ] || ffmpegthumbnailer -i "${file}" -o "$OUT" -s 0       #static image with png in place of gif
    #[ -f $OUT ] || ffmpeg -i "${file}" -r 10 -ss 2 -t 4 -vf scale="720:-1,format=yuv420p" -threads 8 $OUT        #faster but bad quality

    [ -f $OUT ] || $($(ffmpegthumbnailer -i ${file} -o ${TMP_DIR}${filehash}.png & \
    # && $NOTIFIER "Live Wallpaper" "The animated thumbnail for <b>${file: ${#WALLPAPE_DIR}:-4}</b> is being generated..." --icon="${TMP_DIR}${filehash}.png") & \    #Generate tumbnail for notification
        ffmpeg -i ${file} -r 15 -ss 1 -t 3 -vf scale="720:-1" -threads 8 -f image2pipe -vcodec ppm - | convert -delay 6 - $OUT)   #generate animated thumbnail

    SXIVINPUT="$SXIVINPUT ${OUT}"
done

bspc rule -a '*' -o state=floating
selected=$(sxiv -tboa -s f -N "Live Wallpaper" ${SXIVINPUT})     #select
echo ${hashdico[${selected: ${$CACHE_DIR}:-4}]}
# [ $selected != "" ] && $HOME/scripts/livewallpaper ${hashdico[${selected: ${#CACHE_DIR}:-4}]}    #Hash make livewallpaper apply the selected wallpaper
#[ $selected != "" ] && $HOME/scripts/livewallpaper $WALLPAPE_DIR${selected: ${#CACHE_DIR}:-4}.mp4    #NoHash make livewallpaper apply the selected wallpaper

shopt -s extglob
cd $CACHE_DIR
rm !($(echo ${SXIVINPUT} | sed -e "s+$CACHE_DIR++g ; s+ +|+g"))    #Remove useless previews
