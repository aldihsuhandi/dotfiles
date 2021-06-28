set -Ux EDITOR nvim
set -Ux MANPAGER "nvim -c 'set ft=man' -"

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
alias grep='rg'
alias df='df -h'

alias ls="exa -F -s=name --long -S -h --group-directories-first -G"
alias la="ls -a"
alias ld="exa -F -s=name --long -S -h -D -G"
alias sl="ls"
alias l="ls"
alias s="ls"

alias pac="$HOME/Documents/script/pac/./pac"

starship init fish | source
