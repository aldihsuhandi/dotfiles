#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

# general alias
alias rm='rm -i'
alias mv='mv -i'
alias cp='cp -i'
alias mkdir='mkdir -p'
alias free='free -h -m'
alias kernel='uname -r'
alias cl='clear'
alias claer='clear'
alias vim='nvim'
alias v='vim'
alias sv='sudo vim'
alias svim='sudoedit'
alias htop='bashtop'
alias grep='rg'
alias df='df -h'

# EXPORT
export MANPAGER="nvim -c 'set ft=man' -"
export EDITOR="nvim"

# extraction command
extract ()
{
  if [ -f $1 ] ; then
    case $1 in
      *.tar.bz2)   tar xjf $1   ;;
      *.tar.gz)    tar xzf $1   ;;
      *.bz2)       bunzip2 $1   ;;
      *.rar)       unrar x $1   ;;
      *.gz)        gunzip $1    ;;
      *.tar)       tar xf $1    ;;
      *.tbz2)      tar xjf $1   ;;
      *.tgz)       tar xzf $1   ;;
      *.zip)       unzip $1     ;;
      *.Z)         uncompress $1;;
      *.7z)        7z x $1      ;;
      *.deb)       ar x $1      ;;
      *.tar.xz)    tar xf $1    ;;
      *.tar.zst)   unzstd $1    ;;      
      *)           echo "'$1' cannot be extracted via extract" ;;
    esac
  else
    echo "'$1' is not a valid file"
  fi
}

# autocd
shopt -s autocd

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


# prelaunched command
eval "$(starship init bash)"
source ~/.personal_alias
