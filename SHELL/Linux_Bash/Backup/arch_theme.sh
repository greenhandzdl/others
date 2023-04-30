#!/bin/bash

# Check if the operating system is Arch Linux
if [[ -f /etc/arch-release ]]; then
    # Check if yay is installed
    if ! command -v yay &> /dev/null; then
        # Prompt the user to install yay
        read -p "Do you want to install yay? [Y/n] " -n 1 -r
        echo
        # Install yay if the user agrees
        if [[ $REPLY =~ ^[Yy]$ ]] || [[ -z $REPLY ]]; then
            sudo pacman -Syu --needed git base-devel
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
            yay -S albert plank-git
            #tools
            yay -S ghostlexly-gpu-video-wallpaper gdm-settings gnome-tweaks-git
            # theme pack
            yay -S xcursor-genshin-nahida apricity-icons mojave-gtk-theme-git
            #extension
            yay -S gnome-shell-extension-clipboard-indicator compiz gnome-shell-extension-dynamic-panel-transparency-git gnome-shell-extension-simple-system-monitor
            # Add commands to install software here
        elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
        then
            echo "Skipping installation..."
        else
            echo "Invalid input. Skipping installation..."
        fi

    elif [ "$answer" == "N" ] || [ "$answer" == "n" ]
    then
        echo "Skipping installation..."
    else
        echo "Invalid input. Skipping installation..."
    fi
else
    # Print an error message if the operating system is not Arch Linux
    echo "Unsupported operating system. This script only supports Arch Linux."
fi