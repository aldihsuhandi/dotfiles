" $HOME/.config/nvim/init.vim

set nocompatible
filetype off

set rtp+=~/.vim/plugManager/Vundle.vim
call vundle#begin('~/.vim/plug')
" Plugin manager
Plugin 'VundleVim/Vundle.vim'

" HTML plugin
Plugin 'mattn/emmet-vim'

" Laravel plugin
Plugin 'tpope/vim-dispatch'             "| Optional
Plugin 'tpope/vim-projectionist'        "|
Plugin 'noahfrederick/vim-composer'     "|
Plugin 'noahfrederick/vim-laravel'

" Search plugin
Plugin 'junegunn/fzf', { 'do': { -> fzf#install() } }
Plugin 'junegunn/fzf.vim'

" Aestetic Plugin
Plugin 'mhinz/vim-startify'
" Plugin 'luochen1990/rainbow'
Plugin 'Yggdroot/indentLine'
Plugin 'lukas-reineke/indent-blankline.nvim'

" Github Plugin
Plugin 'airblade/vim-gitgutter'
Plugin 'f-person/git-blame.nvim'

" Functional plugin
Plugin 'xiyaowong/nvim-cursorword'
Plugin 'yamatsum/nvim-cursorline'
Plugin 'godlygeek/tabular'
Plugin 'preservim/nerdcommenter'
Plugin 'preservim/nerdtree'
Plugin 'ap/vim-css-color'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'junegunn/goyo.vim'
Plugin 'sheerun/vim-polyglot'
" Plugin 'sbdchd/neoformat'
Plugin 'mhartington/formatter.nvim'
Plugin 'beanworks/vim-phpfmt'
Plugin 'nvim-treesitter/nvim-treesitter'

" Autocomplete plugin
Plugin 'neoclide/coc.nvim'
Plugin 'neoclide/coc-python'
Plugin 'yaegassy/coc-intelephense', {'do': 'yarn install --frozen-lockfile'}
Plugin 'arnaud-lb/vim-php-namespace'
Plugin 'alvan/vim-closetag'
Plugin 'nono/jquery.vim'

" Syntax Highlight
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'vim-python/python-syntax'
Plugin 'plasticboy/vim-markdown'
Plugin 'uiiaoo/java-syntax.vim'
Plugin 'dart-lang/dart-vim-plugin'
Plugin 'natebosch/vim-lsc'
Plugin 'natebosch/vim-lsc-dart'
Plugin 'jwalton512/vim-blade'

" Color Scheme
Plugin 'dracula/vim', { 'name': 'dracula' }
Plugin 'fatih/molokai'
Plugin 'joshdick/onedark.vim'
Plugin 'gosukiwi/vim-atom-dark'
Plugin 'morhetz/gruvbox'
Plugin 'sickill/vim-monokai'
Plugin 'reedes/vim-colors-pencil'
Plugin 'liuchengxu/space-vim-dark'
Plugin 'fmoralesc/molokayo'
Plugin 'NLKNguyen/papercolor-theme'
Plugin 'arcticicestudio/nord-vim'
Plugin 'drewtempelmeyer/palenight.vim'

call vundle#end()
filetype plugin indent on
