" general
syntax on
set tabstop=4
set softtabstop=4
set shiftwidth=4
set expandtab
set smarttab
set smartindent
set autoindent
set number
" set relativenumber number
set ruler
set clipboard=unnamedplus
set cursorline
set mouse=a
set laststatus=2
set splitbelow splitright

" Color Scheme
let g:gruvbox_italic = 1
set background=dark
colorscheme onedark
hi Comment cterm=italic
let g:onedark_termcolors = 1
set termguicolors

" User terminal background
hi Normal guibg=NONE ctermbg=NONE

augroup filetype_tab
    autocmd!
    autocmd FileType dart setlocal tabstop=2 softtabstop=2 shiftwidth=2 expandtab
augroup END
