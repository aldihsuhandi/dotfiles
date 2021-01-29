set nocompatible
filetype off

set rtp+=~/.vim/plugManager/Vundle.vim
call vundle#begin('~/.vim/plug')
" Plugin manager
Plugin 'VundleVim/Vundle.vim'

" Functional plugin
Plugin 'godlygeek/tabular'
Plugin 'airblade/vim-gitgutter'
Plugin 'preservim/nerdcommenter'
Plugin 'preservim/nerdtree'
Plugin 'ap/vim-css-color'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'junegunn/goyo.vim'

" Syntax Highlight
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'vim-python/python-syntax'
Plugin 'plasticboy/vim-markdown'
Plugin 'uiiaoo/java-syntax.vim'

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
Plugin 'netsgnut/arctheme.vim'
Plugin 'NLKNguyen/papercolor-theme'

call vundle#end()   
filetype plugin indent on

" general
syntax on
set tabstop=4 
set softtabstop=4
set shiftwidth=4
set expandtab
set smarttab
set smartindent
set autoindent
set relativenumber number
set ruler
set clipboard=unnamedplus
set cursorline
set mouse=a
set laststatus=2
set splitbelow splitright

" cursor
let &t_SI = "\e[4 q"
let &t_EI = "\e[2 q"

" statusline
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'
let g:airline_section_b = ''
let g:airline_section_y = ''
let g:airline_section_z = ''
" let g:airline_theme = 'atomic'
" let g:airline_section_b = '%{strftime("%c")}'
" let g:airline_section_y = 'BN: %{bufnr("%")}'

filetype plugin on

" Color Scheme
let g:gruvbox_italic = 1
colorscheme dracula
set background=dark
hi Comment cterm=italic
let g:onedark_termcolors = 1
set termguicolors

" NERDTREE
let g:NERDSpaceDelims = 1
let g:NERDCompactSexyComs = 1
let g:NERDDefaultAlign = 'left'
let g:NERDAltDelims_java = 1
let g:NERDCommendEmptyLines = 1
let g:NERDTrimTrailingWhiteSpace = 1
let g:NERDToggleCheckAllLines = 1
let g:NERDTreeDirArrowExpandable = '▸'
let g:NERDTreeDirArrowCollapsible = '▾'

" Markdown
let g:vim_markdown_folding_disabled = 1

" Python
let g:python_highlight_all = 1
let g:python_highlight_indent_errors = 1
let g:python_highlight_space_errorss = 1

" shortcut
map <F1> :NERDTreeToggle<CR>
map <F3> :w<CR>
map <F4> :q<CR>
map <F5> :w! <bar> !clear && ~/Documents/vim\ script/./compile.sh %<CR>
map <F8> :w! <bar> !clear && echo "Insert to IN" && cat > in<CR>
map <F9> :w! <bar> !clear && ~/Documents/vim\ script/./run.sh %<CR>
map <F10> :w! <bar> !clear && ~/Documents/vim\ script/./compile.sh % && ./%:r < in<CR>
nnoremap <F11> :wall! <bar>  !clear && javac Main.java && java Main<CR>
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
nnoremap <C-c> :%y+<CR>
nnoremap <C-w> :wall<CR>
nnoremap <C-R> :so .vimrc<CR>
nnoremap <C-Down> :tabNext<CR>
nnoremap <C-Up> :tabprevious<CR>
noremap <silent> <A-Left> :vertical resize +3<CR>
noremap <silent> <A-Right> :vertical resize -3<CR>
noremap <silent> <A-Up> :resize +3<CR>
noremap <silent> <A-Down> :resize -3<CR>
vmap  <plug>NERDCommenterToggle
nmap  <plug>NERDCommenterToggle

" Automatically closing braces
inoremap {<CR> {<CR>}<Esc>ko

" Alacritty fix
set ttymouse=sgr
hi Normal guibg=NONE ctermbg=NONE
