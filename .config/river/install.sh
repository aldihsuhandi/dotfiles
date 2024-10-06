#!/bin/bash
paru --noconfirm -S river river-bsp-layout wofi waybar lightdm light-locker loupe spectacle nemo nemo-fileroller nemo-preview nemo-share audacious pavucontrol-qt alacritty kitty gnome-calculator okular gnome-system-monitor dunst lxqt-wayland-session-git lxqt-config polkit-kde-agent blueman nordic-darker-theme-git kvantum qt6ct firefox nvim xdg-desktop-portal xdg-desktop-portal-kde xdg-desktop-portal-gtk wl-clipboard rofi brightnessctl playerctl nitrogen arc-gtk-theme kvantum-theme-arc

sudo echo "QT_QPA_PLATFORMTHEME=qt6ct" >> /etc/environment
sudo echo "GTK_USE_PORTAL=1" >> /etc/environment
sudo echo "BROWSER=firefox" >> /etc/environment
sudo echo "EDITOR=nvim" >> /etc/environment
sudo echo "MOZ_ENABLE_WAYLAND=1" >> /etc/environment
