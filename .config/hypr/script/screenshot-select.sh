bash -c 'area=$(slurp); file=~/Pictures/screenshot/screenshot-$(date +%s).png; grim -g "$area" "$file" && wl-copy < "$file"'
