set nocompatible
filetype off
set rtp+=~/.vim/plugManager/Vundle.vim
call vundle#begin('~/.vim/plug')
" Plugin manager
Plugin 'VundleVim/Vundle.vim'

" function plugin
Plugin 'm4xshen/autoclose.nvim'
Plugin 'neovim/nvim-lspconfig'

" file management
Plugin 'nvim-tree/nvim-tree.lua'
Plugin 'ibhagwan/fzf-lua'

" Java plugin
Plugin 'nvim-java/lua-async-await'
Plugin 'williamboman/mason.nvim'
Plugin 'nvim-java/nvim-java-refactor'
Plugin 'nvim-java/nvim-java-core'
Plugin 'nvim-java/nvim-java-test'
Plugin 'nvim-java/nvim-java-dap'
Plugin 'nvim-java/nvim-java'
Plugin 'JavaHello/spring-boot.nvim'

" Golang plugin
Plugin 'fatih/vim-go'
Plugin 'charlespascoe/vim-go-syntax'

"
Plugin 'nvim-telescope/telescope.nvim'

" Git plugin
Plugin 'nvim-lua/plenary.nvim'
Plugin 'NeogitOrg/neogit'

Plugin 'mfussenegger/nvim-dap'
Plugin 'MunifTanjim/nui.nvim'

" Tabbing
Plugin 'lewis6991/gitsigns.nvim'
Plugin 'romgrk/barbar.nvim'


" Autocomplete
Plugin 'neoclide/coc.nvim', {'branch': 'release'}
Plugin 'nvim-treesitter/nvim-treesitter'

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

" icons
Plugin 'nvim-tree/nvim-web-devicons'

" syntax highlighting
Plugin 'rrethy/vim-hexokinase', { 'do': 'make hexokinase' }
Plugin 'hail2u/vim-css3-syntax'
Plugin 'pangloss/vim-javascript'
Plugin 'HerringtonDarkholme/yats.vim', { 'for': 'typescript' }
Plugin 'ianks/vim-tsx', { 'for': 'typescript.tsx' }
Plugin 'posva/vim-vue'
Plugin 'airblade/vim-gitgutter'
Plugin 'mxw/vim-jsx'

" Flutter
Plugin 'stevearc/dressing.nvim'
Plugin 'nvim-flutter/flutter-tools.nvim'

" markdown
Plugin 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}

" plantuml
Plugin 'tyru/open-browser.vim'
Plugin 'aklt/plantuml-syntax'
Plugin 'weirongxu/plantuml-previewer.vim'

" Terminal
Plugin 'voldikss/vim-floaterm'
 
call vundle#end()
filetype plugin indent on
