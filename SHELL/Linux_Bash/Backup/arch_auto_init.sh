#!/bin/bash

# Run the sh by default: yes | ./script.sh

# Check if the operating system is Arch Linux
if [[ -f /etc/arch-release ]]; then
    # Check if yay is installed
    if ! command -v yay &> /dev/null; then
        # Prompt the user to install yay
        read -p "Do you want to install yay? [Y/n] " -n 1 -r
        echo
        # Install yay if the user agrees
        if [[ $REPLY =~ ^[Yy]$ ]] || [[ -z $REPLY ]]; then
            whoami #For test
            pacman -Syu
            pacman -S sudo
            sudo pacman -S git base-devel
            # Check if the /opt directory exists and create it if it doesn't
            [ ! -d /opt ] && sudo mkdir /opt
            cd /opt
            sudo git clone https://aur.archlinux.org/yay.git
            sudo chown -R $USER:$USER yay
            cd yay
            makepkg -si
        fi
    fi

    yay -Syu

    # Check if zsh is already installed
    if yay -Qi zsh &> /dev/null; then
        echo "zsh is already installed"
    else
        read -p "zsh is not installed, do you want to install it? (y/n)" answer
        if [[ $answer == "y" ]]; then
            yay -S zsh
        else
            echo "Skipping zsh installation"
        fi
    fi
    # Check if zsh is the default shell
    if [[ $SHELL != "/bin/zsh" ]]; then
        read -p "Do you want to set zsh as the default shell? (y/n)" answer
        if [[ $answer == "y" ]]; then
            chsh -s /bin/zsh
            echo "zsh has been set as the default shell"
        else
            echo "Skipping setting zsh as the default shell"
        fi
    else
        echo "zsh is already the default shell"
    fi
    # Check if Oh My Zsh is already installed
    if yay -Qi oh-my-zsh-git &> /dev/null; then
        echo "Oh My Zsh is already installed"
    else
        read -p "Oh My Zsh is not installed, do you want to install it? (y/n)" answer
        if [[ $answer == "y" ]]; then
            yay -S oh-my-zsh-git
        else
            echo "it won't be installed."
        fi
    fi

    # Check if lolcat command is installed
    if ! command -v lolcat &> /dev/null
    then
        # Prompt user to install lolcat
        read -p "Do you want to install lolcat? [y/N] " answer
        # Check user's answer
        if [ "$answer" = "y" ] || [ "$answer" = "Y" ]
        then
            # Install lolcat using yay package manager
            yay -S lolcat
        else
            echo "Skipping Lolcat installation."
        fi
    fi

    read -p "Do you want to use lolcat eggs(From Author)? [y/N] " answer
    # Check user's answer
    if [ "$answer" = "y" ] || [ "$answer" = "Y" ]
    then
        # Define the code to be added
        code='
        lol()
        {
            if [ -t 1 ]; then
                "$@" | lolcat
            else
                "$@"
            fi
        }
        COMMANDS=(
            ls
            tree
            git
            cat
            neofecch
        )
        for COMMAND in "${COMMANDS[@]}"; do
            alias "${COMMAND}=lol ${COMMAND}"
            alias ".${COMMAND}=$(which ${COMMAND})"
        done
        '
        # Check if the code already exists in the environment script
        if ! grep -qF "$code" ~/.zshrc; then
            # Append the code to the environment script
            echo "$code" >> ~/.zshrc
        fi
        # Check if the code already exists in the environment script
        if ! grep -qF "$code" ~/.bashrc; then
            # Append the code to the environment script
            echo "$code" >> ~/.bashrc
        else
                    echo "Skipping Lolcat eggs."
        fi
    fi

    # Check if Cockpit is already installed
    if pacman -Qs cockpit > /dev/null ; then
      echo "Cockpit is already installed"
    else
      read -p "Do you want to install Cockpit? [y/N] " confirm
      if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
        echo "Installing Cockpit..."
        yay -S cockpit
      else
        echo "Skipping Cockpit installation"
      fi
    fi
    # Check if the Cockpit service is enabled
    if systemctl is-enabled cockpit.socket > /dev/null ; then
      echo "Cockpit service is enabled"
    else
      read -p "Do you want to enable the Cockpit service? [y/N] " confirm
      if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
        echo "Enabling Cockpit service..."
        sudo systemctl enable cockpit.socket
      else
        echo "Skipping enabling Cockpit service"
      fi
    fi
    # Check if the Cockpit service is started
    if systemctl is-active cockpit.socket > /dev/null ; then
      echo "Cockpit service is started"
    else
      read -p "Do you want to start the Cockpit service? [y/N] " confirm
      if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
        echo "Starting Cockpit service..."
        sudo systemctl start cockpit.socket
      else
        echo "Skipping starting Cockpit service"
      fi
    fi

    # Check if GDM is already installed
    if pacman -Qs gdm > /dev/null ; then
      echo "GDM is already installed"
      # Check if the GDM service is enabled
      if systemctl is-enabled gdm > /dev/null ; then
        echo "GDM service is enabled"
      else
        read -p "Do you want to enable the GDM service? [y/N] " confirm
        if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
          echo "Enabling GDM service..."
          sudo systemctl enable gdm
        else
          echo "Skipping enabling GDM service"
        fi
      fi
    else
      read -p "Do you want to install GDM? [y/N] " confirm
      if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
        echo "Installing GDM..."
        yay -S gdm
        # Check if the GDM service is enabled after installing GDM
        if systemctl is-enabled gdm > /dev/null ; then
          echo "GDM service is enabled"
        else
          read -p "Do you want to enable the GDM service? [y/N] " confirm
          if [[ $confirm == [yY] || $confirm == [yY][eE][sS] ]]; then
            echo "Enabling GDM service..."
            sudo systemctl enable gdm
          else
            echo "Skipping enabling GDM service"
          fi
        fi
      else
        echo "Skipping GDM installation"
      fi
    fi

    # Check if GNOME is installed
    if [ "$XDG_CURRENT_DESKTOP" != "GNOME" ]; then
        # Prompt the user to install GNOME
        read -p "Do you want to install GNOME? [Y/n] " -n 1 -r
        echo
        # Install GNOME if the user agrees
        if [[ $REPLY =~ ^[Yy]$ ]] || [[ -z $REPLY ]]; then
            yay -S gnome
        fi
    fi


    read -p "Do you want to use my custom? (Y/y/N/n)[A long install...]" answer
    if [ "$answer" == "Y" ] || [ "$answer" == "y" ]
    then
        read -p "For Chinese users,you may wish to install Chinese input,do you want to install it? (Y/y/N/n) " answer
        if [ "$answer" == "Y" ] || [ "$answer" == "y" ]
        then
            echo "Installing software..."
            yay -S fcitx5 	fcitx5-configtool fcitx5-gtk fcitx5-qt
            yay -S fcitx5-chewing fcitx5-chinese-addons fcitx5-rime fcitx5-mcbopomofo-git  fcitx5-anthy  fcitx5-kkc fcitx5-mozc fcitx5-skk
            yay -S  fcitx5-input-support fcitx5-pinyin-zhwiki fcitx5-pinyin-sougou
            yay -S  fcitx5-pinyin-moegirl-rime cedict fcitx5-pinyin-moegirl libime
            yay -S fcitx5-skin-zhuobihaotian-luotianyi
            yay -S kimpanel
            # Add commands to install software here
        elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
        then
            echo "Skipping installation..."
        else
            echo "Invalid input. Skipping installation..."
        fi
        
        read -p "For gnome,it will download the theme pack and so on...You can customize it use the following tools.Do you want to install the software? (Y/y/SS) " answer
        if [ "$answer" == "Y" ] || [ "$answer" == "y" ]
        then
            echo "Installing software..."
            yay -S albert plank-git conky
            #tools
            yay -S ghostlexly-gpu-video-wallpaper gdm-settings gnome-tweaks-git gnome-session-properties
            # theme pack
            yay -S xcursor-genshin-nahida apricity-icons mojave-gtk-theme-git
            #extension
            yay -S gnome-shell-extension-clipboard-indicator compiz gnome-shell-extension-dynamic-panel-transparency-git gnome-shell-extension-simple-system-monitor
            #fonts
            yay -S 	ttf-mac-fonts
            if [ -f ~/.conkyrc ]; then
                mv ~/.conkyrc ~/.conkyrc.backup
            fi
              echo "conky.config = {
                alignment = 'top_right',
                background = false,
                border_width = 1,
                cpu_avg_samples = 2,
                default_color = 'white',
                default_outline_color = 'white',
                default_shade_color = 'white',
                double_buffer = true,
                draw_borders = false,
                draw_graph_borders = true,
                draw_outline = false,
                draw_shades = false,
                extra_newline = false,
                font = 'Noto Sans Mono:size=12',
                gap_x = 20,
                gap_y = 20,
                minimum_height = 5,
                minimum_width = 5,
                net_avg_samples = 2,
                no_buffers = true,
                out_to_console = false,
                out_to_ncurses = false,
                out_to_stderr = false,
                out_to_x = true,
                own_window = true,
                own_window_argb_value = 0,
                own_window_argb_visual = true,
                own_window_class = 'Conky',
                own_window_hints = 'undecorated,sticky,below,skip_taskbar,skip_pager',
                own_window_transparent = true,
                own_window_type = 'desktop',
                show_graph_range = false,
                show_graph_scale = false,
                stippled_borders = 0,
                update_interval = 2.0,
                uppercase = false,
                use_spacer = 'none',
                use_xft = true,
            }
            conky.text = [[${voffset 4}${color}${font :bold}HP EliteBook 840 G3${font}${image /home/username/.config/conky/archlogo.png -n -p 280x0 -s 98x30}
            $hr
            ${color grey}Hostname: ${color}$nodename
            ${color grey}OS      : ${color}$sysname $kernel $machine
            ${color grey}Uptime  : ${color}$uptime
            ${color grey}Battery : ${color}$battery ${voffset 3}${battery_bar}${voffset -3}
            ${voffset 8}${color}${font :size=14}CPU ${font} (Intel Core i7-6500U)$hr
            ${voffset 4}${color grey}Core 0: ${color}${alignr}${freq_g 1} GHz  ${color grey}Temperature: ${color}${execi 30 sensors | grep "Core 0" | awk '{print $3}'}
            ${color grey}Core 1: ${color}${alignr}${freq_g 2} GHz  ${color grey}Temperature: ${color}${execi 30 sensors | grep "Core 1" | awk '{print $3}'}
            ${voffset 4}${color grey}Thread 1: ${color}${voffset 3}${cpubar cpu1}${voffset -3}
            ${color grey}Thread 2: ${color}${voffset 3}${cpubar cpu2}${voffset -3}
            ${color grey}Thread 3: ${color}${voffset 3}${cpubar cpu3}${voffset -3}
            ${color grey}Thread 4: ${color}${voffset 3}${cpubar cpu4}${voffset -3}
            ${voffset 4}${color grey}Process              CPU%   MEM%
            ${color}  ${top name 1} ${top cpu 1} ${top mem 1}
            ${color}  ${top name 2} ${top cpu 2} ${top mem 2}
            ${color}  ${top name 3} ${top cpu 3} ${top mem 3}
            ${voffset 6}${color}${font :size=14}RAM ${font}$hr
            ${voffset 4}${color grey}Memory usage: ${color}${memperc}% of ${memmax} ${voffset 3}${membar}${voffset -3}
            ${voffset 4}${color grey}Process              MEM%   CPU%
            ${color}  ${top_mem name 1} ${top_mem mem 1} ${top_mem cpu 1}
            ${color}  ${top_mem name 2} ${top_mem mem 2} ${top_mem cpu 2}
            ${color}  ${top_mem name 3} ${top_mem mem 3} ${top_mem cpu 3}
            ${voffset 6}${color}${font :size=14}DISK ${font}$hr
            ${voffset 4}${color grey}Local root: $color${fs_free /} ${goto 215}${color grey}/ ${color} ${fs_size /}${goto 335}${voffset 3}${fs_bar /}${voffset -3}
            ${color grey}Gentoo    : ${color}${fs_free /mnt/Gentoo} ${goto 215}${color grey}/ ${color}${fs_size /mnt/Gentoo}${goto 335}${voffset 3}${fs_bar /mnt/Gentoo}${voffset -3}
            ${color grey}Google    : ${color}${fs_free /home/username/Cloud/GoogleDrive} ${goto 215}${color grey}/ ${color}${fs_size /home/username/Cloud/GoogleDrive}${goto 335}${voffset 3}${fs_bar /home/username/Cloud/GoogleDrive}${voffset -3}
            ${color grey}OneDrive  : $color${fs_free /home/username/Cloud/OneDrive-Private} ${goto 215}${color grey}/ ${color}${fs_size /home/username/Cloud/OneDrive-Private}${goto 335}${voffset 3}${fs_bar /home/username/Cloud/OneDrive-Private}${voffset -3}
            ${color grey}Dropbox   : $color${fs_free /home/username/Cloud/Dropbox} ${goto 215}${color grey}/ ${color}${fs_size /home/username/Cloud/Dropbox}${goto 335}${voffset 3}${fs_bar /home/username/Cloud/Dropbox}${voffset -3}
            ${color grey}Mega      : $color${fs_free /home/username/Cloud/Mega} ${goto 215}${color grey}/ ${color}${fs_size /home/username/Cloud/Mega}${goto 335}${voffset 3}${fs_bar /home/username/Cloud/Mega}${voffset -3}
            ${color grey}Pelle     : $color${fs_free /mnt/Pelle/Felles} ${goto 215}${color grey}/ ${color}${fs_size /mnt/Pelle/Felles}${goto 335}${voffset 3}${fs_bar /mnt/Pelle/Felles}${voffset -3}
            ${voffset 4}${color grey}      Read: ${color}${diskio_read /dev/sda} ${goto 230}${color grey}Write: ${color}${diskio_read /dev/sda}
            ${voffset 6}${color}${font :size=14}NETWORK ${font}$hr
            ${if_existing /proc/net/route wlp2s0}\
            ${if_existing /proc/net/route enp0s31f6}\
            ${voffset 4}${color grey}Warning: ${color}Both Wi-Fi and wired network active!
            ${else}\
            ${voffset 4}${color grey}ESSID: ${color}${wireless_essid wlp2s0}${goto 240}${color grey}Quality: ${color}${wireless_link_qual_perc wlp2s0}%
            ${voffset 4}${color grey}  IP : ${color}${addr wlp2s0}${goto 240}${voffset 8}${color grey}Down:${goto 300}${color}${downspeed wlp2s0}
            ${voffset -8}${color grey}  Zt : ${color}${addr zerotierdevice}${goto 240}${voffset 8}${color grey}Up  :${goto 300}${color}${upspeed wlp2s0}
            ${voffset -8}${color grey}  GW : ${color}${gw_ip}
            ${color grey}  Pub: ${color}${texeci 30 ~/.config/conky/pubIP.sh}
            ${endif}\
            ${else}\
            ${if_existing /proc/net/route enp0s31f6}\
            ${voffset 4}${color grey}Wired network: ${color}Active
            ${voffset 4}${color grey}  IP : ${color}${addr enp0s31f6}${goto 240}${voffset 8}${color grey}Down:${goto 300}${color}${downspeed enp0s31f6}
            ${voffset -8}${color grey}  Zt : ${color}${addr zerotierdevice}${goto 240}${voffset 8}${color grey}Up  :${goto 300}${color}${upspeed enp0s31f6}
            ${voffset -8}${color grey}  GW : ${color}${gw_ip}
            ${color grey}  Pub: ${color}${texeci 30 ~/.config/conky/pubIP.sh}
            ${endif}\
            ${endif}\
            ${voffset 6}${color}${font :size=14}UPDATES ${font}$hr
            ${voffset 4}${color grey}      Arch: ${color}${execi 600 checkupdates | wc -l}${goto 230}${color grey}AUR: ${color}${execi 600 auracle outdated | wc -l}
            ]]" > ~/.conkyrc
        elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
        then
            echo "Skipping installation..."
        else
            echo "Invalid input. Skipping installation..."
        fi
        read -p "For gnome office,Do you want to install the software? (Y/y/N/n) " answer
        if [ "$answer" == "Y" ] || [ "$answer" == "y" ]
        then
            echo "Installing software..."
            # Add commands to install software here
        elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
        then
            echo "Skipping installation..."
            yay -S gnome-shell-extension-gsconnect google-chrome libreoffice-fresh vim neovim visual-studio-code-bin
        else
            echo "Invalid input. Skipping installation..."
        fi
    elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
    then
        echo "Skipping installation..."
    else
        echo "Invalid input. Skipping installation..."
    fi

    yay -Yc
else
    # Print an error message if the operating system is not Arch Linux
    echo "Unsupported operating system. This script only supports Arch Linux."
fi