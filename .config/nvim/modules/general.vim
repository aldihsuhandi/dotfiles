" $HOME/.config/nvim/init.vim

" general
syntax on
set tabstop=4 
set softtabstop=4
set shiftwidth=4
set expandtab
set smarttab
set smartindent
set autoindent
" set number
set relativenumber number
set ruler
set clipboard=unnamedplus
set cursorline
set mouse=a
set laststatus=2
set splitbelow splitright

" code folding
let g:anyfold_fold_comments=1
set foldlevel=0
hi Folded term=NONE cterm=NONE

" statusline
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'
let g:airline_section_b = ''
let g:airline_section_y = ''
let g:airline_section_z = ''

filetype plugin on

" Syntax Highlighting
au BufReadPost *.rasi set syntax=css

" Color Scheme
let g:gruvbox_italic = 1
colorscheme onedark
set background=dark
hi Comment cterm=italic
let g:onedark_termcolors = 1
set termguicolors

" User terminal background
hi Normal guibg=NONE ctermbg=NONE

" Auto insert mode and turn off line number in terminal mode
if has('nvim')
    autocmd TermOpen term://* startinsert
    autocmd TermOpen * setlocal nonumber norelativenumber
endif

" indentation guides
let g:indent_guides_enable_on_vim_startup=1
let g:indent_guides_start_level=2
let g:indent_guides_guide_size=1
let g:indent_guides_auto_colors=0

autocmd VimEnter,Colorscheme * :hi IndentGuidesOdd  ctermbg=black
autocmd VimEnter,Colorscheme * :hi IndentGuidesEven ctermbg=black
