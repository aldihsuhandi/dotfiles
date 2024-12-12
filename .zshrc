export ZSH="/home/$USER/.oh-my-zsh"
export ANDROID_SDK_ROOT='/opt/android-sdk'
ZSH_THEME="robbyrussell"
plugins=(git zsh-autosuggestions zsh-syntax-highlighting ssh-agent)
source $ZSH/oh-my-zsh.sh

# EXPORT
# export MANPAGER="nvim -c 'set ft=man' -"
export EDITOR="nvim"

# general alias
alias please="sudo"
alias rm='rm -i'
alias mkdir='mkdir -p'
alias free='free -h -m'
alias kernel='uname -r'
alias cl='clear'
alias claer='clear'
alias vim='nvim'
alias v='vim'
alias sv='sudoedit'
alias svim='sudoedit'
alias df='df -h'

# extraction command
extract ()
{
for param in "$@"; do
  if [ -f $param ] ; then
    echo "start extracting '$param'"
    case $param in
      *.tar.bz2)   tar xjf $param   ;;
      *.tar.gz)    tar xzf $param   ;;
      *.bz2)       bunzip2 $param   ;;
      *.rar)       unrar x $param   ;;
      *.gz)        gunzip $param    ;;
      *.tar)       tar xf $param    ;;
      *.tbz2)      tar xjf $param   ;;
      *.tgz)       tar xzf $param   ;;
      *.zip)       unzip $param     ;;
      *.Z)         uncompress $param;;
      *.7z)        7z x $param      ;;
      *.deb)       ar x $param      ;;
      *.tar.xz)    tar xf $param    ;;
      *.tar.zst)   unzstd $param    ;;      
      *)           echo "'$param' cannot be extracted via ex()" ;;
    esac
  else
    echo "'$param' is not a valid file"
  fi
done
}


# autocd
setopt  autocd autopushd
autoload -U compinit
compinit

# alias for ls typo and somefunction
alias ls="exa -F -s=name --long -S -h --group-directories-first -G"
alias la="ls -a"
alias ld="exa -F -s=name --long -S -h -D -G"
alias sl="ls"
alias l="ls"
alias s="ls"

# alias for package manager
alias pac="$HOME/Documents/script/pac/./pac"

# curl?
alias weather='curl wttr.in'
alias rr='curl -s -L https://raw.githubusercontent.com/keroserene/rickrollrc/master/roll.sh | bash'

# prelaunch command
if [ -f $HOME/Documents/zsh/personal_alias ]; then
    source $HOME/Documents/zsh/personal_alias
fi
clear
eval "$(starship init zsh)"
