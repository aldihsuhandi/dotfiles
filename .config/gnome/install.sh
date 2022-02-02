# core packages
paru -S --noconfirm gnome 

# extension
paru -S gnome-tweaks gnome-shell-extension-arc-menu gnome-shell-extension-bluetooth-quick-connect gnome-shell-extension-blur-my-shell-git gnome-shell-extension-clipboard-indicator gnome-shell-extension-dash-to-panel gnome-shell-extension-gsconnect gnome-shell-extension-sound-output-device-chooser gnome-shell-extension-status-area-horizontal-spacing gnome-shell-extension-tray-icons-reloaded --noconfirm

# turn off win + num shortcut
for i in $(seq 1 9); do gsettings set org.gnome.shell.keybindings switch-to-application-${i} []; done
